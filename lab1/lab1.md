---
Authors: Jason Lowe-Power
---


# ECS 154B Lab 1, Winter 2019

**Due by 12:00 AM on January 21, 2019**

**Via Gradescope**

## Goals

- Learn how to use Chisel
- Learn how to run tests and debug Chisel
- Start implementing a CPU

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

## Working with the DArchR CPU code

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


# Grading

This will show the grading breakdown.
This is also on gradescope, of course.

- Diagram
- ALU control
- Add
- Or
- Other instructions
- Multiple cycles

## Submission

**Warning**: read the submission instructions carefully. Failure to
adhere to the instructions will result in a loss of points.

Describe how to submit to gradescope here.

## Hints

- Start early! There is a steep learning curve for Chisel, so start early and ask questions on Piazza and in discussion.
- If you need help, come to office hours for the TAs, or post your questions on Piazza.
