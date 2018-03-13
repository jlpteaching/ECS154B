:Author: Jason Lowe-Power

**ECS 154B Lab 5, Winter 2018**

**Due by 9:00 AM on Mar 19, 2018**

**NOTE: LATE POLICY CHANGE!!**

No late turn-ins will be accepted for this assignment.

**Via Canvas**

Objectives
==========

-  Use a simulation framework to perform experiments

-  Experience writing technical documentation

Description
===========

In this lab, you will use the code developed in `Lab 4`_ to perform experiements varying cache parameters and look at different performance metrics.

.. _Lab 4: https://github.com/jlpteaching/ECS154B/blob/master/lab4/lab4.rst

Below is a set of questions.
For each question, answer the question and provide a graph that backs up your answer.
You should provide the graphs and a one paragraph (a few sentences) answer to each question.

For all of the questions, use the long_trace.txt file from github.
This file has 40,000 accesses to 4 different "arrays" of sizes 10 KB, 30 KB, 60 KB, and 900 KB.
The smaller arrays are accessed more often.
The accesses sizes are 16, 32, and 64 B (randomly chosen), and there are 25% writes.

Run all of your experiments with a 64B block size.

Questions
=========

Question 1: Miss ratio and cache size
-------------------------------------

Using the direct-mapped cache, run the  for cache sizes of 1 KB to 4MB.
Make a graph of the **miss ratio** for each cache size.

- **Question 1a**: Explain how the miss ratio changes for increasing cache sizes and *why* it shows this pattern.

- **Question 1b**: What is the minimum miss ratio? Why is it not 0?

Question 2: Average memory access time
--------------------------------------

Using the data from your previous tests, calculate the average memory access time for each cache size.
Use the value of 15 ticks/cycles for the cache miss penalty and 1 tick/cycle for the cache hit time.
Make a graph of the predicted performance for each cache size by multiplying the AMAT with the number of memory accesses.

*On the same plot*, also include the total execution time as reported by the simulator.

- **Question 2a**: How well does the AMAT model predict performance? (Remember to back up your answer with data.)

- **Question 2b**: You've now used two different types of models to predict performance: a C++ timing model (the code) and a simple analytic model (AMAT). Which model would you choose if you had to evaluate some new system? Why?

Question 3: Set-associative caches
----------------------------------

Run your model with a cache size of 64 KB.
Run the direct-mapped cache, then run your set associative cache with associativities of 1, 2, 4, 8, 16, 32.

Make two plots, one of the miss ratio as you vary the associativity and one of the total execution time as you vary the associativity.

- **Question 3a**: What is the relationship between *execution time* and *miss ratio*? Is this any different between the set associative cache and the direct-mapped cache.

- **Question 3b**: As you increase the set associativity, is it always worth it? Is there a point where increasing the set associativity starts helping less? Assume that the "cost" of set associativity grows quadradically, (e.g., a 2-way SA cache costs 4 times as much as a 1-way and a 16-way costs 64 times as much as a 2-way).

Question 4: Non-blocking cache performance
------------------------------------------

Use a 64 KB 8-way set associative cache for this experiement.
Run your model with 1, 2, 4, 8, 16, 32, and 64 MSHRs.
Plot the *performance* of the system as you vary the number of MSHRs.

- **Question 4a**: As you increase the number of MSHRs, do you see a linear performance improvement (e.g., 2x the MSHRs means the trace runs 2x faster)? Why or why not?

- **Extra credit question 4b**: (You will get 10pts extra credit for a correct answer). Assume the cache receives a request on average every 0.667 cycles and that memory takes, on average, 15 cycles to respond. How many MSHRs do you need to minimize stalling? You must show your work to receive points. Hint: Use Little's Law.

Question 5: Real systems
------------------------

You can find a blocked matrix-multiply implementation on github (mm.cc) along with a Makefile.
Build this file on your computer (or one of the CSIF machines).

When you run ``make``, you will get mulitple different binaries with different "block" sizes.
Take a look at the code to get an idea of how the blocked matrix multiple algorithm works. wikipedia_ might help as well.
There is also a version without blocking (nbmm for non-blocked).

.. _wikipedia: https://en.wikipedia.org/wiki/Block_matrix#Block_matrix_multiplication

Run each version of matrix multiplication *on your computer* with an input size of 1024.
This will run a matrix multiplication of two 1024x1024 matricies.
Plot the runtime of this application for each block size and the non-blocking version.
Use this plot to answer the following questions.

- **Question 5a**: What block size shows the fastes runtime on your computer? Why do you think smaller block sizes are slower? Why do you think larger block sizes are slower?

- **Question 5b**: What if you ran this on a different computer, for instance, your smart phone? Do you think the fastest block size will be the same or different? **Why?**


Submission
==========

**Warning**: read the submission instructions carefully. Failure to adhere to the instructions will result in a loss of points.

-  Upload to Canvas a **pdf** file that contains the following. Your submission **must** be only in pdf format. No other formats will be accepted!

   -  The names of you and your partner.

   -  The answers to the questions above and a graph for each answer.

-  Only one partner should submit the assignment.

-  You may submit your assignment as many times as you want.
