---
Author: Jason Lowe-Power
Title: Getting Started with Chisel
---

# Getting Started with Chisel

## Outline

- Converting between scala and chisel types
- Wires
- Vals vs vars and `=` vs `:=`
- Muxes
  - Muxes
  - switch is
  - when elsewhen otherwise
  - mux case
- How to use IO
- How to run debug test
  - Getting the verilog, etc.

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
