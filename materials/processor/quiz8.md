# Quiz 8 Solutions

## **Q1** Performance of single cycle 1

There is a processor design that combines some steps. It has three stages: fetch & decode, execute, and memory & writeback. Use the following information to answer the questions below.

|Fetch & Decode|Execute|Memory & Writeback|
|---|---|---|
|150ps|200ps|250ps|

### **Q1.1** Cycle time

What is the cycle time of this processor in ps?

> 600

### **Q1.2** CPI

What is the CPI of this processor?

> 1

### **Q1.3** Time for program

How long does it take to execute an application with 4 billion instructions on this single cycle processor (in seconds)?

> 2.4

## **Q2** Performance of single cycle 2

Assume the following latencies to answer the questions below. Assume that the register file and the PC includes the time to both read and write the registers.

| I-mem/ D-mem | Register file | Mux  | ALU   | Adder | PC   | ImmGen | Control |
|-------------|---------------|------|-------|-------|------|--------|---------|
| 250ps       | 150ps         | 25ps | 200ps | 150ps | 30ps | 60ps   | 50ps    |

### **Q2.1** R-type

What is the latency of an `R-type` instruction in ps?

> 655

### **Q2.2** 

What is the latency of a `ld` instruction?

> 905

## **Q3** Multi-cycle performance

Suppose you could build a CPU where the clock cycle time was different for each instruction. What would the speedup of this new CPU be over a "normal" single cycle CPU?

Assume the following:

| | r-type/ i-type | lw | sw | beq | jal |
| --- | --- | --- | --- | --- | --- |
| instruction mix | 52% | 25% | 11% | 8% | 4%|
| Delay | 500ps | 750ps | 700ps | 510ps | 600ps|

> 1.27
