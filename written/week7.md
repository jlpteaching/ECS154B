---
Author: Justin Perona
Title: ECS 154B Written Problems for Week 7, Winter 2019
---

# Written problems for week 7

This problem set covers lectures 18 through 21.
This is the last problem set before the second midterm.

Solutions won't be posted on GitHub.
If you'd like answers to the problems, either post on Piazza or go to Jason's or Justin's office hours.

## Lectures

18. [Memory hierarchy](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/02-20-Lecture-18.pdf)
19. [Caching reminder](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/02-22-Lecture-19.pdf)
20. [Multi-level cache hierarchies](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/02-25-Lecture-20.pdf)
21. [Review](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/02-27-Lecture-21.pdf)

## Topics covered

* Memory
    * Memory types
    * Memory hierarchy
* Caches
    * Accessing a cache
    * Types of caches
    * Cache parameters
    * Multi-level cache hierarchies
    * Average memory access time (AMAT)

## Problems

### Memory

1. Why do we build a memory system with a combination of many technologies? What benefit do we get from combining all these technologies?
2. Imagine that somebody was able to create a non-volatile memory type with the latency of SRAM, the memory density of flash memory, the cost per byte of the cloud, and very little power usage. Would we even need a memory hierarchy in that case? Why or why not?
3. Would your answer to the previous question change if the new memory type was volatile? Why or why not?
4. Name two things that decrease as we go up from the bottom of the memory hierarchy to the top.
5. Name two things that decrease as we go down from the top of the memory hierarchy to the bottom.

### Caches

6. What principle do caches work upon? We normally talk about that principle in two different ways; explain each in one sentence.
7. Rank the three cache placement types (DM, FA, SA) in order of increasing numbers of sets.
8. For the cache example that we did in class (64 byte DM cache with a line size of 4 bytes), partition out the following address and indicate which bits go to which part of the address. On the diagram, indicate where the byte would be written or read from, what the tag of the line becomes, and what the valid bit gets set to.

```
1001 0101 0010 1110 0011
```

9. Why do we need a valid bit in a cache?
10. On a cache read, what do we do if the tag for the line that we check doesn't match the tag of the address we have?
11. Given a 16 KB byte-addressable DM cache with a 21-bit physical address and a line size of 16 bytes, show how a physical address is laid out for use in the cache. Label each portion of the address and give the number of bits for each portion.
12. Given a 512 byte byte-addressable FA cache with a 12-bit physical address and a line size of 4 bytes, show how a physical address is laid out for use in the cache. Label each portion of the address, and give the number of bits for each portion.
13. What type of cache placement policy would you use for a L1 cache versus a cache that is further away?
14. Intel CPUs have typically used a multiple-cache hierarchy. The L1 cache is closest to the CPU, while the L3 cache is the furthest away. How does the L3 cache compare to the L1 terms of the following: power usage, cost, capacity, and speed?
15. Assume that for some certain program executed on a processor without caches, we hit in DRAM 99.9% (0.999) of the time. An access to DRAM takes 100 cycles. When we miss, we need to go out to disk, which is an HDD in this case. This takes 1 000 000 cycles. What is the average memory access time in this case?
16. Assume we swap out the HDD in the previous problem with an SSD that has an access latency of 150 000 cycles. What does the hit rate in DRAM need to at least be in order to get the AMAT from the previous problem down to 300 cycles?
