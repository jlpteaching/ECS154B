
#include <cassert>

#include "cache.hh"
#include "memory.hh"
#include "processor.hh"

Cache::Cache(int64_t size, Memory& memory, Processor& processor) :
    size(size), memory(memory), processor(processor)
{
    memory.setCache(this);
    processor.setCache(this);
}

void
Cache::sendResponse(int request_id, const uint8_t* data)
{
    processor.receiveResponse(request_id, data);
}

void
Cache::sendMemRequest(uint64_t address, int size, const uint8_t* data,
                      int request_id)
{
    memory.receiveRequest(address, size, data, request_id);
}
