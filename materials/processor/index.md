# Processor Architecture

![Coffee lake die shot](./800px-coffee_lake_die_(hexa_core).png)

In this section of the course, we will learn details of how to design a processor core.
The processor core is the "brain" of the computing system.
It reads in (fetches) instructions from memory, figures out what the instruction is supposed to do (decodes it), and performs the task(s) of the instruction (executes it).

## ISA and Machine Representation

![RISC-V logo](https://content.riscv.org/wp-content/uploads/2018/09/riscv-logo.png).

We will begin with what should be a review of [ISAs and machine representation of instructions](./isa.md).
These topics were covered mostly in ECS 50.
However, we will be using the [RISC-V open source ISA](https://riscv.org/).
If you did not take ECS 50 or find yourself struggling to keep up in this first set of lectures, please refer to Chapter 2 in *Computer Organization and Design*.

* [ISA and Machine Representation](./isa.md)
  * Work in progress. Available 4/3. Due 4/9.

## Single cycle processor design

Next, we will talk about [how to design a single-cycle CPU](./single-cycle.md).
This design will use combinational logic to do all of the steps to complete an instruction *in a single cycle*.
[Assignment 1](https://github.com/jlpteaching/dinocpu-sq20/tree/master/assignments/assignment-1.md) and [Assignment 2](https://github.com/jlpteaching/dinocpu-sq20/tree/master/assignments/assignment-2.md) have you implement this design in Chisel.
This design is covered in Section 4.3 and 4.4 of *Computer Organization and Design*.

* [Single cycle processor](./single-cycle.md)
  * Work in progress. Available 4/8. Due 4/14.

## Pipelined processor design

After covering the basics of processor design, we will start optimizing this design to try to get better performance and come closer to how real systems like the one pictured above is designed.
Our first optimization will be adding [pipelining](./pipelined.md) to our design.
This is covered in Section 4.5 and 4.6 of *Computer Organization and Design* and is the basis for [Assignment 3](https://github.com/jlpteaching/dinocpu-sq20/tree/master/assignments/assignment-3.md).

* [Pipelined processor](./pipelined.md)
  * Work in progress. Available 4/10. Due 4/16 and 4/21.

## Instruction level parallelism

Finally, we will introduce the idea of [instruction level parallelism](./ilp.md) and introduce a couple of algorithms that can be used to extract performance from scalar (not parallel) applications.
Most of this topic is covered in the graduate level computer architecture course (ECS 201A), but we will touch on some of these topics in this class.

* [Instruction level parallelism](./ilp.md)
  * Work in progress. Available 4/22. Due 4/28.

## Summary

After [summarizing the content covered](./summary.md) by looking at some real systems, we will have a short test on this section of the course.

* [Summary of processor architecture](./summary.md)
  * Work in progress. Available 4/24. Due 4/30.

## Test

Date: 5/1. More information to follow.

[Up next: Memory Architecture.](../memory/index.md)
