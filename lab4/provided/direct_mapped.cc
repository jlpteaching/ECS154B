
#include <cstring>

#include "direct_mapped.hh"
#include "memory.hh"
#include "processor.hh"
#include "util.hh"

DirectMappedCache::DirectMappedCache(int64_t size, Memory& memory,
                                     Processor& processor) :
    Cache(size, memory, processor),
    tagBits(processor.getAddrSize() - log2int(size / memory.getLineSize()) -
            memory.getLineBits()),
    indexMask(size / memory.getLineSize() - 1),
    tagArray(size / memory.getLineSize(), // Lines
         2, // 1 bit for valid, 1 bit for dirty.
         tagBits), // Bits for the tag
    dataArray(size / memory.getLineSize(), memory.getLineSize()),
    blocked(false), mshr({-1,0,0,nullptr})
{

}

int64_t
DirectMappedCache::getIndex(uint64_t address)
{
    return (address >> memory.getLineBits()) & indexMask;
}

int
DirectMappedCache::getBlockOffset(uint64_t address)
{
    return address & (memory.getLineSize() - 1);
}

uint64_t
DirectMappedCache::getTag(uint64_t address)
{
    return address >> (processor.getAddrSize() - tagBits);
}

bool
DirectMappedCache::receiveRequest(uint64_t address, int size,
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

    int index = getIndex(address);

    if (hit(address)) {
        DPRINT("Hit in cache");
        // get a pointer to the data
        uint8_t* line = dataArray.getLine(index);

        int block_offset = getBlockOffset(address);

        if (data) {
            // if this is a write, copy the data into the cache.
            memcpy(&line[block_offset], data, size);
            sendResponse(request_id, nullptr);
            // Mark dirty
            tagArray.setState(index, Dirty);
        } else {
            // This is a read so we need to return data
            sendResponse(request_id, &line[block_offset]);
        }
    } else {
        DPRINT("Miss in cache " << tagArray.getState(index));
        if (dirty(address)) {
            DPRINT("Dirty, writing back");
            // If the line is dirty, then we need to evict it.
            uint8_t* line = dataArray.getLine(index);
            // Calculate the address of the writeback.
            uint64_t wb_address =
                tagArray.getTag(index) << (processor.getAddrSize() - tagBits);
            wb_address |= (index << memory.getLineBits());
            // No response for writes, no need for valid request_id
            sendMemRequest(wb_address, memory.getLineSize(), line, -1);
        }
        // Mark the line invalid.
        tagArray.setState(index, Invalid);
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
        // Mark the cache as blocked
        blocked = true;
    }

    // We have accepted the request, so return true.
    return true;
}

void
DirectMappedCache::receiveMemResponse(int request_id, const uint8_t* data)
{
    assert(request_id == 0);
    assert(data);

    int index = getIndex(mshr.savedAddr);

    // Copy the data into the cache.
    uint8_t* line = dataArray.getLine(index);
    memcpy(line, data, memory.getLineSize());

    assert(tagArray.getState(index) == Invalid);

    // Mark valid
    tagArray.setState(index, Valid);

    // Set tag
    tagArray.setTag(index, getTag(mshr.savedAddr));

    // Treat as a hit
    int block_offset = getBlockOffset(mshr.savedAddr);

    if (mshr.savedData) {
        // if this is a write, copy the data into the cache.
        memcpy(&line[block_offset], mshr.savedData, mshr.savedSize);
        sendResponse(mshr.savedId, nullptr);
        // Mark dirty
        tagArray.setState(index, Dirty);
    } else {
        // This is a read so we need to return data
        sendResponse(mshr.savedId, &line[block_offset]);
    }

    blocked = false;
    mshr.savedId = -1;
    mshr.savedAddr = 0;
    mshr.savedSize = 0;
    mshr.savedData = nullptr;
}

bool
DirectMappedCache::hit(uint64_t address)
{
    int index = getIndex(address);
    State state = (State)tagArray.getState(index);
    uint64_t line_tag = tagArray.getTag(index);
    if ((state == Valid || state == Dirty) && // dirty implies valid
        line_tag == getTag(address)) return true;
    else return false;
}

bool
DirectMappedCache::dirty(uint64_t address)
{
    int index = getIndex(address);
    State state = (State)tagArray.getState(index);
    if (state == Dirty) return true;
    else return false;
}
