# Pipelined CPU Design

We've now seen how to design a simple [single cycle](./single-cycle.md) CPU.
Next, we're going to start talking about how to improve its performance and look at a more realistic design.

## Basic pipeline design

### What is pipelining?

![Under construction]({{ "/under-construction.png" | relative_url }})

This is a video introducing the concept of pipelining.

### Pipelined design for the DINO CPU

![Under construction]({{ "/under-construction.png" | relative_url }})

This video explains how to modify the single-cycle DINO CPU to be pipelined.

### Example execution in pipelined DINO CPU

![Under construction]({{ "/under-construction.png" | relative_url }})

This video shows an example of how a program will execute in a pipelined CPU.

### Pipelined CPU performance

![Under construction]({{ "/under-construction.png" | relative_url }})

This video discusses the performance of a pipelined CPU.

## Pipeline hazards

Now that we understand the basics of pipelining, let's look at some of the limitations and requirements to implement real system.

### Limits of our basic pipelined design and data hazards

![Under construction]({{ "/under-construction.png" | relative_url }})

This video introduces data hazards.

### How to handle data hazards (forwarding)

![Under construction]({{ "/under-construction.png" | relative_url }})

This video introduces forwarding to handle data hazards.

#### Load to use hazards

![Under construction]({{ "/under-construction.png" | relative_url }})

This video talks about a special kind of data hazard: load to use hazards.

### Control hazards and branch prediction

![Under construction]({{ "/under-construction.png" | relative_url }})

This video talks about a special kind of data hazard: load to use hazards.

### Other kinds of hazards: Structural hazards

![Under construction]({{ "/under-construction.png" | relative_url }})

This video talks about structural hazards.

## Exceptions in a pipelined processor

![Under construction]({{ "/under-construction.png" | relative_url }})

This video talks about how to handle exceptions/interrupts/errors in a pipelined processor design.

## Putting it all together: examples of pipelined execution

![Under construction]({{ "/under-construction.png" | relative_url }})

This video goes over an end-to-end example with forwarding and hazards.
