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

# Single cycle CPU design

Below is a diagram of the single cycle DINO CPU.
This diagram includes all of the necessary data path wires and muxes.
However, it is missing the control path wires.
This figure has all of the muxes necessary, but does not show which control lines go to which mux.
**Hint**: the comments in the code for the control unit give some hints on how to wire the design.

In this assignment, you will be implementing the data path shown in the figure below, implementing the control path for the DINO CPU, and wiring up the control path.
You can extend your work from [Lab 1](../lab1.md), or you can take the updated code from [GitHub](https://github.com/jlpteaching/dinocpu/).
You will be implementing everything in the diagram in Chisel (the `cpu.scala` file only implements the R-type instructions), which includes the code for the muxes and wiring all of the components together.
You will also implement the [control unit](#control-unit-overview)) and the [branch control unit](#branch-control-unit).

![Single cycle DINO CPU without control wires](../dino-resources/single-cycle.svg)


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

```
sbt:dinocpu> testOnly dinocpu.SingleCycleRTypeTesterLab2
```

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


```
sbt:dinocpu> testOnly dinocpu.SingleCycleITypeTesterLab2
```

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


```
sbt:dinocpu> testOnly dinocpu.SingleCycleLoadTesterLab2
```

# Part IV: U-type instructions

## `auipc` instruction details


|31           20|19 15|14     12|11  7|6       0|        |
|---------------|-----|---------|-----|---------|--------|
|imm            | rs1 | 010     | rd  | 0000011 | lw     |

The instruction has the following effect.

```
R[rd] = pc + imm << 12
```

## `lui` instruction details


|31           20|19 15|14     12|11  7|6       0|        |
|---------------|-----|---------|-----|---------|--------|
|imm            | rs1 | 010     | rd  | 0000011 | lw     |

The instruction has the following effect.

```
R[rd] = imm << 12
```

## Testing

```
sbt:dinocpu> testOnly dinocpu.SingleCycleUTypeTesterLab2
```

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


```
sbt:dinocpu> testOnly dinocpu.SingleCycleStoreTesterLab2
```

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


```
sbt:dinocpu> testOnly dinocpu.SingleCycleLoadStoreTesterLab2
```

# Part VII: Branch instructions

This part is a little more involved than the previous instructions.
First, you will implement the branch control unit.
Then, you will wire up the branch control unit and the other necessary muxes.


## Branch instruction details


|imm[12] | imm[10:5]  | rs2  | rs1 | funct3  | imm[4:1]    imm[11]|  opcode | B-type |
|--------|------------|------|-----|---------|--------------------|---------|--------|
|31                 25|24  20|19 15|14     12|11                 7|6       0|        |
|     imm[12,10:5]]   | rs2  | rs1 |   000   |     imm[4:1,11]    | 1100011 |  BEQ   |
|     imm[12,10:5]]   | rs2  | rs1 |   001   |     imm[4:1,11]    | 1100011 |  BNE   |
|     imm[12,10:5]]   | rs2  | rs1 |   100   |     imm[4:1,11]    | 1100011 |  BLT   |
|     imm[12,10:5]]   | rs2  | rs1 |   101   |     imm[4:1,11]    | 1100011 |  BGE   |
|     imm[12,10:5]]   | rs2  | rs1 |   110   |     imm[4:1,11]    | 1100011 |  BLTU  |
|     imm[12,10:5]]   | rs2  | rs1 |   111   |     imm[4:1,11]    | 1100011 |  BGEU  |

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

## Implementing branch instructions

Next, you need to wire the branch control unit into the data path.
You can follow the diagram given in [Single cycle CPU design](#Single-cycle-CPU-design).
Note that the diagram does not specify what to do with the `taken` result from the branch control unit.
You must add the required logic to drive the correct mux output based on this `taken` output.

## Testing branches

```
sbt:dinocpu> testOnly dinocpu.SingleCycleBranchTesterLab2
```

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


```
sbt:dinocpu> testOnly dinocpu.SingleCycleJALTesterLab2
```

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


```
sbt:dinocpu> testOnly dinocpu.SingleCycleJALRTesterLab2
```

# Part X: Full applications

At this point, you should have a fully implemented RISC-V CPU!
In this final part of the assignment, you will run some full RISC-V applications.

We have provided four applications for you.

- `fibonacci` which computes the nth Fibonacci number. The initial value of t1 contains the Fibonacci number to compute and after computing the value is found in t0.
- `naturalsum`
- `multiplier`
- `divider`

If you have passed all of the above tests, your CPU should execute these applications with no issues!
If you do not pass the test, you may need to dig into the debug output of the test.

## Testing

You can run all of the applications at once with the following test.

```
sbt:dinocpu> testOnly dinocpu.SingleCycleApplicationsTesterLab2
```

To run a single application, you can use the following command:


```
sbt:dinocpu> testOnly dinocpu.SingleCycleApplicationsTesterLab2 -- -z <binary name>
```

# Feedback

This time, instead of uploading a paper version to Gradescope, you will give feedback via a Google form.
Note that the assignment will be out of 90 points and the last 10 points from the feedback will appear in Canvas sometime later.

<Link to google form here>

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

## Feedback form

<put link here>

## Academic misconduct reminder

You are to work on this project **individually**.
You may discuss *high level concepts* with one another (e.g., talking about the diagram), but all work must be completed on your own.

**Remember, DO NOT POST YOUR CODE PUBLICLY ON GITHUB!**
Any code found on GitHub that is not the base template you are given will be reported to SJA.
If you want to sidestep this problem entirely, don't create a public fork and instead create a private repository to store your work.
GitHub now allows everybody to create unlimited private repositories for up to three collaborators, and you shouldn't have *any* collaborators for your code in this class.

## Checklist

- [ ] You have commented out or removed any extra debug statements.
- [ ] You have uploaded three files: `cpu.scala`, `control.scala`, and `branchcontrol.scala`.
- [ ] You have filled out the [feedback form]().

# Hints

- Start early! There is a steep learning curve for Chisel, so start early and ask questions on Piazza and in discussion.
- If you need help, come to office hours for the TAs, or post your questions on Piazza.

## Common errors

See the [first lab](../lab1/lab1.md#common-errors) for more common errors.

## Printf debugging

This is the best style of debugging for this assignment.

- Use printf when you want to print *during the simulation*.
  - Note: this will print *at the end of the cycle* so you'll see the values on the wires after the cycle has passed.
  - Use `printf(p"This is my text with a $var\n")` to print Chisel variables. Notice the "p" before the quote!
  - You can also put any Scala statement in the print statement (e.g., `printf(p"Output: ${io.output})`).
  - Use `println` to print during compilation in the Chisel code or during test execution in the test code. This is mostly like Java's `println`.
  - If you want to use Scala variables in the print statement, prepend the statement with an 's'. For example, `println(s"This is my cool variable: $variable")` or `println("Some math: 5 + 5 = ${5+5}")`.

