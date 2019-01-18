---
authors: Jason Lowe-Power, Filipe Eduardo Borges
title: ECS 154B Lab 2, Winter 2019
---

# ECS 154B Lab 2, Winter 2019

**Due by 12:00 AM on January 21, 2019**

*Turn in via Gradescope*. [See below for details.](#Submission)

# Table of Contents

* [Introduction](#introduction)

# Introduction

![Cute Dino](../dino-resources/dino-128.png)

In the last assignemnt you implemented the ALU control and incorporated the ALU Control into the DINO CPU to test some baremetal R-type RISC-V instructions.
In this assignement you will implement the branch-control and the main control unit.
After implementing the individual components and successfully passing all individual component tests, you will combine these along with the other CPU components to complete the single-cycle DINO CPU.

The simple in-order CPU design is based closely on the CPU model in Patterson and Hennessey's Computer Organization and Design.

This is the first time we have used this set of assignments, so there may be mistakes.
To offset this, we will be offering a variety of ways to get extra credit.
See [the extra credit page](../extra-credit.md) for an up-to-date list of ways to get extra credit.

## How this assignment is written

The goal of this assignment is to implement a single-cycle RISC-V CPU which can execute all of the RISC-V integer instructions.
The rest of this assignment, [Part I](#part-i-r-type) through [Part X](#part-x-full-applications), you will implement all of the RISC-V instructions step by step.
If you prefer, you can simply skip to the end and implement all of the instructions at once and then run all of the tests for this assignment (`sbt:dinocpu> test`).

We are making one major constraint on how you are implementing your CPU.
**You cannot modify the I/O for any module**.
We will be testing your control unit with our data path and our data path with your control unit.
Therefore, you **must keep the exact same I/O**.

Below, is a diagram of the DINO CPU.
This diagram shows all of the data path, but does not have the control path wired, yet.
The control path isn't wired mostly to make the diagram easier to read and partly for you to have to think about where the wires go.
Each mux specifies the the selection value for which wire is selected to go on the output.
Be sure to create your muxes in the same way so we can test your control unit!

## Goals

- Learn how to implement a control and data path in a single cycle CPU.
- Learn how different RISC-V instructions interact in the control and data path of a single cycle CPU.


# Control unit overview

In this part you will be implementing the main control unit in the CPU design.
The control unit which has the instruction as an input, is ued to determine how to set the control lines for the functional units and the the multiplexers.

It takes a single input which is the 7-bit `opcode` and generates 9 control signals as output.

```
 branch	:  true if branch or jal and update PC with immediate
 memread: true if we should read memory
 toreg	: if writing ALU result, 1 if writing memory data, 2 if writing pc+4
 add	: true if the ALU should add the results
 memwrite: write the memory
 regwrite: write the register file
 immediate: true if use the immediate value
 alusrc1: 0 is Read data 1, 1 is zero, 2 is PC
 jump	: 0 no jump, 2 jump, 3 jump and link register
```

The following table specifies the `opcode` format and the control signals to be generated for a couple of example instruction types.

|---------|-------------|--------|---------|-------|--------|----------|-----------|----------|---------|------|
| opcode  |opcode format| branch | memread | toreg |   add  | memwrite | immediate | regwrite | alusrc1 | jump |
|---------|-------------|--------|---------|-------|--------|----------|-----------|----------|---------|------|
|    -    |   default   | false  |  false  |   3   |  false |  false   |   false   |   false  |    0    |   0  |
| 0000000 |   invalid   | false  |  false  |   0   |  false |  false   |   false   |   false  |    0    |   0  |
| 0110011 |      R      | false  |  false  |   0   |  false |  false   |   false   |   true   |    0    |   0  |

We have given you the control signals for the R-type instructions.
You must fill in all of the other instructions in the table in `src/main/scala/components/control.scala`.
Notice how the third line of the table (under the `// R-type`) is an exact copy of the values in this table.

Given the input opcode, you must generate the correct control signals.
The template code from `src/main/scala/components/control.scala` is shown below.
You will fill in where it says *Your code goes here*.
```
// Control logic for the processor

package dinocpu

import chisel3._
import chisel3.util.{BitPat, ListLookup}

/**
 * Main control logic for our simple processor
 *
 * Output: branch,  true if branch or jal and update PC with immediate
 * Output: memread, true if we should read memory
 * Output: toreg, 0 if writing ALU result, 1 if writing memory data, 2 if writing pc+4
 * Output: add, true if the ALU should add the results
 * Output: memwrite, write the memory
 * Output: regwrite, write the register file
 * Output: immediate, true if use the immediate value
 * Output: alusrc1, 0 is Read data 1, 1 is zero, 2 is PC
 * Output: jump, 0 no jump, 2 jump, 3 jump and link register
 *
 * For more information, see section 4.4 of Patterson and Hennessy
 * This follows figure 4.22
 */
class Control extends Module {
  val io = IO(new Bundle {
    val opcode = Input(UInt(7.W))

    val branch = Output(Bool())
    val memread = Output(Bool())
    val toreg = Output(UInt(2.W))
    val add = Output(Bool())
    val memwrite = Output(Bool())
    val regwrite = Output(Bool())
    val immediate = Output(Bool())
    val alusrc1 = Output(UInt(2.W))
    val jump    = Output(UInt(2.W))
  })

  val signals =
    ListLookup(io.opcode,
      /*default*/           List(false.B, false.B, 3.U,   false.B, false.B,  false.B, false.B,    0.U,    0.U),
      Array(                 /*  branch,  memread, toreg, add,     memwrite, immediate, regwrite, alusrc1,  jump */
      // Invalid
      BitPat("b0000000") -> List(false.B, false.B, 0.U,   false.B, false.B,  false.B, false.B,     0.U,    0.U),
      // R-format
      BitPat("b0110011") -> List(false.B, false.B, 0.U,   false.B, false.B,  false.B, true.B,      0.U,    0.U)

      // Your code goes here (remember to make sure to have commas at the end of each line but the last)

      ) // Array
    ) // ListLookup

  io.branch := signals(0)
  io.memread := signals(1)
  io.toreg := signals(2)
  io.add := signals(3)
  io.memwrite := signals(4)
  io.immediate := signals(5)
  io.regwrite := signals(6)
  io.alusrc1 := signals(7)
  io.jump := signals(8)
}
```

In this code, you can see that the `ListLookup` looks very similar to the table above.
You will be filling in the rest of the lines of this table. 
As you work through each of the parts below, you will be adding a line to the table.
You will have one line for each type of instruction (i.e., each unique opcode that for the instructions you are implementing).

**Important: DO NOT MODIFY THE I/O.**
You do not need to modify any other code in this file other than the `signals` table!


# Part I: R-type

In the last assignment you implemented a subset of the RISC-V data path for just R-type instructions.
This did not require a control unit since there were no need for extra muxes. 
In this assignment, you will be implementing the rest of the RISC-V instructions so you will need to use the control unit.

The first step is to hook up the control unit and get the R-type instructions working again.
You shouldn't have to change much code in `cpu.scala` from the first assignment. 
All you have to do is to hook up the `opcode` to the input of the control unit.
We have already implemented the R-type control logic for you.
You can also use the appropriate signals generated from the control unit (e.g., `regwrite`) to drive your data path.

## R-type instruction details

|31    25|24  20|19 15|14     12|11  7|6       0|        |
|--------|------|-----|---------|-----|---------|--------|
|funct7  | rs2  | rs1 | funct3  | rd  | 0110011 | R-type |

Each instruction has the following effect.
`<op>` is specified by the funct3 and funct7 fields.

```
R[rd] = R[rs1] <op> R[rs2]
```



## Testing

**FILL THIS IN**

# Part II: I-type

Next, you will implement the I-type instructions.
These are mostly the same as the the R-type, except that the second data comes from the immediate value instead of the second register.

To implement the I-types, you should first extend the table in `control.scala`.
Then, you can add the appropriate muxes to the CPU (in `cpu.scala`) and wire the control signals to those muxes.
**HINT**: You only need one extra mux compared to your R-type-only design.

## I-type instruction details


|31           20|19 15|14     12|11  7|6       0|        |
|---------------|-----|---------|-----|---------|--------|
|imm            | rs1 | funct3  | rd  | 0010011 | I-type |

Each instruction has the following effect.
`<op>` is specified by the funct3 field.

```
R[rd] = R[rs1] <op> immediate
```

## Testing

**FILL THIS IN**

# Part III: load word

Now, we will implement the `lw` instruction.
Officially, this is a I-type instruction, so you shouldn't have to make too many modifications to your data path.

As with the previous parts, first, update your control unit to assert the necessary control signals for the `lw` instruction, then modify your CPU data path to add the necessary muxes and wire up your control.
For this part, you will have to think about how this instruction uses the ALU.

## `lw` instruction details


|31           20|19 15|14     12|11  7|6       0|        |
|---------------|-----|---------|-----|---------|--------|
|imm            | rs1 | 010     | rd  | 0000011 | lw     |

The instruction has the following effect.

```
R[rd] = M[R[rs1] + immediate]
```

## Testing

**FILL THIS IN**

# Part IV: U-type instructions

## `auipc` instruction details


|31           20|19 15|14     12|11  7|6       0|        |
|---------------|-----|---------|-----|---------|--------|
|imm            | rs1 | 010     | rd  | 0000011 | lw     |

The instruction has the following effect.

```
R[rd] = M[R[rs1] + immediate]
```

## `lui` instruction details


|31           20|19 15|14     12|11  7|6       0|        |
|---------------|-----|---------|-----|---------|--------|
|imm            | rs1 | 010     | rd  | 0000011 | lw     |

The instruction has the following effect.

```
R[rd] = M[R[rs1] + immediate]
```

## Testing

**FILL THIS IN**

# Part V: Store word

## `sw` instruction details


|31    25|24  20|19 15|14     12|11  7|6       0|        |
|--------|------|-----|---------|-----|---------|--------|
|imm     | rs2  | rs1 | 010     | imm | 0100011 | sw     |

The instruction has the following effect.

```
sw:  M[R[rs1] + immediate] = R[rs2]
```

## Testing

**FILL THIS IN**

# Part VI: Other memory instructions

## Memory instruction details


|31    25|24  20|19 15|14     12|11  7|6       0|        |
|--------|------|-----|---------|-----|---------|--------|
|imm     |      | rs1 | 000     | rd  | 0000011 | lb     |
|imm     |      | rs1 | 001     | rd  | 0000011 | lh     |
|imm     |      | rs1 | 010     | rd  | 0000011 | lw     |
|imm     |      | rs1 | 100     | rd  | 0000011 | lbu    |
|imm     |      | rs1 | 101     | rd  | 0000011 | lhu    |
|imm     | rs2  | rs1 | 000     | imm | 0100011 | sb     |
|imm     | rs2  | rs1 | 001     | imm | 0100011 | sh     |
|imm     | rs2  | rs1 | 010     | imm | 0100011 | sw     |

The instructions have the following effects.

```
lb:  R[rd] = sext(M[R[rs1] + immediate] & 0xff)
lh:  R[rd] = sext(M[R[rs1] + immediate] & 0xffff)
lw:  R[rd] = M[R[rs1] + immediate]
lbu: R[rd] = M[R[rs1] + immediate] & 0xff
lhu: R[rd] = M[R[rs1] + immediate] & 0xffff
sw:  M[R[rs1] + immediate] = R[rs2]
sb:  M[R[rs1] + immediate] = R[rs2] & 0xff
sh:  M[R[rs1] + immediate] = R[rs2] & 0xffff
```

## Testing

**FILL THIS IN**

# Part VII: Branch instructions

This part is a little more involved than the previous instructions.
First, you will implement the branch control unit.
Then, you will wire up the branch control unit and the other necessary muxes.


## Branch instruction details

|31                 25|24  20|19 15|14     12|11                 7|6       0|
|--------|------------|------|-----|---------|-----------|--------|---------|--------|
|imm[12] | imm[10:5]  | rs2  | rs1 | funct3  | imm[4:1]  | imm[11]|  opcode | B-type |
|--------|------------|------|-----|---------|-----------|--------|---------|--------|
|     imm[12|10:5]]   | rs2  | rs1 |   000   |     imm[4:1|11]    | 1100011 |  BEQ   |
|     imm[12|10:5]]   | rs2  | rs1 |   001   |     imm[4:1|11]    | 1100011 |  BNE   |
|     imm[12|10:5]]   | rs2  | rs1 |   100   |     imm[4:1|11]    | 1100011 |  BLT   |
|     imm[12|10:5]]   | rs2  | rs1 |   101   |     imm[4:1|11]    | 1100011 |  BGE   |
|     imm[12|10:5]]   | rs2  | rs1 |   110   |     imm[4:1|11]    | 1100011 |  BLTU  |
|     imm[12|10:5]]   | rs2  | rs1 |   111   |     imm[4:1|11]    | 1100011 |  BGEU  |

