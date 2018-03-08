
#include <cstring>
#include <iostream>

#include "memory.hh"
#include "processor.hh"
#include "ticked_object.hh"
#include "util.hh"

Processor::Processor() : cache(nullptr), memory(nullptr), blocked(false),
    totalRequests(0)
{
    createRecords();
    Record &r = trace.front();
    schedule(r.ticksFromNow, [this, &r]{sendRequest(r);});
}

Processor::~Processor()
{
    std::cout << "Total requests: " << totalRequests << std::endl;
}

void
Processor::sendRequest(Record &r)
{
    DPRINT("Sending request 0x" << std::hex << r.address
            << std::dec << ":" << r.size << " (" << r.requestId << ")");
    outstanding[r.requestId] = r;
    if (cache->receiveRequest(r.address, r.size, &r.dataVec[0], r.requestId)) {
        totalRequests++;
        trace.pop();

        if (trace.empty()) return;

        // Queue the next request.
        Record &next = trace.front();
        schedule(r.ticksFromNow, [this, &next]{sendRequest(next);});
    } else {
        DPRINT("Cache is blocked. Wait for later.");
        // Cache is blocked wait for later.
        blocked = true;
        // Remove the last thing we added to the outstanding list, it's not
        // outstanding.
        outstanding.erase(r.requestId);
    }
}

void
Processor::receiveResponse(int request_id, const uint8_t* data)
{
    // Check to make sure the data is correct!
    DPRINT("Got response for id " << request_id);

    auto it = outstanding.find(request_id);
    assert(it != outstanding.end());
    checkData(it->second, data);
    outstanding.erase(it);

    if (blocked) {
        // unblock now.
        DPRINT("Unblocking processor at " << curTick());
        blocked = false;
        Record &r = trace.front();
        schedule(r.ticksFromNow, [this, &r]{sendRequest(r);});
    }
}

int
Processor::getAddrSize()
{
    return 32;
}

void
Processor::checkData(Record &record, const uint8_t* cache_data)
{
    assert(memory);
    if (record.write) {
        memory->processorWrite(record.address, record.size, &record.dataVec[0]);
    } else {
        memory->checkRead(record.address, record.size, cache_data);
    }
}

void
Processor::createRecords()
{
    //               Ticks   Write  Address   ID#   size   data
    trace.push(Record(5,      1,    0x10000,   1,     8,    {0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}));
    trace.push(Record(5,      1,    0x10008,   2,     8,    {0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}));
    trace.push(Record(5,      1,    0x12000,   3,     8,    {0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}));
    trace.push(Record(5,      1,    0x1c000,   4,     8,    {0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}));
    trace.push(Record(5,      1,    0x10a00,   5,     8,    {0x5, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}));
    trace.push(Record(5,      0,    0x10010,   6,     8,    {0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}));
    trace.push(Record(5,      0,    0x10018,   7,     8,    {0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}));
    trace.push(Record(5,      0,    0x10004,   8,     4,    {0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}));
    trace.push(Record(5,      0,    0x10008,   9,     4,    {0x9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}));
    trace.push(Record(5,      0,    0x1000c,   10,    4,    {0xa, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}));
    trace.push(Record(5,      0,    0x110000,  11,    4,    {0xb, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}));
}
