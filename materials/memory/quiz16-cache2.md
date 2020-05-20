# Quiz 16: AMAT, hierarchy, and performance

## Comparing cache systems

Use the following system characteristics to answer the questions below.

L1 cache latency: 2 cycles
L1 cache hit ratio: 95%
Memory latency: 40 cycles
Instruction mix: 40% loads and stores

### AMAT 1

What is the average memory access time in cycles for the cache?

[____](=4.0+-.05)

[[AMAT=2+.05 x 40 = 2 + 2 = 4]]

### IPC

Assume 0 time for instruction fetch (for instance, there is a very good instruction prefetcher) and assume that all instructions other than loads and stores complete with a CPI of 1.

What is the CPI of this realistic system with an L1 cache?

[____](=2.2+-.05)

[[ld/st have a CPI of 4 (see AMAT above). CPI = 1 x .6 + 4 x .4 = 2.2]]

### Two levels

To improve performance you add another level of cache. You have two options:

|           | L2 Cache A | L2 Cache B |
|-----------|------------|------------|
| Hit ratio | 80%        | 90%        |
| Latency   | 10 cycles  | 15 cycles  |

Recompute the AMAT for these two systems.

AMAT with L2 design A:

[____](=2.9+-.01)

AMAT with L2 design B:

[____](=2.95+-.01)

Which design is better?

(x) Design A
( ) Design B

[[AMAT_A = 2 + .05 (10 + .2x40) = 2.9; AMAT_B = 2 + .05 (15 + .1x40) = 2.95]]

### Speedup

What is the speedup of the best system with the two level cache (use the best L2 design from the previous question).

[____](=1.25+-.02)

[[CPI_A = 1 x .6 + 2.9 x .4=1.76; speedup = 2.2/1.76=1.25]]