The instructions have the following effects.
The operation is given by funct3 (see above).

```
if (R[rs1] <op> R[rs2]) pc = pc + immediate
else pc = pc + 4
```

## Branch control unit

In this part you will be implementing the branch-control component in the CPU design.
The branch-control controls whether or not branches are taken.

It takes four inputs: `branch`, `funct3`, `inputx`, `inputy` and generates one output `taken`.

``` 
branch: true if we are looking at a branch
funct3: the middle three bits of the instruction (12-14). Specifies the type of branch. See RISC-V spec for details.
inputx: first value  (e.g., reg1)
inputy: second value  (e.g., reg2)
taken: true if the branch is taken.
```

Note that this is one of the main places the DINO CPU differs from the CPU implemented in the book.
Instead of using the ALU to compute whether the branch is taken or not (the zero output), we are using a dedicated branch control unit.

You must take the RISC-V ISA specification and implement the proper control to choose the right type of branch test and correctly set or reset the `taken` output if the branch test passes or fails respectively. 
You can find the specification in the following places:


This table is from the RISC-V User-level ISA Specification v2.2, page 104.
You can find the same information in Chapter 2 of the Specification, Chapter 2 of the RISC-V reader, or in the front of the Computer Organization and Design book.

Given these inputs, you must generate the correct output on the taken wire.
The template code from `src/main/scala/components/branch-control.scala` is shown below.
You will fill in where it says *Your code goes here*.

