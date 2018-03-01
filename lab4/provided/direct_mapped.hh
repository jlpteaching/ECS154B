
#ifndef CSIM_DIRECT_MAPPED_H
#define CSIM_DIRECT_MAPPED_H

#include <cstdint>

#include "cache.hh"
#include "tag_array.hh"
#include "sram_array.hh"

class DirectMappedCache: public Cache
{
  public:
    /**
    * @param size is the *total* size of the cache in bytes
    * @param the memory that is below this cache
    * @param processor this cache is connected tos
    */
    DirectMappedCache(int64_t size, Memory& memory, Processor& processor);

    /**
     * Called when the processors sends load or store request.
     * All requests can be assummed to be naturally aligned (e.g., a 4 byte
     * request will be aligned to a 4 byte boundary)
     *
     * @param address of the request
     * @param size in bytes of the request.
     * @param data is non-null, then this is a store request.
     * @param request_id the id that must be used when replying to this request
     *
     * @return true if the request can be received, false if the cache is
     *         blocked and the request must be retried later.
     */
    bool receiveRequest(uint64_t address, int size, const uint8_t* data,
                        int request_id) override;

    /**
     * Called when memory id finished processing a request.
     * Data will always be the length of memory.getLineSize()
     *
     * @param request_id is the id assigned to this request in sendMemRequest
     * @param data is the data from memory (length of data is line length)
     *        NOTE: This pointer will be invalid when this function returns.
     */
    void receiveMemResponse(int request_id, const uint8_t* data) override;

  private:

    enum State {
        Invalid=0,
        Valid=1,
        Invalid2=2,
        Dirty=3 // Dirty implies valid
    };

    /**
     * @return the index number for the given address
     */
    int64_t getIndex(uint64_t address);

    /**
     * @return the block offset for the given address
     */
    int getBlockOffset(uint64_t address);

    /**
     * @return the block offset for the given address
     */
    uint64_t getTag(uint64_t address);

    /**
     * @return true if there is a hit.
     */
    bool hit(uint64_t address);

    /**
     * @return true if the line is dirty
     */
    bool dirty(uint64_t address);

    /// Number of tag bits in the address
    int64_t tagBits;

    /// Mask for getting the index bits
    uint64_t indexMask;

    /// The cache's tag array
    TagArray tagArray;

    /// The cache's data array
    SRAMArray dataArray;

    /// If true, the cache is currently blocked
    bool blocked;

    struct MSHR {
        /// This is the current request_id that is blocking the cache.
        int savedId;

        /// The address for the blocking request.
        uint64_t savedAddr;

        /// This is the size of the original request. Needed for writes.
        int savedSize;

        /// This is the data that will be written after a miss
        const uint8_t* savedData;
    };

    MSHR mshr;
};

#endif // CSIM_DIRECT_MAPPED_H
