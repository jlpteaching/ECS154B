# Pipelined CPU Design

![XKCD comic](https://imgs.xkcd.com/comics/is_it_worth_the_time.png)

We've now seen how to design a simple [single cycle](./single-cycle.md) CPU.
Next, we're going to start talking about how to improve its performance and look at a more realistic design.

## Reading for this section

*Computer Organization and Design* Sections 4.5-4.9.

## Basic pipeline design

### What is pipelining? **VIDEO**

**READING:** *Computer Organization and Design* Section 4.5

{% include video.html id="0_w56q0cw5" %}

This is a video introducing the concept of pipelining.

### Pipelined design for the DINO CPU  **VIDEO**

**READING:** *Computer Organization and Design* Section 4.6

{% include video.html id="0_g7shogls" %}

This video explains how to modify the single-cycle DINO CPU to be pipelined.

### Example execution in pipelined DINO CPU  **VIDEO**

{% include video.html id="0_chtmmxco" %}

This video shows an example of how a program will execute in a pipelined CPU.

### Pipelined CPU performance **VIDEO**

{% include video.html id="0_zpwup7cg" %}

This video discusses the performance of a pipelined CPU.

### **QUIZ** Basic pipelining

[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/451227)

## Pipeline hazards

Now that we understand the basics of pipelining, let's look at some of the limitations and requirements to implement real system.

Note: these lectures will be useful when completing [Part II](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/assignment-3.md#part-ii-implementing-forwarding) of [assignment 3](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/assignment-3.md).

### Limits of our basic pipelined design and data hazards

**READING:** *Computer Organization and Design* Section 4.7

Through the following videos we will be understanding data hazards and the way the affect the pipeline performance and implementation.
These videos are bit more detailed than some of the others.
I suggest you give yourself enough time to go through the videos a couple of times to make sure you understand these concepts.

As always, don't hesitate to ask questions on [campuswire](https://campuswire.com/c/GDBEBE971/) or during discussions and office hours.

#### Detailed examples of data hazards and dependencies **VIDEO**

First, let's look at a very detailed example of how an example application uses this pipelined design.
This video is *very* detailed.
You may want to watch the next video first which goes over the example at a higher level and then come back to this video.

{% include video.html id="0_agprwal6" %}

This video introduces data hazards and goes over a very detailed example.

Next, let's bring things up a level and look at a different way to represent the same example.

{% include video.html id="0_v82gkaut" %}

This video introduces data hazards in a slightly different way than the previous video.
After this video, you may want to watch the first video again to make sure you understand the details.

#### "Solving" data hazards with stalling **VIDEO**

Now that we see how data hazards can cause a problem, let's look at a naive way to "solve" this problem by stalling some instructions.

{% include video.html id="0_ldm6ixoh" %}

This video discusses how to "fix" the data hazard problem by stalling instructions that cause the hazard.

> Note that in a "statically" scheduled design, the compiler can actually detect/predict which instructions are going to cause hazards and insert `nop` instructions in the right places.
> These designs are not common since you would have to recompile your program for every different hardware design.
> This is a good example of why you don't want you *micro*architecture leaking into your architecture.

### How to handle data hazards (forwarding) **VIDEO**

{% include video.html id="0_l0t4w443" %}

This video introduces forwarding to handle data hazards.

#### Load to use hazards **VIDEO**

{% include video.html id="0_gramyi32" %}

This video talks about a special kind of data hazard: load to use hazards.

### **QUIZ** Data hazards

[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/456000)

### Control hazards and branch prediction **VIDEO**

**READING:** *Computer Organization and Design* Section 4.8

{% include video.html id="0_w6v7pbcn" %}

This video introduces control hazards with an example.

{% include video.html id="0_tzm8692t" %}

This video introduces the idea of branch prediction.

{% include video.html id="0_8sbmejke" %}

This video discusses the requirements of a branch predictor and some more advanced branch predictions schemes.

### Other kinds of hazards: Structural hazards **VIDEO**

{% include video.html id="0_9pi7eacf" %}

This video talks about structural hazards.

## Exceptions in a pipelined processor **VIDEO**

**READING:** *Computer Organization and Design* Section 4.9

{% include video.html id="0_b0k5r233" %}

This video talks about how to handle exceptions/interrupts/errors in a pipelined processor design.

## Putting it all together: examples of pipelined execution **VIDEO**

{% include video.html id="0_irjgkd8a" %}

This video goes over an end-to-end example of the pipelined DINO CPU.
This video should be helpful on [Assignment 3.2](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/assignment-3.md#part-ii-implementing-forwarding)

### **QUIZ** Pipelining review

[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/464646)
