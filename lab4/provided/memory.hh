
#ifndef CSIM_MEMORY_H
#define CSIM_MEMORY_H

#include <cstdint>
#include <map>

#include "cache.hh"
#include "ticked_object.hh"

class Memory : public TickedObject
{
  public:
    Memory(int line_size);
    ~Memory();

    /**
     * Called when the cache sends load or store request.
     * All requests can be assummed to be naturally aligned (e.g., a 4 byte
     * request will be aligned to a 4 byte boundary)
     *
     * @param address of the request
     * @param size in bytes of the request (should be line size).
     * @param data is non-null, then this is a store request.
     * @param request_id the id that must be used when replying to this request
     */
    void receiveRequest(uint64_t address, int size, const uint8_t* data,
                        int request_id);

    /**
     * @return the line size in bytes
     */
    int getLineSize();

    /**
     * @return the line size in bytes
     */
    int getLineBits();

    /**
     * Connect the cache
     */
    void setCache(Cache *cache) { this->cache = cache; }

  private:
    Cache *cache;

    int64_t memorySize;
    int lineSize;

    /// Cheat and only allocate the blocks needed
    std::map<uint64_t, uint8_t*> dataStorage;

    int64_t cacheWritebacks;
    int64_t cacheMisses;
};

#endif // CSIM_MEMORY_H
