# Intro and Processor design

For all math questions, write out the full equations used in the long-answer space if you want the option of partial credit.

## What is architecture? (9)

### Architecture (3)

List three things that are part of the *architecture* of the system (i.e., defined in the ISA).

|___|

[[The architecture is the interface between the hardware and software. It contains the things that are explicitly visible to the programmer. For instance, the instructions and their format, number of registers, I/O interfaces, and others.]]

### *Micro*architecture (3)

List three things that are part of the **micro**architecture.

|___|

[[The microarchitecture is the *implementation* of the architecture. Details of the microarchitecture should be invisible to the programmer. Examples include, characteristics of caches, whether the processor is pipelined or out of order, number of stages, and others.]]

## Comparing systems (3)

**Other than performance,** list three different characteristics you can use to compare two systems

|___|

[[Power, energy, tail latency, size, weight, usability, and many others.]]

## How to compare systems

In this question, you'll be comparing two systems, System A and System B.
The table below give some details about these two systems.

| System   | ISA    | CPI |
|----------|--------|-----|
| System A | ARM    | 3   |
| System B | X86    | 2   |
| System C | RISC-V | 4   |
| System D | X86    | 0.5 |

### Which is better A or B? (3)

Given the above information, is System **A or B** "better"? If you don't have enough information to answer the question, say so. **EXPLAIN WHY.**

|___|

