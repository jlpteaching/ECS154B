---
author: Justin Perona
title: ECS 154B Written Problems for Week 3, Winter 2019
---

# Written problems for week 3

This problem set covers lectures 7 through 10.
This is the last problem set before the first midterm.

Solutions won't be posted on GitHub.
If you'd like answers to the problems, either post on Piazza or go to Jason's or Justin's office hours.

## Lectures

7. [Performance](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/01-23-Lecture-7.pdf)
8. [Multi-cycle and pipeline introduction](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/01-25-Lecture-8.pdf)
9. [More performance](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/01-28-Lecture-9.pdf)
10. [Review](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/01-30-Lecture-10.pdf)

## Topics covered

* Performance
    * Measuring performance
    * Iron law
    * Amdahl's law
    * Latency and throughput
* Introduction to pipelining

## Problems

### Performance

1. Name at least three things that can help determine whether a system is "good" compared to another.
2. Crysis, released in 2007, used to be considered one of the best games for benchmarking GPUs at the time. ("But can it run Crysis?" was a common question at the time.) Many consumer GPUs at the time struggled to achieve even moderate frames per second (FPS) on lower graphic settings. Now, most modern GPUs can play Crysis on high settings with high FPS. If we wanted to benchmark GPUs released within the last year, would Crysis be a good choice of a benchmark? Why or why not?
3. Based on your answer to the previous question, do you think benchmarks remain valid indefinitely, or should our choice of benchmarks change over time?
4. A video player spends 60% of its time fetching frames from disk, and 40% playing the frames. With an improvement to the direct memory access (DMA) controller, we can improve fetch times by 3x. What is the speedup of the improvement?
5. Processor A requires 100 instructions to execute a given program, uses 5 cycles per instruction, and runs at 1 GHz. Processor B requires 400 instructions to execute the same program, but only uses 2 cycles per instruction, and runs at 2 GHz. Which processor executes the given workload faster?
6. Processor C requires 200 instructions to execute a given program, uses 1 cycle per instruction, and has a cycle time of 5 ns. Processor D requires 4 cycles per instruction, but only requires 125 instructions to do the same program. What must the cycle time of Processor D be in order to give the same CPU time as Processor C?
7. An important program spends 50% of its time doing integer arithmetic operations, 30% of its time doing loads and stores, and 20% of its time doing floating point arithmetic. By redesigning the hardware, you can make the floating point unit 90% faster (take 10% as long), the load/store unit 70% faster (take 30% as long), or the integer unit 40% faster (take 60% as long). Which should you do, and why?
8. What is the speedup of the best improvement in the previous problem, compared to the base? (Hint: this number should be greater than one, else it's not a speedup!)
9. Say we add a second core to a single-core machine and keep the frequency the cores run at the same. Would this improve the latency of the machine, or the throughput? What would happen if instead of adding the second core, we increased the frequency of the single core? Which term would this improve?

### Introduction to pipelining

10. What does pipelining a processor improve - the latency of the processor, or the throughput?
11. With our canonical five-stage pipeline, what's the maximum number of instructions that we can run at once? How many could we potentially execute at once with a twenty-stage pipeline?

For the next two questions, examine the following five-stage pipeline. The time it takes for each stage to execute is below.

* Fetch: 220 ps
* Decode: 180 ps
* Execute: 420 ps
* Memory: 210 ps
* Writeback: 190 ps

12. Why is the pipeline above not balanced?
13. Suggest two ways that we can make this pipeline balanced.
