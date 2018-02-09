**ECS 154B Lab 3, Winter 2018**

**Due by 9:00 AM on Feb 26, 2018**

**Via Canvas**

Objectives
==========

-  Build and test a pipelined MIPS CPU that implements a subset of the
   MIPS instruction set.

-  Handle hazards through forwarding and stalling.

Description
===========

In this lab, you will use Logisim to design and test a pipelined MIPS
CPU that implements a subset of the MIPS instruction set, along with
data hazard resolution. Make sure to use the given circuit for this
assignment, as the Register File included implements internal
forwarding, while previous versions do not.

Remember that you are implementing MIPS instructions, and therefore should base
your structures on the MIPS architecture definitions, unless otherwise stated
in this assignment.

** **DO NOT CHANGE THE GIVEN SUBCIRCUITS IN ANY WAY. DOING SO WILL LEAD TO AN
AUTOMATIC ZERO.** **

Details
=======

Your CPU must implement all instructions from Lab 2, and a few more:

-  Data instructions:
   ``ADD, ADDI, AND, ANDI, OR, ORI, SLL, SLT, SRL, SUB, XOR``

-  Memory access instructions: ``LW, SW``

-  Control flow instructions: ``BEQ, J, JAL, JR``

``SLL`` and ``SRL`` are new instructions you need to implement.

The control signals for the ALU are mostly identical to Lab 2, and are
reposted here:

+-----------+-------------+-------------+-------------+
| Operation | **ALUCtl2** | **ALUCtl1** | **ALUCtl0** |
+===========+=============+=============+=============+
| ``AND``   | 0           | 0           | 0           |
+-----------+-------------+-------------+-------------+
| ``ADD``   | 0           | 0           | 1           |
+-----------+-------------+-------------+-------------+
| ``OR``    | 0           | 1           | 0           |
+-----------+-------------+-------------+-------------+
| ``SUB``   | 0           | 1           | 1           |
+-----------+-------------+-------------+-------------+
| ``SLT``   | 1           | 0           | 0           |
+-----------+-------------+-------------+-------------+
| ``XOR``   | 1           | 0           | 1           |
+-----------+-------------+-------------+-------------+
| ``SRL``   | 1           | 1           | 0           |
+-----------+-------------+-------------+-------------+
| ``SLL``   | 1           | 1           | 1           |
+-----------+-------------+-------------+-------------+

Your CPU should not have any branch delay slots, and should use a branch
not taken strategy for branch prediction. You may implement your control
signals using any method you prefer. You can use combinational logic,
microcode, or a combination of the two.

Forwarding
==========

The 5th edition of *Computer Organization and Design: The
Hardware/Software Interface* contains an error in the forwarding logic,
as do the previous editions of the book. On page 311 of the 5th edition,
the last blue line of the first piece of pseudocode should read:

    ``and (EX/MEM.RegisterRd = ID/EX.RegisterRs))``

Similarly, the last blue line of the second piece of pseudocode should
read:

    ``and (EX/MEM.RegisterRd = ID/EX.RegisterRt))``

The parts in blue are actually just the EX hazards from page 308, so the
blue portion of the first hazard on page 311 can be replaced with
``and not(ForwardA = 10)``, and the blue portion of the second hazard
can be replaced with ``and not(ForwardB = 10)``.

Hazards
=======

As you have learned in lecture, pipelining a CPU introduces the
possibilities of hazards. Your CPU must be able to handle **all
possible** hazards. Your CPU must use forwarding where possible, and
resort to stalling only where necessary. Below is a subset of the
possible hazards you may encounter. This means that, while all possible
hazards may not be listed here, your CPU must still be able to handle
all possible hazards.

