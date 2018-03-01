
#ifndef CSIM_TAG_ARRAY_H
#define CSIM_TAG_ARRAY_H

#include <cstdint>
#include <vector>

class TagArray
{
  public:
    /**
     * Allocates the tag and state data. All data defaults to 0
     *
     * @param lines that are in the tag array
     */
    TagArray(int lines, int state_bits, int tag_bits);

    /**
     * @return a pointer to the bits that correspond to the tag for the given
     *         line.
     */
    uint64_t getTag(int line);

    /**
    * @return a pointer to the bits that correspond to the state for the given
    *         line.
    */
    uint32_t getState(int line);

    /**
     * Sets the tag to the bits provided.
     */
    void setTag(int line, uint64_t tag);

    /**
     * Sets the state to the bits provided.
     */
    void setState(int line, uint32_t state);

  private:

    int stateBits;
    int tagBits;

    /// The storage for the tags. Cheating and using more bits than neeeded.
    std::vector<uint64_t> tags;

    /// The storage for the state. Cheating and using more bits that needed.
    std::vector<uint32_t> states;
};

#endif // CSIM_SRAM_ARRAY_H
