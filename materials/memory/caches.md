# Caches and Memory Hierarchy

![xkcd comic](https://imgs.xkcd.com/comics/bun.png)

## Memory hierarchy introduction

Unfortunately, there isn't a perfect memory device.
So, we need to construct a system with multiple different memory devices to try to get the best of all possible devices!

## Basic caching

### Combining memory technologies into a single system **VIDEO**

{% include video.html id="0_38jc7xsz" %}

This video talks about how to combine multiple memory technologies in to a **memory *hierarchy***.

### Locality and caching **VIDEO**

{% include video.html id="0_5rrwmsln" %}

This video introduces caches and talks about different kinds of caches.

{% include video.html id="0_upx2wqjb" %}

This video talks about different blocks sizes to take advantage of spatial locality.

### Cache performance **VIDEO**

{% include video.html id="0_u9ucuipd" %}

This video introduces measuring cache performance with *hit ratio* and *average memory access time* or AMAT.

### **QUIZ** Basic caching

[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/)

## Memory hierarchy **VIDEO**

{% include video.html id="0_39vj4rjv" %}

To motivate a memory hierarchy, this video goes over another AMAT example.

{% include video.html id="0_u9qzm15z" %}

This video talks about how a multi-level hierarchy can improve cache performance.

## Cache design

Now that we've talked about cache performance and how caches fit into the broader memory system, let's dig into how to design a cache.

To motivate cache design, we will be answering three questions.

1. How do we find data for a given address?
2. What do we do when there isn't enough room in the cache (or, which data should we replace)?
3. What happens when we want to write data?

The next sections will discuss each of these questions in detail.

### Direct-mapped caches **VIDEO**

First, we'll look at a "simple" direct-mapped cache.
After understanding this, we can dive into more realistic cache designs.

{% include video.html id="0_df72mesd" %}

This video introduces direct-mapped caches and starts to answer the question "How do we find data for a given address?"

{% include video.html id="0_f2aqs6vd" %}

This video talks about how to take an address and figure out where in the cache to look for the data.

{% include video.html id="0_rbldzock" %}

This video goes deeper into the hardware design of direct-mapped caches and begins to motivate set associativity.

### Set-associative caches **VIDEO**

There are major problems with direct-mapped caches.
Specifically, many addresses *conflict* for the same index in the cache.
But! We have set-associative caches coming to the rescue!

{% include video.html id="0_k4900yv2" %}

This video goes into detail of how to design a set-associative cache and how to figure out where to look in a set-associative cache for data given an address.

{% include video.html id="0_yjckyt1j" %}

This video talks about the area and power overheads of set-associative caches.

### **QUIZ** Cache design

[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/)
![Coming soon](/under-construction.png)

## Replacement policies **VIDEO**

Now, onto the next question: *Which data should we replace?*

{% include video.html id="0_ped6e37e" %}

This video introduces some replacement policies and some tradeoffs when trying to choose a replacement policy for a cache.

## Write-back policies **VIDEO**

And our final question: *What happens when we want to write data?*

{% include video.html id="0_0niqqg80" %}

This video discusses what happens when we try to write data to a cache and different write-back policies.

## Summary of caches **VIDEO**

{% include video.html id="0_33cjboxj" %}

This final video discusses the three C's of cache misses.

### **QUIZ** Summary of caches

[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/)
![Coming soon](/under-construction.png)

[Next up: Virtual memory](./virtual.md)
