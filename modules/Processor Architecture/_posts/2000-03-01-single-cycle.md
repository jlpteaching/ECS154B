---
title: Single Cycle CPU Design
---

![XKCD comic](https://imgs.xkcd.com/comics/old_days.png)

**READING:** *Computer Organization and Design* Sections 4.1-4.4.

In this section, we will be digging into the necessary components and details on how to design a processor.
The goal of this section will be to design a full RISC-V processor, which is [Assignment 2](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/assignment-2.md) (Due 4/17).

## Steps to execute an instruction **VIDEO**

"Executing" an instruction takes many different steps.
It's more complicated than just "execution."

Canonically, we have the following five steps to complete an instruction:

1. **Fetch** the instruction: get the instruction data (machine code) from memory.
2. **Decode** the instruction: figure out what we should do and read the data from the register file.
3. **Execute** the instruction: use the ALU to compute a result, the effective address, or direction of the branch.
4. **Memory**: if the instruction needs to access memory, do it.
5. **Writeback** the instruction: (if required) write the result of the instruction to the register file.

The video below explains these steps in more detail and some example instructions.

{% include video.html id="0_vnludqwx" %}

This is a video describing the first two of the canonical five steps to execute an instruction.

{% include video.html id="0_6hppdgq5" %}

This is a video describing the last three of the canonical five steps to execute an instruction.

## Data path and control path **VIDEO**

Next, we'll discuss how to split up the hardware into two parts, the control path and the data path.
By splitting the hardware this way, we're able to use *one set of hardware* to execute many different instructions.

{% include video.html id="0_q2vuxnkt" %}

This video describes how we can split up the hardware into two parts, the control path and the data path.

Now, we can use the following design (what you will be implementing in [Assignment 2](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/assignment-2.md)) to run *any* RISC-V instruction with *one* set of hardware!

![Single cycle DINO CPU design](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/single-cycle-no-control.svg)

{% include video.html id="0_mr5qnvuu" %}

This video goes through a couple of examples with the DINO CPU design as shown above.

## **QUIZ** Single cycle design

[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/439561)

## Performance and limits to a single cycle design

In these videos, we will analyze this microarchitecture to understand the performance characteristics and limits of this design.

### Performance of the single cycle design **VIDEO**

{% include video.html id="0_ou13i1lw" %}

This video discusses the performance of the above single cycle design and provides an example of computing the performance.

### How to improve this design and single cycle limitations **VIDEO**

{% include video.html id="0_qzy1eka9" %}

This video discusses the limitations of single cycle designs and why real systems aren't implemented this way.

### **QUIZ** The Single cycle design's performance

[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/439578)

[Next up: Pipelined processor design.](./pipelined.md)
