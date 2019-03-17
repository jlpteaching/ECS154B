---
Author: Justin Perona
Title: ECS 154B Written Problems for Week 10, Winter 2019
---

# Written problems for week 10

This problem set covers lectures 25 through 28.
This is the last problem set.

Solutions won't be posted on GitHub.
If you'd like answers to the problems, either post on Piazza or go to Jason's or Justin's office hours.

## Lectures

25. [Parallel architectures 1](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/03-08-Lecture-25.pdf)
26. [Parallel architectures 2](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/03-11-Lecture-26.pdf)
27. [Parallel architectures 3](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/03-13-Lecture-27.pdf)
28. [Review](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/03-15-Lecture-28.pdf)

## Topics covered

* Parallel architectures
    * Flynn's taxonomy
    * Parallel processing and memory
    * Warehouse-scale computing
    * Accelerators

## Problems

### Parallel architectures

1. For each type of classification in Flynn's taxonomy, name an architecture or mechanism that falls under it.
2. How does a SIMD architecture attempt to execute code in parallel?
3. Following up from the previous question, there are significant benefits to a SIMD architecture. Given this, should we run everything on SIMD architectures? Is it appropriate in every instance? If not, name an instance where it wouldn't be appropriate.
4. Given your answer to the previous question, what are the downsides (if any) to a SIMD architecture?
5. In a MIMD architecture, is each execution unit running the same or a different instruction stream? Are they working on the same or different pieces of data?
6. Are your answers to the previous question the same if we are running different threads of the same application?
7. What are the three different types of multi-threading? Which one looks like it would be able to execute the most instructions at once?
8. What do you think a barrier operation does to application performance? If some threads finish more quickly than others and hit the barrier, what ends up happening to them?
9. Why do we need to ensure cache coherency? What would be the issue if we didn't have a coherency protocol?
10. In a multi-core machine that is running multiple threads, we can write to a location and another thread can read from it. This is known as a shared memory system. Why is this not possible in a warehouse-scale system?
11. Following from the previous question, what do we need to do instead? Is this easier or harder on the programmer than shared memory? Why?
12. An accelerator requires data and results to be transferred to and from the CPU. (We do the same with GPUs.) In most cases, we can also run the same workload that we would give to an accelerator on a CPU, though usually not as quickly. Is it possible that it would be more beneficial to run a workload on the CPU than pass it over to an accelerator? Why or why not?

### Coalescing questions

The following questions build on many topics covered over the course of the class.

13. Say we are running a program you wrote that is 60% serial and 40% parallel. Assuming we could perfectly map even portions of the workload to additional cores on a MIMD machine, how many cores would we need to run this program on in order to achieve a 2x speedup?
14. What does the answer to the previous problem mean to you as the programmer? Why does this tie in to the power wall and that we can no longer increase processor frequencies by a significant amount?