#. **Read After Write** (RAW) hazards. Your CPU must perform forwarding
   on both ALU inputs to prevent Read After Write hazards. Your CPU must
   handle the hazards in the following code segments without stalling.

   +------------------+-------------------+-------------------+------------------+
   |``ADD $4, $5, $6``|``ADD $4, $5, $6`` |``ADD $4, $5, $6`` |``ADD $4, $5, $6``|
   |                  |                   |                   |                  |
   +------------------+-------------------+-------------------+------------------+
   |``ADD $7, $4, $4``|``ADD $8, $9, $10``|``ADD $8, $9, $10``|``LW $8, 0($4)``  |
   |                  |                   |                   |                  |
   +------------------+-------------------+-------------------+------------------+
   |                  |``ADD $7, $4, $4`` |``ADD $7, $4, $8`` |                  |
   |                  |                   |                   |                  |
   +------------------+-------------------+-------------------+------------------+

#. **Load Use** hazards. Your CPU must handle load-use hazards through
   stalling and forwarding. You may only stall when necessary.

   +---------------------+---------------------+
   | ``LW $8, 0($4)``    | ``LW $8, 0($4)``    |
   +=====================+=====================+
   | ``ADD $10, $9, $8`` | ``ADD $4, $5, $6``  |
   +---------------------+---------------------+
   |                     | ``ADD $10, $9, $8`` |
   +---------------------+---------------------+

#. **Store Word** (``SW``) hazards. Your CPU must handle all Read After
   Write hazards associated with ``SW`` using forwarding. You may need
   to stall in certain cases, as well.

   +--------------------+-------------------+-------------------+
   | ``ADD $4, $5, $6`` | ``LW $4, 0($0)``  | ``LW $4, 0($0)``  |
   +====================+===================+===================+
   | ``SW $4, 0($4)``   | ``SW $4, 10($0)`` | ``SW $5, 10($4)`` |
   +--------------------+-------------------+-------------------+

#. **Control Flow** hazards. Read After Write hazards can also occur
   with the ``BEQ`` and ``JR`` instructions.

   The following hazards must be solved with forwarding.

   +-----------------+-----------------+-----------------+-------------------+
   | ``ADD $4, $5,   | ``ADD $4, $5,   |``LW $10, 0($0)``|``LW $10, 0($0)``  |
   | $6``            | $6``            |                 |                   |
   +-----------------+-----------------+-----------------+-------------------+
   | ``ADD $8, $9,   | ``ADD $8, $9,   | ``ADD $4, $5,   |``ADD $4, $5, $6`` |
   | $10``           | $10``           | $6``            |                   |
   +-----------------+-----------------+-----------------+-------------------+
   | ``BEQ $0, $4,   | ``JR $4``       | ``ADD $8, $9,   |``ADD $8, $9, $10``|
   | BranchAddr``    |                 | $10``           |                   |
   +-----------------+-----------------+-----------------+-------------------+
   |                 |                 | ``BEQ $0, $10,  | ``JR $10``        |
   |                 |                 | BranchAddr``    |                   |
   +-----------------+-----------------+-----------------+-------------------+


   The following hazards should be resolved with stalls.

   +----------------------------+--------------------+-----------------------------+
   | ``ADD $4, $5, $6``         | ``ADD $4, $5, $6`` | ``LW $10, 0($0)``           |
   +----------------------------+--------------------+-----------------------------+
   | ``BEQ $0, $4, BranchAddr`` | ``JR $4``          | ``ADD $4, $5, $6``          |
   +----------------------------+--------------------+-----------------------------+
   |                            |                    | ``BEQ $0, $10, BranchAddr`` |
   +----------------------------+--------------------+-----------------------------+

   +--------------------+-----------------------------+-------------------+
   | ``LW $10, 0($0)``  | ``LW $10, 0($0)``           | ``LW $10, 0($0)`` |
   +--------------------+-----------------------------+-------------------+
   | ``ADD $4, $5, $6`` | ``BEQ $0, $10, BranchAddr`` | ``JR $10``        |
   +--------------------+-----------------------------+-------------------+
   | ``JR $10``         |                             |                   |
   +--------------------+-----------------------------+-------------------+

