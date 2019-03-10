---
Author: Justin Perona
Title: ECS 154B Written Problems for Weeks 8-9, Winter 2019
---

# Written problems for weeks 8-9

This problem set covers lectures 22 through 24.
(The week numbers are slightly off, due to the fact that the second midterm was in the middle of the week.)

Solutions won't be posted on GitHub.
If you'd like answers to the problems, either post on Piazza or go to Jason's or Justin's office hours.

## Lectures

22. [Virtual memory 1](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/03-01-Lecture-22.pdf)
23. [Virtual memory 2](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/03-04-Lecture-23.pdf)
24. [Finishing virtual memory](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/03-06-Lecture-24.pdf)

### Discussion

Questions about the paper covered in this discussion will also be on the final.

9. [Branch prediction](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/03-07-Discussion-9.pdf)

## Topics covered

* Virtual memory
    * Translation mechanisms
    * Paging
    * Page tables
    * TLB
    * AMAT with TLBs
    * Reducing translation overhead
    * Virtualizing the whole system
* Branch prediction
    * Perceptron paper
    * Timing constraints

## Problems

### Virtual memory

1. What are some of the benefits of implementing a virtual memory system? What is a drawback of implementing a virtual memory system?
2. In order to virtualize a CPU, what pieces of state do we need to save from each process?
3. Say we were running a small C program and Photoshop on a machine. What would be the issue if we assigned the same amount of physical memory to each process?
4. How do we solve the problem mentioned in the previous problem?
5. Assuming a 24-bit virtual address, a byte-addressable memory size of 128 KB, and a page size of 1 KB, show how virtual addresses and physical addresses are laid out for use in this machine's virtual memory system. Label each portion of each address, and give the number of bits for each portion.
6. Assuming a 31-bit virtual address, a byte-addressable memory size of 2 MB, and a page size of 2 KB, show how virtual addresses and physical addresses are laid out for use in this machine's virtual memory system. Label each portion of each address, and give the number of bits for each portion.
7. Using the previous problem, determine how many entries are in the page table, and how wide each entry of the page table is. How does the page table size compare to the size of the entire memory? Will we be able to fit the entire page table into our memory?
8. How do we solve the issue raised in the previous problem?
9. Using the following page table and the virtual addresses below, either translate the virtual address and give the corresponding physical address, or determine that there will be a page fault. The page size for this virtual memory system is 256 B.

![Page table for problem 8.](./graphics/pagetable.png)

The virtual addresses are below.

    1. 0x25F
    2. 0x0EC
    3. 0x709
    4. 0x5AD

10. What is the TLB? Why is it almost necessary for a virtual memory implementation?
11. One option to ensure that a virtual memory system is fast is to make the TLB have a very high hit rate. What should our TLB look like (in terms of cache parameters) in order to ensure that the hit rate is high? (There's a couple of answers to this, though none are necessarily "right" for every case.)
12. What is the other option to ensure that a virtual memory system is fast? What are some mechanisms that we can use to accomplish this?
13. What occurs on a TLB miss? How is this different than what occurs on a TLB hit?
14. A page table walk costs 100 cycles. Our TLB has a hit rate of 99.5% and an access time of 0.5 cycles. What is the average time it takes to translate an address?
15. Why is it especially important that our TLB has a high hit rate if we are virtualizing an entire OS?

### Branch prediction

16. How did the authors evaluate the perceptron predictor against other predictors to test if their predictor was outperforming the others?
17. What is a major advantage of the perceptron predictor's usage of history, compared to other predictor schemes that use history like *gshare*?
18. Say we were able to create a branch predictor that has 100% accuracy, but takes 25 cycles to return an prediction. Would we want to use this predictor in a CPU? Why or why not?
19. In our typical five-stage in-order pipeline that we've discussed in class, what stage does a branch predictor need to be placed in? What would be the issue of placing it in later stages than that one?
