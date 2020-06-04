# Quiz 20: Virtual memory 2

## Multi-level page table

Use the following information to answer the questions below.

* The base page size is 1KB.
* Each PTE is 64 bits.
* There are four levels in the page table.
* Every level (chunk) of the page table is the same size as the base page size (like in rv32, rv64, and x86).

### Bits per index

The number of bits to index each level of the page table:
[____](7)

[[There would be 128 entries in each page table chunk (1024/(64/8)=128) and you need 7 bits to address 128 entries.]]

### Number of levels

What is the size of the virtual address space. Give your answer in gigabytes (GB).

[____](256)

[[You need 10 bits for the offset + 7x4=28 bits for the page table index = 38 bits. 2^38=256 GB.]]

### TLB pressure

Compared to rv32 with a base page size of 4KB, how would you expect this new address translation design to compare? Mark all that are true.

[x] For the same size TLB, the new design would have more misses than rv32.
[ ] The new design requires *fewer* memory accesses for every TLB miss than rv32.
[x] There would be less fragmentation in memory with the new design compared to rv32.
[x] The overhead from the page table would be higher with this design. I.e., this new design requires more memory than the rv32 design.

[[All are true except for the second. This new design requires more memory accesses since it has four levels instead of two levels.]]

## AMAT for TLB

For this question, use the following assumptions:

* Memory latency is 100 cycles
* The average page walk time is 200 cycles
* The TLB latency is 0 cycles (it is fully pipelined with the L1 cache access)
* The TLB hit ratio is 99%
* The L1 cache has a hit ratio of 95%
* The L1 cache has a hit time of 1 cycle

### Current AMAT

What is the AMAT of this system in cycles?

[____](8)

[[You need to add the AMAT of the TLB with the L1 cache. $$AMAT_{TLB}=0+.01*200=2$$ $$AMAT_{MEM}=1+.05*100=6$$ For a total AMAT of 8.]]

### System optimization

It turns out that in the next generation of this system, you have a larger area budget. You can use this area to increase the size of the TLB or the size of the L1 cache. Here are your two options:

Option 1:
TLB is larger. It has a 10x lower mis ratio (now 99.9% hit ratio), but it now has a 1 cycle latency.

Option 2:
The L1 cache is larger. It has a 5x lower miss ratio (now 99% hit ratio), but it now has a 2 cycle latency.

Which is the faster option?

( ) Option 1: Larger TLB
(x) Option 2: Larger cache

What is the new AMAT in cycles?

[____](5)

[[The larger cache is the better option. $$AMAT_{opt1}=1+.001*200+1+.05*100=1.2+6=7.2$$ $$AMAT_{opt2}=0+.01*200+2+.01*100=2+3=5$$]]
