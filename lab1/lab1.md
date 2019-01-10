---
authors: Jason Lowe-Power
title: ECS 154B Lab 1, Winter 2019
---

# ECS 154B Lab 1, Winter 2019

**Due by 12:00 AM on January 21, 2019**

*Turn in via Gradescope*. [See below for details.](#Submission)

# Table of Contents

* [Introduction](#introduction)
  * [Goals](#goals)
  * [Chisel](#chisel)
      * [Using the Singularity image/container](#using-the-singularity-imagecontainer)
      * [Using scala, sbt, etc.](#using-scala-sbt-etc)
  * [Working with the DINO CPU code](#working-with-the-dino-cpu-code)
* [Grading](#grading)
* [Part I: Implement the ALU Control](#part-i-implement-the-alu-control)
  * [Testing your ALU control unit](#testing-your-alu-control-unit)
* [Part II: Draw a diagram for implementing R-type instructions](#part-ii-draw-a-diagram-for-implementing-r-type-instructions)
* [Part III: Implement the ADD instruction](#part-iii-implement-the-add-instruction)
  * [Testing](#testing)
  * [Debugging with the simulator](#debugging-with-the-simulator)
* [Part IV: Implementing the rest of the R-type instructions](#part-iv-implementing-the-rest-of-the-r-type-instructions)
  * [Testing](#testing-1)
  * [Debugging with the simulator](#debugging-with-the-simulator-1)
* [Part V: Moving on to multiple cycles](#part-v-moving-on-to-multiple-cycles)
  * [Testing](#testing-2)
  * [Debugging](#debugging)
* [Part VI: Feedback](#part-vi-feedback)
* [Submission](#submission)
  * [Code portion](#code-portion)
  * [Written portion and feedback](#written-portion-and-feedback)
* [Hints](#hints)
  * [Printf debugging](#printf-debugging)
  * [Common errors](#common-errors)

# Introduction

![Cute Dino](../dino-resources/dino-128.png)

In this assignment you will start implementing the DINO CPU (Davis IN-Order CPU).
This is a simple in-order CPU design based closely on the CPU model in Patterson and Hennessey's Computer Organization and Design.
Before starting on the CPU, we will give you a brief tour of [Chisel](https://chisel.eecs.berkeley.edu/), the language that we will be using to describe the hardware that implements the CPU.

Through the course of this quarter, we will be building this CPU from the ground up.
You will be provided with some template code which contains a set of interfaces between CPU components and some pre-written components.
You will combine these components together into a working processor!

This is the first time we have used this set of assignments, so there may be mistakes.
To offset this, we will be offering a variety of ways to get extra credit.
See [the extra credit page](../extra-credit.md) for an up-to-date list of ways to get extra credit.

## Goals

- Learn how to use Chisel
- Learn how to run tests and debug Chisel
- Start implementing a RISC-V CPU!

## Chisel

[Chisel](https://chisel.eecs.berkeley.edu/) is an open-source hardware construction language, developed at UC Berkeley.
You write Scala code, which is syntactically similar to Java.
Chisel can then generate low-level Verilog code, which is a hardware description language used by a variety of tools to describe how an electronic circuit works.

There is a more detailed Chisel overview found under the [chisel notes directory](../chisel-notes/overview.md).
Before diving into this assignment, you are encouraged to go through the [chisel notes](../chisel-notes/overview.md).
You can find additional help and documentation on [Chisel's](https://chisel.eecs.berkeley.edu/) website.

### Using the Singularity image/container

We have created a Singularity container image for you to use for the labs this quarter.
[Singularity](https://www.sylabs.io/singularity/) is a [container](https://linuxcontainers.org/) format similar to [Docker](https://www.docker.com/).
We cannot use Docker on the CSIF machines for security reasons.
We are using containers because the DINO CPU has a number of unique dependencies (e.g., [`chisel`](https://chisel.eecs.berkeley.edu/), [`firrtl`](https://bar.eecs.berkeley.edu/projects/firrtl.html), [`sbt`](https://www.scala-sbt.org/), [`scala]`(https://www.scala-lang.org/), [`java`](https://www.java.com/en/), and many others).
Of course, each of these dependencies requires a specific version to work correctly!
Containers allow us to give you a known-good starting point with the correct versions of all of the dependencies installed.
This also means less hassle on your end attempting to install the correct dependencies!

We may make updates to the Singularity image throughout the quarter.
We have done our best to make sure all of the labs will work with the current image, but there may be unforeseen issues.
Therefore, make sure to always use the "default" version of the image, and always use the image from the library.
Don't download the image locally, as the library version may change.
**We will announce when we push any changes to the image.**

To use the Singularity image, you can simply run the following command:

```
singularity run library://jlowepower/default/dinocpu
```

This will download the most up-to-date version of the image to your local machine (e.g., `~/.singularity/cache` on Linux machines).

The first time you run the container, it will take a while to start up.
When you execute `singularity run`, it automatically starts in `sbt`, the [scala build tool](https://www.scala-sbt.org/), which we will use for running Chisel for all of the labs.
The first time you run `sbt`, it downloads all of the dependencies to your local machine.
After the first time, it should start up much faster!

#### Using the CSIF machines

Singularity is installed on the CSIF machines.
So, if you are using one of the CSIF machines either locally or remotely, things should *just work*.
However, if you run into any problems, post on Piazza or come to office hours.

The images are relatively large files.
As of the beginning of the quarter, the image is 380 MB.
We have tried to keep the size as small as possible.
Thus, especially if we update the image throughout the quarter, you may find that the disk space on your CSIF account is full.
If this happens, you can remove the singularity cache to free up space.

To remove the singularity cache, you can run the following command.

```
rm -r ~/.singularity/cache
```

To find out how much space the singularity containers are using, you can use `du` (disk usage):

```
du -sh ~/.singularity/cache
```

You can also download the images to `/tmp`, if you do not have space in your user directory.
Let us know if you would like more details on this method via Piazza.

#### Using your own machine

Details on how to install Singularity on your own machine can be found on the [Singularity website](https://www.sylabs.io/guides/3.0/user-guide/installation.html).
It's easiest to install it on Linux, but there are also directions for installing on Windows and MacOS.
On Windows and MacOS, you will have to run a Linux virtual machine to work with the Singularity containers.
**IMPORTANT: If you are using the installation directions for Windows/Mac, make sure to use the version 3.0 vagrant box!**

For Linux, I suggest using the provided packages, not building from source.
Details are available [here](https://www.sylabs.io/guides/3.0/user-guide/installation.html#install-the-debian-ubuntu-package-using-apt).
**Be sure to use version 3 of Singularity as it's the only version that supports the Singularity library!**

For Windows/Mac you can follow [these instructions from sylabs](https://www.sylabs.io/guides/3.0/user-guide/installation.html#install-on-windows-or-mac).
We've made a couple of changes to make things easier.
There is a Vagrantfile included in the DINO CPU repository for you to use.
Thus, the steps are as follows:

On Widows:
1) Install virtualbox: https://www.virtualbox.org/wiki/Downloads
2) Install vagrant: https://www.vagrantup.com/downloads.html

On Mac:
1) Install homebrew
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
2) Install virtualbox and vagrant
```
brew cask install virtualbox && \
    brew cask install vagrant && \
    brew cask install vagrant-manager
```

3) **Do not follow the directions to create the Singularity Vagrant Box on sylabs.io.** Instead simply run the following *in the `dinocpu` directory*.
```
vagrant up
vagrant ssh
```

The first line, `vagrant up`, starts the virtual machine.
You may have to run this whenever you restart your computer or you kill your running virtual machine. (See the [Vagrant documentation](https://www.vagrantup.com/docs/) for more information.)
The second line, `vagrant ssh`, starts an ssh session from your host to the running virtual machine.
In this ssh session, when you're running on the virtual machine, you will be able to use the `singularity` command.

Thus, after running `vagrant ssh`, you can then follow the directions below in [Using scala, sbt, etc](#Using-scala,-sbt,-etc.).
Note: If you use your own `Vagrantfile`, you will find the contents of the current working directory on the host in `/vagrant` on the guest.
In the `Vagrantfile` in the DINO CPU repository, we have mapped the the dinocpu directory to `/home/vagrant/dinocpu` to make things easier.

When using vagrant, singularity, and sbt, the first time you run everything, it will take some time.
All of these tools automatically download things from the internet and the total downloaded is on the order of a gigabyte.
Be patient while everything is getting set up.
After the first time you run everything, it should be *much quicker* since the downloaded files should be cached.

**We will only support using the provided Singularity container!**
At your own risk, you can try to install the required dependencies.
However, we will not support this.
We will give priority to all other questions on Piazza and in office hours before we help you get set up without using the Singularity container.

#### Common vagrant problems

- On Windows, if you receive an error saying that ssh cannot establish a connection, you may need to enable virtualization in your BIOS.

### Using scala, sbt, etc.

- How to use the sbt repl interface
- Run tests, main, etc.

To start sbt in the REPL (Read-eval-print loop), run the following code in the base DINO directory.

```
singularity run library://jlowepower/default/dinocpu
```

## Working with the DINO CPU code

You can find all of the details on how to work with the DINO CPU in the [README file](https://github.com/jlpteaching/dinocpu/README.md) and the [documentation](https://github.com/jlpteaching/dinocpu/tree/master/documentation) in the [DINO CPU repository](https://github.com/jlpteaching/dinocpu/).

# Grading

Grading will be done on Gradescope.
See [Submission](#Submission) for more information on how to submit to Gradescope.

|                    |     |
|--------------------|-----|
| ALU control        | 25% |
| Diagram            | 25% |
| Add                | 10% |
| Other instructions | 20% |
| Multiple cycles    | 10% |
| Feedback           | 10% |

# Part I: Implement the ALU Control

**The test for this part is `dinocpu.ALUControlTesterLab1`**

In this part you will be implementing a component in the CPU design.

The ALU has already been implemented for you.
It takes three inputs: the `operation`, and two inputs, `inputx` and `inputy`.
It generates the `result` of the operation on the two inputs.

The following table details the `operation` input and which values produce which results.

|      |     |
|------|-----|
| 0000 | and |
| 0001 | or  |
| 0010 | add |
| 0011 | sub |
| 0100 | slt |
| 0101 | sltu |
| 0110 | sll |
| 0111 | srl |
| 1000 | sra |
| 1001 | xor |



You must take the RISC-V ISA specification, which you can find on the first page of the Computer Organization and Design book, on page 16 in the RISC-V reader, or [on the web](https://riscv.org/specifications/), and implement the proper control to choose the right ALU operation.


|31--25 |24--20|19--15|14--12|11--7|6--0     |  |
|-------|------|------|------|-----|---------|--|
|funct7 | rs2  | rs1  |funct3| rd  | opcode  |R-type|
|-------|------|------|------|-----|---------|--|
|0000000| rs2  | rs1  | 000  | rd  | 0110011 | ADD |
|0100000| rs2  | rs1  | 000  | rd  | 0110011 | SUB |
|0000000| rs2  | rs1  | 001  | rd  | 0110011 | SLL |
|0000000| rs2  | rs1  | 010  | rd  | 0110011 | SLT |
|0000000| rs2  | rs1  | 011  | rd  | 0110011 | SLTU |
|0000000| rs2  | rs1  | 100  | rd  | 0110011 | XOR |
|0000000| rs2  | rs1  | 101  | rd  | 0110011 | SRL |
|0100000| rs2  | rs1  | 101  | rd  | 0110011 | SRA |
|0000000| rs2  | rs1  | 110  | rd  | 0110011 | OR |
|0000000| rs2  | rs1  | 111  | rd  | 0110011 | AND |

This table is from the RISC-V User-level ISA Specification v2.2, page 104.
You can find the same information in Chapter 2 of the Specification, Chapter 2 of the RISC-V reader, or in the front of the Computer Organization and Design book.

The ALU control takes four inputs: `add` and `immediate` which come from the control unit (you will implement this in the next lab), and `funct7` and `funct3` which come from the instruction.
You can ignore the `add` and `immediate` for now, assume it is always `false`.

Given these inputs, you must generate the correct output on the operation wire.
The template code from `src/main/scala/components/alucontrol.scala` is shown below.
You will fill in where it says *Your code goes here*.

```
/**
 * The ALU control unit
 *
 * Input:  add, if true, add no matter what the other bits are
 * Input:  immediate, if true, ignore funct7 when computing the operation
 * Input:  funct7, the most significant bits of the instruction
 * Input:  funct3, the middle three bits of the instruction (12-14)
 * Output: operation, What we want the ALU to do.
 *
 * For more information, see Section 4.4 and A.5 of Patterson and Hennessy
 * This follows figure 4.12
 */
class ALUControl extends Module {
  val io = IO(new Bundle {
    val add       = Input(Bool())
    val immediate = Input(Bool())
    val funct7    = Input(UInt(7.W))
    val funct3    = Input(UInt(3.W))

    val operation = Output(UInt(4.W))
  })

  io.operation := 15.U // invalid operation

  // Your code goes here
}
```

**HINT:** Use Chisel's `switch` / `is`,  `when` / `elsewhen` / `otherwise`, or `MuxCase` syntax.
See [the Chisel getting started guide](../chisel-notes/getting-started.md) for examples.
You may also find the [Chisel Cheat sheet](https://chisel.eecs.berkeley.edu/2.2.0/chisel-cheatsheet.pdf) helpful.

### Testing your ALU control unit

We have implemented some tests for your ALU control unit.
The general ALU control unit tests are in `src/test/scala/components/ALUControlUnitTest.scala`.
However, these tests require you to implement the required control for not only the R-Type instructions but also for I-Types and loads/stores.
Thus, there are Lab1-specific tests in `src/test/scala/labs/Lab1Test.scala`.

To run these tests, you simply need to execute the following at the sbt command prompt:

```
sbt> test
```

If you try this before you implement your ALU control unit, you'll see something like the following:

```
sbt:dinocpu> test
[info] Compiling 8 Scala sources to /home/jlp/Code/chisel/darchr-dinocpu/target/scala-2.11/classes ...
[warn] there were 52 feature warnings; re-run with -feature for details
[warn] one warning found
[info] Done compiling.
[info] [0.001] Elaborating design...
[info] [0.001] Elaborating design...
[info] [0.070] Done elaborating.
[info] [0.193] Done elaborating.
Total FIRRTL Compile Time: 241.8 ms
Total FIRRTL Compile Time: 5.5 ms
End of dependency graph
Circuit state created
[info] [0.001] SEED 1546475696368
[info] [0.006] EXPECT AT 1 add wrong  io_operation got 15 expected 2 FAIL
[info] [0.006] EXPECT AT 2 sub wrong  io_operation got 15 expected 3 FAIL
[info] [0.006] EXPECT AT 3 sll wrong  io_operation got 15 expected 6 FAIL
[info] [0.006] EXPECT AT 4 slt wrong  io_operation got 15 expected 4 FAIL
...
```

This output continues for a while and somewhere in it you'll see that all of the tests failed.

```
[info] Run completed in 2 seconds, 969 milliseconds.
[info] Total number of tests run: 8
[info] Suites: completed 2, aborted 0
[info] Tests: succeeded 0, failed 8, canceled 0, ignored 0, pending 0
[info] *** 8 TESTS FAILED ***
[error] Failed: Total 8, Failed 8, Errors 0, Passed 0
[error] Failed tests:
[error]         dinocpu.ALUControlTesterLab1
[error]         dinocpu.SingleCycleCPUTesterLab1
[error] (Test / test) sbt.TestsFailedException: Tests unsuccessful
```

Some of the failures will look scary.
This is expected.
As given, the template code causes compile errors in the tests.
This is because no registers are connected to input or output, so the compiler optimizes them away!
This confuses the simulator since it is trying to compare register values.
Once you have implemented your ALU control unit, these errors will go away.

In this part of the assignment, you only need to run the ALU control unit tests.
To run just these tests, you can use the `sbt` command `testOnly`, as demonstrated below.

```
sbt> testOnly dinocpu.ALUControlTesterLab1
```

Feel free to add your own tests in `src/tests/scala`, modify the current tests, and add `print` statements in the tests.

# Part II: Draw a diagram for implementing R-type instructions

For the rest of the assignments, you will implement all of RISC-V's R-type instructions.
Since you have implemented the ALU control, there isn't much more to do except to connect the correct wires together.
However, before you start writing code, you should know what you're going to do!

To get an idea of how you are going to implement this, it's a good idea to first draw your design on a piece of paper.
It's such a good idea that we're going to make it mandatory, and you'll need to turn it in as part of your assignment.
We've provided you with a [blank circuit diagram](./lab1-written.pdf).
Draw all of the wires and label which bits are on each wire.

The second page of the diagram is a feedback form.
An explanation about that is in the [Feedback section](#part-vi-feedback).

<TODO: Add more here>

# Part III: Implement the ADD instruction

**The test for this part is `dinocpu.SingleCycleAddTesterLab1`**

Now you're ready to implement your first instruction!

## Testing

Testing the CPU is very similar to testing your control unit [above](#Testing-your-ALU-control-unit).
To run the tests, you execute the `SingleCycleCPUTesterLab1` suite as follows.

```
sbt> testOnly dinocpu.SingleCycleAddTesterLab1
```

## Debugging with the simulator

<TODO>

### Running the simulator

<TODO>

### Building your own applications

<TODO>

# Part IV: Implementing the rest of the R-type instructions

**The test for this part is `dinocpu.SingleCycleRTypeTesterLab1`**

If you have passed the `AddTest` test and you passed the `ALUControlTest`, then all of the other R-type instruction should "just work"!
Now, test them to make sure that they do!

## Testing

Testing the CPU is very similar to testing your control unit [above](#Testing-your-ALU-control-unit).
To run the tests, you execute the `SingleCycleRTypeTesterLab1` suite as follows.

```
sbt> testOnly dinocpu.SingleCycleRTypeTesterLab1
```

This will load some binary applications from `src/test/resources/risc-v`.
The applications that it is running is specified in the output.
Below is an example of a test that failed.

```
[info] SingleCycleCPUTesterLab1:
[info] Single Cycle CPU
[info] - should run rtype add1 *** FAILED ***
...
```

This ran an **rtype** application which used the binary **add1**.
You can view the RISC-V assembly for this application in `src/test/resources/risc-v/add1.riscv`
The list of applications that this suite will run can be found in the `InstTests.scala` file (`src/test/scala/cpu-tests/InstTests.scala`).
If you want more details on the syntax and how to extend this to other RISC-V binaries, ask on Piazza and we will be happy to expand this section.

If you want to run only a single application from this suite of tests, you can add a parameter to the `test` `sbt` task.
You can pass the option `-z` which will execute any tests that match the text given to the parameter.
You must use `--` between the parameters to the `sbt` task (e.g., the suite to run) and the parameters for testing.
For instance, to only run the subtract test, you would use the following:

```
sbt> testOnly dinocpu.SingleCycleRTypeTesterLab1 -- -z sub
```

**IMPORTANT**: Passing all of the tests we have provided for you does not guarantee you have implemented the ALU control or the CPU correctly!
You are **strongly encouraged** to make your own unit tests and make your own RISC-V applications to test out.

## Debugging with the simulator

You can use the same strategy as described above.
This time, you will change which binary your are executing.

# Part V: Moving on to multiple cycles

**The test for this part is `dinocpu.SingleCycleMultiCycleTesterLab1`**

Now, let's try a more complicated program that executes more that one instruction.
`addfwd` is one example of this.

## Testing

To run this test, you can use the `-z` trick from above.

```
sbt> testOnly dinocpu.SingleCycleCPUTesterLab1 -- -z addfwd
```

## Debugging

<TODO>

# Part VI: Feedback

The second page of the [blank circuit diagram](./lab1-written.pdf) discussed [above](#part-ii-draw-a-diagram-for-implementing-r-type-instructions) contains a short feedback form.
This the first time we have used these assignments, so we are soliciting feedback to improve them for future quarters.
You will submit this together with your completed circuit diagram.

Filling out the feedback is worth 10% of your grade on the assignment.
There are no wrong answers, so as long as you have completed the form, you will receive the points.
(Note: The more detailed feedback you give the better we can improve the assignments.)

# Submission

**Warning**: read the submission instructions carefully.
Failure to adhere to the instructions will result in a loss of points.

There are two different assignments on Gradescope that will be open for the duration of the assignment.
One of them is for the code you've written for this lab, and the other is for the [circuit diagram and feedback form](./lab1-written.pdf).

## Code portion

Describe how to submit the code portion to Gradescope here.
<I think we want them to upload just the files they touched (`components/alu-control.scala`, and `single-cycle/cpu.scala`). We need to figure out how to get these files in the right places.>

## Written portion

Submit your filled circuit diagram and feedback form on the (Lab 1 - Written)[https://www.gradescope.com/courses/35106/assignments/141816] assignment on Gradescope.
Make sure to upload the files the same way they were given to you: circuit diagram first, feedback form second, both in landscape orientation with the correct side up (so not upside down).
(Gradescope *should* let you know what we're expecting, but we're not entirely sure.)

Gradescope provides a great overview of how to upload paper assignments [in their help section](http://gradescope-static-assets.s3-us-west-2.amazonaws.com/help/submitting_hw_guide.pdf).
Using an actual scanner (either on campus through the computer labs or your own) will give the best quality, but your phone will also work as long as you're careful in taking the pictures.

## Academic misconduct reminder

You are to work on this project **individually**.
You may discuss *high level concepts* with one another (e.g., talking about the diagram), but all work must be completed on your own including drawing the diagram.

**Remember, DO NOT POST YOUR CODE PUBLICLY ON GITHUB!**
Any code found on GitHub that is not the base template you are given will be reported to SJA.
If you want to sidestep this problem entirely, don't create a public fork and instead create a private repository to store your work.
GitHub now allows everybody to create unlimited private repositories for up to three collaborators, and you shouldn't have *any* collaborators for your code in this class.

# Hints

- Start early! There is a steep learning curve for Chisel, so start early and ask questions on Piazza and in discussion.
- If you need help, come to office hours for the TAs, or post your questions on Piazza.

## Common errors

Note: We will populate this with questions from Piazza when it looks like many people are running into the same issue.

## Printf debugging

<TODO: Expand this>
This is the best style of debugging for this assignment.

- Use printf when you want to print *during the simulation*.
  - Note: this will print *at the end of the cycle* so you'll see the values on the wires after the cycle has passed.
  - Use `printf(p"This is my text with a $var\n")` to print Chisel variables. Notice the "p" before the quote!
  - You can also put any Scala statement in the print statement (e.g., `printf(p"Output: ${io.output})`)
  - Use `println` to print during compilation in the Chisel code or during test execution in the test code. This is mostly like Java's `println`.
  - If you want to use Scala variables in the print statement, prepend the statement with an 's'. For example, `println(s"This is my cool variable: $variable")` or `println("Some math: 5 + 5 = ${5+5}")`.

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
