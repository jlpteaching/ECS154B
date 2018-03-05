
#include <cassert>
#include <iostream>

#include "tag_array.hh"

TagArray::TagArray(int lines, int state_bits, int tag_bits) :
    lines(lines), stateBits(state_bits), tagBits(tag_bits)
{
    assert(stateBits <= 32);
    assert(tagBits <= 64);

    assert(lines > 0);

    tags.resize(lines, 0);
    states.resize(lines, 0);

    totalSize += getSize();
}

uint64_t
TagArray::getTag(int line)
{
    assert(line >= 0);
    assert(line < lines);
    return tags[line];
}

uint32_t
TagArray::getState(int line)
{
    assert(line >= 0);
    assert(line < lines);
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

int64_t
TagArray::getSize()
{
    int64_t bits = (stateBits + tagBits) * tags.size();
    return bits/8;
}

int64_t
TagArray::getTotalSize()
{
    return totalSize;
}

int64_t TagArray::totalSize = 0;
