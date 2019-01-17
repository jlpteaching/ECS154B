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
      * [Using Scala, sbt, etc.](#using-scala-sbt-etc)
  * [Working with the DINO CPU code](#working-with-the-dino-cpu-code)
* [Part I: Implement the ALU Control](#part-i-implement-the-alu-control)
  * [Testing your ALU control unit](#testing-your-alu-control-unit)
* [Part II: Draw a diagram for implementing R-type instructions](#part-ii-draw-a-diagram-for-implementing-r-type-instructions)
* [Part III: Implement the ADD instruction](#part-iii-implement-the-add-instruction)
  * [Testing your ADD instruction](#testing-your-add-instruction)
* [Part IV: Implementing the rest of the R-type instructions](#part-iv-implementing-the-rest-of-the-r-type-instructions)
  * [Testing the rest of the instructions](#testing-the-rest-of-the-instructions)
* [Part V: Moving on to multiple cycles](#part-v-moving-on-to-multiple-cycles)
  * [Testing](#testing)
* [Part VI: Feedback](#part-vi-feedback)
* [Grading](#grading)
* [Submission](#submission)
  * [Code portion](#code-portion)
  * [Written portion](#written-portion)
  * [Academic misconduct reminder](#academic-misconduct-reminder)
  * [Checklist](#checklist)
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

There is a more detailed Chisel overview found under the [Chisel notes directory](../chisel-notes/overview.md).
Before diving into this assignment, you are encouraged to go through the [Chisel notes](../chisel-notes/overview.md).
You can find additional help and documentation on [Chisel's website](https://chisel.eecs.berkeley.edu/).

### Using the Singularity image/container

We have created a Singularity container image for you to use for the labs this quarter.
[Singularity](https://www.sylabs.io/singularity/) is a [container](https://linuxcontainers.org/) format similar to [Docker](https://www.docker.com/).
We cannot use Docker on the CSIF machines for security reasons.
We are using containers because the DINO CPU has a number of unique dependencies (e.g., [Chisel](https://chisel.eecs.berkeley.edu/), [FIRRTL](https://bar.eecs.berkeley.edu/projects/firrtl.html), [sbt](https://www.scala-sbt.org/), [Scala](https://www.scala-lang.org/), [Java](https://www.java.com/en/), and many others).
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
If this happens, you can remove the Singularity cache to free up space.

To remove the Singularity cache, you can run the following command.

```
rm -r ~/.singularity/cache
```

To find out how much space the Singularity containers are using, you can use `du` (disk usage):

```
du -sh ~/.singularity/cache
```

You can also download the images to `/tmp`, if you do not have space in your user directory.
Let us know if you would like more details on this method via Piazza.

#### Using your own machine

Details on how to install Singularity on your own machine can be found on the [Singularity website](https://www.sylabs.io/guides/3.0/user-guide/installation.html).
It's easiest to install it on Linux, but there are also directions for installing on Windows and MacOS.
On Windows and MacOS, you will have to run a Linux virtual machine to work with the Singularity containers.
**IMPORTANT: If you are using the installation directions for Windows or Mac, make sure to use the version 3.0 Vagrant box!**

For Linux, I suggest using the provided packages, not building from source.
Details are available [here](https://www.sylabs.io/guides/3.0/user-guide/installation.html#install-the-debian-ubuntu-package-using-apt).
**Be sure to use version 3 of Singularity, as it's the only version that supports the Singularity library!**

For Windows and Mac, you can follow [these instructions from Sylabs](https://www.sylabs.io/guides/3.0/user-guide/installation.html#install-on-windows-or-mac), **but read below first**.

We've made a couple of changes to make things easier.
There is a Vagrantfile included in the DINO CPU repository for you to use.
Thus, the steps are as follows:

On Windows:
1) Install [VirtualBox](https://www.virtualbox.org/wiki/Downloads).
2) Install [Vagrant](https://www.vagrantup.com/downloads.html).

On Mac:
1) Install Homebrew:
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
2) Install VirtualBox and Vagrant:
```
brew cask install virtualbox && \
    brew cask install vagrant && \
    brew cask install vagrant-manager
```
3) **Do not follow the directions to create the Singularity Vagrant Box on sylabs.io.** Instead, simply run the following *in the `dinocpu` directory*:
```
vagrant up
vagrant ssh
```

The first line, `vagrant up`, starts the virtual machine.
You may have to run this whenever you restart your computer or you kill your running virtual machine.
(See the [Vagrant documentation](https://www.vagrantup.com/docs/) for more information.)
The second line, `vagrant ssh`, starts an SSH session from your host to the running virtual machine.
In this SSH session, when you're running on the virtual machine, you will be able to use the `singularity` command.

Thus, after running `vagrant ssh`, you can then follow the directions below in the [Using Scala, sbt, etc. section](#using-scala-sbt-etc).
Note: If you use your own `Vagrantfile`, you will find the contents of the current working directory on the host in `/vagrant` on the guest.
In the `Vagrantfile` in the DINO CPU repository, we have mapped the the `dinocpu` directory to `/home/vagrant/dinocpu` to make things easier.

When using Vagrant, Singularity, and sbt, the first time you run everything, it will take some time.
All of these tools automatically download things from the Internet.
The total download is on the order of a gigabyte.
Be patient while everything is getting set up.
After the first time you run everything, it should be *much quicker* since the downloaded files should be cached.

**We will only support using the provided Singularity container!**
At your own risk, you can try to install the required dependencies.
However, we will not support this.
We will give priority to all other questions on Piazza and in office hours before we help you get set up without using the Singularity container.

#### Common Vagrant problems

- On Windows, if you receive an error saying that SSH cannot establish a connection, you may need to enable virtualization in your BIOS.

### Using Scala, sbt, etc.

- How to use the sbt REPL interface
- Run tests, main, etc.

To start sbt in the REPL (Read-Eval-Print Loop), run the following code in the base DINO directory.

```
singularity run library://jlowepower/default/dinocpu
```

## Working with the DINO CPU code

You can find all of the details on how to work with the DINO CPU in the [README file](https://github.com/jlpteaching/dinocpu/README.md) and the [documentation](https://github.com/jlpteaching/dinocpu/tree/master/documentation) in the [DINO CPU repository](https://github.com/jlpteaching/dinocpu/).

You must first download the template code before you can start working on the DINO CPU.
The template code is on GitHub, so you can simply clone the repository:

```
git clone https://github.com/jlpteaching/dinocpu.git
```

Then, if you change into the newly created `dinocpu` directory, you can run the Singularity container with Chisel and start working on the assignment!

```
cd dinocpu
singularity run library://jlowepower/default/dinocpu
[Lots of output your first time.
This may also take 5-10 minutes to download all of the libraries, etc.]
...
sbt:dinocpu>
```

# Part I: Implement the ALU Control

**The test for this part is `dinocpu.ALUControlTesterLab1`.**

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

You must take the RISC-V ISA specification and implement the proper control to choose the right ALU operation.
You can find the specification in the following places:

- the first page of the Computer Organization and Design book
- on page 16 in the RISC-V reader
- [on the RISC-V website](https://riscv.org/specifications/)

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

The ALU control takes four inputs:
- `add` and `immediate`, which come from the control unit (you will implement this in the next lab)
- `funct7` and `funct3`, which come from the instruction

You can ignore the `add` and `immediate` for now, assume both are always `false`.

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
You may also find the [Chisel cheat sheet](https://chisel.eecs.berkeley.edu/2.2.0/chisel-cheatsheet.pdf) helpful.

### Testing your ALU control unit

We have implemented some tests for your ALU control unit.
The general ALU control unit tests are in `src/test/scala/components/ALUControlUnitTest.scala`.
However, these tests require you to implement the required control for not only the R-type instructions but also for I-Types and loads/stores.
Thus, there are Lab 1-specific tests in `src/test/scala/labs/Lab1Test.scala`.

To run these tests, you simply need to execute the following at the sbt command prompt:

```
dinocpu:sbt> test
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
To run just these tests, you can use the sbt command `testOnly`, as demonstrated below.

```
dinocpu:sbt> testOnly dinocpu.ALUControlTesterLab1
```

Feel free to add your own tests in `src/tests/scala`, modify the current tests, and add `print` statements in the tests.

# Part II: Draw a diagram for implementing R-type instructions

For the rest of the assignments, you will implement all of RISC-V's R-type instructions.
Since you have implemented the ALU control, there isn't much more to do except to connect the correct wires together.
However, before you start writing code, you should know what you're going to do!
The goal of this part of the assignment is to allow you to design your hardware before you start trying to describe your design in Chisel.

To get an idea of how you are going to implement this, it's a good idea to first draw your design on a piece of paper.
It's such a good idea that we're going to make it mandatory, and you'll need to turn it in as part of your assignment.
We've provided you with a [blank circuit diagram](./lab1-written.pdf).
Draw all of the wires and label which bits are on each wire.

The second page of the diagram is a feedback form.
An explanation about that is in the [Feedback section](#part-vi-feedback).

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
The above diagram shows the required hardware to implement a very small subset of the RISC-V instructions (a few R-type, lw, sw, and beq).
For this assignment, you only need to add the hardware to implement the R-type instructions.

**Hint**: You may not need to use all of the modules provided.
You only need to implement the *R-type* instructions, not all RISC-V instructions, on this lab assignment.

# Part III: Implement the ADD instruction

**The test for this part is `dinocpu.SingleCycleAddTesterLab1`.**

Now you're ready to implement your first instruction!
For this part of the assignment, you will modify the `src/main/scala/single-cycle/cpu.scala` file.
You are beginning to implement the DINO CPU!

In the `src/main/scala/single-cycle/cpu.scala` file, you will find all of the components that are shown on the [blank circuit diagram](./lab1-written.pdf).
The components are all instantiated Chisel `Module`s.

Notice that in the template code all of the IO for each module is set to `DontCare`.
This allows the Chisel code to compile, but it also means these modules are optimized away when generating the hardware.
You will be removing the `:= DontCare` as you hook up the modules in this part of the assignment.

We have given you the one part of the answer:

```
io.imem.address := pc
```

This creates a wire from the PC to the instruction memory.

![PC to inst mem](pc-to-imem.svg)

You should fill in the other wires (and instruction subsets) that are required to implement the `add` RISC-V instruction.
We will be talking in detail about RISC-V instructions and how to design a RISC-V processor during the second week's lectures, as shown on the [schedule](https://github.com/jlpteaching/ECS154B/blob/master/syllabus/schedule.csv).

**Important**: You will not need to modify anything below the `// debug / pipeline viewer` line.
This code should be kept the same for everyone.
You may add more debug code, as you are working on the assignment.
However, when you turn in your assignment, please comment out or remove your debug code before submitting.

## Testing your ADD instruction

Testing the CPU is very similar to testing your control unit [above](#testing-your-alu-control-unit).
To run the tests, you execute the `SingleCycleCPUTesterLab1` suite as follows.

```
dinocpu:sbt> testOnly dinocpu.SingleCycleAddTesterLab1
```

This runs a very simple RISC-V application that has a single instruction: `add`.
You can find the code for this program in `src/test/resources/risc-v/add1.riscv` and below:

```
  .text
  .align 2       # Make sure we're aligned to 4 bytes
  .globl _start
_start:
    add t1, zero, t0 # (reg[6] = 0 + reg[5])

    nop
    nop
    nop
    nop
    nop
_last:
```

(There are a number of `nop` instructions at the end for testing the pipelined CPU in Lab 3.
You can ignore them for now.)

When you get the correct answer, you should see the following output.

```
sbt:dinocpu> testOnly dinocpu.SingleCycleAddTesterLab1
[info] [0.001] Elaborating design...
[info] [0.164] Done elaborating.
Total FIRRTL Compile Time: 608.3 ms
Total FIRRTL Compile Time: 282.1 ms
file loaded in 0.571095804 seconds, 539 symbols, 470 statements
DASM(500333)
CYCLE=1
pc: 4
control: Bundle(opcode -> 51, branch -> 0, memread -> 0, toreg -> 0, add -> 0, memwrite -> 0, regwrite -> 1, immediate -> 0, alusrc1 -> 0, jump -> 0)
registers: Bundle(readreg1 -> 0, readreg2 -> 5, writereg -> 6, writedata -> 1234, wen -> 1, readdata1 -> 0, readdata2 -> 1234)
aluControl: Bundle(add -> 0, immediate -> 0, funct7 -> 0, funct3 -> 0, operation -> 2)
alu: Bundle(operation -> 2, inputx -> 0, inputy -> 1234, result -> 1234)
immGen: Bundle(instruction -> 5243699, sextImm -> 0)
branchCtrl: Bundle(branch -> 0, funct3 -> 0, inputx -> 0, inputy -> 1234, taken -> 0)
pcPlusFour: Bundle(inputx -> 0, inputy -> 4, result -> 4)
branchAdd: Bundle(inputx -> 0, inputy -> 0, result -> 0)
```

The test only runs for a single cycle, since you're just executing one instruction.
This shows that at the end of the cycle, the cycle count is 1 (`CYCLE=1`) and the PC is now 4 (`pc: 4`).
This also shows the I/O for every module in the CPU.
You are only concerned with a subset of the modules right now (i.e., `registers`, `aluControl`, and `alu`).

Note that the test initializes `t0` to 1234.
You can see this on line 70 in `src/test/scala/labs/Lab1Test.scala`.
This creates a `CPUTestCase` that:
- runs the `add1` program
- uses the `single-cycle` CPU
- initializes the `t0` register to 1234
- checks that `zero` is 0, `t0` is 1234, and `t1` is 1234
- doesn't initialize any memory addresses
- doesn't check any memory addresses

More information about `CPUTestCase` can be found in the code (`src/test/scala/cpu-tests/CPUTesterDriver.scala`, line 94), and in the [DINO CPU documentation](https://github.com/jlpteaching/dinocpu/blob/master/documentation/testing.md).

# Part IV: Implementing the rest of the R-type instructions

**The test for this part is `dinocpu.SingleCycleRTypeTesterLab1`.**

In this part of the lab, you will be implementing all of the other R-type RISC-V instructions.
These are all of the ALU operations in the ISA.
For each of the operations, we have included a test program that has only that one instruction.

If you have passed the `AddTest` test and you passed the `ALUControlTest`, then all of the other R-type instruction should *just work*!
Now, test them to make sure that they do!

You may need to update the wires in your CPU design to get all of the R-type instructions to work.
There are a couple of tricky ones that may cause you to re-think your design.

- `add0` tests to make sure you don't overwrite register 0 (it should always be 0 in RISC-V).
- The `sub` and `sra` instructions will stress corner cases in your ALU control unit, but you already passed those tests so it should work!
- The signed and unsigned versions of instructions are also tricky.

## Testing the rest of the instructions

Testing the CPU is very similar to testing your control unit [above](#testing-your-alu-control-unit).
To run the tests, you execute the `SingleCycleRTypeTesterLab1` suite as follows:

```
dinocpu:sbt> testOnly dinocpu.SingleCycleRTypeTesterLab1
```

This will load some binary applications from `src/test/resources/risc-v`.
The applications that it is running is specified in the output.
Below is an example of a test that failed:

```
[info] SingleCycleCPUTesterLab1:
[info] Single Cycle CPU
[info] - should run rtype add1 *** FAILED ***
...
```

This ran an **rtype** application which used the binary **add1**.
You can view the RISC-V assembly for this application in `src/test/resources/risc-v/add1.riscv`.
The list of applications that this suite will run can be found in the `InstTests.scala` file (`src/test/scala/cpu-tests/InstTests.scala`).
If you want more details on the syntax and how to extend this to other RISC-V binaries, ask on Piazza and we will be happy to expand this section.

If you want to run only a single application from this suite of tests, you can add a parameter to the `test` sbt task.
You can pass the option `-z` which will execute any tests that match the text given to the parameter.
You must use `--` between the parameters to the sbt task (e.g., the suite to run) and the parameters for testing.
For instance, to only run the subtract test, you would use the following:

```
sbt> testOnly dinocpu.SingleCycleRTypeTesterLab1 -- -z sub
```

# Part V: Moving on to multiple cycles

**The test for this part is `dinocpu.SingleCycleMultiCycleTesterLab1`.**

Now, let's try a more complicated program that executes more that one instruction.
`addfwd` is one example of this which executes 10 add instructions in a row.

There is only one minor change from [Part IV](#part-iv-implementing-the-rest-of-the-r-type-instructions) to get these programs to execute correctly.
These programs are starting to be able to do some "real" things.
For instance, `power2` computes whether the input register is a power of 2.

```
  .text
  .align 2       # Make sure we're aligned to 4 bytes
  .globl _start
_start: #checks if v is a power of 2
	#stores 1 in f if true or 0 if false
	#  t0 =v and t2 = f and t1 = 1
    sub t2, t0, t1  # t2 = v - 1
    and t2, t0, t2  # t2 = v & (v-1)
    sltu t2,t2,t1   # f = (t2 <1)
    nop
    nop
    nop
    nop
    nop
_last:
```

## Testing

To run just one test, you can use the `-z` trick from above.

```
dinocpu:sbt> testOnly dinocpu.SingleCycleMultiCycleTesterLab1 -- -z addfwd
```

# Part VI: Feedback

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
| ALU control        | 25% |
| Diagram            | 25% |
| Add                | 10% |
| Other instructions | 20% |
| Multiple cycles    | 10% |
| Feedback           | 10% |

# Submission

**Warning**: read the submission instructions carefully.
Failure to adhere to the instructions will result in a loss of points.

There are two different assignments on Gradescope that will be open for the duration of the assignment.
One of them is for the code you've written for this lab, and the other is for the [circuit diagram and feedback form](./lab1-written.pdf).

## Code portion

You will upload the two files that you changed to Gradescope on the [Lab 1 - Code](https://www.gradescope.com/courses/35106/assignments/143133) assignment.

- `src/main/scala/components/alucontrol.scala`
- `src/main/scala/single-cycle/cpu.scala`

Once uploaded, Gradescope will automatically download and run your code.
This should take less than 5 minutes.
For each part of the assignment, you will receive a grade.
If all of your tests are passing locally, they should also pass on Gradescope.

Note: There is no partial credit on Gradescope.
Each part is all or nothing.
Either the test passes or it fails.

## Written portion

Submit your filled circuit diagram and feedback form on the [Lab 1 - Written](https://www.gradescope.com/courses/35106/assignments/141816) assignment.
Make sure to upload the files the same way they were given to you:
- circuit diagram first
- feedback form second
- both in landscape orientation with the correct side up (so not upside down)

Gradescope *should* let you know what we're expecting, but we're not entirely sure for now.
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
- [ ] You have uploaded two files: `cpu.scala` and `alucontrol.scala`.
- [ ] You have filled in and uploaded the blank circuit diagram.
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

### java.lang.Exception: Problem with compilation

If you see this error, then your mistake is likely in your Chisel syntax or a type error in Chisel.

For instance, if I try to connect a signed number to an unsigned input I get the following output from Chisel.

```
class Adder extends Module {
  val io = IO(new Bundle{
    val inputx    = Input(UInt(32.W))
    val inputy    = Input(UInt(32.W))

    val result    = Output(UInt(32.W))
  })

  io.result := io.inputx + io.inputy
}
```

```
val pcPlusFour = Module(new Adder())
pcPlusFour.io.inputy := 4.S
```

The output when I try to run Chisel is:

```
[info] [0.001] Elaborating design...
[error] chisel3.internal.ChiselException: Connection between sink (chisel3.core.UInt@1b206824) and source (chisel3.core.SInt@511647f3)
failed @: Sink (chisel3.core.UInt@1b206824) and Source (chisel3.core.SInt@511647f3) have different types.
[error]         ...
[error]         at dinocpu.SingleCycleCPU.<init>(cpu.scala:33)
[error]         at dinocpu.CPUConfig.getCPU(configuration.scala:30)
[error]         at dinocpu.Top.$anonfun$cpu$1(top.scala:14)
[error]         at chisel3.core.Module$.do_apply(Module.scala:51)
[error]         at dinocpu.Top.<init>(top.scala:14)
[error]         at dinocpu.simulate$.$anonfun$build$1(simulate.scala:80)
[error]         ... (Stack trace trimmed to user code only, rerun with --full-stacktrace if you wish to see the full stack trace)
[info] SingleCycleAddTesterLab1:
[info] Single Cycle CPU
[info] - should run add test add1 *** FAILED ***
[info]   java.lang.Exception: Problem with compilation
[info]   at dinocpu.simulate$.build(simulate.scala:89)
[info]   at dinocpu.CPUTesterDriver.<init>(CPUTesterDriver.scala:24)
[info]   at dinocpu.CPUTesterDriver$.apply(CPUTesterDriver.scala:108)
[info]   at dinocpu.SingleCycleAddTesterLab1.$anonfun$new$6(Lab1Test.scala:77)
[info]   at org.scalatest.OutcomeOf.outcomeOf(OutcomeOf.scala:85)
[info]   at org.scalatest.OutcomeOf.outcomeOf$(OutcomeOf.scala:83)
[info]   at org.scalatest.OutcomeOf$.outcomeOf(OutcomeOf.scala:104)
[info]   at org.scalatest.Transformer.apply(Transformer.scala:22)
[info]   at org.scalatest.Transformer.apply(Transformer.scala:20)
[info]   at org.scalatest.FlatSpecLike$$anon$1.apply(FlatSpecLike.scala:1682)
```

The important part to notice is the following:

```
[error] chisel3.internal.ChiselException: Connection between sink (chisel3.core.UInt@1b206824) and source (chisel3.core.SInt@511647f3)
failed @: Sink (chisel3.core.UInt@1b206824) and Source (chisel3.core.SInt@511647f3) have different types.
```

This says the source and sink (input and output) types don't match.
In other words, one is signed and one is unsigned.

As a general hint, look at the *highest* error in the output, or the error that's generated *first*, not the error at the bottom.
