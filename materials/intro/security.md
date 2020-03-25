# Computer Architecture and Security

In this section, I am going to talk about some recently discovered security vulnerabilities, [Spectre and Meltdown](https://meltdownattack.com/).
These vulnerabilities were first publicized at the beginning of 2018.
Since then, there has been a large number of similar vulnerabilities discovered including [Foreshadow](https://foreshadowattack.eu/), [Fallout](https://mdsattacks.com/), and most recently, in March of 2020, [LVI](https://lviattack.eu/) (I guess they ran out of clever names).

## Why talk about these vulnerabilities

![Under construction](/under-construction.png)

Video describing that we are talking about these vulnerabilities because they touch on many concepts that we will learn in this class.

## A brief overview of Meltdown

These attacks made huge news when they were first announced from tech-based sites like [Ars Technica](https://arstechnica.com/gadgets/2018/01/meltdown-and-spectre-every-modern-processor-has-unfixable-security-flaws/) and [Wired](https://www.wired.com/story/critical-intel-flaw-breaks-basic-security-for-most-computers/) to mainstream media like [The New York Times](https://www.nytimes.com/2018/01/03/business/computer-flaws.html).
(BTW, since you're a student at UC Davis, you can access the NYTimes [for free through the library](https://www.library.ucdavis.edu/news/get-free-access-to-the-new-york-times/).)

Not only did the news cover it, but so did YouTubers.
I think the video below gives a good, quick, explanation of Meltdown.
After watching this video, I'm going to go through some of the details that it missed.

<iframe width="608" height="402" src="https://www.youtube.com/embed/d1BRw32nMqg" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

YouTube video explaining Meltdown to a lay person.

## A little deeper on Meltdown

![Under construction](/under-construction.png)

Video explaining Meltdown works.

## What about Spectre?

Spectre is actually much worse than Meltdown.
[Below](), I'll talk about how to mitigate Meltdown, but mitigating Spectre is basically impossible without completely redesigning the processor.
I explain more about Spectre works below.

![Under construction](/under-construction.png)

A video explaining how Spectre works.

## Take away and something to think about

![Under construction](/under-construction.png)

Video describing the key problems that led to Spectre and Meltdown.

### Required readings

As mentioned in the video above, in our first discussion we will talk about the ethical implications of disclosing hardware vulnerabilities.
Before your discussion section, read these two short blog posts and *write one paragraph explaining whether you believe researchers should disclose vulnerabilities.*
Turn this in on [canvas]().

* Post 1: [Let’s Keep it to Ourselves: Don’t Disclose Vulnerabilities](https://www.sigarch.org/lets-keep-it-to-ourselves-dont-disclose-vulnerabilities/)
* Post 2: [Please Disclose Security Vulnerabilities!](https://www.sigarch.org/please-disclose-security-vulnerabilities/)

These were written for the [SIGARCH Computer Architecture Today Blog](https://www.sigarch.org/blog/).
[SIGARCH](https://www.sigarch.org/) is the ACM's special interest group (SIG) for computer architecture.
This is the professional and research society for computer architects.
If you're interested in cutting edge computer architecture research and you don't want to wade through 12 page research papers, the [SIGARCH blog](https://www.sigarch.org/blog/) is a great way to see what's going on in the research community.
I even wrote one about the [simulator infrastructure development going on here at UC Davis](https://www.sigarch.org/re-gem5-building-sustainable-research-infrastructure/)!

## Quiz 1: Security and architecture

![Under construction](/under-construction.png)

Link coming soon.

## Extra reading

Actually, this exact bug happened back in 2005, but no one knew it could be used to exfiltrate data.
They just thought it was a nasty one-off bug.

[This blog post](https://randomascii.wordpress.com/2018/01/07/finding-a-cpu-design-bug-in-the-xbox-360/) describes how a very similar bug was discovered in the Xbox 360 hardware and how it reeked havoc on the game developers before the Xbox engineers "fixed" the problem by removing what they thought was a clever feature.
