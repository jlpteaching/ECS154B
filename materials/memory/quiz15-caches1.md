# Caches 1

## Locality 1

Given the following address streams
ame the kind of locality they exploit

```
0x31c4
0x31cc
0x31d4
0x31dc
0x31e4
```

[____](spatial)

```
0x31c4
0x7808
0x31c4
0x7808
0x31c4
```

[____](temporal)

[[Spatial locality is when each address in the address stream is near the others and temporal locality is when the same addresses are used multiple times.]]

## Locality 2

Increasing the block size of a cache will help when there is what type of locality?

( ) Temporal
(x) Spatial
( ) Associative

[[Block size takes advantage of spatial locality since as you increase the block size you bring in more *nearby* (in addresses) data.]]

## hit/miss ratio

There are two cache systems. System A has a block size of 16 Bytes and System B has a block size of 256 Bytes. Assume the caches are initially empty and have a large capacity.

Given the following address stream, calculate the hit ratio for each cache

```
0x3214
0x31e8
0x31e8
0x3220
0x31dc
0x31e0
0x320c
0x31d8
0x3224
0x31f8
```

### System A

This system has a block size of 16 B. What is the hit ratio?

[___](=0.4+-.05)

[[Since the block size is 16B, any address that matches the first 3 digits will be a hit (after the initial miss). M M H M M H M H H M. 4/10.]]

### System B

This system has a block size of 256 B. What is the hit ratio?

[___](=0.8+-.05)

[[Since the block size is 16B, any address that matches the first 3 digits will be a hit (after the initial miss). M M H H H H H H H H. 8/10.]]

### AMAT

Compute the average memory access time for the following system.

The cache has a hit time of 2ns and memory takes 40ns to respond with data. The cache has a *hit* ratio of 0.8.

Give your answer in nanoseconds.

[____](=10+-.5)

[[2 + 0.2*40 = 10ns]]
