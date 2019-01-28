---
author: Justin Perona
title: ECS 154B Written Problems for Week 2, Winter 2019
---

# Written problems for week 2

This problem set covers lectures 4 through 6.

Solutions won't be posted on GitHub.
If you'd like answers to the problems, either post on Piazza or go to Jason's or Justin's office hours.

## Lectures

4. [Instruction sets + RISC-V introduction](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/Lecture-4.pdf)
5. [Example machine design](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/Lecture-5.pdf)
6. [Single cycle RISC-V](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/Lecture-6.pdf)

## Topics covered

* Instruction set architectures (ISAs)
  * RISC versus CISC
* RISC-V
  * Instruction types
  * Extensions
* From code to execution
  * Going from higher-level languages to machine code
  * Executing an instruction
* Single-cycle CPU
  * Datapath
  * Adding new instructions

## Problems

### Instruction set architectures

1. What is an instruction set architecture? (Hint: think about software and hardware.)
2. Name three things that are part of an ISA. Is the frequency of the CPU part of the ISA?
3. What differentiates a RISC architecture and a CISC architecture? Give a real-life example of each.
4. What is the Iron Law? (This will be covered later in class, but it was also mentioned in the 2017 Turing Lecture.)
5. RISC quickly overtook CISC as the ISA style of choice due to its performance. As mentioned in the 2017 Turing Lecture (14:15), the VAX had an average CPI of 10. How would a RISC architecture be faster than the VAX? Use your answer from the previous problem to show this.

### RISC-V

6. Is RISC-V an implementation of hardware? What about x86 or ARM - are they implementations of hardware?
7. How many operands does a RISC-V R-type instruction specify? What about an I-type?
  * (inspired by something I learned after making this document) What type of instruction is `lui` and `auipc`? How does this type differ from an I-type?
8. What is the difference between the `addi` and `addiw` instructions? Can you run the `addiw` instruction in a processor that implements only the RV32I specification?

### From code to execution

9. What steps do we take to translate C code into machine code? How does this process differ compared to the process for a language like JavaScript? (Hint: look up the difference between a compiled and an interpreted language.)
10. Using the following RISC-V assembly, translate the following instructions to machine code. The register numbers have been provided in a comment.
  * `auipc a0, 0 # (reg[10] = 0 + pc (4))`
  * `add t0, t0, t1 # reg[5] = reg[5] + reg[6]`
11. Using the following machine code provided in hex, translate the following machine code to RISC-V assembly mnemonics. You can specify just the register numbers instead of using the standardized names.
  * `0x00858593`
  * `0x00e51513`
12. List the five steps to execute an instruction, and what each step does. At what point is the current PC value updated with the address of the next instruction?

### Single-cycle CPU

13. In lecture, when we made the change to implement the memory instructions `lw` and `sw`, why did we add a MUX right in front of the register file's `writedata` input? Why is this MUX necessary?
14. The MUX in the previous problem was controlled by a control signal from the control unit. In English, explain what the control signal that controls this MUX means, and why it would be 0 or 1 for a specific instruction.
15. Is it possible that the value of a control signal (say, the one from the previous problem) doesn't matter at all for a given instruction? Why or why not?
16. In lecture, when we made the change to implement branch-type instructions in the datapath, why did we need to use an additional adder? Why couldn't we use the adder we had previously, or even the ALU?
