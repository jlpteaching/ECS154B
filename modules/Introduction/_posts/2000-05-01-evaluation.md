---
title: Computer System Performance
discussion: 791101413332615208
---

![XKCD comic](https://imgs.xkcd.com/comics/efficiency.png)

In this section, we will discuss how to evaluate the "goodness" of computing systems and some simple models for their performance.

## Reading for this section

{% include reading.html section="Section 1.6 and 1.9" %}

## What determines the "value" of a system?

[![Zen and the art of motorcycle maintenance](https://upload.wikimedia.org/wikipedia/en/8/85/Zen_motorcycle.jpg)](https://en.wikipedia.org/wiki/Zen_and_the_Art_of_Motorcycle_Maintenance)

This book is also "An Inquiry into Values," though in a more philosophical sense.
This video discuss what makes a system "good" and how to measure these characteristics.

{% include video.html id="0_y6agqjpk" %}

### Physics is an underlying barrier

A lecture from [Admiral Grace Hopper](https://en.wikipedia.org/wiki/Grace_Hopper) which talks about the latency of light.
Please watch from 45:02-48:25.

<iframe width="560" height="315" src="https://www.youtube.com/embed/ZR0ujwlvbkQ?start=2702&end=2905" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Now, let's talk about the difference between latency and bandwidth a bit more.

{% include video.html id="0_jhry1bp4" %}

{% include prompt.html content="
If latency is a fundamental physical constraint, how can we every make computers faster?!

There are two things we can do, and this is what computer architecture is all about!
" %}

## Explaining Computer System Performance

{% include reading.html section="Section 1.6" %}

The next video covers the Iron Law of performance and how to explain the performance of a processor.
This breaks down the performance of a processor into three constituent parts.
By breaking down the performance into these parts, we can think about how to optimize each component on its own which helps us focus our efforts in making processors more efficient.

{% include video.html id="0_la9fl95m" %}

This video shows an example of running a benchmark and applying the Iron Law.

{% include video.html id="0_f53fz5rk" %}

{% include quiz.html id="105248" %}

## Comparing Systems with Speedup

This video describes how to compare systems by using the *speedup* metric.

{% include video.html id="0_pvfjbkk5" %}

{% include prompt.html content="
Speedup is a metric to compare the *performance* of two systems, but there are other things we might want to compare as well.

Can you think of other comparison metrics which compare things other than performance?
"%}

## **QUIZ** Performance and Evaluation

{% include quiz.html id="105390" %}
