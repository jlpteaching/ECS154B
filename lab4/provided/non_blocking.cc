
#include <cassert>

#include "non_blocking.hh"
#include "util.hh"

NonBlockingCache::NonBlockingCache(int64_t size, Memory& memory,
                                   Processor& processor, int ways, int mshrs)
    : SetAssociativeCache(size, memory, processor, ways)
{
    assert(mshrs > 0);
}

NonBlockingCache::~NonBlockingCache()
{

}

bool
NonBlockingCache::receiveRequest(uint64_t address, int size,
                                const uint8_t* data, int request_id)
{
    return false;
}

void
NonBlockingCache::receiveMemResponse(int request_id, const uint8_t* data)
{

}
