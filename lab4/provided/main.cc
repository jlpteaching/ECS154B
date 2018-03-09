
#include <iostream>

#include "direct_mapped.hh"
#include "memory.hh"
#include "processor.hh"
#include "record_store.hh"

int main(int argc, char *argv[])
{
    const char* recordFile = "simple.txt";
    if (argc == 2) {
        recordFile = argv[1];
    } else if (argc > 2) {
        std::cout << "Usage: cache_simulator [records file]" << std::endl;
    }

    Processor p;
    Memory m(8);
    RecordStore records(recordFile);
    if (!records.loadRecords()) {
        std::cerr << "Could not load file: " << recordFile << std::endl;
        return 1;
    }
    p.setMemory(&m);
    p.setRecords(&records);
    DirectMappedCache c(1 << 10, m, p);
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
