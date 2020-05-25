# Parallel Architectures

![Picture of NVIDIA Ampere architecture](./ampere.png)

In the [processor section](../processor/index.md) we learned about *instruction-*level parallelism and how there are limits to how much parallelism there is in our applications.
However, we can overcome this, by leveraging *multiple processors*.

In this section, we're going to learn about how to combine multiple *independent* instruction streams executing on different hardware to improve performance.

Unfortunately, we're running out of time this quarter.
If we had another 4-6 weeks, I would love to spend that entire time on this subject!
But, we can't.

Therefore, we're going to touch on a number of topics quickly.
Not all of the videos/lectures in the following section will be required.
Feel free to skip the ones that are not required if you need to spend time on other classes, or just need a mental break.
However, if you're interested to learn about how modern architecture work, you'll find lots of good information in these optional lectures.
The optional lectures will be clearly marked.

## Parallel system's performance

* [Parallel Systems' Performance](./performance.md)
  * [Amdahl's law revisited](./performance.md#amdahl-s-law-revisted)

## Parallel Architectures and Programming

* [Parallel Architectures and Programming](./architectures.md)
  * [Kinds of parallel architectures](./architectures.md#kinds-of-parallel-architectures)
  * [**QUIZ** Parallel performance and architectures](./architectures.md#quiz-parallel-performance-and-architectures)
  * (Optional, but encouraged) [Shared memory architectures](./architectures.md#shared-memory-architectures)

## Parallel Memory Systems

* (Optional) [Parallel Memory Systems](./memory.md)
  * (Optional) [Cache coherence and memory consistency](./memory.md#cache-coherence-and-memory-consistency)
    * (Optional) [Cache coherence](./memory.md#cache-coherence)
    * (Optional) [Memory consistency](./memory.md#memory-consistency)

## Accelerator architecture

* (Optional) [GPUs and Accelerators](./accelerators.md)
