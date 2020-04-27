# Quiz 4 Solutions

## **Q1** Iron Law

For a different application, libquantum which is a quantum chemistry benchmark, I get the following results from the AMD Epyc and Intel i7 systems.

| | AMD Epyc | Intel i7 |
|--|--|--|
|Cycles | 949429232883 |900190883413 |
|Instructions | 1653448268698 |1643600607577  |
|Time |313.053s  | 230.4s  |

Using this data, answer the following questions.

### **Q1.1** CPI

What is the cycles per instruction for each system?


AMD Epyc

> 0.57

Intel i7

> 0.55

### **Q1.2** Architecture

Which system has the better architecture?

- [ ] AMD Epyc
- [X] Intel i7

### **Q1.3** Biggest factor

Does the frequency or the CPI have more impact on the difference in performance?

- [X] Frequency
- [ ] CPI

## **Q2** Comparing systems

Again, we'll use some real data from these two systems.

| | AMD Epyc | Intel i7 |
|--|--|--|
|gcc | 274.3s | 180.0s |
|mcf| 301.1s | 186.3s |
|libquantum | 313.1s | 230.4s |

### **Q2.1** Speedup

For which application does the i7 get the greatest speedup?

- [ ] gcc
- [X] mcf
- [ ] libquantum

### **Q2.2** Average speedup

What is the average speedup for these three applications?

Hint: Use the *correct* average statistic. See section 1.9 in the book.

> 1.5