Branch Prediction
=================

In order to reduce the number of stall cycles in our CPU, we will be
using a branch not taken prediction strategy. This means that, if a
branch is taken, we will need to provide hardware to squash the
incorrectly predicted instructions. For example:

+----------------------------+------------------------------------+
| ``BEQ $0, $0, BranchAddr`` |                                    |
+============================+====================================+
| ``ADD $1, $1, $1``         | This instruction must be squashed. |
+----------------------------+------------------------------------+

The number of instructions that must be squashed is dependent on where
in the pipeline you evaluate your branch condition. Jump instructions
can be viewed as branches that are always taken and therefore are able
to have their “branch” conditions evaluated in the Decode stage.

Grading
=======

Your implementation will be tested and graded as follows:

+-----------------------+-----------------------+-----------------------+
| **Name**              | **Percentage of Lab   | **Description**       |
|                       | Grade**               |                       |
+=======================+=======================+=======================+
| **basic.mps**         | 15%                   | A basic test of your  |
|                       |                       | pipelined CPU. No     |
|                       |                       | forwarding or         |
|                       |                       | stalling is required. |
|                       |                       | Contains no control   |
|                       |                       | flow instructions.    |
+-----------------------+-----------------------+-----------------------+
| **forwarding.mps**    | 15%                   | A test of your        |
|                       |                       | forwarding logic. No  |
|                       |                       | stalling is needed.   |
|                       |                       | Contains no control   |
|                       |                       | flow instructions.    |
|                       |                       | This also means that  |
|                       |                       | it does not test      |
|                       |                       | forwarding to control |
|                       |                       | flow instructions.    |
+-----------------------+-----------------------+-----------------------+
| **final.mps**         | 20%                   | Anything and          |
|                       |                       | everything possible.  |
|                       |                       | Requires both         |
|                       |                       | forwarding, stalling, |
|                       |                       | and squashing.        |
|                       |                       | Contains control flow |
|                       |                       | instructions.         |
+-----------------------+-----------------------+-----------------------+
| **Interactive         | 50%                   | Ensuring that you     |
| Grading**             |                       | understand the lab    |
|                       |                       | and pipelining, and   |
|                       |                       | that your partner did |
|                       |                       | not do everything.    |
+-----------------------+-----------------------+-----------------------+

For each test file, the grader will look at the contents of your
registers and memory to check if your CPU is performing correctly.
We will also examine your circuit to ensure that you correctly
implement your instructions as defined by the MIPS architecture and
this assignment. Partial credit is at the grader’s discretion.
**basic.mps** and **forwarding.mps** do not have any infinite loops
to terminate themselves with, so you will have to step through
those programs manually.

Submission
==========

**Warning**: read the submission instructions carefully. Failure to
adhere to the instructions will result in a loss of points.

-  Upload to Canvas the zip/tar/tgz of your .circ file along with a README
   file that contains:

   -  The names of you and your partner.

   -  Any difficulties you had.

   -  Anything that doesn’t work correctly and why.

   -  Anything you feel that the graders should know.

-  **Copy and paste the README into the comment box when you are
   submitting your assignment**, as well.

-  Only one partner should submit the assignment.

-  You may submit your assignment as many times as you want.

Hints
=====

-  The pipelined CPU diagram in the book should be used as a guide, and
   not a goal. It does not show everything you need to do to implement
   all of the instructions. Also, it is very possible to improve on
   their design.

-  Build, test, and debug in parts. Build a basic pipelined CPU first.
   After confirming that it works, add in the forwarding logic and test
   again. Finally, add in the logic to stall and squash instructions. By
   doing work in parts, you minimize the amount of time spent debugging,
   and maximize the amount of points gained if you do not finish.

-  After finishing a portion of the lab, save that implementation as a
   separate circuit so that you have something to go back to in case you
   need to restart.
