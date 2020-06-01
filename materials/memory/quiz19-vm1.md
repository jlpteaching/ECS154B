# Quiz 19: Virtual memory 1

## Why we want to virtualize

Which of the following are reasons why we want to virtualize processes?

[x] Isolate each process's data
[x] Protect one process from reading or writing another processes data
[x] Run a process on a machine with a *smaller* amount of physical memory than the ISA-defined address space
[x] Run a process on a machine with a *larger* amount of physical memory than the ISA-defined address space
[x] Share physical hardware between multiple processes
[x] View the system as if each process was running on its own
[ ] To increase performance of the process

[[The only wrong answer is increasing performance. Virtualization is not a performance optimization. In fact, often it *hurts* performance. Virtualization improves *programmability* and *usability* of a system, which are other very important characteristics that we care about.]]

## Translation owner

What controls the virtual to physical address translation?

( ) The process
( ) The user
(x) The operating system
( ) The compiler
( ) The hardware

[[The OS controls the translation since it has access to the physical hardware. If the process or user could control the virtual to physical translation then it would break isolation and protection as any process could read/write any other processes data. In most systems, the OS is trusted by all processes to carry this out fairly and safely.]]

## Segmentation

### Registers

When implementing segmentation, each segment has three registers, a base, a bounds, and an offset.
Are these virtual or physical addresses?

Base:
(x) virtual
( ) physical

Bounds
(x) virtual
( ) physical

Offset
( ) virtual
(x) physical

[[The base and bounds are "virtual" address and are then translated by using the offset which is "physical" (at least logically)]]

### Architectural state

Which of the following is true

(x) The segmentation registers are part of the architectural state and *must be* saved when doing a context switch. They are part of the ISA.
( ) The segmentation registers are *not* part of the architectural state and *are not* saved when doing a context switch. They are *not* part of the ISA.

[[The state of the address translation mechanisms is also part of the ISA and the architectural state.]]

## Translation example

Assume the following flat translation table. The following is given like a C array (e.g., the 0th entry is the leftmost entry).

```
[0x1234, 0x5678, 0x9abc, 0xffff]
```

### Translation

Assuming the page size is 64KB, translate the following addresses. Give your answers in hex. (E.g., 0xabcd)

0x120a4
[____](0x567820a4)

0x4000
[____](0x12344000)

0x1af88
[____](0x5678af88)

[[Since the page size is 64KB, the offset is 16 bits or the first 4 hex digits. Thus, you just need to look at the most significant hex digit and then use that to look up the value in the table (1, 0, and 1 in this case).]]

### Address size

What is the size of the virtual address space (in KBs)?

[____](=256+-1)

[[There are only 4 entries in the page table, so there can only be 4 pages. Each page is 64KB x 4 pages = 256 KB.]]

What is the minimum size of the physical address space given the information that you know? (Give your answer in MBs.)

[____](=4096+-1)

[[The largest physical address is 0xffffffff which requires 32 bits for up to 4GB or 4096 MBs]]