[[You cannot know which is better as you don't know what the frequency of the processors are or the number of instructions.]]

### Which is better B or D? (3)

Given the above information, is System **B or D** "better"? If you don't have enough information to answer the question, say so. **EXPLAIN WHY.**

|___|

[[You cannot know which is better as you don't know what the frequency of the processors.]]

### Which is better B or D? (5)

Assume that given an ISA the program produced by a compiler will be the same. If the frequency of system B was 2 GHz, what would the **frequency** of system D need to be *so they have the same performance*? If you don't have enough information to answer the question, say so. **EXPLAIN WHY.**

[____](=.500+-.01)

|___|

[[insts are equal. So, for the same performance you need $$B_{CPI}  \times  B_{delay} = D_{CPI}  \times D_{delay}. D_{delay} = B_{CPI} \times B_{delay}/D_{CPI} = 2  \times  0.5 / 0.5 = 2ns \;\; 1s/2ns = 500MHz.$$]]

## Performance, power, and energy

Use the following to answer the questions below. Assume you care about one application.

|          | Voltage | Instructions | Relative capacitive load | CPI | Frequency |
|----------|---------|--------------|--------------------------|-----|-----------|
| System A | 1.6 V   | 10,000       | 1                        | 2   | 1.5 GHz   |
| System B | 1 V     | 12,000       | 0.8                      | 1   | 500 MHz   |

(Relative capacitive load means System B has 0.8 * system A's capacitive load.)

### Performance

What is the speedup of System A over system B?

[___](=1.8+-.05)

Space for work, if needed
|___|

[[ time B / time A = 12 * 1 * 2 / 10 * 2 * (1/1.5) = 1.8 ]]

### Power

What is the *power* of **System B *relative to* System A**. If System B uses more power, this number will be above 1, if it uses less power it will be below 1.

[___](=0.9375+-0.05)

Space for work, if needed
|___|

[[power ~ $$c \times v^2 \times f$$. B_power / A_power = relative c \times B_voltage^2 / A_voltage^2 \times B_freq / A_freq = 0.8 * 0.390625 * 3 = 0.9375]]

### Relative goodness

Assume that the speedup was greater than 1 and the relative power was less than 1. Describe which system is better **AND WHY.** (Note: there may not be an easy answer. Talk about tradeoffs.)

|___|

[[It depends. If you are concerned about latency, then System A is better, if you are concerned about power then system B is better.]]

## Single Cycle design

![Single cycle design]()

This is the same picture as from [Assignment 2](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/assignment-2.md).

### Muxes

For the two muxes highlighted, describe why they are needed.

Mux A
|___|

Mux B
|___|

If not answered above, generally why do we need muxes in our design?

|___|

[[Mux A is used to select between `readdata2` and the `immediate` value. This is required since some instructions use two register values while other use a register and the immediate. Mux B is used to select between the data from memory and the result from the execute "stage". This mux is required since some instructions write data from memory back to the registers while other instructions want to write back other data (e.g., ALU result).]]

### CPI

What is the CPI for this design?

[____](=1+-.01)

[[The CPI is always 1 for a single cycle design.]]

### Control vs data path

Describe the difference between the control path and the data path.

|___|

Which one is shown in the image above?

[___](data path)

[[The data path is shown in the figure above. The instruction's data moves through the data path. which parts of the data path it used is selected by the control path. The data path is "multiplexed" and shared across all instructions.]]

## Pipeline design 1

![]()

This is the same picture as from [Assignment 3]().

### PC

Describe how the pipelined processor updates the PC each cycle. Ignore stalling for load-to-use hazards.

|___|

[[Each cycle, the PC gets the PC+4 unless there is a taken control instruction in memory. If there is a taken control instruction, then the PC is updated with the new address from memory. When a load to use hazard is detected, the PC is stalled (not updated with anything).]]

### Hazard detection

What is the hazard detection logic for load to use hazards? You can write chisel code, or just describe the logic in prose. Include which pipeline stages the information comes from and what you need to do.

|____|

[[When `rs1` or `rs2` in decode is the same as `rd` in execute and the instruction in execute is a load, you need to stall fetch and decode (hold the same values in the pc and IF/ID).]]

### Flushing

When do you need to flush the EX/MEM pipeline register?

|____|

[[The EX/MEM register is flushed when squashing a mis-speculated instruction that is in execute. This happens in the DINO CPU when a branch is detected as `taken` in the memory stage.]]

## Pipeline performance

### Simple CPI

What is the latency, *in cycles*, to execute a single instruction?

[___](=5+-.01)

What is the CPI of this design? Assume a perfect branch predictor and no load-to-use hazards.

[___](=1+-.01)

[[Each instruction takes 5 cycles to execute, but the CPI is 1 since one instruction finishes each cycle]]

### More realistic CPI

What is the CPI of this design if 30% of instructions are loads? Assume a perfect branch predictor, and 10% of the load values are used by the next instruction.

[___](=1.03+-.01)

[[.3 * .1 = .03 instructions introduce a stall. Total CPI is increased by 0.03 to 1.03.]]

## Pipeline design 2

Assume the following details about a pipelined processor design:

| Fetch | Decode | Execute | Memory | Writeback |
|---|---|---|---|---|
| 2100ps | 1250ps | 2500ps | 2000ps | 1250ps |

### Latency

What is the maximum frequency of this design, in MHz?

[___](400)

[[The longest latency stage is execute which takes 2500ps. 1/2500/10^12 = 400*10^6 = 400 MHz. ]]

### Pipeline balance

Which stages would you target to balance this pipeline? How many stages would you make your design to balance this pipeline?

|___|

[[You should target the stages that take the most time. First execute, but also memory and fetch. The best design would probably split fetch, execute, and memory into two stages each giving you an 8 stage pipeline.]]

## Pipeline execution 1

Use the following program to answer the questions below.

```
0:  addi x4, x3, 1000
4:  add  x2, x3, x4
8:  sub  x4, x2, x3
12: sw   x2, 40(x4)
16: beq  x4, x3, -20
```

### Dependencies

Which instructions is the `beq` dependent on?

[____]

[[`beq` reads registers x4 and x3. x4 is the only register that's written by another instruction, the `sub` at 8.]]

### Forwarding

Assume the instructions are in the following locations in the pipeline.

| Fetch | Decode | Execute | Memory | Writeback |
|---|---|---|---|---|
| `beq  x4, x3, -20` |`sw   x2, 40(x4)` | `sub  x4, x2, x3`|`add  x2, x3, x4` |`addi x4, x3, 1000` |

For the two fowarding muxes, what are they selecting? What are the values on the two control wires?

`forwardA`
[___](1)

`forwardB`
[___](0)

[[The `sub` is currently in the execute stage. It is reading from `x2` and `x3`. `x2` (input A) was written by the previous instruction, so we need to get the value from memory. `x3` was not written by anything, so there's no need to forward.]]

### Hazards

Assume the instructions are in the following locations in the pipeline.

| Fetch | Decode | Execute | Memory | Writeback |
|---|---|---|---|---|
| `beq  x4, x3, -20` |`sw   x2, 40(x4)` | `sub  x4, x2, x3`|`add  x2, x3, x4` |`addi x4, x3, 1000` |

Do we need to stall the pipeline this cycle? **Why or why not?** Assume an always not taken branch predictor.

|___|

[[We don't need to stall the pipeline. Only load to use hazards requires stalls.]]

## Pipeline execution diagram

![]()

Draw out the pipeline diagram for the following program.
Assume the DINO CPU pipeline as pictured above and a always not taken branch predictor.
The branch at address 12 is taken (to address 32).
(Note: you *may* attach a picture of your pipeline diagram for partial credit. This is not required.)

```
0:  add x1, x2, x3
4:  lw  x3, 0(x1)
8:  sub x2, x3, x4
12: beq x2, x3, 20
16: sw  x2, 0(x3)
20: xor x4, x2, x4
24: and x4, x4, x4
...
32: sw  x2, 0(x3)
36: xor x4, x2, x4
40: and x4, x4, x4
```

### Cycles

What is the total number cycles to execute this program? I.e., how many cycles does it take until `40: and x4, x4, x4` reaches writeback.

[___](15)

[[(monospace format)    1   2   3   4   5   6   7   8   9  10  11  12  13  14  15 \n 0:  add x1, x2, x3  | F | D | E | M | W |   |   |   |   |   |   |   |   |   |   | \n  4:  lw  x3, 0(x1)   |   | F | D | E | M | W.|   |   |   |   |   |   |   |   |   | \n  8:  sub x2, x3, x4  |   |   | F | D | D | E^| M.| W |   |   |   |   |   |   |   | \n  12: beq x2, x3, 20  |   |   |   | F | F | D | E^| M | W |   |   |   |   |   |   | \n  16: sw  x2, 0(x3)   |   |   |   |   |   |~F~|~D~|~E~|   |   |   |   |   |   |   | \n  20: xor x4, x2, x4  |   |   |   |   |   |   |~F~|~D~|   |   |   |   |   |   |   | \n  24: and x4, x4, x4  |   |   |   |   |   |   |   |~F~|   |   |   |   |   |   |   | \n ... \n 32: sw  x2, 0(x3)   |   |   |   |   |   |   |   |   | F | D | E | M | W |   |   | \n  36: xor x4, x2, x4  |   |   |   |   |   |   |   |   |   | F | D | E | M.| W |   | \n  40: and x4, x4, x4  |   |   |   |   |   |   |   |   |   |   | F | D | E^| M | W | \n ]]

### Forwarding

How many times did you have to forward *from memory*?

[___](2)

[[See above]]

How many times did you have to forward *from writeback*?

[___](1)

[[See above]]

### **Optional** diagram

Attach your diagram below.

## Out of order execution

```
A: add a0, a2, s1
B: sub s1, a1, s1
C: mul s3, a1, a2
D: xor a1, s1, s3
E: and a0, s1, a0
```

### Dependencies 1

In the program above, find all of the dependencies, both true and false of the two instructions below. List the instruction letter (e.g., "E"), the type of dependence (e.g., "RAW"), and the register (e.g., "`a0`").

`D: xor a1, s1, s3`

|___|

[[There's a RAW dependence via `s1` on inst B, a RAW dependence via `s3` on inst C, a WAR dependence via `a0` on inst C and inst D.]]

### Dependencies 2

In the program above, find all of the dependencies, both true and false of the two instructions below. List the instruction letter (e.g., "E"), the type of dependence (e.g., "RAW"), and the register (e.g., "`a0`").

`E: and a0, s1, a0`

|___|

[[There's a RAW dependence via `s1` on inst B, and a WAW dependence via `a0` on inst A.]]

### Static scheduling

Re-write the above code to remove all of the false dependencies. Use `t0`, `t1`, `t2`, etc. as the temporary register. (Note: instructions other than D and E may have false dependencies.)

|___|

[[`add a0, a2, s1; sub t0, a1, s1; mul s3, a1, a2; xor t1, t0, s3; and t2, t0, a2;`]]

## Notes



`addi x4, x3, 1000`
`add  x2, x3, x4`
`sub  x4, x2, x3`
`sw   x2, 40(x4)`
`beq  x4, x3, -20`


addi x4, x3, 1000
add  x2, x3, x4
sub  x4, x2, x3
sw   x2, 40(x4)
beq  x4, x3, -20



A: add a0, a2, s1
B: sub s1, a1, s1
C: mul s3, a1, a2
D: xor a1, s1, s3
E: and a0, s1, a0

add a0, a2, s1
sub t0, a1, s1
mul s3, a1, a2
xor t1, t0, s3
and t2, t0, a2

add a0, a2, s1; sub t0, a1, s1; mul s3, a1, a2; xor t1, t0, s3; and t2, t0, a2;

```
                      1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
0:  add x1, x2, x3  | F | D | E | M | W |   |   |   |   |   |   |   |   |   |   |
4:  lw  x3, 0(x1)   |   | F | D | E | M | W.|   |   |   |   |   |   |   |   |   |
8:  sub x2, x3, x4  |   |   | F | D | D | E^| M.| W |   |   |   |   |   |   |   |
12: beq x2, x3, 20  |   |   |   | F | F | D | E^| M | W |   |   |   |   |   |   |
16: sw  x2, 0(x3)   |   |   |   |   |   |~F~|~D~|~E~|   |   |   |   |   |   |   |
20: xor x4, x2, x4  |   |   |   |   |   |   |~F~|~D~|   |   |   |   |   |   |   |
24: and x4, x4, x4  |   |   |   |   |   |   |   |~F~|   |   |   |   |   |   |   |
...
32: sw  x2, 0(x3)   |   |   |   |   |   |   |   |   | F | D | E | M | W |   |   |
36: xor x4, x2, x4  |   |   |   |   |   |   |   |   |   | F | D | E | M.| W |   |
40: and x4, x4, x4  |   |   |   |   |   |   |   |   |   |   | F | D | E^| M | W |
```

(monospace format)    1   2   3   4   5   6   7   8   9  10  11  12  13  14  15 \n 0:  add x1, x2, x3  | F | D | E | M | W |   |   |   |   |   |   |   |   |   |   | \n  4:  lw  x3, 0(x1)   |   | F | D | E | M | W.|   |   |   |   |   |   |   |   |   | \n  8:  sub x2, x3, x4  |   |   | F | D | D | E^| M.| W |   |   |   |   |   |   |   | \n  12: beq x2, x3, 20  |   |   |   | F | F | D | E^| M | W |   |   |   |   |   |   | \n  16: sw  x2, 0(x3)   |   |   |   |   |   |~F~|~D~|~E~|   |   |   |   |   |   |   | \n  20: xor x4, x2, x4  |   |   |   |   |   |   |~F~|~D~|   |   |   |   |   |   |   | \n  24: and x4, x4, x4  |   |   |   |   |   |   |   |~F~|   |   |   |   |   |   |   | \n ... \n 32: sw  x2, 0(x3)   |   |   |   |   |   |   |   |   | F | D | E | M | W |   |   | \n  36: xor x4, x2, x4  |   |   |   |   |   |   |   |   |   | F | D | E | M.| W |   | \n  40: and x4, x4, x4  |   |   |   |   |   |   |   |   |   |   | F | D | E^| M | W | \n
