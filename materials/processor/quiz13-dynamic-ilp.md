# Quiz 13: Dynamic ILP

## Question 1: Benefits of dynamic ILP

Mark all that are true:

[X] Dynamic methods for finding ILP are more flexible to runtime dependences (e.g., address dependences)
[ ] Dynamic ILP techniques implemented in hardware use *less* power and area than static techniques implemented in the compiler
[ ] VLIW ISAs are better than RISC ISAs when implementing hardware for *dynamic* ILP

[[Correct! Dynamic ILP implementations in hardware are much more complex and take more power and area than what is required when the compiler statically determines the independent instructions. Also, VLIW ISAs are used when implementing *static* techniques for ILP, not dynamic. Trying to apply static techniques to VLIW architectures would be difficult (e.g., EPIC didn't do very well).]]

## Question 2: Out of order

In out-of-order processor you can only *execute* instructions out of order, you still must issue instructions in order and complete (or commit) instructions in order. Why?

[x] Must issue in order to determine their dependencies.
[ ] Must commit instructions in order to determine their dependencies.
[ ] Must issue in order to  make sure that exceptions/interrupts happen *precisely* for the right instruction.
[x] Must commit instructions in order to make sure that exceptions/interrupts happen *precisely* for the right instruction.

[[Correct!]]

## Question 3: DIS

Assume the following hardware state. There are some instructions currently executing, and others that have been decoded and are waiting to execute. Use this information to answer the questions below.

**Currently executing instructions**
```
add x4, x6, x9
lw  x2, 0(x8)
```

**Instructions waiting to execute**
```
sub  x6, x12, x0
sw   x3, 0(x9)
andi x12, x4, 0xFFFF
xor  x3, x9, x8
```

### Question 3.1: Simple DIS

Which instructions can be sent to execute at this time (assume there are enough execution/functional units and busses)

[x] `sub  x6, x12, x0`
[x] `sw   x3, 0(x9)`
[ ] `andi x12, x4, 0xFFFF`
[ ] `xor  x3, x9, x8`

[[Correct! The `sub` *can* issue because it's not reading from `x6` (which is busy). The `sw` can issue because it doesn't depend on the currently executing instructions or the `sub`. The `andi` cannot be issued because it has a true dependence on the `add` and register 6 is busy. Finally, the `xor` cannot issue because it would overwrite `x3` which is needed by `sw`]]

### Question 3.2: Register renaming

If we had register renaming, then which instructions could be sent to execute?

[x] `sub  x6, x12, x0`
[x] `sw   x3, 0(x9)`
[ ] `andi x12, x4, 0xFFFF`
[x] `xor  x3, x9, x8`

[[Correct! Now, you can execute the `xor` because you can rename `x3` to break the false dependence with `sw` (which is readying from `x3`). The `andi` has a true dependence on the `add` so it cannot be executed even with register renaming.]]

## Question 4: Types of hazards

Mark *all* of the types of hazards that can occur in an out-of-order superscalar processor design.

[x] Structural
[x] Read after write
[ ] Read after read
[X] Write after write
[x] Write after read
[x] Control
[ ] Rename

[[Correct! Rename hazards don't exist and read-after-read will never be a problem because nothing is being written so it doesn't matter what order to read it in.]]
