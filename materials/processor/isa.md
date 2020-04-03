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

![Under construction]({{ "/under-construction.png" | relative_url }})

This video discuss the computing stack and and defines the instruction set architecture.

### RISC vs CISC **VIDEO**

<iframe width="608" height="402" src="https://www.youtube.com/embed/3LVeEjsn8Ts?start=788&end=1000" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Callback to the [Turing Lecture](https://www.youtube.com/watch?v=3LVeEjsn8Ts).
From 13:08-16:40 talks about *why* we moved from CISC ISAs to RISC ISAs.
You can (optionally) read a [blog post](https://www.sigarch.org/riscy-history/) that Dave Patterson wrote which gives some more background on this fundamental change in computer architecture.

![Under construction]({{ "/under-construction.png" | relative_url }})

This video gives more details about the difference between RISC and CISC machines

### **QUIZ** ISAs and RISC vs CISC

![Under construction]({{ "/under-construction.png" | relative_url }})

## RISC-V **VIDEO**

**READING:** *Computer Organization and Design* Sections 2.6-2.11 (Optional/skim)

![RISC-V logo](https://content.riscv.org/wp-content/uploads/2018/09/riscv-logo.png)

In this class, we will be using the 32-bit RISC-V ISA.
Specifically, we'll be using the rv32i variant of RISC-V.
You can find *all* of the details about the RISC-V ISA in the [RISC-V Specification document](https://riscv.org/specifications/isa-spec-pdf/).

![Under construction]({{ "/under-construction.png" | relative_url }})

This video discusses some details of the RISC-V ISA.
More details are available in Chapter 2 of *Computer Organization and Design* and the *RISC-V Reader*.

## Other ISAs **VIDEO**

![Under construction]({{ "/under-construction.png" | relative_url }})

This video discusses some other ISAs (e.g., x86 and ARM) and how they differ from RISC-V.

## C to machine code **VIDEO**

Finally, let's put this all together and talk about how to go from high-level languages down to the hardware.

**READING:** *Computer Organization and Design* Sections 2.13 and 2.15

![Under construction]({{ "/under-construction.png" | relative_url }})

This video gives a high-level overview of compiling, assembling, and linking as well as a little bit about how dynamic languages work.

## **QUIZ** RISC-V and machine representation

![Under construction]({{ "/under-construction.png" | relative_url }})

[Next up: Single cycle processor design.](./single-cycle.md)
