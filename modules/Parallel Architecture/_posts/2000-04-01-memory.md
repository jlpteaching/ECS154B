# Parallel Memory Systems

![An SMBC this time](https://www.smbc-comics.com/comics/1583424176-20200305.png)

## Cache coherence and memory consistency

Note: This section is **optional.**
However, it's recommended that you watch the video as it reinforces the previous content.

These two topics are near and dear to my heart.
I've spent the last 10 years of my life working on these topics.
The next 20 minutes of lecture don't do them justice at all.
If you're interested to know more, there's a great book by my former advisors: [A Primer on Memory Consistency and Cache Coherence](https://www.morganclaypool.com/doi/abs/10.2200/S00346ED1V01Y201104CAC016).
I could teach a whole course just on that book!
(Note: if you're on campus or use a campus VPN, you can download the PDF for free.)

### Cache coherence

{% include video.html id="0_wyed932m" %}

This video discusses what happens with the previous barrier example when we add caches to the system.

{% include video.html id="0_hsvaxk02" %}

This video goes into the detail of one cache coherence protocol implementation that has three states: Modified, shared, and invalid or MSI.

### Memory consistency

While coherence ensures that caches stay transparent to the programmer, the *memory consistency model* is actually something that's part of the ISA and defines how the programmer should expect multi-threaded programs to behave.
Another way of looking at this is that cache coherence defines what happens to a single address (e.g., the single-writer multi-reader invariant) whereas memory consistency defines the behavior when multiple addresses are involved.

{% include video.html id="0_kzqc9bsa" %}

This video introduces the idea of memory consistency and talks about the importance of a `fence` instruction.

[Next up: accelerator architecture](./accelerators.md)
