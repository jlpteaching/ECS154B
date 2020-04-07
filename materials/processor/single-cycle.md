# Single Cycle CPU Design

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

![Under construction]({{ "/under-construction.png" | relative_url }})

This is a video describing the canonical five steps to execute an instruction.

## Data path and control path **VIDEO**

Next, we'll discuss how to split up the hardware into two parts, the control path and the data path.
By splitting the hardware this way, we're able to use *one set of hardware* to execute many different instructions.

![Under construction]({{ "/under-construction.png" | relative_url }})

This video describes how we can split up the hardware into two parts, the control path and the data path.

Now, we can use the following design (what you will be implementing in [Assignment 2](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/assignment-2.md)) to run *any* RISC-V instruction with *one* set of hardware!

![Single cycle DINO CPU design](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/single-cycle-no-control.svg)

## **QUIZ** Single cycle design

![Under construction]({{ "/under-construction.png" | relative_url }})
[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/XXXXXX)

## Performance and limits to a single cycle design

In these videos, we will analyze this microarchitecture to understand the performance characteristics and limits of this design.

### Performance of the single cycle design **VIDEO**

![Under construction]({{ "/under-construction.png" | relative_url }})

This video discusses the performance of the above single cycle design and provides an example of computing the performance.

### How to improve this design and single cycle limitations **VIDEO**

![Under construction]({{ "/under-construction.png" | relative_url }})

This video discusses the limitations of single cycle designs and why real systems aren't implemented this way.

### **QUIZ** The Single cycle design's performance

![Under construction]({{ "/under-construction.png" | relative_url }})
[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/XXXXXX)
