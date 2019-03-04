---
Author: Justin Perona
Title: ECS 154B Written Problems for Weeks 4-5, Winter 2019
---

# Written problems for weeks 4-5

This problem set covers lectures 11 through 14.
(The week numbers are slightly off, due to the fact that the first midterm was in the middle of the week.)

Solutions won't be posted on GitHub.
If you'd like answers to the problems, either post on Piazza or go to Jason's or Justin's office hours.

## Lectures

11. [More pipelining](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/02-01-Lecture-11.pdf)
12. [Hazards](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/02-04-Lecture-12.pdf)
13. [Control hazards](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/02-06-Lecture-13.pdf)
14. [Pipeline correctness](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/02-08-Lecture-14.pdf)

## Topics covered

* Pipelining
    * Performance implications
    * Datapath modifications
* Hazards
    * Data hazards
    * Control hazards
    * Branch prediction
* Exceptions
    * Reasoning
    * Types of exceptions

## Problems

### Pipelining

1. Consider our traditional 5-stage pipeline. Assume that we are in the middle of executing a completely unrealistic program with no data dependencies, no branch or jump instructions, and no exceptions occurring. What is the CPI of the processor?
2. Now consider if we had just started the program in the previous problem. What is the CPI of the processor through the first 5 cycles? What happens to this number as we increase the number of cycles executed up to 10? Up to infinity?
3. How does a pipelined processor compare to a single cycle processor for the following terms? Do they go up, down, or stay the same?
    * amount of power consumed
    * amount of time consumed
    * amount of energy consumed
4. We don't usually see extremely large pipelines. (Intel processors peaked at 31 stages in the Prescott and Cedar Mill microarchitectures around 2006.) Part of the reason is due to propagation delay from the pipeline registers. Why does that propagation delay influence pipeline length? (Hint: what happens to the cycle time when we split a 5-stage pipeline into a 100-stage one?)

### Hazards

5. Another reason why we don't see extremely large pipelines is due to hazards. Why do hazards influence pipeline length? What happens to the hazard and forwarding units in a longer pipeline?
6. Would pipeline hazards affect your answer to #1 above? Is it possible to get the same CPI if we were executing a more realistic program?
7. Name the three types of hazards, and a solution to solve some of the problems that each hazard brings.
8. True or false: forwarding sends the result of an earlier stage in the pipeline to a later stage. (IF comes earlier in the pipeline than ID, as an example.)
9. True or false: forwarding sends the result of an instruction that comes earlier in program order to a instruction that comes later in program order.
10. Assume a traditional 5-stage pipeline. Answer the following questions using the code block below.
    1. Indicate all data dependencies between instructions.
    2. If we didn't implement forwarding, how many NOPs would we need to insert to ensure correct execution? You may assume that writes to the register file occur on the first half of the cycle, and reads occur on the second half.
    3. Now assume we implemented forwarding. How many NOPs are left?
    4. Is is possible to reschedule this code to remove any NOPs? If so, how many NOPs are left?

```
0:    lw   x5, 0(x2)
4:    lw   x2, 4(x6)
8:    add  x3, x2, x1
12:   sw   x3, 20(x9)
16:   sub  x8, x7, x8
20:   and  x8, x8, x5
```

11. Why do we need to flush instructions? How do we implement this in the hardware?
12. Assume a traditional 5-stage pipeline. Answer the following questions using the code block below.
    1. Assume that, when we start executing this code block, `x7 = 72` and `x8 = 228`. Can we move the `sw` before the `lw`? Why or why not?
    2. Assume we do not have a forwarding unit. Can we move instruction 8 between instructions 0 and 4 to eliminate some of the NOPs? Why or why not?
```
0:    add  x3, x1, x2
4:    bne  x3, x4, 16
8:    lw   x5, 124(x7)
12:   sw   x6, -32(x8)
16:   add  x4, x1, x3
20:   ...
```

13. What two pieces of information does a processor need in order to make a branch prediction?
14. What is the difference between a static and a dynamic branch predictor? Which one requires more hardware to implement?

### Exceptions

15. What is an exception? Are these common?
16. When an exception is raised, what does the OS do?