```
// Control logic for whether branches are taken or not

package dinocpu

import chisel3._
import chisel3.util._

/**
 * Controls whether or not branches are taken.
 *
 * Input:  branch, true if we are looking at a branch
 * Input:  funct3, the middle three bits of the instruction (12-14). Specifies the
 *         type of branch
 * Input:  inputx, first value (e.g., reg1)
 * Input:  inputy, second value (e.g., reg2)
 * Output: taken, true if the branch is taken.
 */
class BranchControl extends Module {
  val io = IO(new Bundle {
    val branch = Input(Bool())
    val funct3 = Input(UInt(3.W))
    val inputx = Input(UInt(32.W))
    val inputy = Input(UInt(32.W))

    val taken  = Output(Bool())
  })

// Your code goes here

  io.taken := false.B
}
```

**HINT:** Use Chisel's `switch` / `is`,  `when` / `elsewhen` / `otherwise`, or `MuxCase` syntax.
See [the Chisel getting started guide](../chisel-notes/getting-started.md) for examples.
You may also find the [Chisel cheat sheet](https://chisel.eecs.berkeley.edu/2.2.0/chisel-cheatsheet.pdf) helpful.

You can also use normal operators (e.g., `<`, `>`, `===`, `=/=`, etc.)

### Testing your branch-control unit

We have implemented some tests for your branch-control unit. The tests along with the other lab-2 tests are in `src/test/scala/labs/Lab2Test.scala`.

In this part of the assignment, you only need to run the branch-control unit tests.
To run just these tests, you can use the sbt command `testOnly`, as demonstrated below.


```
dinocpu:sbt> testOnly dinocpu.BranchControlTesterLab2
```

## Testing branches

**FILL THIS IN**

# Part VIII: jump and link

## `jal` instruction details


|31        12|11  7|6       0|        |
|------------|-----|---------|--------|
|imm         | rd  | 1101111 | jal    |

The instruction has the following effect.

```
pc = pc + imm
R[rd] = pc + 4
```

## Testing

**FILL THIS IN**

# Part IX: jump and link register

## `jalr` instruction details


|31           20|19 15|14     12|11  7|6       0|        |
|---------------|-----|---------|-----|---------|--------|
|imm            | rs1 | 000     | rd  | 1100111 | jalr   |

The instruction has the following effect.

```
pc = R[rs1] + imm
R[rd] = pc + 4
```

## Testing

**FILL THIS IN**

# Part X: Full applications

At this point, you should have a fully implemented RISC-V CPU!
In this final part of the assignment, you will run some full RISC-V applications.

## Testing

**FILL THIS IN**


# Part II: Implement the Control Unit

**The test for this part is `dinocpu.ControlTesterLab2`.**



## Testing your control unit

We have implemented some tests for your control unit. The tests along with the other lab 2 tests are in `src/test/scala/labs/Lab2Test.scala`.

In this part of the assignment, you only need to run the control unit tests.
To run just these tests, you can use the sbt command `testOnly`, as demonstrated below.

```
dinocpu:sbt> testOnly Lab2 / dinocpu.ControlTesterLab2
```

Feel free to add your own tests in `src/tests/scala`, modify the current tests, and add `print` statements in the tests.

## Draw a diagram for implementing all the instructions

You are now ready to  complete all the connections for the single-cycle DINO CPU! If you have passed all the tests so far, you can now begin connecting the control unit to the all the other components. 
Note: You will have to build on the connections you made in the earlier section and so you will need to show those connections as well, making changes if required. 

Use the same sheet you used for Part I.
Draw all of the wires and label which bits are on each wire.

We will be grading this diagram and looking for the following things:
- The correct wires.
- Every wire should contain its width in bits.
- For wires that are a subset of all of the bits, label which bits are on the wire.

Figure 4.15 from Computer Organization and Design below is an example of what we are looking for.
Notice how the instruction wire is broken into is sub-components.

![Figure 4.15](./fig-4-15.svg)

**Important**: The book shows the answer for 64-bit RISC-V (rv64i) and a slightly different CPU design.
We are creating a 32-bit RISC-V CPU (rv32i).
The book will not contain the *exact* answers to the labs, though it will be very useful.

**Hint**: You may not need to use all of the modules provided.
The only instructions left to implement are the jump and load/store instructions.


## Testing all the instuctions
To run the tests, you execute the `SingleCycleTesterLab2` suite as follows:

```
dinocpu:sbt> testOnly Lab2 / dinocpu.SingleCycleTesterLab2
```

This will load some binary applications from `src/test/resources/risc-v`.
The applications that it is running is specified in the output.

The list of applications that this suite will run can be found in the `InstTests.scala` file (`src/test/scala/cpu-tests/InstTests.scala`).
If you want more details on the syntax and how to extend this to other RISC-V binaries, ask on Piazza and we will be happy to expand this section.

If you want to run only a single application from this suite of tests, you can add a parameter to the `test` sbt task.
You can pass the option `-z` which will execute any tests that match the text given to the parameter.
You must use `--` between the parameters to the sbt task (e.g., the suite to run) and the parameters for testing.
For instance, to only run the jump and link register instruction, you would use the following:

```
sbt> testOnly Lab2 / dinocpu.SingleCycleTesterLab2 -- -z jlr
```


# Part XI: Feedback

The second page of the [blank circuit diagram](./lab1-written.pdf) discussed [above](#part-ii-draw-a-diagram-for-implementing-r-type-instructions) contains a short feedback form.
This the first time we have used these assignments, so we are soliciting feedback to improve them for future quarters.
You will submit this together with your completed circuit diagram.

Filling out the feedback is worth 10% of your grade on the assignment.
There are no wrong answers, so as long as you have completed the form, you will receive the points.
(Note: The more detailed feedback you give, the better we can improve the assignments.)

# Grading

Grading will be done automatically on Gradescope.
See [the Submission section](#Submission) for more information on how to submit to Gradescope.

|                    |     |
|--------------------|-----|
| Each instruction type  | 8% each (×10 parts=80%) |
| Full programs      | 10% |
| Feedback           | 10% |

# Submission

**Warning**: read the submission instructions carefully.
Failure to adhere to the instructions will result in a loss of points.

There are two different assignments on Gradescope that will be open for the duration of the assignment.
One of them is for the code you've written for this lab, and the other is for the [circuit diagram and feedback form](./lab1-written.pdf).

## Code portion

You will upload the two files that you changed to Gradescope on the [Lab 2 - Code](https://www.gradescope.com/courses/35106/assignments/) assignment.

- `src/main/scala/components/branchcontrol.scala`
- `src/main/scala/components/control.scala`
- `src/main/scala/single-cycle/cpu.scala`

Once uploaded, Gradescope will automatically download and run your code.
This should take less than 5 minutes.
For each part of the assignment, you will receive a grade.
If all of your tests are passing locally, they should also pass on Gradescope unless you made changes to the I/O, **which you are not allowed to do**.

Note: There is no partial credit on Gradescope.
Each part is all or nothing.
Either the test passes or it fails.

## Written portion

Submit your filled circuit diagram and feedback form on the [Lab 2 - Written](https://www.gradescope.com/courses/35106/assignments/) assignment.
**If your written portion is not legible because of uploading problems, you will not receive any points.**
Check your feedback from lab 1 to make sure you uploaded your written portion correctly.

Gradescope also provides a great overview of how to upload paper assignments [in their help section](https://www.gradescope.com/help#help-center-item-student-scanning).
Using an actual scanner (either on campus through the computer labs or your own) will give the best quality, but your phone will also work as long as you're careful in taking the pictures.

## Academic misconduct reminder

You are to work on this project **individually**.
You may discuss *high level concepts* with one another (e.g., talking about the diagram), but all work must be completed on your own, including drawing the diagram.

**Remember, DO NOT POST YOUR CODE PUBLICLY ON GITHUB!**
Any code found on GitHub that is not the base template you are given will be reported to SJA.
If you want to sidestep this problem entirely, don't create a public fork and instead create a private repository to store your work.
GitHub now allows everybody to create unlimited private repositories for up to three collaborators, and you shouldn't have *any* collaborators for your code in this class.

## Checklist

- [ ] You have commented out or removed any extra debug statements.
- [ ] You have uploaded three files: `cpu.scala`, `control.scala`, and `branchcontrol.scala`.
- [ ] You have filled in and uploaded the feedback form.

# Hints

- Start early! There is a steep learning curve for Chisel, so start early and ask questions on Piazza and in discussion.
- If you need help, come to office hours for the TAs, or post your questions on Piazza.

## Printf debugging

This is the best style of debugging for this assignment.

- Use printf when you want to print *during the simulation*.
  - Note: this will print *at the end of the cycle* so you'll see the values on the wires after the cycle has passed.
  - Use `printf(p"This is my text with a $var\n")` to print Chisel variables. Notice the "p" before the quote!
  - You can also put any Scala statement in the print statement (e.g., `printf(p"Output: ${io.output})`).
  - Use `println` to print during compilation in the Chisel code or during test execution in the test code. This is mostly like Java's `println`.
  - If you want to use Scala variables in the print statement, prepend the statement with an 's'. For example, `println(s"This is my cool variable: $variable")` or `println("Some math: 5 + 5 = ${5+5}")`.

## Common errors

Note: We will populate this with questions from Piazza when it looks like many people are running into the same issue.

### VBoxManage: error: Details: code NS_ERROR_FAILURE...

```
There was an error while executing `VBoxManage`, a CLI used by Vagrant
for controlling VirtualBox. The command and stderr is shown below.

Command: ["startvm", "...", "--type", "headless"]

Stderr: VBoxManage: error: The virtual machine 'vm-singularity_default_...' has terminated unexpectedly during startup with exit code 1 (0x1)

VBoxManage: error: Details: code NS_ERROR_FAILURE (0x80004005), component MachineWrap, interface IMachine
```

This is a Vagrant and/or VirtualBox issue, not with Singularity or Chisel.
You'll most likely see this because you ran the following command in the Sylabs Singularity installation guide:

```
export VM=sylabs/singularity-ubuntu-bionic64 ...
```

This is the wrong image!
To fix this, go back to the folder you created during the tutorial and run `vagrant destroy`.
Then run the following:

```
cd dinocpu
vagrant up
vagrant ssh
```

The Vagrantfile in the `dinocpu` folder is correctly initialized, so doing this should just work.

### FATAL: container creation failed: mount error...

If you see the following error, it is likely because you ran out of disk space on the CSIF machine.

```
FATAL:   container creation failed: mount error: can't mount image /proc/self/fd/8: failed to mount squashfs filesystem: invalid argument
```

You can find out how much space you're using with the `fquota` command as shown below.
`fquota` is a script only on the CSIF machines to help you find the largest directories, so you can clean up your files.

```
jlp@ad3.ucdavis.edu@pc12:~$ fquota
QUOTA SUMMARY   -- Disk quotas for user jlp@ad3.ucdavis.edu (uid 832205):
Currently using 1717 MB of 2048 MB in your quota.
```

If you clear your Singularity cache (`.singularity/cache/`), you can free up some disk space, but the Singularity image will be re-downloaded the next time you run `singularity`.

### [warn] No sbt.version set in project/build.properties...

```
WARNING: Authentication token file not found : Only pulls of public images will succeed
[warn] No sbt.version set in project/build.properties, base directory: ...
[info] Set current project to ... (in build file: ...)
>
```

This occurs when you try to run Singularity outside of the `dinocpu` directory.
Run the `singularity run` command within the `dinocpu` directory.

### Cannot find cpu.registers.regs_5 in symbol table

```
sbt:dinocpu> testOnly dinocpu.SingleCycleAddTesterLab1
[info] Compiling 1 Scala source to /home/jlp/Code/dinocpu/target/scala-2.12/classes ...
[warn] there were 18 feature warnings; re-run with -feature for details
[warn] one warning found
[info] Done compiling.
[info] [0.001] Elaborating design...
[info] [0.148] Done elaborating.
[info] SingleCycleAddTesterLab1:
[info] Single Cycle CPU
[info] - should run add test add1 *** FAILED ***
[info]   firrtl.passes.CheckInitialization$RefNotInitializedException: @[cpu.scala 22:26] : [module SingleCycleCPU]  Reference registers is not fully initialized.
[info]    : registers.io.wen <= VOID
[info]   at firrtl.passes.CheckInitialization$.$anonfun$run$6(CheckInitialization.scala:79)
[info]   at firrtl.passes.CheckInitialization$.$anonfun$run$6$adapted(CheckInitialization.scala:74)
[info]   at scala.collection.TraversableLike$WithFilter.$anonfun$foreach$1(TraversableLike.scala:789)
[info]   at scala.collection.mutable.HashMap.$anonfun$foreach$1(HashMap.scala:138)
[info]   at scala.collection.mutable.HashTable.foreachEntry(HashTable.scala:236)
[info]   at scala.collection.mutable.HashTable.foreachEntry$(HashTable.scala:229)
[info]   at scala.collection.mutable.HashMap.foreachEntry(HashMap.scala:40)
[info]   at scala.collection.mutable.HashMap.foreach(HashMap.scala:138)
[info]   at scala.collection.TraversableLike$WithFilter.foreach(TraversableLike.scala:788)
[info]   at firrtl.passes.CheckInitialization$.checkInitM$1(CheckInitialization.scala:74)
[info]   ...
[info] ScalaTest
[info] Run completed in 776 milliseconds.
[info] Total number of tests run: 1
[info] Suites: completed 1, aborted 0
[info] Tests: succeeded 0, failed 1, canceled 0, ignored 0, pending 0
[info] *** 1 TEST FAILED ***
[error] Failed: Total 1, Failed 1, Errors 0, Passed 0
[error] Failed tests:
[error]         dinocpu.SingleCycleAddTesterLab1
[error] (test / testOnly) sbt.TestsFailedException: Tests unsuccessful
[error] Total time: 2 s, completed Jan 8, 2019 6:49:17 PM
```

If you encounter an error saying that the simulator (Treadle) can't find some register in the symbol table, this is likely because the register file is being optimized away.
*You will see this error before you add any of your own code.*
Chisel is an optimizing compiler that checks to see if the hardware will ever be used.
If Chisel determines the hardware will never be used, it will remove the hardware.

**To fix this error**: Make sure that you have connected up the register file correctly.
More specifically, check the write enable input to the register file.

### possible cause: maybe a semicolon is missing before 'value is'?

If Chisel complains about a missing semicolon before an `is` statement it is likely that you have a nested `is`.

For instance, this is an error you may see.

```
[error] /home/jlp/dinocpu/src/main/scala/components/alucontrol.scala:40:13: value is is not a member of Unit
[error] possible cause: maybe a semicolon is missing before `value is'?
[error]           } is ("b0100000".U) {
```

Below is an example **incorrect** nested `is` statement.

```
switch (io.funct3) {
  is ("b000".U) {
    switch (io.funct7) {
      is (xxxxxxx) {
        io.operation := wwwwwwww
      } is (yyyyyyyy) {
        io.operation := zzzzzzzz
      }
    }
  }
  ...
```

You can fix this by changing the inner `switch` to a `when`.

```
switch (io.funct3) {
  is ("b000".U) {
    when (io.funct7 === xxxxxxx) { io.operation := wwwwwwww }
    otherwise { io.operation := zzzzzzzz }
  }
  ...
```
