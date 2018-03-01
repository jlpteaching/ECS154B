
#ifndef CSIM_CACHE_H
#define CSIM_CACHE_H

#include <cstdint>

class Memory;
class Processor;

class Cache
{
  public:
    /**
     * @param size is the *total* size of the cache in bytes
     * @param the memory that is below this cache
     * @param processor this cache is connected tos
     */
    Cache(int64_t size, Memory& memory, Processor& processor);

    /**
     * Virtual destructor. Please override in sub classes
     */
    virtual ~Cache() { }

    /**
     * Called when the processors sends load or store request.
     * All requests can be assummed to be naturally aligned (e.g., a 4 byte
     * request will be aligned to a 4 byte boundary)
     *
     * @param address of the request
     * @param size in bytes of the request.
     * @param data is non-null, then this is a store request.
     *        NOTE: data is invalid when this function returns. Data must be
     *              copied.
     * @param request_id the id that must be used when replying to this request
     *
     * @return true if the request can be received, false if the cache is
     *         blocked and the request must be retried later.
     */
    virtual bool receiveRequest(uint64_t address, int size, const uint8_t* data,
                                int request_id) = 0;

    /**
     * Called when memory id finished processing a request.
     * Data will always be the length of memory.getLineSize()
     *
     * @param request_id is the id assigned to this request in sendMemRequest
     * @param data is the data from memory (length of data is line length)
     *        NOTE: This pointer will be invalid when this function returns.
     */
    virtual void receiveMemResponse(int request_id, const uint8_t* data) = 0;

  protected:
    /**
     * Send a response to the procesor.
     *
     * @param request_id is the id that the processor used when it called
     *        receiveRequest
     * @param data is the data for the request. This data will only be read.
     */
    void sendResponse(int request_id, const uint8_t* data);

    /**
     * Send a request to get data from main memory.
     *
     * @param address of the request
     * @param size of the request. NOTE: This must be the same as the memory
     *        line size.
     * @param when writing back to memory, data is a pointer to the data to
     *        write back. When reading it is nullptr.
     * @param request_id the id that must be used when replying to this request
     *        NOTE: You may choose any request id you want and the memory will
     *        use that id when it replies.
     */
    void sendMemRequest(uint64_t address, int size, const uint8_t* data,
                        int request_id);

    /// Size of cache in bytes
    int64_t size;

    /// Memory below this cache
    Memory &memory;

    /// Processor that is sending this cache requests.
    Processor &processor;
};

#endif // CSIM_CACHE_H
