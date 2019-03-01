[![License: CC BY 4.0](https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0/)

# Welcome to ECS 154B

This is the canonical version of the ECS 154B class materials.
The [syllabus](syllabus/syllabus.md) can be found in the syllabus directory.
See the [syllabus](syllabus/syllabus.md) for all class details.

# Overview of class resources

- [Syllabus](syllabus/syllabus.md)
- [Lecture Notes](lecture%20notes/): This directory contains the notes that I write in OneNote during lecture. These will be posted soon after each class.
  - You can find notes from previous offerings by checking out the previous year's branches: [WQ 18](https://github.com/jlpteaching/ECS154B/tree/wq18/lecture%20notes).
- [Lecture Outlines](lecture%20outlines/): This directory contains the outlines for the lectures. I will try to post outlines for the lectures sometime the morning before lecture when there are complex figures included.
- Labs
  - [Lab 1](lab1/lab1.md): Chisel intro and beginning DINO CPU
  - [Lab 2](lab21/lab2.md): Single cycle DINO CPU
  - [Lab 3](lab3/lab3.md): Pipelined DINO CPU
  - [Lab 4](lab4/lab4.md): DINO CPU branch predictor and performance
  - ~~[Lab 5](lab5/lab5.md): TBD~~
- Chisel resources
  - [Overview](chisel-notes/overview.md): An overview of what chisel is, how to use it, and how to install it.
  - [Getting Started](chisel-notes/getting-started.md): Some simple examples to get you started with Chisel.
  - [Testing with Chisel](chisel-notes/testing.md): Some examples of writing directed unit tests with Chisel.
  - [Building Systems](chisel-notes/building-systems.md): Examples of using Chisel modules, I/O, and other features to build larger systems.
- DINO CPU Resources (most of these can be found in the DINO CPU template repository).

## Building pdfs for syllabus and assignments

First, you must set up your environment.
To initialize this folder, run
> ./setup.sh

After initial setup is complete, each time you want to build pdfs you will need to activate the virtualenv.
> source venv/bin/activate

Then, to build a pdf of the syllabus, for example, run
> rst2pdf syllabus.rst Syllabus.pdf -s letter
