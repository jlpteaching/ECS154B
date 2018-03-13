
#include <cassert>
#include <cstring>

#include "set_assoc.hh"
#include "memory.hh"
#include "processor.hh"
#include "util.hh"

SetAssociativeCache::SetAssociativeCache(int64_t size, Memory& memory,
                                         Processor& processor, int ways) :
    Cache(size, memory, processor),
    ways(ways),
    lines(size / memory.getLineSize()),
    tagBits(processor.getAddrSize() - log2int(lines) + log2int(ways) -
            memory.getLineBits()),
    indexMask(size / memory.getLineSize() / ways - 1),
    nextVictim(0),
    blocked(false)
{
    assert(ways > 0);
    for (int i=0; i<ways; i++) {
        // Create one tag/data array for each way
        tagArrays.emplace_back(lines / ways, 2, tagBits);
        dataArrays.emplace_back(lines / ways, memory.getLineSize());
    }
}

SetAssociativeCache::~SetAssociativeCache()
{

}

int64_t
SetAssociativeCache::getIndex(uint64_t address)
{
    return (address >> memory.getLineBits()) & indexMask;
}

int
SetAssociativeCache::getBlockOffset(uint64_t address)
{
    return address & (memory.getLineSize() - 1);
}

uint64_t
SetAssociativeCache::getTag(uint64_t address)
{
    return address >> (processor.getAddrSize() - tagBits);
}

bool
SetAssociativeCache::receiveRequest(uint64_t address, int size,
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
        int victim_way = evictionPolicy(address);
        uint64_t wb_address = tagArrays[victim_way].getTag(index) <<
                                    (processor.getAddrSize() - tagBits);
        wb_address |= (index << memory.getLineBits());
        DPRINT("Miss in cache. Victim way " << victim_way <<
               " State " << tagArrays[victim_way].getState(index) <<
               " Addr " << wb_address);
        if (dirty(address, victim_way)) {
            DPRINT("Dirty, writing back");
            // If the line is dirty, then we need to evict it.
            uint8_t* line = dataArrays[victim_way].getLine(index);
            // Calculate the address of the writeback.
            // No response for writes, no need for valid request_id
            sendMemRequest(wb_address, memory.getLineSize(), line, -1);
        }
        // Mark the line invalid.
        tagArrays[victim_way].setState(index, Invalid);
        // Forward to memory and block the cache.
        // no need for req id since there is only one outstanding request.
        // We need to read whether the request is a read or write.
        uint64_t block_address = address & ~(memory.getLineSize() -1);
        sendMemRequest(block_address, memory.getLineSize(), nullptr, 0);

        // remember the CPU's request id
        mshr.savedId = request_id;
        // Remember the address
        mshr.savedAddr = address;
        // Remember the data if it is a write.
        mshr.savedSize = size;
        mshr.savedData = data;
        mshr.savedWay = victim_way;
        // Mark the cache as blocked
        blocked = true;
    }

    // We have accepted the request, so return true.
    return true;
}

void
SetAssociativeCache::receiveMemResponse(int request_id, const uint8_t* data)
{
    assert(request_id == 0);
    assert(data);

    int index = getIndex(mshr.savedAddr);
    int way = mshr.savedWay;

    // Copy the data into the cache.
    uint8_t* line = dataArrays[way].getLine(index);
    memcpy(line, data, memory.getLineSize());

    assert(tagArrays[way].getState(index) == Invalid);

    // Mark valid
    tagArrays[way].setState(index, Valid);

    // Set tag
    tagArrays[way].setTag(index, getTag(mshr.savedAddr));

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
    mshr.savedId = -1;
    mshr.savedAddr = 0;
    mshr.savedSize = 0;
    mshr.savedWay = -1;
    mshr.savedData = nullptr;
}


int
SetAssociativeCache::hit(uint64_t address)
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
SetAssociativeCache::dirty(uint64_t address, int way)
{
    int index = getIndex(address);
    State state = (State)tagArrays[way].getState(index);
    return state == Dirty;
}


int
SetAssociativeCache::evictionPolicy(uint64_t address)
{
    int index = getIndex(address);

    int victim_way = nextVictim;

    int way = 0;
    for (auto& tagArray : tagArrays) {
        State state = (State)tagArray.getState(index);
        if (state == Invalid) {
            DPRINT("Address " << std::hex << address << " has room." << std::endl);
            return way;
        }
        way++;
    }
    DPRINT("Address " << std::hex << address << " NO room." << std::endl);
    return victim_way;
}
