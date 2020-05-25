# Parallel Architectures and Programming

![Relevant xkcd](https://xkcd.com/1838/)
#howifeelaboutml

## Kinds of parallel architectures

In this section, we will start by discussing different kinds of parallel architectures.

{% include video.html %}

This video discusses Flynn's taxonomy and the different kinds of parallelism (from the perspective of software).

{% include video.html %}

This video discusses different kinds of parallel architectures (from the perspective of hardware).

## **QUIZ** Parallel performance and architectures

![under construction]({{ "/under-construction.png" | relative_url }})
[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/)

## Shared memory architectures

Note: This section is **optional.**
However, it's recommended that you watch the video as it reinforces the previous content.

**IMPORTANT NOTE:** If you notice that I got a haircut, it's not because I am breaking the quarantine, but because I'm time traveling.
These videos are from last quarter.

{% include video.html id="0_iisjinyw" %}

This video talks about shared memory vs message passing, and different synchronization primitives in a shared memory system.

{% include video.html id="0_6la61f2h" %}

This video talks about how to implement a barrier in a shared memory system.
This implementation is going to be the motivation our next few videos about the hardware implementation of these system.

[Up next, how to deal with memory in a multi processor system.](./memory.md)
