
# Quiz 12: Static scheduling

## Question 1: Static scheduling

Mark the true statements

[x] Compilers can re-arrange instructions to increase performance
[x] Compilers can re-arrange instructions to reduce hazards and stalls
[x] The order of instructions in the program can affect the performance
[x] Sometimes there are independent instructions that the compiler cannot find

[[Correct! All of the above statements are true.]]

## Question 2: Static scheduling by hand

For the following program, what is the "best" schedule *without changing the program*?
Assume the DINO CPU pipeline without any branch prediction.
I.e., there is a one cycle load to use hazard and branches are resolved in the memory stage.

```
a: lw   x2, 0(x1)
b: addi x1, x2, 45
c: add  x3, x4, x7
d: beq  x2, x3, 100
e: sub  x4, x0, x1
f: sw   x7, 0(x1)
```

( ) a,b,c,d,e,f
(x) a,c,b,d,e,f
( ) a,c,b,e,f,d
( ) a,b,c,e,f,d
( ) b,c,a,d,e,f

[[Correct! By moving the `add` after the `lw` you no longer need to insert a bubble between the `lw` and the `addi` that uses its result. Also, you cannot move any instruction around the `beq` since there's no way to know (from this information) if it's taken or not.]]

## Question 3: Loop unrolling

Mark the true statements

[x] Loop unrolling can expose instruction level parallelism
[ ] Loop unrolling makes the code smaller
[ ] Loop unrolling always increases performance
[x] Loop unrolling reduces the number of dynamic branch instructions

[[Correct! Loop unrolling almost always increases the code size, and because of this, it can lead to performance degradation. In most cases, you should trust the compiler!]]

# Question 4: False/name dependencies

Which two instructions have a false/name dependence that would require using a new temporary register?

```
a: addi x4,  x0, 0
b: lw   x12, 200(x4)
c: addi x31, x12, 2345
d: sub  x20, x4, x31
e: sw   x12, 0(x4)
f: and  x31, x4, x20
```

( ) a & b
( ) a & e
( ) b & c
( ) b & e
( ) c & e
(x) c & f
( ) d & f

[[Correct! c and f both write to register 31, but they are actually independent.]]
