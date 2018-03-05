
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
        assert(it.second.data);
        delete[] it.second.data;
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

    // Only accept lineSize requests that are correctly aligned
    assert(size == lineSize);
    assert((address & (lineSize - 1)) == 0);

    // get pointer from map.
    auto it = dataStorage.find(address);
    if (it == dataStorage.end()) {
        uint8_t *new_data = new uint8_t[lineSize];
        memset(new_data, 1, lineSize);
        dataStorage[address] = {new_data, false};
    }

    uint8_t* mem_data = dataStorage[address].data;

    if (data) {
        // Instead of writing the data, make sure the data is correct.
        bool match = compareData(mem_data, data, lineSize);
        if (!match) {
            std::cout << "Address " << std::hex << address << std::endl;
            std::cout << "ERROR! Writeback contains wrong data." << std::endl;
            assert(0); // Assert for easier gdb
        }
        // Now that it's written back, it's no longer dirty in the cache
        dataStorage[address].dirty = false;
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

void
Memory::processorWrite(uint64_t address, int size, const uint8_t* data)
{
    uint64_t line_address = address & ~(lineSize - 1);
    auto it = dataStorage.find(line_address);

    // We should always have backing data since processorWrite is called after
    // the request completes.
    assert(it != dataStorage.end());

    int block_offset =  address & (lineSize - 1);

    // Write the data to the backing store.
    memcpy(it->second.data + block_offset, data, size);

    // Mark that the cache contains dirty data
    it->second.dirty = true;
}

void
Memory::checkRead(uint64_t address, int size, const uint8_t* data)
{
    uint64_t line_address = address & ~(lineSize - 1);
    auto it = dataStorage.find(line_address);

    // We should always have backing data since processorWrite is called after
    // the request completes.
    assert(it != dataStorage.end());

    int block_offset = address & (lineSize - 1);

    bool match = compareData(it->second.data + block_offset, data, size);
    if (!match) {
        std::cout << "Address " << std::hex << address << std::endl;
        std::cout << "ERROR! Read contains wrong data." << std::endl;
        assert(0); // Assert for easier gdb
    }
}

bool
Memory::compareData(const uint8_t *correct, const uint8_t *compare, int num)
{
    bool match = true;
    for (int i = 0; i < num; i++) {
        if (correct[i] != compare[i]) {
            std::cout << "Mismatch on byte " << i;
            std::cout << " is " << std::hex << (uint32_t)compare[i];
            std::cout << " should be " << std::hex << (uint32_t)correct[i];
            std::cout << std::endl;
            match = false;
        }
    }
    return match;
}
