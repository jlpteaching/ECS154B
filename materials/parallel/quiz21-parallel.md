# Quiz 21: Parallel Architectures

## Amdahl's Law

90% of a program can be parallelized, what is the speedup on

4 cores
[___](=3.077+-.05)

8 cores
[___](=4.706+-.05)

50 cores
[___](=8.475+-.05)

100 cores
[___](=9.174+-.05)

[[Correct! s=1/(.1+.9/p) where s is the speedup and p in the number of cores. Notice the difference between 50 and 100 cores is much less than the difference between 4 and 8 cores.]]

## Accelerator performance

Let's say 95% of an application can be ported to run on the GPU.
When we run this on the GPU we see a 100x speedup.

### Overall speedup

What is the overall speedup of the application?

[____](=16.8+-.1)

[[s = 1/.05+.95/100=16.8x]]

### More realism

Let's make this a bit harder. Say, that the original application took 100 seconds and there is a flat 1 second overhead from offloading something from the CPU to the GPU. What's the speedup in this case?

[____](=14.388+-.1)

[[t_old = 100. t_new = 5 + 95/100 + 1 = 6.95. s = 100/6.95 = 14.388]]

## Types of parallelism

Which of the following represent data-level parallelism?

[x] Applying a filter to an image (e.g., making every pixel darker)
[ ] A webserver serving requests from many clients
[X] `for (int i=0; i<size; i++) result[i] = a*x[i] + y[i]`
[ ] Parallel version of mergesort

[[Applying a filter and the for loop apply the *same* operations to many different pieces of data and are data-level parallelism. A webserver uses different data and (possibly) different code paths to serve requests from different clients. Finally, mergesort can be parallelized using recursive parallel calls (e.g., sorting the left and right part of the array at the same time). In this case, the two parallel tasks are operating on *different* data and doing different operations so this is an example of task-level parallelism.]]

## SIMD vs MIMD

When the application has *task-level* parallelism, a SIMD architecture is probably more efficient than a MIMD architecture.

( ) True
(X) False

[[This is false. If it had said "data-level" parallelism, it would have been true. SIMD architectures can be more efficient because there is only a single fetch/decode for many different operations. MIMD architectures replicate this hardware at each core and thus are less efficient, but only if SIMD hardware can be properly utilized. Task-level parallelism isn't amenable to running on SIMD architectures efficiently.]]

## Message passing vs shared memory

### Message passing

Implementing communication via message passing is required when which of the following is true?

[X] The workload scales to multiple machines
[ ] The workload will only execute on a single machine at a time
[ ] The workload uses multiple cores on a single machine
[X] The workload requires more memory than will fit on a single machine

[[Message passing is needed when you can't use shared memory. Shared memory is more efficient if the workload can fit on a single machine.]]

### Shared memory

Which of the following are examples of shared memory architectures?

[X] The AMD Epyc system discussed at the end of the memory section
[ ] Data centers
[ ] Super computers (e.g., [Summit](https://www.olcf.ornl.gov/summit/) at ORNL and [Sierra](https://computing.llnl.gov/computers/sierra) and LLNL)
[X] Most smartphones
[X] Most desktop computers
[X] A GPU

[[Systems with multiple nodes (datacenters and supercomputers) are not shared memory. The GPU is debatable. All GPU cores share one memory (the GPU memory), but this isn't (usually) shared the CPU and sometimes the GPU programming model doesn't allow writing applications that share data through memory.]]

## The last question

I learned something in this class.

(X) True

[[I certainly hope you learned something! Though it was stressful at times, I had a great quarter teaching you all! I particularly enjoyed the discussions. It was a lot of fun for me to be able to directly interact with so many of you. Good luck in the months and years to come, and stay safe and healthy!]]
