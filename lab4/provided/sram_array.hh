
#ifndef CSIM_SRAM_ARRAY_H
#define CSIM_SRAM_ARRAY_H

#include <cstdint>

class SRAMArray
{
    int64_t lines;
    int lineBytes;

    uint8_t *data;
  public:
    /**
     * Allocates a new SRAM array. Total size is lines * line_bytes
     */
    SRAMArray(int64_t lines, int line_bytes) :
        lines(lines), lineBytes(line_bytes), data(nullptr)
    {
        data = new uint8_t[lines * lineBytes];
    }

    ~SRAMArray() {
        delete[] data;
    }

    uint8_t* getLine(int index)
    {
        return &data[index * lineBytes];
    }
};

#endif // CSIM_SRAM_ARRAY_H
