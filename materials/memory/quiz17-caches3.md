# Quiz 17: Cache design 1

## Direct-mapped cache design

Use the following characteristics to answer the questions below.

Cache capacity: 64 KB
Block size: 128 B
Address size: 36 bits
Associativity: None, direct-mapped

What bits of the address are used to access the cache? Answer using chisel syntax (e.g., the lowest order 4 bits would be "(3,0)").

Tag:
[___]((35,16))

Offset into the block:
[___]((6,0))

Index:
[___]((15,7))

[[The first 7 bits are for the offset, then the next 9 bits (log2(64KB/128)) are used to calculate the index, and the rest of the upper-order bits (20) are used as the tag.]]

## Set-associative cache design

Use the following characteristics to answer the questions below.

Cache capacity: 2 MB
Block size: 32 B
Address size: 46 bits
Associativity: 16-way set associative
Metadata: 3 bits per block

### Address bits

What bits of the address are used to access the cache? Answer using chisel syntax (e.g., the lowest order 4 bits would be "(3,0)").

Index:
[___]((16,5))

Tag:
[___]((45,17))

Offset into the block:
[___]((4,0))

[[The first 5 bits are for the offset. The total number of sets is 2MB/32/16=2048 or 2^12, so there are 12 bits for the index and the rest of the upper-order bits (29) are used as the tag.]]

### Total cache size

What is the total size of the SRAM for this cache? Assume that each block requires 3 bits of extra metadata to store valid, dirty, etc. Give the answer in terms of *bytes*.

[___](=2359296+-1)

[[There is 2^21/2^5=2^16 blocks. Each block requires 32 bytes for data + 29 bits for tag + 3 bits for metadata for a total of 36 bytes. 36*2^16=‬2359296 bytes total. This is a 12.5% overhead.]]

### Dynamic power

How many bits are read every time the cache is accessed? Assume that all ways are accessed in parallel.

[___](=4880+-1)

[[One set is accessed. There are 16 blocks in the set. Each block has (32B x 8bits)+46bits+3bits)=305 x 16 ways = 4880 bits or 610 bytes.]]
