
#include <cassert>
#include <iostream>

#include "direct_mapped.hh"
#include "set_assoc.hh"
#include "non_blocking.hh"
#include "memory.hh"
#include "processor.hh"
#include "record_store.hh"

int main(int argc, char *argv[])
{

    if (argc != 5) {
        std::cout << "Input error!" << std::endl;
        std::cout << "Usage: " << argv[0] << " <trace file> " << "<size bits> ";
        std::cout << "<ways> " << "<mshrs> " << std::endl;
        exit(1);
    }

    char* recordFile = argv[1];
    int sizebits = atoi(argv[2]);
    int ways = atoi(argv[3]);
    int mshrs = atoi(argv[4]);
    int block_size = 64;

    assert(sizebits > 6 && sizebits < 22);
    assert(ways < ((1 << sizebits) / block_size));
    assert(mshrs > 0);

    Processor p(32);
    Memory m(block_size);
    RecordStore records(recordFile);
    if (!records.loadRecords()) {
        std::cerr << "Could not load file: " << recordFile << std::endl;
        return 1;
    }
    p.setMemory(&m);
    p.setRecords(&records);
    NonBlockingCache c(1 << sizebits, m, p, ways, mshrs);
    p.scheduleForSimulation();

    std::cout << "Running simulation" << std::endl;
    TickedObject::runSimulation();
    std::cout << "Simulation done" << std::endl;

    std::cout << "Data size: ";
    std::cout << ((float)SRAMArray::getTotalSize())/1024 << "KB" << std::endl;

    std::cout << "Tag size: ";
    std::cout << ((float)TagArray::getTotalSize())/1024 << "KB" << std::endl;

    return 0;
}
