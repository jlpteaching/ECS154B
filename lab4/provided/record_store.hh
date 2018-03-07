#pragma once

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

class Record {
public:
    int64_t ticksFromNow;
    bool write;
    uint64_t address;
    int requestId;
    int size;
    uint8_t* data;

    Record(int64_t ticks = 5, bool wr = false, uint64_t addr = 0x10000, int reqId = 0, int size = 4, uint8_t* dat = nullptr):
        ticksFromNow(ticks),
        write(wr),
        address(addr),
        requestId(reqId),
        size(size),
        data(dat)
        {}
    ~Record() {
        if (data)
            delete[] data;
    }
};

class RecordStore
 {
protected:
    string filename;
    vector<Record> records;

public:
    RecordStore(string filename);

    vector<Record>& getRecords();

    bool loadRecords();
    bool writeRecords();
    //
};