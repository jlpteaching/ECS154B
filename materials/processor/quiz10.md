# Quiz 10 Solutions

## **Q1** Data dependencies 1

For the following program mark the data dependencies. Put a check when the register listed after the `:` depends on a previous (older) instruction.

```
addi a0, s1, 0
sub  a0, t0, s1
sll  a2, a0, s1
xori t3, a2, 31
```

- [ ] `addi a0, s1, 0`: `a0`
- [ ] `addi a0, s1, 0`: `s1`
- [ ] `sub  a0, t0, s1`: `a0`
- [ ] `sub  a0, t0, s1`: `t0`
- [ ] `sub  a0, t0, s1`: `s1`
- [ ] `sll  a2, a0, s1`: `a2`
- [X] `sll  a2, a0, s1`: `a0`
- [ ] `sll  a2, a0, s1`: `s1`
- [ ] `xori t3, a2, a0`: `t3`
- [X] `xori t3, a2, a0`: `a2`

## **Q2** Data dependencies 2

For the following programs mark the data dependencies. Put a check when the register listed after the `:` depends on a previous (older) instruction.

### **Q2.1** data deps 2.1

```
add s10, t3, s0
lw  a4, 12(s10)
lw  s10, -16(t3)
```

- [ ] `lw a4, 12(s10)`: `a4`
- [X] `lw a4, 12(s10)`: `s10`
- [ ] `lw s10, -16(t3)`: `s10`
- [ ] `lw s10, -16(t3)`: `t3`

### **Q2.2** data deps 2.2

```
add s10, t3, s0
sw  a4, 12(s10)
sw  s10, -16(t3)
```

- [ ] `sw a4, 12(s10)`: `a4`
- [X] `sw a4, 12(s10)`: `s10`
- [X] `sw s10, -16(t3)`: `s10`
- [ ] `sw s10, -16(t3)`: `t3`

## **Q3** Pipeline performance

Using the five stage DINO CPU pipeline and assuming *there is not forwarding*, list the number of cycle each instruction below must be stalled to avoid data hazards. It would be helpful to draw out the pipeline diagram.

```
add x2, x4, x5
sub x6, x3, x4
sll x4, x7, x8
sra x4, x6, x2
xor x8, x4, x6
and x9, x4, x4
```

### **Q3.1** sll

For `sll x4, x7, x8` how many cycles must you stall?

> 0

### **Q3.2** sra

For `sra x4, x6, x2` how many cycles must you stall?

> 1

### **Q3.3** xor

For `xor x8, x4, x6` how many cycles must you stall?

> 2

### **Q3.4** and

For `and x9, x4, x4` how many cycles must you stall?

> 0

## **Q4** Forwarding example

How many cycles does the following program take to execute? It will be helpful to draw a pipeline diagram. Count the cycles until the final instruction writes into the register file (Note: for one instruction, the answer would be 5 cycles). 

```
addi a0, zero, 1024
sub  t1, a0, t0
lw   a1, -12(t1)
add  s0, a1, t1
sw   s0, 0(t1)
lw   t1, 8(s0)
```

> 11

```
**Explanation**
If there were no stalls, it would take 10 cycles. However, the add must wait one extra cycle for the load to use hazard after `lw a1, -12(t1)`
```
