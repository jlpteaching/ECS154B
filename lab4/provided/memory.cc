
#include <cstring>
#include <iostream>

#include "cache.hh"
#include "memory.hh"
#include "util.hh"

Memory::Memory(int line_size) :
    memorySize(1<<26), // 64 MB
    lineSize(line_size),
    cacheWritebacks(0), cacheMisses(0)
{
}

Memory::~Memory()
{
    std::cout << "Writebacks: " << cacheWritebacks << std::endl;
    std::cout << "Misses:     " << cacheMisses << std::endl;
    for (auto it : dataStorage) {
        assert(it.second);
        delete[] it.second;
    }
}

void
Memory::receiveRequest(uint64_t address, int size, const uint8_t* data,
                       int request_id)
{
    if (data) {
        // writing back data, so this is a writeback.
        cacheWritebacks++;
    } else {
        // Reading data, must be a cache miss.
        cacheMisses++;
    }
    // Immediately deal with the request.
    assert(size == lineSize);

    // get pointer from map.
    auto it = dataStorage.find(address);
    if (it == dataStorage.end()) {
        dataStorage[address] = new uint8_t[lineSize];
    }

    uint8_t* mem_data = dataStorage[address];

    if (data) {
        // If writing, write the data
        memcpy(mem_data, data, lineSize);
    } else {
        // If reading schedule a request for later.
        // Wait for a "random" amount of time to reply
        schedule(10+curTick() % 10,
                [this, request_id, mem_data]{
                    cache->receiveMemResponse(request_id, mem_data);
                });
    }
}

int
Memory::getLineSize()
{
    return lineSize;
}

int
Memory::getLineBits()
{
    return log2int(lineSize);
}
