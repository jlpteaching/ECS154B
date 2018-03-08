
#include "sram_array.hh"

SRAMArray::SRAMArray(int64_t lines, int line_bytes) :
    lines(lines), lineBytes(line_bytes), data(nullptr)
{
    data = new uint8_t[lines * lineBytes];

    totalSize += getSize();
}

SRAMArray::~SRAMArray()
{
    delete[] data;
}

uint8_t*
SRAMArray::getLine(int index)
{
    return &data[index * lineBytes];
}

int64_t
SRAMArray::getSize()
{
    return lines * lineBytes;
}

int64_t
SRAMArray::getTotalSize()
{
    return totalSize;
}

int64_t SRAMArray::totalSize = 0;
