
#include <iostream>

#include "direct_mapped.hh"
#include "memory.hh"
#include "processor.hh"

int main(int argc, char *argv[])
{
    Processor p;
    Memory m(8);
    RecordStore records("simple.txt");
    records.loadRecords();
    p.setMemory(&m);
    p.setRecords(&records);
    DirectMappedCache c(1 << 10, m, p);
    p.run();

    std::cout << "Running simulation" << std::endl;
    TickedObject::runSimulation();
    std::cout << "Simulation done" << std::endl;

    std::cout << "Data size: ";
    std::cout << ((float)SRAMArray::getTotalSize())/1024 << "KB" << std::endl;

    std::cout << "Tag size: ";
    std::cout << ((float)TagArray::getTotalSize())/1024 << "KB" << std::endl;

    return 0;
}
