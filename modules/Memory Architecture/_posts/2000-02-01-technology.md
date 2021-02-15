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

This video introduces the technology behind general memory arrays.
This shows what's going on inside your DRAM chips and inside the SRAM arrays that are used for caches.
At the base, all of these things are just *memory arrays* though they may be used for a variety of different things (e.g., main memory, cache, or even storage).

{% include video.html id="0_jpfyz8c7" %}

Here's a good picture, from wikipedia, showing what a set of DRAM banks looks like.
This is 1 mega*bit*.
Each square bank has 4 sub-arrays.
There are a total of 8*4=32 banks.
Each sub-array has 2^13 bits or 8192 bits.

![DRAM die](https://upload.wikimedia.org/wikipedia/commons/thumb/9/9b/MT4C1024-HD.jpg/1280px-MT4C1024-HD.jpg)

Now that we've introduced the idea of memory arrays, the next video talks specifically about two memory technologies that are very common: SRAM or *static* random access memory and DRAM or *dynamic* RAM.
Note that this use of "static" and "dynamic" is different than in the processor section where we were talking about the compiler or runtime.
Now, *static* means stays there forever (at least until the power is shut off) and *dynamic* means that it loses its data on a read.

{% include video.html id="0_6hbs8kj5" %}

This video looks at the characteristics we care about for memory technologies, and also talks about a few other storage-based technologies (Flash, disk, and 3D-XPoint).

{% include video.html id="0_x6zpqmef" %}
{% comment %}
It would be good to add a row to the table which is "RAM" and whether it's byte or block addressable
{% endcomment %}

## Moving data around

Now that we've talked about how we want to have different places to store data, the next question is "what is the technology required to move data around?"

{% include video.html id="0_qda0avr3" %}

## **QUIZ** Memory technology

{% include quiz.html id="113921"%}
