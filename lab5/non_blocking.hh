
#ifndef CSIM_NON_BLOCKING_H
#define CSIM_NON_BLOCKING_H

#include <map>

#include "cache.hh"
#include "set_assoc.hh"
#include "tag_array.hh"
#include "sram_array.hh"

class NonBlockingCache: public SetAssociativeCache
{
  public:
    /**
    * @param size is the *total* size of the cache in bytes
    * @param the memory that is below this cache
    * @param processor this cache is connected to
    * @param the number of ways in this set associative cache. If the number
    *        of ways cannot be realized, this will cause an error
    * @param number of MSHRs (or max number of concurrent outstanding requests)
    */
    NonBlockingCache(int64_t size, Memory& memory, Processor& processor,
                        int ways, int mshrs);

    /**
     * Destructor
     */
    ~NonBlockingCache() override;

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
        Busy=2, // This is not valid!
        Dirty=3 // Dirty implies valid
    };

    struct MSHR {
    /// This is the current request_id that is blocking the cache.
    int savedId;

    /// The address for the blocking request.
    uint64_t savedAddr;

    /// This is the size of the original request. Needed for writes.
    int savedSize;

    /// This is the way we will put this into
    int savedWay;

    /// This is the data that will be written after a miss
    const uint8_t* savedData;
    };

    std::map<int, MSHR> mshrs;
    unsigned int maxMSHRs;
    int mshrsActive;
    int nextId;

    /**
     * returns true if the address is currently busy
     */
    bool busy(uint64_t address);

    /**
    * @return way number if hit, -1 otherwise
    */
    int hit(uint64_t address);

    /**
    * @return true if the line is dirty
    */
    bool dirty(uint64_t address, int way);

};

#endif // CSIM_NON_BLOCKING_H
