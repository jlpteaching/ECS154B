
#ifndef CSIM_SRAM_ARRAY_H
#define CSIM_SRAM_ARRAY_H

#include <cstdint>
#include <iostream>

class SRAMArray
{
    int64_t lines;
    int lineBytes;

    uint8_t *data;

    /// Sum of the size of all SRAM arrays.
    static int64_t totalSize;
  public:
    /**
     * Allocates a new SRAM array. Total size is lines * line_bytes
     */
    SRAMArray(int64_t lines, int line_bytes);

    ~SRAMArray();

    /**
     * @return a pointer to the data for the line in the SRAM array.
     *         NOTE: This data *is* mutable. And this object manages the
     *         dynamic data.
     */
    uint8_t* getLine(int index);

    /**
     * Return the size in bytes.
     */
    int64_t getSize();

    /**
     * Returns the total size of all SRAM arrays.
     */
    static int64_t getTotalSize();
};

#endif // CSIM_SRAM_ARRAY_H
