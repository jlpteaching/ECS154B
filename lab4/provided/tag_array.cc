
#include <cassert>

#include "tag_array.hh"

TagArray::TagArray(int lines, int state_bits, int tag_bits) :
    stateBits(state_bits), tagBits(tag_bits)
{
    assert(stateBits <= 32);
    assert(tagBits <= 64);

    assert(lines > 0);

    tags.resize(lines, 0);
    states.resize(lines, 0);
}

uint64_t
TagArray::getTag(int line)
{
    assert(line >= 0);
    assert(line < tags.size());
    return tags[line];
}

uint32_t
TagArray::getState(int line)
{
    assert(line >= 0);
    assert(line < states.size());
    return states[line];
}

void
TagArray::setTag(int line, uint64_t tag)
{
    uint64_t tag_mask = ((uint64_t)-1) >> (64 - tagBits);
    assert((tag & tag_mask) == tag);
    tags[line] = tag;
}

void
TagArray::setState(int line, uint32_t state)
{
    uint64_t state_mask = ((uint64_t)-1) >> (64 - stateBits);
    assert((state & state_mask) == state);
    states[line] = state;
}
