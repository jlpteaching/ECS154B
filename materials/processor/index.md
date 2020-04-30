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
  * [Reading for this section](./isa.md#reading-for-this-section)
  * [What is an ISA? **VIDEO**](./isa.md#what-is-an-isa--video)
    * [RISC vs CISC **VIDEO**](./isa.md#risc-vs-cisc-video)
    * [**QUIZ** ISAs and RISC vs CISC](./isa.md#quiz-isas-and-risc-vs-cisc) **DUE 4/9**
  * [RISC-V **VIDEO**](./isa.md#risc-v-video)
  * [Machine code examples **VIDEO**](./isa.md#machine-code-examples-video)
    * [Optional further reading: Compiling, linking, and assembling](./isa.md#optional-further-reading-compiling-linking-and-assembling)
  * [**QUIZ** RISC-V and machine representation](./isa.md#quiz-risc-v-and-machine-representation) **DUE 4/9**

### [Assignment 1](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/assignment-1.md) **DUE 4/10**

See [Machine code examples **VIDEO**](./isa.md#machine-code-examples-video) for some helpful hints.

## Single cycle processor design

Next, we will talk about [how to design a single-cycle CPU](./single-cycle.md).
This design will use combinational logic to do all of the steps to complete an instruction *in a single cycle*.
[Assignment 1](https://github.com/jlpteaching/dinocpu-sq20/tree/master/assignments/assignment-1.md) and [Assignment 2](https://github.com/jlpteaching/dinocpu-sq20/tree/master/assignments/assignment-2.md) have you implement this design in Chisel.
This design is covered in Section 4.3 and 4.4 of *Computer Organization and Design*.

* [Single cycle processor](./single-cycle.md)
  * [Steps to execute an instruction **VIDEO**](./single-cycle.md#steps-to-execute-an-instruction-video)
  * [Data path and control path **VIDEO**](./single-cycle.md#data-path-and-control-path-video)
  * [**QUIZ** Single cycle design](./single-cycle.md#quiz-single-cycle-design)
  * [Performance and limits to a single cycle design](./single-cycle.md#performance-and-limits-to-a-single-cycle-design)
    * [Performance of the single cycle design **VIDEO**](./single-cycle.md#performance-of-the-single-cycle-design-video)
    * [How to improve this design and single cycle limitations **VIDEO**](./single-cycle.md#how-to-improve-this-design-and-single-cycle-limitations-video)
    * [**QUIZ** The Single cycle design's performance](./single-cycle.md#quiz-the-single-cycle-design-s-performance)

### [Assignment 2](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/assignment-2.md) **DUE 4/20**

## Pipelined processor design

After covering the basics of processor design, we will start optimizing this design to try to get better performance and come closer to how real systems like the one pictured above is designed.
Our first optimization will be adding [pipelining](./pipelined.md) to our design.
This is covered in Section 4.5 and 4.6 of *Computer Organization and Design* and is the basis for [Assignment 3](https://github.com/jlpteaching/dinocpu-sq20/tree/master/assignments/assignment-3.md).

* [Pipelined processor](./pipelined.md)
  * [Basic pipeline design](./pipelined.md#basic-pipeline-design)
    * [What is pipelining? **VIDEO**](./pipelined.md#what-is-pipelining-video)
    * [Pipelined design for the DINO CPU  **VIDEO**](./pipelined.md#pipelined-design-for-the-dino-cpu-video)
    * [Example execution in pipelined DINO CPU  **VIDEO**](./pipelined.md#example-execution-in-pipelined-dino-cpu-video)
    * [Pipelined CPU performance **VIDEO**](./pipelined.md#pipelined-cpu-performance-video)
    * [**QUIZ** Basic pipelining](./pipelined.md#quiz-basic-pipelining) **Due 4/21**
  * [Pipeline hazards](./pipelined.md#pipeline-hazards)
    * [Limits of our basic pipelined design and data hazards](./pipelined.md#limits-of-our-basic-pipelined-design-and-data-hazards)
      * [Detailed examples of data hazards and dependencies **VIDEO**](./pipelined.md#detailed-examples-of-data-hazards-and-dependencies-video)
      * ["Solving" data hazards with stalling **VIDEO**](./pipelined.md#-solving--data-hazards-with-stalling-video)
    * [How to handle data hazards (forwarding) **VIDEO**](./pipelined.md#how-to-handle-data-hazards-forwarding-video)
      * [Load to use hazards **VIDEO**](./pipelined.md#load-to-use-hazards-video)
    * [**QUIZ** Data hazards](./pipelined.md#quiz-data-hazards)  **Due 4/23**
    * [Control hazards and branch prediction **VIDEO**](./pipelined.md#control-hazards-and-branch-prediction-video)
    * [Other kinds of hazards: Structural hazards **VIDEO**](./pipelined.md#other-kinds-of-hazards-structural-hazards-video)
  * [Exceptions in a pipelined processor **VIDEO**](./pipelined.md#exceptions-in-a-pipelined-processor-video)
  * [Putting it all together: examples of pipelined execution **VIDEO**](./pipelined.md#putting-it-all-together-examples-of-pipelined-execution-video)
    * [**QUIZ** Pipelining review](./pipelined.md#quiz-pipelining-review) **Due 4/23**

## Instruction level parallelism

Finally, we will introduce the idea of [instruction level parallelism](./ilp.md) and introduce a couple of algorithms that can be used to extract performance from scalar (not parallel) applications.
Most of this topic is covered in the graduate level computer architecture course (ECS 201A), but we will touch on some of these topics in this class.

* [Instruction level parallelism](./ilp.md)
  * [Static ILP](#static-ilp)
    * [Instruction scheduling **VIDEO**](#instruction-scheduling-video)
    * [A new ISA type: VLIW **VIDEO**](#a-new-isa-type-vliw-video)
      * [A bit about Intel Itanium (a *real* VLIW design) **VIDEO**](#a-bit-about-intel-itanium-a-real-vliw-design-video)
    * [**QUIZ** Static scheduling](#quiz-static-scheduling)
  * [Dynamic ILP](#dynamic-ilp)
    * [Dynamic instruction scheduling](#dynamic-instruction-scheduling)
      * [A cool historical perspective](#a-cool-historical-perspective)
      * [DIS details **VIDEO**](#dis-details-video)
  * [Register renaming **VIDEO**](#register-renaming-video)
    * [**QUIZ** Dynamic ILP](#quiz-dynamic-ilp)

## Summary

After [summarizing the content covered](./summary.md) by looking at some real systems, we will have a short test on this section of the course.

* [Summary of processor architecture](./summary.md)
  * [Summary of what we've learned **VIDEO**](./summary.md#summary-of-what-we-ve-learned-video)
  * [Real systems **VIDEO**](./summary.md#real-systems-video)

## Test

Date: 5/5. More information to follow.

[Up next: Memory Architecture.](../memory/index.md)
