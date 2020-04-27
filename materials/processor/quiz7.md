# Quiz 7 Solutions


## **Q1** Executing an instruction
Fill in the blanks below. (Note: Gradescope requires precise answers.) Use the canonical 5 steps to complete an instruction found [here](https://jlpteaching.github.io/ECS154B/materials/processor/single-cycle.html#steps-to-execute-an-instruction-video).

The processor generates control signals for the instruction in

> decode

The processor generates the effective address for load and store instructions in

> execute

The processor may write the instruction’s result to the register file in

> writeback

The instruction is read from memory in

> fetch

Only loads and stores perform a function and other instructions do nothing in

> memory

## **Q2** Single cycle design

Use this picture to answer the questions below.



![single-cycle-no-control.png](/files/008cdb75-7ccf-477a-8b15-fdf42ff75c67)

### **Q2.1** Mux 1

For the mux highlighted and labeled with (A) in the picture, select which instructions will use the 1 input on the mux.

- [ ] Branches
- [X] jalr
- [ ] jal
- [ ] R-type
- [ ] I-type
- [ ] lw
- [ ] sw
- [ ] Other instructions

### **Q2.2** Mux 2

For the mux highlighted and labeled with (B) in the picture, select which instructions will use the 1 input on the mux.

- [ ] Branches
- [ ] jalr
- [ ] jal
- [ ] R-type
- [ ] I-type
- [X] lw/lh/lb/lbu/lhu/etc.
- [ ] sw/sh/sb/etc.
- [ ] Other instructions

## **Q3** Control vs datapath

Shared by all instructions

- [X] data path
- [ ] control path

Selects subsets of components to use for each instruction

- [ ] data path
- [X] control path

## **Q4** Data path elements

"A state element that contains a set of locations that can be read/written by supplying a location number and that is usually accessed multiple time for each instruction" describes which of the following data path elements?

- [ ] PC
- [ ] Instruction memory
- [X] Register file
- [ ] Control unit
- [ ] ALU
- [ ] Immediate generator
- [ ] Data memory
- [ ] Muxes
