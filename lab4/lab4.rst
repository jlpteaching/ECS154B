:Author: Jason Lowe-Power

**ECS 154B Lab 4, Winter 2018**

**Due by 9:00 AM on Mar 12, 2018**

**Via Canvas**

Objectives
==========

-  Build a controller for a set-associative and non-blocking cache.

-  Analyze the performance of different cache designs with a simulator.

Description
===========

In this lab, you will build a cache model of a set-associative non-blocking cache in C++.
Computer architects often use high-level languages like C++ to *model* hardware in early research and development of new design.
Using high-level languages gives architects more freedom and flexibility to quickly iterate with designs than using hardware description languages or actually making hardware.

You will be given a simulation framework and an example direct-mapped cache implementation.
You will build your new cache models in this framework and evaluate them.
You will be graded in two ways:
#. Correctly implementing your cache models (e.g., the correct number of tag bits).
#. Understanding the tradeoffs between different designs.

**DO NOT MODIFY THE GIVEN CODE IN ANY WAY. DOING SO WILL LEAD TO AN AUTOMATIC ZERO.**
(Unless expressly stated below.)

**EXTRA CREDIT**: This is my first time giving this assignment.
I have written this code over the last couple of days, so it's likely there are bugs.
If you're unsure if you've found a bug, post on piazza.
If you find a bug, please open a pull request on github_.
**You will receive 5 points of extra credit for each pull request I merge**.

.. _github: https://github.com/jlpteaching/ECS154B/

Details
=======

Given code
----------

You will find the code in the ``lab4/provided/`` directory.
The code is heavily documented.
Please see the code for all details.

There is a Makefile included that will build the ``cache_simulator``.
The cache simulator currently has a very simple test implemented.
In ``main.cc``, a processor, a cache, and a memory are instantiated.
Then, the simulation is executed.

Processor
~~~~~~~~~
The processor drives the simulation.
It sends memory requests to the cache by calling ``receiveRequest`` on the cache object.
The processor will continually send requests to the cache until the cache responds that it is blocked (``receiveRequest`` returns ``false``).
There requests may be sent multiple in a single *tick* or cycle.

The test that is run is initialized in ``Processor::createRecords()``.
This function populates a queue which is the "trace" of memory accesses.
See ``processor.cc`` for details.

Feel free to add your own tests and/or modify the tests in ``createRecords``.
When we test your code we will use a different implementation of ``Processor::createRecords``.


Cache
~~~~~
You will be inheriting from the ``Cache`` object.
See the code in ``cache.hh`` for details of the interface you will implement.
You will need to implement the following functions:
- ``receiveRequest``: Called by the Processor when sending a new request.
- ``receiveMemResponse``: Called by memory when it has finished reading the data previously requested by the cache.

**DO NOT MODIFY THIS INTERFACE! OR THE IMPLEMENTATION OF THE NON-VIRTUAL FUNCTIONS.**

Memory
~~~~~~

Memory receives requests from the cache.
After some delay, it will respond to the request (the delay is guaranteed to be more than 1 tick).
This object also has an interface for you to determine the line size.
The memory line size is used as the cache line size.

TickedObject
~~~~~~~~~~~~
This object implements the discrete event simulation.
Feel free to ignore it :).

DirectMappedCache
~~~~~~~~~~~~~~~~~
This is an example cache implementation.
Feel free to base you implementation of the set associative cache on the direct mapped cache that is included.
You can use any code from the class in your set associative cache.

TagArray and SRAMArray
~~~~~~~~~~~~~~~~~~~~~~
**DO NOT MODIFY THIS CODE IN ANY WAY**

You are required to use the ``TagArray`` and ``SRAMArray`` to hold tags/state and data, respectively.
Constraining yourself to this interface will help ensure your cache controller design is realistic.

The ``TagArray`` holds both tag and the state for each line.
There is only room for a single tag and state for each line, so you will have to consider how to implement a set-associative cache.
The ``TagArray`` takes the number of tag bits and data bits as parameters.
We will check to make sure you use the correct number of tag and data bits.

The ``SRAMArray`` is a simple data storage array that only takes the size of the data (cache block) and the number of elements to store as parameters.

You will instantiate multiple tag and SRAM arrays for your set-associative cache implementation.

Implementing a set-associative cache
-----------------------------------

You are given a file ``set_assoc.cc`` which has empty functions for each function you are required to implement.
You will be modifying and turning in this file and ``set_assoc.hh``.
Feel free to add new private/protected functions to the ``SetAssociativeCache``, but **DO NOT MODIFY THE PUBLIC INTERFACE**.

You implementation of the set associative cache should behave *exactly the same* as the direct-mapped cache when there is only one way.
It should also be able to be any associative up to fully-associative (unless you explain why this is not possible as described below).

