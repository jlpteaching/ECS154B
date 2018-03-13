
#include <cassert>
#include <cstring>

#include "non_blocking.hh"
#include "memory.hh"
#include "processor.hh"
#include "util.hh"

NonBlockingCache::NonBlockingCache(int64_t size, Memory& memory,
                                   Processor& processor, int ways, int _mshrs)
    : SetAssociativeCache(size, memory, processor, ways),
    maxMSHRs(_mshrs),
    mshrsActive(0),
    nextId(0)
{
    assert(maxMSHRs > 0);
}

NonBlockingCache::~NonBlockingCache()
{

}

bool
NonBlockingCache::receiveRequest(uint64_t address, int size,
                                const uint8_t* data, int request_id)
{
    assert(size <= memory.getLineSize()); // within line size
    // within address range
    assert(address < ((uint64_t)1 << processor.getAddrSize()));
    assert((address &  (size - 1)) == 0); // naturally aligned

    if (blocked) {
        DPRINT("Cache is blocked!");
        // Cache is currently blocked, so it cannot receive a new request
        return false;
    }

    (++nextVictim) %= ways;

    int index = getIndex(address);

    int way = hit(address);
    if (way != -1) {
        DPRINT("Hit in cache");
        // get a pointer to the data
        uint8_t* line = dataArrays[way].getLine(index);

        int block_offset = getBlockOffset(address);

        if (data) {
            // if this is a write, copy the data into the cache.
            memcpy(&line[block_offset], data, size);
            sendResponse(request_id, nullptr);
            // Mark dirty
            tagArrays[way].setState(index, Dirty);
        } else {
            // This is a read so we need to return data
            sendResponse(request_id, &line[block_offset]);
        }
    } else {
        if (busy(address)) {
            return false; // Stall if the address is busy.
        }
        int victim_way = evictionPolicy(address);
        uint64_t wb_address = tagArrays[victim_way].getTag(index) <<
                                    (processor.getAddrSize() - tagBits);
        wb_address |= (index << memory.getLineBits());
        DPRINT("Miss in cache. Victim way " << victim_way <<
               " State " << tagArrays[victim_way].getState(index) <<
               " Addr " << wb_address);
        if (busy(wb_address)) {
            return false; // stall
        }
        if (dirty(address, victim_way)) {
            DPRINT("Dirty, writing back");
            // If the line is dirty, then we need to evict it.
            uint8_t* line = dataArrays[victim_way].getLine(index);
            // Calculate the address of the writeback.
            // No response for writes, no need for valid request_id
            sendMemRequest(wb_address, memory.getLineSize(), line, -1);
        }
        uint64_t block_address = address & ~(memory.getLineSize() -1);
        // Mark the line busy.
        tagArrays[victim_way].setState(index, Busy);
        tagArrays[victim_way].setTag(index, getTag(block_address));
        // Forward to memory and block the cache.
        // no need for req id since there is only one outstanding request.
        // We need to read whether the request is a read or write.
        sendMemRequest(block_address, memory.getLineSize(), nullptr, ++nextId);

        MSHR& mshr = mshrs[nextId];

        // remember the CPU's request id
        mshr.savedId = request_id;
        // Remember the address
        mshr.savedAddr = address;
        // Remember the data if it is a write.
        mshr.savedSize = size;
        mshr.savedData = data;
        mshr.savedWay = victim_way;

        if (mshrs.size() == maxMSHRs) {
            blocked = true;
        }
    }

    // We have accepted the request, so return true.
    return true;
}

void
NonBlockingCache::receiveMemResponse(int request_id, const uint8_t* data)
{
    assert(data);

    MSHR& mshr = mshrs[request_id];

    DPRINT("Response for addr 0x" << std::hex << mshr.savedAddr);

    int index = getIndex(mshr.savedAddr);
    int way = mshr.savedWay;

    // Copy the data into the cache.
    uint8_t* line = dataArrays[way].getLine(index);
    memcpy(line, data, memory.getLineSize());

    assert(tagArrays[way].getState(index) == Busy);

    // Mark valid
    tagArrays[way].setState(index, Valid);

    assert(hit(mshr.savedAddr) >= 0);

    // Treat as a hit
    int block_offset = getBlockOffset(mshr.savedAddr);

    if (mshr.savedData) {
        // if this is a write, copy the data into the cache.
        memcpy(&line[block_offset], mshr.savedData, mshr.savedSize);
        sendResponse(mshr.savedId, nullptr);
        // Mark dirty
        tagArrays[way].setState(index, Dirty);
    } else {
        // This is a read so we need to return data
        sendResponse(mshr.savedId, &line[block_offset]);
    }

    blocked = false;
    mshrs.erase(request_id);
}


bool
NonBlockingCache::busy(uint64_t address)
{
    int index = getIndex(address);
    for (auto& tagArray : tagArrays) {
        State state = (State)tagArray.getState(index);
        uint64_t line_tag = tagArray.getTag(index);
        // dirty implies valid
        if (line_tag == getTag(address) && state == Busy) {
            return true;
        }
    }
    return false;
}

int
NonBlockingCache::hit(uint64_t address)
{
    int index = getIndex(address);
    int way = 0;
    for (auto& tagArray : tagArrays) {
        State state = (State)tagArray.getState(index);
        uint64_t line_tag = tagArray.getTag(index);
        // dirty implies valid
        if ((state == Valid || state == Dirty) && line_tag == getTag(address)) {
            return way;
        }
        way++;
    }
    return -1; // miss
}

bool
NonBlockingCache::dirty(uint64_t address, int way)
{
    int index = getIndex(address);
    State state = (State)tagArrays[way].getState(index);
    return state == Dirty;
}
