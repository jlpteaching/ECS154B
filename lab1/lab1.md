---
authors: Jason Lowe-Power
title: ECS 154B Lab 1, Winter 2019
---

# ECS 154B Lab 1, Winter 2019

**Due by 12:00 AM on January 21, 2019**

**Turn in Via Gradescope** [See below for details](#Submission)

# Introduction

![Cute Dino](../dino-resources/dino-128.png)

In this assignment you will start implementing the DINO CPU (Davis IN-Order CPU).
This is a simple in-order CPU design based closely on the CPU model in Patterson and Hennessey's Computer Organization and Design.
Before starting on the CPU, we will give you a brief tour of [Chisel](https://chisel.eecs.berkeley.edu/) the language that we will be using to describe the hardware that implements the CPU.

Through the course of this quarter, we will be building this CPU from the ground up.
You will be provided with some template code which contains a set of interfaces between CPU components and some pre-written components.
You will combine these components together into a working processor!

This is the first time we have used the assignments, so there may be mistakes.
To offset this, we will be offering a variety of ways to get extra credit.
See [the extra credit page](../extra-credit.md) for an up to date list of ways to get extra credit.

## Goals

- Learn how to use Chisel
- Learn how to run tests and debug Chisel
- Start implementing a RISC-V CPU!

## Chisel

TO DO FILL THIS IN.
Explain some about chisel and where to get resources for it

### Using the CSIF machines

- Using singularity.
- Explain where to download

### Using your own machine

- Using singularity
- Other options (note: these will not be supported!)

### Using scala, sbt, etc.

- How to use the sbt repl interface
- Run tests, main, etc.

To start sbt in the REPL (Read-eval-print loop), run the following code in the base DINO directory.

```
singularity run library://jlowepower/default/dinocpu
```

## Working with the DINO CPU code

### Overview of code

The `src/` directory:

- `main/scala/`
  - `components/`: This contains a number of components that are needed to implement a CPU. You will be filling in some missing pieces to these components in this lab. You can also all of the interfaces between components defined in this file.
  - `five-cycle/`: This is the code for the five cycle CPU. Right now, this is just an empty template. You will implement this in Lab 3.
  - `pipelined/`: This is the code for the pipelined CPU. Right now, this is just an empty template. You will implement this in Lab 4.
  - `single-cycle/`: This is the code for the single cycle CPU. Right now, this is just an empty template. You will implement this in Lab 2.
  - `configuration.scala`: Contains a simple class to configure the CPU. **Do not modify**
  - `elaborate.scala`: Contains a main function to output FIRRTL- and Verilog-based versions of the CPU design. You can use this file by executing `runMain CODCPU.elaborate` in sbt. More details below. **Do not modify**
  - `simulate.scala`: Contains a main function to simulate your CPU design. This simulator is written in Scala using the [Treadle executing engine](https://github.com/freechipsproject/treadle). You can execute the simulator by using `runMain CODCPU.simulate` from sbt. This will allow you to run *real RISC-V binaries* on your CPU design. More detail about this will be given in Lab 2. **Do not modify**
  - `top.scala`: A simple Chisel file that hooks up the memory to the CPU. **Do not modify**
- `test/`
  - `java/`: This contains some gradescope libraries for automated grading. **Feel free to ignore.**
  - `resources/riscv`: Test RISC-V applications that we will use to test your CPU design and that you can use to test your CPU design.
  - `scala/`
    - `components/`: Tests for the CPU components/modules. **You may want to add additional tests here. Feel free to modify, but do not submit!**
    - `cpu-tests/`: Tests the full CPU design. **You may want to add additional tests here in future labs. Feel free to modify, but do not submit!**
    - `grading/`: The tests that will be run on gradescope. Note: These won't work unless you are running inside the gradescope docker container. They should match the tests in `components` and `cpu-tests`. **Do not modify** (Well, technically, you *can* modify, but it will be ignored when uploading to gradescope.)

### More information

For more details on how each component works, the I/O, etc. see the given code.


# Grading

Grading will be done on gradescope.
See [Submission](# Submission) for more information on how to submit to gradescope.

|                    |     |
|--------------------|-----|
| ALU control        | 25% |
| Diagram            | 25% |
| Add                | 10% |
| Other instructions | 20% |
| Multiple cycles    | 20% |


# Part I: Implement the ALU Control

In this part you will be implementing a component in the CPU design.

The ALU has already been implemented for you.
It takes three inputs the `operation` and two inputs, `inputx` and `inputy`.
It generates the `result` of the operation on the two inputs.

The following table details the `operation` input and which values produce which results.

|      |     |
|------|-----|
| 0000 | and |
| 0001 | ... |
... and so on <TODO: FILL THIS IN>

You must take the RISC-V ISA specification, which you can find on the first page of the Computer Organization and Design book, on page 16 in the RISC-V reader, or [on the web](FIND THIS) and implement the proper control to choose the right ALU operation.

The ALU control takes three inputs the `memory` which comes from the control unit (you will implement this in the next lab), `funct7`, and `funct3` which come from the instruction.
You can ignore the `memory` for now, assume it is always `false`.

Given these inputs, you must generate the correct output on the operation wire.

**HINT** Use Chisel's `switch` / `is`,  `when` / `elsewhen` / `otherwise`, or `MuxCase` syntax.

<TODO: Move this to our "chisel overview", make it switch with 2 bits (so elsewhen works better) and link to that from here!>

The following will set the wire `out` to "high" when the `input` is greater than zero and "low" when it is less than zero in twos complement.
The input is 5 bits wide.

```
class ZeroCheck extends Module {
  val io = IO(new Bundle {
    // Another module will connect a wire to this. This is 5 bits wide.
    val input = Input(UInt(5.W))

    // Another module will connect a wire to this. This is 1 bit wide.
    val output = Wire(Bool())
  }

  switch (io.input(4)) {    // Get the 4th bit (zero indexed, so this is the MSB)
    is ("b0".U) {           // If it's 0
      io.output := false.B  // convert scala's boolean to a chisel bool. Input is not negative
    }
    is ("b1".U) {           // If it's 1
      io.output := true.B   // convert scala's boolean to a chisel bool. Input is negative
    }
  }
}
```


```
class ZeroCheck extends Module {
  val io = IO(new Bundle {
    // Another module will connect a wire to this. This is 5 bits wide.
    val input = Input(UInt(5.W))

    // Another module will connect a wire to this. This is 1 bit wide.
    val output = Wire(Bool())
  }

  when (io.input(4) === "b0".U) {    // In Chisel you must us === to check for equality
    io.output := false.B     // Input is not negative
  } .otherwise {             // Note! In this case you must use "." in front of otherwise
    io.output := true.B      // Input is negative
  }
}
```

In the above example, we could have also used `.elsewhen` if we wanted to add another check (like `else if` from C).

<TODO: Add example of using `MuxCase`>

### Testing your ALU control unit

We have implemented some tests for your ALU control unit.
The general ALU control unit tests are in `src/test/scala/components/ALUControlUnitTest.scala`.
However, these tests require you to implement the required control for not only the R-Type instructions but also for I-Types and loads/stores.
Thus, there are Lab1-specific tests in `src/test/scala/labs/Lab1Test.scala`.

To run these tests, you simply need to execute the following at the sbt command prompt:

```
sbt> test
```

If you try this before you implement your ALU control unit, you'll see something like the following.

```
sbt:dinocpu> test
[info] Compiling 8 Scala sources to /home/jlp/Code/chisel/darchr-codcpu/target/scala-2.11/classes ...
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
[error]         CODCPU.ALUControlTesterLab1
[error]         CODCPU.SingleCycleCPUTesterLab1
[error] (Test / test) sbt.TestsFailedException: Tests unsuccessful
```

Some of the failures will look scary.
This is expected.
As given, the template code causes compile errors in the tests.
This is because no registers are connected to input or output, so the compiler optimizes them away!
This confuses the simulator since it is trying to compare register values.
Once you have implemented your ALU control unit these errors will go away.

There are two main tests given for Lab 1.
(There will be many more in future labs!)
- `ALUControlUnitRTypeTester`: Directed tests which poke the input of the control unit and expect a specific output.
- and `SingleCycleCPUTester`: This runs *actual RISC-V applications* on your CPU model. This will be used below.

In this part of the assignment, you only need to run the ALU control unit tests. To run just these tests, you can use the sbt command `testOnly` as demonstrated below.

```
sbt> testOnly CODCPU.ALUControlTesterLab1
```

Feel free to add your own tests in `src/tests/scala`, modify the current tests, and add `print` statements in the tests.

## Part II: Draw a diagram for implementing R-type instructions

For the rest of the assignments you will implement all of RISC-V's R-type instructions.
Since you have implemented the ALU control, there isn't much more to do except to connect the correct wires together.

However, before you start writing code, you should know what you're going to do!
To get an idea of how you are going to implement this, it's a good idea to first draw your design on a piece of paper.
We provide you with a [blank circuit diagram](../dino-resources/single-cycle.pdf).

Draw all of the wires and label which bits are on each wire.
You will turn this in as part of your assignment.

<TODO: Add more here>

## Part III: Implement the add instruction

Now you're ready to implement your first instruction!

### Testing

Testing the CPU is very similar to testing your control unit [above](#Testing-your-ALU-control-unit).
To run the tests, you execute the `SingleCycleCPUTesterLab1` suite as follows.

```
sbt> testOnly CODCPU.SingleCycleAddTesterLab1
```

### Debugging with the simulator

#### Running the simulator

#### Building your own applications


## Part IV: Implementing the rest of the R-type instructions

If you have passed the `AddTest` test and you passed the `ALUControlTest`, then all of the other R-type instruction should "just work"!
Now, test them to make sure that they do!

### Testing

Testing the CPU is very similar to testing your control unit [above](#Testing-your-ALU-control-unit).
To run the tests, you execute the `SingleCycleCPUTesterLab1` suite as follows.

```
sbt> testOnly CODCPU.SingleCycleCPUTesterLab1
```

This will load some binary applications from `src/test/resources/risc-v`.
The applications that it is running is specified in the output.
For instance, below is a failing test.

```
[info] SingleCycleCPUTesterLab1:
[info] Single Cycle CPU
[info] - should run rtype add1 *** FAILED ***
...
```

This ran an **rtype** application which used the binary **add1**.
You can view the RISC-V assembly for this application in `src/test/resources/risc-v/add1.riscv`
The list of applications that this suite will run can be found in the `InstTests.scala` file (`src/test/scala/cpu-tests/InstTests.scala`).
If you want more details on the syntax and how to extend this to other RISC-V binaries, ask on piazza and we will be happy to expand this section.

If you want run only a single application from this suite of tests, you can add a parameter to the `test` sbt task.
You can pass the option `-z` which will execute any tests that match the text given to the parameter.
You must use `--` between the parameters to the sbt task (e.g., the suite to run) and the parameters for testing.
For instance, to only run the subtract test you would use the following.

```
sbt> testOnly CODCPU.SingleCycleCPUTesterLab1 -- -z sub
```

**IMPORTANT**: Passing all of the tests we have provided for you does not guarantee you have implemented the ALU control or the CPU correctly!
You are **strongly encouraged** to make your own unit tests and make your own RISC-V applications to test out.

### Debugging with the simulator

You can use the same strategy as described above.
This time you will change which binary your are executing.

## Part V: Moving on to multiple cycles

Now, let's try a more complicated program that executes more that one instruction.
`addfwd` is one example of this.

### Testing

To run this test, you can use the `-z` trick from above.

```
sbt> testOnly CODCPU.SingleCycleCPUTesterLab1 -- -z addfwd
```

### Debugging

<TODO>

# Submission

**Warning**: read the submission instructions carefully. Failure to adhere to the instructions will result in a loss of points.

Describe how to submit to gradescope here.
<I think we want them to upload just the files they touched (`components/alu-control.scala`, and `single-cycle/cpu.scala`). We need to figure out how to get these files in the right places.>

## Academic misconduct reminder

You are to work on this project **individually**.
You may discuss *high level concepts* with one another (e.g., how to draw the diagram), but all work must be completed on your own.

# Hints

- Start early! There is a steep learning curve for Chisel, so start early and ask questions on Piazza and in discussion.
- If you need help, come to office hours for the TAs, or post your questions on Piazza.

## Common errors

Note: We will populate this with questions from piazza when it looks like many people are running into the same issue.

## Printf debugging

<TODO: Expand this>
This is the best debugging.

- Use printf when you want to print *during simulation*.
  - Note: this will print *at the end of the cycle* so you'll see the values on the wires after the cycle has passed.
  - Use `printf(p"This is my text with a $var\n")` to print chisel variables. Notice the "p" before the quote!
  - You can also put any scala statement in the print statement (e.g., `printf(p"Output: ${io.output})`)
- Use println to print during compilation in the Chisel code or during test execution in the test code.
  - This is mostly like java's println
  - If you want to use scala variables in the print statement prepend with an "s". E.g., `println(s"This is my cool variable: $variable")` or `println("Some math: 5 + 5 = ${5+5}")`


