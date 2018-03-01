
#include <cassert>

#include "set_assoc.hh"
#include "util.hh"

SetAssociativeCache::SetAssociativeCache(int64_t size, Memory& memory,
                                         Processor& processor, int ways)
    : Cache(size, memory, processor)
{
    assert(ways > 0);
}

SetAssociativeCache::~SetAssociativeCache()
{

}

bool
SetAssociativeCache::receiveRequest(uint64_t address, int size,
                                    const uint8_t* data, int request_id)
{
    return false;
}

void
SetAssociativeCache::receiveMemResponse(int request_id, const uint8_t* data)
{

}
