---
title: "Parallel Architectures and Programming"
discussion: 816348321055506454
---

![Relevant xkcd](https://imgs.xkcd.com/comics/machine_learning.png)
#howifeelaboutml

{% include reading.html section="Chapter 6" %}

## Kinds of parallel architectures

{% include reading.html section="Sections 6.1 and 6.3" %}

In this section, we will start by discussing different kinds of parallel architectures.

{% include video.html id="0_tdlkxuf6" %}

This video discusses Flynn's taxonomy and the different kinds of parallelism (from the perspective of software).

{% include video.html id="0_2p28yi6y" %}

This video discusses different kinds of parallel architectures (from the perspective of hardware).

## Shared memory architectures

{% include reading.html section="Sections 6.4" %}

**IMPORTANT NOTE:** If you notice that I got a haircut, it's because I'm time traveling.
These videos are from Winter quarter 2020.
**IT'S NOW BEEN AN ENTIRE YEAR!!**

{% include video.html id="0_iisjinyw" %}

This video talks about shared memory vs message passing, and different synchronization primitives in a shared memory system.

{% include video.html id="0_6la61f2h" %}

This video talks about how to implement a barrier in a shared memory system.
This implementation is going to be the motivation our next few videos about the hardware implementation of these system.

## **QUIZ** Parallel architectures

{% include quiz.html id="116887" %}