You may choose to implement any replacement policy.
**However, if your replacement policy requires any state, you must store this state in the tag array!**
Note: The tag-array state is limited to 32 bits per line.
If this constrains your associativity, be sure to include assertions in your code and explain this in the README file (see below).

You **must** use the given TagArray and DataArray objects to store your tags and data.

Implementing a non-blocking cache
---------------------------------

Your non-blocking cache should inherit from you set associative implementation as it must both non-blocking and set-associative.
Much of the code will be shared between the set-associative and the non-blocking cache.

We discussed non-blocking caches in class.
To implement a non-blocking cache, you must track the outstanding requests from the cache.
You may choose any software implementation of this you would like.
However, you will be expected to explain how your software implementation would translate to hardware in interactive grading.



Grading/Testing
===============

You should expect that we will test the following things:
- Changing the size, associativity, and number of MSRHs of the cache.
- Changing the line size of the memory.
- Sending requests of any power-of-two size to the cache from the processor that are less than or equal to the line size.
- Changing the address width.

Note, we may use different implementations of ``TagArray``, ``SRAMArray``, ``Memory``, and ``Processor`` when testing.
The only thing you can rely on is the interfaces in the header files.
The underlying implementation may change.

You should perform simulations with your code to answer the following questions.
Include the answers to these questions in your README when submitting your assignment.
**You should include specific data that back up your answers**.
- How can you determine the hit ratio of the cache?
- How does increasing the set-associativity from direct-mapped to 8-way set-associative affect the hit ratio?
- How can you determine the performance of the system?
- How does increasing the set-associativity from direct-mapped to 8-way set-associative affect the performance of the system?
- How does increasing the number of MSHRs affect the performance of the system?

Think about the following questions for interactive grading:
- How does my software implementation compare to a real hardware implementation?
- What parts of the hardware does your code model explicitly and which parts of the hardware design are not modeled?

+-----------------------+-----------------------+------------------------------+
| **Name**              | **Percentage of Lab   | **Description**              |
|                       | Grade**               |                              |
+=======================+=======================+==============================+
| **set_assoc.cc**      | 25%                   |Implementation of the         |
|                       |                       |set-associative cache. This   |
|                       |                       |includes the correct number of|
|                       |                       |tag/index bits, etc.          |
+-----------------------+-----------------------+------------------------------+
| **non_blocking.cc**   | 25%                   |Implementation of the         |
|                       |                       |non-blocking cache. This      |
|                       |                       |includes the correct          |
|                       |                       |implementation of MSHRs and   |
|                       |                       |per-line state.               |
+-----------------------+-----------------------+------------------------------+
| **Interactive         | 50%                   |Your answers to the questions |
| Grading**             |                       |will be evaluated during      |
|                       |                       |interactive grading. 25% of   |
|                       |                       |your overall grade will come  |
|                       |                       |from the answers to these     |
|                       |                       |questions and the other 25%   |
|                       |                       |from your answers to the      |
|                       |                       |interactive grading questions.|
+-----------------------+-----------------------+------------------------------+

Submission
==========

**Warning**: read the submission instructions carefully. Failure to
adhere to the instructions will result in a loss of points.

-  Upload to Canvas the zip/tar/tgz of your ``set_assoc.cc``, ``set_assoc.hh``, ``non_blocking.cc`` *and* ``non_blocking.hh`` file along with a README file that contains:

   -  The names of you and your partner.

   -  If there are any constraints on the associativity of your cache, explain what they are and why.

   -  Your answers to the following questions:
       - How can you determine the hit ratio of the cache?
       - How does increasing the set-associativity from direct-mapped to 8-way set-associative affect the hit ratio?
       - How can you determine the performance of the system?
       - How does increasing the set-associativity from direct-mapped to 8-way set-associative affect the performance of the system?
       - How does increasing the number of MSHRs affect the performance of the system?

   -  Any difficulties you had.

   -  Anything that doesn’t work correctly and why.

   -  Anything you feel that the graders should know.

-  **Copy and paste the README into the comment box when you are
   submitting your assignment**, as well.

-  Only one partner should submit the assignment.

-  You may submit your assignment as many times as you want.


Hints
=====

- We discussed the state machines for the caches in class. Use these ideas when implementing your cache models.

- Use the DPRINT macro in ``util.hh`` for debugging. This allows you to insert extra debugging print statements that are easily turned off (see the makefile).

- Using git may prove useful for keeping history in case you need go back. In that case however, make sure you commit at reasonable times with reasonable messages :)

- If you find a bug, submit a pull request on github! You'll get 5pts extra credit on the assignment per PR that I accept!
