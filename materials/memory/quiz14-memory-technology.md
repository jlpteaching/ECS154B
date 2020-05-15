# Quiz 14: Memory technology

## Question 1: Memory latency

Rank the following memory technologies from fastest to slowest (lowest to highest latency). Put 1, 2, 3, or 4 with each technology. 1 is fastest 4 is slowest.

DRAM
[__](2)

Flash
[__](3)

SRAM
[__](1)

Spinning disk
[__](4)

## Question 2: Memory arrays

It doesn't matter what size the memory array is, the latency to access a cell only depends on the cell technology.

( ) True
(x) False

## Question 3: addressing memory

A memory array has a 1024 bit word/block and has a capacity of 65536 bits.

### Bit lines

How many bit lines are there?

[____](1024)

[[There are 1024 bit lines since the word/block size is 1024]]

### Word lines

How many word lines are there?

[____](64)

[[65536/1024 = 2^(16-10) = 2^6 = 64]]

### Row select bits

How many bits do you need to use from the address for the row select?

[____](6)

[[There's 64 rows 2^6=64. Therefore, 6 bits]]

### Column select bits

If the memory is *byte* addressable (1 byte = 8 bits), how many bits would you need from the address to choose a column (byte) from the active row? This gives you the offset into the row.

[____](7)

[[1024/8=128 different bytes to address in the row, so we need 7 bits (128=2^7) for the offset]]

## volatile vs non-volatile memory

Mark the statements that are true *for all volatile memories*

[X] Data can be lost when the power is removed
[ ] Data must be refreshed because charge leaks
[ ] They are faster than non-volatile memories
[X] They can only be used for temporary data
