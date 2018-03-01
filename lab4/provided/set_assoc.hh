
#include "cache.hh"

class SetAssociativeCache: public Cache
{
  public:
    /**
    * @param size is the *total* size of the cache in bytes
    * @param the memory that is below this cache
    * @param processor this cache is connected to
    * @param the number of ways in this set associative cache. If the number
    *        of ways cannot be realized, this will cause an error
    */
    SetAssociativeCache(int64_t size, Memory& memory, Processor& processor,
                        int ways);

    /**
     * Destructor
     */
    ~SetAssociativeCache() override;

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
    virtual bool receiveRequest(uint64_t address, int size, const uint8_t* data,
                                int request_id) override;

    /**
     * Called when memory id finished processing a request.
     * Data will always be the length of memory.getLineSize()
     *
     * @param request_id is the id assigned to this request in sendMemRequest
     * @param data is the data from memory (length of data is line length)
     *        NOTE: This pointer will be invalid when this function returns.
     */
    virtual void receiveMemResponse(int request_id, const uint8_t* data)
        override;

  private:
    /// Put any code you want here.
};
