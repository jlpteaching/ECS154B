[![License: CC BY 4.0](https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0/)

# Welcome to ECS 154B

This is the canonical version of the ECS 154B class materials.

## Building pdfs for syllabus and assignments

First, you must set up your environment.
To initialize this folder, run
> ./setup.sh

After initial setup is complete, each time you want to build pdfs you will need to activate the virtualenv.
> source venv/bin/activate

Then, to build a pdf of the syllabus, for example, run
> rst2pdf syllabus.rst Syllabus.pdf -s letter
