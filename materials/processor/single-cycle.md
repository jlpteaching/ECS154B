# Single Cycle CPU Design

![XKCD comic](https://imgs.xkcd.com/comics/old_days.png)

**READING:** *Computer Organization and Design* Sections 4.1-4.4.

In this section, we will be digging into the necessary components and details on how to design a processor.
The goal of this section will be to design a full RISC-V processor, which is [Assignment 2](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/assignment-2.md) (Due 4/17).

## Steps to execute an instruction **VIDEO**

"Executing" an instruction takes many different steps.
It's more complicated than just "execution."

Canonically, we have the following five steps to complete an instruction:

1. **Fetch** the instruction: get the instruction data (machine code) from memory.
2. **Decode** the instruction: figure out what we should do and read the data from the register file.
3. **Execute** the instruction: use the ALU to compute a result, the effective address, or direction of the branch.
4. **Memory**: if the instruction needs to access memory, do it.
5. **Writeback** the instruction: (if required) write the result of the instruction to the register file.

The video below explains these steps in more detail and some example instructions.

<iframe id="kaltura_player" src="https://cdnapisec.kaltura.com/p/1770401/sp/177040100/embedIframeJs/uiconf_id/29032722/partner_id/1770401?iframeembed=true&playerId=kaltura_player&entry_id=0_vnludqwx&flashvars[mediaProtocol]=rtmp&amp;flashvars[streamerType]=rtmp&amp;flashvars[streamerUrl]=rtmp://www.kaltura.com:1935&amp;flashvars[rtmpFlavors]=1&amp;flashvars[localizationCode]=en&amp;flashvars[leadWithHTML5]=true&amp;flashvars[sideBarContainer.plugin]=true&amp;flashvars[sideBarContainer.position]=left&amp;flashvars[sideBarContainer.clickToClose]=true&amp;flashvars[chapters.plugin]=true&amp;flashvars[chapters.layout]=vertical&amp;flashvars[chapters.thumbnailRotator]=false&amp;flashvars[streamSelector.plugin]=true&amp;flashvars[EmbedPlayer.SpinnerTarget]=videoHolder&amp;flashvars[dualScreen.plugin]=true&amp;flashvars[Kaltura.addCrossoriginToIframe]=true&amp;&wid=0_opppboq6" width="608" height="402" allowfullscreen webkitallowfullscreen mozAllowFullScreen allow="autoplay *; fullscreen *; encrypted-media *" sandbox="allow-forms allow-same-origin allow-scripts allow-top-navigation allow-pointer-lock allow-popups allow-modals allow-orientation-lock allow-popups-to-escape-sandbox allow-presentation allow-top-navigation-by-user-activation" frameborder="0" title="Kaltura Player"></iframe>

This is a video describing the first two of the canonical five steps to execute an instruction.

<iframe id="kaltura_player" src="https://cdnapisec.kaltura.com/p/1770401/sp/177040100/embedIframeJs/uiconf_id/29032722/partner_id/1770401?iframeembed=true&playerId=kaltura_player&entry_id=0_6hppdgq5&flashvars[mediaProtocol]=rtmp&amp;flashvars[streamerType]=rtmp&amp;flashvars[streamerUrl]=rtmp://www.kaltura.com:1935&amp;flashvars[rtmpFlavors]=1&amp;flashvars[localizationCode]=en&amp;flashvars[leadWithHTML5]=true&amp;flashvars[sideBarContainer.plugin]=true&amp;flashvars[sideBarContainer.position]=left&amp;flashvars[sideBarContainer.clickToClose]=true&amp;flashvars[chapters.plugin]=true&amp;flashvars[chapters.layout]=vertical&amp;flashvars[chapters.thumbnailRotator]=false&amp;flashvars[streamSelector.plugin]=true&amp;flashvars[EmbedPlayer.SpinnerTarget]=videoHolder&amp;flashvars[dualScreen.plugin]=true&amp;flashvars[Kaltura.addCrossoriginToIframe]=true&amp;&wid=0_egowlk1b" width="608" height="402" allowfullscreen webkitallowfullscreen mozAllowFullScreen allow="autoplay *; fullscreen *; encrypted-media *" sandbox="allow-forms allow-same-origin allow-scripts allow-top-navigation allow-pointer-lock allow-popups allow-modals allow-orientation-lock allow-popups-to-escape-sandbox allow-presentation allow-top-navigation-by-user-activation" frameborder="0" title="Kaltura Player"></iframe>

This is a video describing the last three of the canonical five steps to execute an instruction.

## Data path and control path **VIDEO**

Next, we'll discuss how to split up the hardware into two parts, the control path and the data path.
By splitting the hardware this way, we're able to use *one set of hardware* to execute many different instructions.

<iframe id="kaltura_player" src="https://cdnapisec.kaltura.com/p/1770401/sp/177040100/embedIframeJs/uiconf_id/29032722/partner_id/1770401?iframeembed=true&playerId=kaltura_player&entry_id=0_q2vuxnkt&flashvars[mediaProtocol]=rtmp&amp;flashvars[streamerType]=rtmp&amp;flashvars[streamerUrl]=rtmp://www.kaltura.com:1935&amp;flashvars[rtmpFlavors]=1&amp;flashvars[localizationCode]=en&amp;flashvars[leadWithHTML5]=true&amp;flashvars[sideBarContainer.plugin]=true&amp;flashvars[sideBarContainer.position]=left&amp;flashvars[sideBarContainer.clickToClose]=true&amp;flashvars[chapters.plugin]=true&amp;flashvars[chapters.layout]=vertical&amp;flashvars[chapters.thumbnailRotator]=false&amp;flashvars[streamSelector.plugin]=true&amp;flashvars[EmbedPlayer.SpinnerTarget]=videoHolder&amp;flashvars[dualScreen.plugin]=true&amp;flashvars[Kaltura.addCrossoriginToIframe]=true&amp;&wid=0_s5rjxoh7" width="608" height="402" allowfullscreen webkitallowfullscreen mozAllowFullScreen allow="autoplay *; fullscreen *; encrypted-media *" sandbox="allow-forms allow-same-origin allow-scripts allow-top-navigation allow-pointer-lock allow-popups allow-modals allow-orientation-lock allow-popups-to-escape-sandbox allow-presentation allow-top-navigation-by-user-activation" frameborder="0" title="Kaltura Player"></iframe>

This video describes how we can split up the hardware into two parts, the control path and the data path.

Now, we can use the following design (what you will be implementing in [Assignment 2](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/assignment-2.md)) to run *any* RISC-V instruction with *one* set of hardware!

![Single cycle DINO CPU design](https://github.com/jlpteaching/dinocpu-sq20/blob/master/assignments/single-cycle-no-control.svg)

<iframe id="kaltura_player" src="https://cdnapisec.kaltura.com/p/1770401/sp/177040100/embedIframeJs/uiconf_id/29032722/partner_id/1770401?iframeembed=true&playerId=kaltura_player&entry_id=0_mr5qnvuu&flashvars[mediaProtocol]=rtmp&amp;flashvars[streamerType]=rtmp&amp;flashvars[streamerUrl]=rtmp://www.kaltura.com:1935&amp;flashvars[rtmpFlavors]=1&amp;flashvars[localizationCode]=en&amp;flashvars[leadWithHTML5]=true&amp;flashvars[sideBarContainer.plugin]=true&amp;flashvars[sideBarContainer.position]=left&amp;flashvars[sideBarContainer.clickToClose]=true&amp;flashvars[chapters.plugin]=true&amp;flashvars[chapters.layout]=vertical&amp;flashvars[chapters.thumbnailRotator]=false&amp;flashvars[streamSelector.plugin]=true&amp;flashvars[EmbedPlayer.SpinnerTarget]=videoHolder&amp;flashvars[dualScreen.plugin]=true&amp;flashvars[Kaltura.addCrossoriginToIframe]=true&amp;&wid=0_od595fhl" width="608" height="402" allowfullscreen webkitallowfullscreen mozAllowFullScreen allow="autoplay *; fullscreen *; encrypted-media *" sandbox="allow-forms allow-same-origin allow-scripts allow-top-navigation allow-pointer-lock allow-popups allow-modals allow-orientation-lock allow-popups-to-escape-sandbox allow-presentation allow-top-navigation-by-user-activation" frameborder="0" title="Kaltura Player"></iframe>

This video goes through a couple of examples with the DINO CPU design as shown above.

## **QUIZ** Single cycle design

[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/439561)

## Performance and limits to a single cycle design

In these videos, we will analyze this microarchitecture to understand the performance characteristics and limits of this design.

### Performance of the single cycle design **VIDEO**

![Under construction]({{ "/under-construction.png" | relative_url }})

This video discusses the performance of the above single cycle design and provides an example of computing the performance.

### How to improve this design and single cycle limitations **VIDEO**

![Under construction]({{ "/under-construction.png" | relative_url }})

This video discusses the limitations of single cycle designs and why real systems aren't implemented this way.

### **QUIZ** The Single cycle design's performance

[Use gradescope to take the quiz.](https://www.gradescope.com/courses/105214/assignments/439578)
