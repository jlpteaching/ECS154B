#include "record_store.hh"

#include <fstream>
#include <sstream>

istream& operator>>(istream& is, Record& r) {
    is >> r.ticksFromNow >> r.write >> hex >> r.address >> dec >> r.requestId >> r.size;

    r.dataVec.clear();
    r.dataVec.reserve(r.size);
    if (r.write) {
        for (int i = 0; i < r.size; ++i) {
            int byte;
            is >> hex >> byte >> dec;
            r.dataVec.push_back((uint8_t) byte);
        }
    }

    return is;
}

ostream& operator<<(ostream& os, Record& r) {
    os << r.ticksFromNow << ' ' << r.write << ' ' << hex << "0x" << r.address << dec << ' ' << r.requestId << ' ' << r.size;

    if (r.write) {
        for (int i = 0; i < r.size; ++i) {
            os << ' ';
            os << hex << "0x" << int(r.dataVec[i]) << dec;
        }
    }

    os << endl;

    return os;
}

RecordStore::RecordStore(string filename):
    filename(filename)
{}

vector<Record>& RecordStore::getRecords() {
    return records;
}

bool RecordStore::loadRecords() {
    ifstream in(filename.c_str());

    if (!in) return false;

    records.clear();
    Record r;
    while (in >> r) {
        records.push_back(r);
    }

    in.close();

    return true;
}

bool RecordStore::writeRecords() {
    ofstream out(filename.c_str(), ofstream::out | ofstream::trunc);

    if (!out) return false;

    for (auto& record : records) {
        out << record;
    }

    out.close();

    return true;
}
