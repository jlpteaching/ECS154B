---
Author: Jason Lowe-Power
Title: Chisel cheat sheet
---

# Chisel cheat sheet for 154B

This document contains some of the Chisel patterns you will use while implementing the DINO CPU.

The Chisel project provides [a more complete cheat sheet](https://chisel.eecs.berkeley.edu/2.2.0/chisel-cheatsheet.pdf).

# Wires

## Create a new wire.

```
val x = UInt()
```

<TODO ADD A PICTURE>

Create a wire (named `x`) that is of type `UInt`.
The width of the wire will be inferred.
**Important**, this is one of the few times you will use `=` and not `:=`.

## Connect two wires.

```
x := y
```

<TODO ADD A PICTURE>

Connect wire y to wire x.
This is "backwards" in some sense.

## Another wire example

```
val adder1 = Adder()
val adder2 = Adder()

adder2.io.inputx := adder1.io.result
```

<TODO ADD A PICTURE>

`adder2.io.inputx := adder1.io.result` connects the output of adder 1 to the input of adder 2.

# Muxes

## Mux

```
val x = UInt()

x := Mux(selector, true_value, false_value)
```

## When-elsewhen-otherwise

## switch-is

# Types

## Boolean

- `Bool()`: a 1-bit value
- `true.B`: To convert from Scala boolean to chisel use `.B`
- `false.B`: To convert from Scala boolean to chisel use `.B`

## Integers


- `UInt(32.W)`: an unsigned integer that is 32 bits wide.
- `UInt()`: an unsigned integer width inferred (you may get an error saying it can't infer the width)
- `77.U`: To convert from scala integer to chisel unsigned int use `.U` (you may get type incompatible errors if you don't do this correctly).
- `3.S(2.W)`: Signed integer that is 2 bits wide (e.g., -1)

# Circuits provided as operators:

## Math

You can use simple operators like `+`, `-`, `>>`, etc. and they will generate circuits to match those operations.
See [the more complete cheat sheet](https://chisel.eecs.berkeley.edu/2.2.0/chisel-cheatsheet.pdf) for more details.

## Comparisons

The way to compare two chisel values is a little different than scala since it's creating a circuit and not doing a comparison.

- Equality: `===`
- Inequality: `=/=`

Less than, greater than, etc. work as expected.
However, make sure you are using the correct type (signed or unsigned).

# State elements (registers)

- `Reg(UInt(64.W))`: A 64 bit register
- `RegInit(1.U(32.W))`: A 32 bit register that has the value 1 when the system starts.

Registers can be connected to other wires.

```
val register = Reg(UInt(32.W))

x := register
```

<TODO ADD A PICTURE>

This takes the value coming out of the register and connects it to the wire `x`

Similarly, you can set a register to a value (at the end of a clock cycle).

```
val register = Reg(UInt(32.W))

register := y
```

<TODO ADD A PICTURE>

This will set the register to the value on wire `y` at the end of the clock cycle.

# Modules

## IO

## Using modules

# Bundles

# Frequently asked questions

You may also find your answer in [Chisel's FAQs](https://github.com/freechipsproject/chisel3/wiki/frequently-asked-questions).

## When to use `=` vs `:=`

You should use `=` when *creating a new variable*.
The `=` should always be on the same line as a `var`.

`:=` is the operator to *create a new wire* connecting the output wire on the right to the input wire on the left.
Note: This is backwards from the way you would draw it, but it's forwards for the way you would say it.
