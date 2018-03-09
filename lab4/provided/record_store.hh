#ifndef CSIM_RECORD_STORE_HH
#define CSIM_RECORD_STORE_HH

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
    vector<uint8_t> dataVec;

    Record(int64_t ticks = 5, bool wr = false, uint64_t addr = 0x10000, int reqId = 0, int size = 4, vector<uint8_t> data = {}):
        ticksFromNow(ticks),
        write(wr),
        address(addr),
        requestId(reqId),
        size(size),
        dataVec(data)
        {}
    friend istream& operator>>(istream& is, Record& r);
    friend ostream& operator<<(ostream& os, Record& r);
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
};
#endif
