---
authors: Jason Lowe-Power
title: ECS 154B Lab 1, Winter 2019
---

# ECS 154B Lab 1, Winter 2019

**Due by 12:00 AM on January 21, 2019**

**Via Gradescope**

# Introduction

![Cute Dino](../dino-resources/dino-128.png)

In this assignment you will start implementing a the DINO CPU (Davis IN-Order CPU).
This is a simple in-order CPU design based closely on the CPU model in Patterson and Hennessey's Computer Organization and Design.

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

## Working with the DINO CPU code

### Overview of code

The `src/` directory:

- `main/`
  - `scala/`
   - `components/`
   - `five-cycle/`
   - `pipelined/`
   - `single-cycle/`
- `test/`
  - `java/`: This contains some gradescope libraries for automated grading. Feel free to ignore.
  - `resources/riscv`: Test RISC-V applications that we will use to test your CPU design and that you can use to test your CPU design.
  - `scala/`
    - `components/`: Tests for the CPU components/modules.
    - `cpu-tests/`: Tests the full CPU design
    - `grading/`: The tests that will be run on gradescope. Note: These won't work unless you are running inside the gradescope docker container. They should match the tests in `components` and `cpu-tests`.


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
You can ignore the `memory` for now.

Given these inputs, you must generate the correct output on the operation wire.

**HINT** Use Chisel's `switch` / `is` or `when` / `elsewhen` / `otherwise` syntax.

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

### Testing your ALU control unit

This describes how to run the tests and what you should expect.

<TODO: Add more here>

## Part II: Draw a diagram for implementing R-type instructions

For the rest of the assignments you will implement all of RISC-V's R-type instructions.
Since you have implemented the ALU control, there isn't much more to do except to connect the correct wires together.

However, before you start writing code, you should know what you're going to do!
To get an idea of how you are going to implement this, it's a good idea to first draw your design on a piece of paper.
We provide you with a [blank circuit diagram](LINK TO PDF).

Draw all of the wires and label which bits are on each wire.
You will turn this in as part of your assignment.

<TODO: Add more here>

## Part III: Implement the add instruction

Now you're ready to implement your first instruction!

### Testing

### Debugging with the simulator

## Part IV: Implementing the rest of the R-type instructions

If you have passed the `AddTest` test and you passed the `ALUControlTest`, then all of the other R-type instruction should "just work"!
Now, test them to make sure that they do!

### Testing

### Debugging with the simulator

You can use the same strategy as described above.
This time you will change which binary your are executing.

## Part V: Moving on to multiple cycles

Now, let's try a more complicated program that executes more that one instruction.

### Testing

### Debugging

# Submission

**Warning**: read the submission instructions carefully. Failure to
adhere to the instructions will result in a loss of points.

Describe how to submit to gradescope here.

## Academic misconduct reminder

You are to work on this project **individually**.
You may discuss *high level concepts* with one another (e.g., how to draw the diagram), but all work must be completed on your own.

# Hints

- Start early! There is a steep learning curve for Chisel, so start early and ask questions on Piazza and in discussion.
- If you need help, come to office hours for the TAs, or post your questions on Piazza.

## Common errors

Note: We will populate this with questions from piazza when it looks like many people are running into the same issue.

