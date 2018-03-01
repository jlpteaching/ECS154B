
#ifndef CSIM_UTIL_H
#define CSIM_UTIL_H

#include <cassert>
#include <cstdint>
#include <iostream>

/**
 * This function returns the log base 2 of value.
 * It is only valid if the value is a power of two.
 */
inline int log2int(uint64_t value)
{
    assert(__builtin_popcountll(value) == 1);
    return __builtin_ctzll(value);
}

#ifdef DEBUG
#define DPRINT(args) \
    do {\
    std::cout << args << std::endl; \
    } while(0);
#else
#define DPRINT(args)
#endif

#endif // CSIM_UTIL_H
