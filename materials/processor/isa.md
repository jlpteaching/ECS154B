# Instruction set architectures and machine representation

![XKCD comic "real programmers"](https://imgs.xkcd.com/comics/real_programmers.png)

We will begin with what should be a review of ISAs and machine representation of instructions.
These topics were covered mostly in ECS 50.
However, we will be using the [RISC-V open source ISA](https://riscv.org/).
If you did not take ECS 50 or find yourself struggling to keep up in this first set of lectures, please refer to Chapter 2 in *Computer Organization and Design*.

## Reading for this section

*Computer Organization and Design* Chapter 2. (Skim)

## What is an ISA? **VIDEO**

**READING:** *Computer Organization and Design* Section 1.3

{% include video.html id="0_j97k7yb5" %}

This video discuss the computing stack and and defines the instruction set architecture.

{% include video.html id="0_ftbvfftf" %}

This video gives more more details on what makes an ISA an ISA.

### RISC vs CISC **VIDEO**

<iframe width="608" height="402" src="https://www.youtube.com/embed/3LVeEjsn8Ts?start=788&end=1000" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Callback to the [Turing Lecture](https://www.youtube.com/watch?v=3LVeEjsn8Ts).
From 13:08-16:40 talks about *why* we moved from CISC ISAs to RISC ISAs.
You can (optionally) read a [blog post](https://www.sigarch.org/riscy-history/) that Dave Patterson wrote which gives some more background on this fundamental change in computer architecture.

{% include video.html id="0_1ss43wzz" %}

This video gives more details about the difference between RISC and CISC machines

### **QUIZ** ISAs and RISC vs CISC

[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/432724)

## RISC-V **VIDEO**

**READING:** *Computer Organization and Design* Sections 2.6-2.11 (Optional/skim)

![RISC-V logo](https://content.riscv.org/wp-content/uploads/2018/09/riscv-logo.png)

In this class, we will be using the 32-bit RISC-V ISA.
Specifically, we'll be using the rv32i variant of RISC-V.
You can find *all* of the details about the RISC-V ISA in the [RISC-V Specification document](https://riscv.org/specifications/isa-spec-pdf/).

You can find the instructions that we care about, the 32-bit integer instructions, in the [opcode table](./riscv-instr.pdf).

{% include video.html id="0_41tifybp" %}

{% include video.html id="0_bc54a6ps" %}

These two videos (I got tired after the first one) discuss some details of the RISC-V ISA and give a quick example of a small RISC-V program.
More details are available in Chapter 2 of *Computer Organization and Design* and the *RISC-V Reader*.

### Question: "Why 7 bits for the opcode?"

There was a great question on [campuswire](https://campuswire.com/c/GDBEBE971/feed/91) which asked

> From my understanding, the opcode of an instruction specifies what type of instruction it is or what the instruction does.
> My question is why is the opcode 7 bits wide (representing 2^7=128 possible operations) when there are only 47 types of instructions in the RISC-V table here.
> In this table there are much less than 128 unique opcodes.
> Couldn't we use less bits to represent the opcode?
> What occurs if a value of say 0b1111111 (which isn't in the table) happens to be the value of the opcode?

{% include video.html id="0_xrz5rmxs" %}

This video answers the question above.

## Machine code examples **VIDEO**

Finally, let's put this all together and look at how an instruction is executed on a simple processor (this is an intro to [the next section](./single-cycle.md)).

**READING:** *Computer Organization and Design* Section 2.5

{% include video.html id="0_oc8059yb" %}

This video covers the example of an R-type instruction.
Note that this is what you need to implement for [assignment 1](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/assignment-1.md).

{% include video.html id="0_cf2ocpfl" %}

This video covers a `lw` instruction.

### Optional further reading: Compiling, linking, and assembling

**READING:** *Computer Organization and Design* Sections 2.13 and 2.15

## **QUIZ** RISC-V and machine representation

[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/433513)

[Next up: Single cycle processor design.](./single-cycle.md)
