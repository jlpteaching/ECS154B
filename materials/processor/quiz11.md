# Quiz 11 Solutions


## **Q1** Control hazards

Which of the following instructions will *cause* later instructions to stall assuming there's no branch predictor?

```
add  x3, x4, x6
bge  x3, x0, 100
jal  x4, 12384
addi x4, x0, 144
sub  x2, x1, x4
blt  x5, x2, -20
add  x6, x8, x2
```

- [ ] `add  x3, x4, x6`
- [X] `bge  x3, x0, 100`
- [X] `jal  x4, 12384`
- [ ] `addi x4, x0, 144`
- [ ] `sub  x2, x1, x4`
- [X] `blt  x5, x2, -20`
- [ ] `add  x6, x8, x2`

## **Q2** Control hazards

In which stage do you *know* you need to stall for a control hazard?

- [ ] Fetch
- [X] Decode
- [ ] Execute
- [ ] Memory
- [ ] Writeback

## **Q3** Control hazards

When predicting a branch, you need to predict which two things:

- [X] taken or not taken
- [ ] forward or backward
- [ ] which stage it is in
- [X] the target address
- [ ] number of cycles to stall
- [ ] if it is an exception

## **Q4** Control hazards

You can compute the accuracy of branch predictors by running a simple "simulation" of the outcomes for a branch predictor and compare this to the actual outcomes. 
The accuracy will be $$\frac{num\_correct}{total\_branches}$$

Assume the following branch pattern: (`T`->taken, `NT`->not taken)

`T NT T NT NT NT T T T T NT T T T T T NT T T T`

### **Q4.1** Always not taken

For an *always not taken* predictor, what is the accuracy?

> 0.3

```
**Explanation**
6 branches (all of the not taken branches) are predicted correctly out of 20. 6/20=0.3
```

### **Q4.2** Always taken

For an *always taken* predictor, what is the accuracy?

> 0.7

```
**Explanation**
14 branches (all of the not taken branches) are predicted correctly out of 20. 14/20=0.7
```

### **Q4.3** 1-bit counter

For a *1-bit* counter (i.e., last outcome) predictor, what is the accuracy? Assume the initial prediction is taken.

> 0.6

```
**Explanation**
`c`->correct, `i`->incorrect: `c i  i i  c  c  i c c c i  i c c c c i  i c c`... 12/20=0.6
```

### **Q4.4** 2-bit counter

For a *2-bit* counter predictor, what is the accuracy? Assume the initial prediction is weakly taken.

> 0.6

```
**Explanation**
`c`->correct, `i`->incorrect, `ST`->strongly taken, etc.:                    State: `ST WT ST WT WN SN WN WT ST ST WT ST ST ST ST ST WT ST ST ST` Prediction: `T  T  T  T  T  N  N  N  T  T  T  T  T  T  T  T  T  T  T  T` Correct: `c  i  c  i  i  c  i  i  c  c  i  c  c  c  c  c  i  c  c  c` 13/20 = .65
```
