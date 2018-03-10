
#ifndef CSIM_PROCESSOR_H
#define CSIM_PROCESSOR_H

#include <cstdint>
#include <map>
#include <queue>
#include <utility>
#include <string>

#include "cache.hh"
#include "ticked_object.hh"
#include "record_store.hh"

class Processor: public TickedObject
{
  protected:
    int addressSize;

    Cache *cache;
    Memory *memory;

    RecordStore *records;

    std::queue<Record*> trace;

    std::map<int, Record*> outstanding;

    void sendRequest(Record &r);

    bool blocked;

    virtual void createRecords();

    int64_t totalRequests;

    void checkData(Record &record, const uint8_t* cache_data);

  public:
    Processor(int addrSize = 32);
    ~Processor();

    /**
     * Called to schedule the processor to run in the simulation.
     */
    void scheduleForSimulation();

    /**
     * Called by the cache when it sends a response.
     *
     * @param the original request id
     * @param the data returned if it was a read (nullptr if write)
     */
    void receiveResponse(int request_id, const uint8_t* data);

    /**
     * Connect the cache
     */
    void setCache(Cache *cache) { this->cache = cache; }

    /**
     * Connect memory for debugging and checking purposes
     */
    void setMemory(Memory *memory) { this->memory = memory; }

    /**
     * Connect a record store (like an instruction ROM)
     */
    void setRecords(RecordStore *recordStore) { this->records = recordStore; }

    /**
     * @return the number of bits in the address
     */
    int getAddrSize();
};

#endif // CSIM_PROCESSOR_H
