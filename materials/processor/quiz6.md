# Quiz 6 Solutions


## **Q1** Machine representation 1

What is the source register number for the following instruction? (note: your answer should be a single number)

`0x0FF2F313`

> 5

## **Q2** Machine representation 2

What is the assembly instruction for the following instruction? (note: your answer should just be the instruction, not any of the operands. The answer is just 2-4 letters. E.g., "add")

`0x40502023`

> sw

## **Q3** Machine representation 3

What is the machine code (in hex) for the following code? (Your answer should have the form "0x12345678")

`sub x7, x5, x6`

> 0x406283B3

## **Q4** RISC ISA

Which of the following characteristics of the RISC-V ISA makes it simpler to implement in hardware than a CISC ISA?

- [ ] It has many different kinds of R-type instructions.
- [X] The instructions are all the same width (32 bits).
- [ ] There are extensions so customers can add their own instructions.
- [X] The destination register is always in the same location in the instruction.

## **Q5** Jump instructions

The JAL instruction is used for:

- [ ] Conditional statements
- [ ] Simple arithmetic operations
- [ ] System calls
- [X] Function calls
- [ ] Memory operations
- [ ] Loading immediate values into the register file
