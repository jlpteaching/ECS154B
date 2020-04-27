# Quiz 9 Solutions


## **Q1** Laundry

Assume the following details about doing laundry:

| Pre-wash | Washing | Drying | Folding/Hanging |
|---|---|---|---|
|40 minutes | 40 minutes | 60 minutes | 60 minutes |

### **Q1.1** Latency

How long does it take to complete a single load of laundry (in minutes)?

> 200

### **Q1.2** Limiting factor

What is the limiting "stage" for this laundry system? (Can have multiple answers)

- [ ] Pre-wash
- [ ] Washing
- [X] Drying
- [X] Folding/Hanging

### **Q1.3** Cycle time

What is the cycle time for the pipelined laundry (in minutes)? I.e., how frequently will a load be finished?

> 60

### **Q1.4** Throughput

How many loads can you complete per hour at steady state?

> 1.0

### **Q1.5** Speedup

What is the speedup of pipelining compared to not pipelining? Assume you only care about the steady state (i.e., no need to consider warmup/cooldown time).

> 3.3

## **Q2** Processor

Assume the following details about a processor design:

| Fetch | Decode | Execute | Memory | Writeback |
|---|---|---|---|---|
| 500ps | 300ps | 450ps | 550ps | 200ps |

### **Q2.1** Latency

How long does it take to complete a single instruction (in ps)?

> 2000

### **Q2.2** Limiting factor

Which stage(s) will limit the cycle time?

- [ ] Fetch
- [ ] Decode
- [ ] Execute
- [X] Memory
- [ ] Writeback

### **Q2.3** Cycle time

What is the cycle time if this was a *single cycle* design (not pipelined)?

Give answers in ps.

> 2000

What is the cycle time if this is a *pipelined* design?

Give answers in ps.

> 550

### **Q2.4** CPI

At steady state, how many instructions are completed each cycle (i.e., what is the CPI)?

> 1

### **Q2.5** Speedup

What is the speedup of pipelining compared to the single cycle design?

> 3.64
