# Quiz 18: Cache design 2

## Set associative cache 2

Assume the following address breakdown:

| tag | index | offset |
|---|---|---|
|37 | 14 | 8 |

### Block size

What is the block size (in bytes)?

[___](=256+-1)

[[You need 8 bits, so it must be 2^8 or 256 bytes.]]

### Capacity

Assume the associativity is 8-way set associative.

What is the cache capacity? (Give the answer in bytes.)

[___](=33554432+-1)

[[There are 2^14 sets, 8 blocks in each set, and 256 bytes per block. So, 2^14 x 2^3 x 2^8 = 2^25 or 32 MB (33554432 bytes).]]

### Associativity

Assume the total cache capacity is 4 MB.

What is the associativity?

[___](1)

[[size / #sets = 4MB / 2^14 = 2^8 = 256 B per set. This means that there is only *1* block per set.]]

## Replacement policies

### Best policy

Which replacement policy will perform the best?

( ) Least recently used
( ) Most recently used
(x) It depends on the workload
( ) Random
( ) Pseudo least-recently used

### Overhead of replacement

Which policy has the *least* hardware overhead?

( ) Least recently used
( ) Most recently used
( ) It depends on the workload
(x) Random
( ) Pseudo least-recently used

## Write-back policy

Which of the following are benefits of a write-*through* policy?

[ ] Lower memory bandwidth
[x] Easier to handle faults in the cache
[x] Less metadata in the cache
[ ] Lower latency for writes

## Reducing miss ratio

Assume that after analyzing your workload and cache design, you find that most of the misses are due to *capacity* misses. Which of the following *will not* improve the hit ratio.

( ) Increasing the capacity of the cache
(x) Increasing the set associativity
( ) None of the above
( ) All of the above
