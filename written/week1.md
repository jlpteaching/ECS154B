---
author: Justin Perona
title: ECS 154B Written Problems for Week 1, Winter 2019
---

# Written problems for week 1

This problem set covers lectures 1 through 3.

Solutions won't be posted on GitHub.
If you'd like answers to the problems, either post on Piazza or go to Jason's or Justin's office hours.

## Lectures

1. [Introduction](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/Lecture-1.pdf)
2. [Technology](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/Lecture-2.pdf)
3. [More technology](https://github.com/jlpteaching/ECS154B/blob/master/lecture%20notes/Lecture-3.pdf)

## Topics covered

* Security
   * Meltdown and Spectre
   * Security as a design constraint
* History of computing
  * Moore's law
  * Dennard scaling
* CMOS devices
  * Energy
  * Power
* Trends in computing

## Problems

### Security

1. How do we decide if a system is good? What factors would you use to determine if one system is "better" than another?
2. Assume you had one machine that was more "secure" (say, an Intel x86 CPU that fixed Meltdown), but had to run at a moderately reduced frequency to achieve that security. Would this be a worthwhile trade-off? Is security a factor to consider in the context of the previous question?

### History of computing

3. What is Dennard scaling? How does it differ from Moore's law?
4. In the mid-2000s, we hit a peak in terms of single-core frequency. However, we were able to continue increasing the number of transistors on a chip. What were those transistors used to implement? (What major change occurred at that time?)

### CMOS devices

5. In a CMOS device, what is power equal to?
6. Use your answer from the previous problem to help answer this question. Assume we want to improve performance of a CMOS device. If we keep the same number of transistors in a chip, what variable stays constant? In what two ways can we improve a CMOS device's performance, using the same number of transistors?
7. We were able to steadily improve the frequency that CMOS devices were run at, without raising power that much. We accomplished this via reducing the voltage these devices were run at. Does reducing the voltage have the same impact as changing the other terms? Why or why not?
8. Why can't we continue to reduce the voltage CMOS devices are run at? (Hint: use both static and dynamic power to explain your answer.)
9. As predicted by Moore's law, we were able to pack increasingly larger amounts of transistors onto a single chip. However, we've come across the "dark silicon" problem, where large portions of the transistors on a chip are left turned off, or "dark," at a time. Why are they left turned off? What would happen if we tried to power them all at the same time?

### Trends in computing

10. We've steadily reduced the size of transistors. Has the reliability of transistor devices remained the same as the transistor size became smaller? Why or why not?
11. Computer architecture design doesn't remain constant. New technology ends up changing the underlying architecture. As mentioned in the 2017 Turing Lecture, how is computer architecture going to change with new technologies?
