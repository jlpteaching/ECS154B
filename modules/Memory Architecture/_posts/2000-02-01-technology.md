---
title: "Memory Technology"
discussion: 809206696055668746
---

![XKCD comic](https://imgs.xkcd.com/comics/obsolete_technology.png)

## Reading for this section

{% include reading.html section="Sections 5.1-5.2" %}

## Introduction: Why does memory architecture matter?

This video describes why we're learning about memory architecture and shows an example of memory from a real (old) system.

{% include video.html id="0_t7ft823s" %}

Unfortunately, the video didn't show the board-level wires very well.
Here's a better picture.
On the left are the pins for the processor and on the right are the pins for the DDR (or similar) controller.
Here, you can see the squiggly lines that I was talking about to make sure that they are all the same length.

![PCB trace for memory](/img/pcbtrace.png)

## Memory technology

{% include reading.html section="Section 5.2" %}

{% include video.html id="0_jpfyz8c7" %}

This video introduces the technology behind general memory arrays.

Here's a good picture, from wikipedia, showing what a set of DRAM banks looks like.
This is 1 mega*bit*.
Each square bank has 4 sub-arrays.
There are a total of 8*4=32 banks.
Each sub-array has 2^13 bits or 8192 bits.

![DRAM die](https://upload.wikimedia.org/wikipedia/commons/thumb/9/9b/MT4C1024-HD.jpg/1280px-MT4C1024-HD.jpg)

{% include video.html id="0_6hbs8kj5" %}

This video talks about how SRAM and DRAM cells work.

{% include video.html id="0_x6zpqmef" %}

This video looks at the characteristics we care about for memory technologies, and also talks about a few other storage-based technologies (Flash, disk, and 3D-XPoint).

## Moving data around

Now that we've talked about how we want to have different places to store data, the next question is "what is the technology required to move data around?"

{% include video.html id="0_qda0avr3" %}

## **QUIZ** Memory technology

{% include quiz.html %}
