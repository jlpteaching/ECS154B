:Author: Jason Lowe-Power

.. _Canvas: https://canvas.ucdavis.edu/
.. _GitHub: https://github.com/jlpteaching/ECS154B
.. _Gradescope: https://gradescope.com/courses/13842
.. _Piazza: https://piazza.com/class/jc0wjo8xjr77

================================
ECS 154B - Computer Architecture
================================

Important Information
---------------------

Time and Location
~~~~~~~~~~~~~~~~~

**202 Wellman Hall**

*Lecture*: Tuesday, Thursday 12:10 - 1:30 PM

*Discussion*: Friday 4:10 - 5:00 PM


Instructor
~~~~~~~~~~

**Professor Jason Lowe-Power** (jlowepower@ucdavis.edu)

*Office Hours*: Wednesday 4:00 - 5:30 PM, or by appointment.

*Office Location*: 3049 Kemper Hall

Please suggest a meeting time when you email me for an appointment.
You can use `my calendar`_ to quickly find a time I am available.
It's not guaranteed to be completely up-to-date, but it gives a good starting point.

.. _`my calendar`: http://goo.gl/hmtAH

Teaching Assistants
~~~~~~~~~~~~~~~~~~~

**Justin Perona** (jlperona@ucdavis.edu)

*Office Hours*: Thursday 3:10 - 4:00 PM

*Office Location*: 3106 Kemper Hall

**Bradley Wang** (radwang@ucdavis.edu)

*Office Hours*: Monday 1:00 - 2:00 PM

*Office Location*: 53 Kemper Hall

GitHub
~~~~~~

We will use GitHub_ as the main website and entry point for all course information.
The version of documents found on GitHub are the canonical versions of all documents.
Other downloaded versions of documents may become out of date.
If I make changes to those documents, they will appear first on GitHub.

GitHub will contain this document and the assignments.

Canvas
~~~~~~

We will be using Canvas_ for assignment submission and grade distribution.

Gradescope
~~~~~~~~~~

We will use Gradescope_ for returning quizzes, the midterm, and the final.
Gradescope gives you a graded PDF version of your test, along with a rubric, immediately after we're done grading.
You will receive an email from Gradescope to make your account after we grade the first test.

Piazza
~~~~~~

We will use Piazza_ for class discussions outside of the classroom.
If you haven't used Piazza before, it's a cool tool that is essentially a message board for the class.
Both the TAs and I will be on Piazza to answer questions.

It's best to ask your questions on Piazza.
That way, all of your classmates can see the answer instead of emailing the TAs or me.
Additionally, you might get a much faster response from one of your classmates!

Through asking and answering questions on Piazza, you improve your understanding of the material, and improve other students' understanding as well.
As an incentive to answer other students' questions and participate, I will drop your lowest quiz score if you consistently participate on Piazza.
I will check Piazza participation and drop the lowest score at the end of the quarter.

In the spirit of the above, please ask questions as public questions on Piazza, if possible.
This way, your question, and the answer to your question, can help somebody else who might have the same question.
We will change questions asked privately to public, if we deem it appropriate.
If your question involves code you've written, or is about a personal issue, we will leave those private.

10% of your grade is tied to participation, much of which will take place over Piazza.
The benchmark for good Piazza participation is at least 10 questions asked, answered, or follow-ups throughout the quarter.

Regrade Requests
~~~~~~~~~~~~~~~~

Regrade requests must be made within one week of the return of the assignment or test.

Accommodations
~~~~~~~~~~~~~~

The exam schedule is available on the schedule_.
Per `official UC Davis policy`_, if you have an accommodation request from the `Student Disability Center`_, or have any conflicts with exam times for religious observances, you must notify me **by the fourth class, January 16, 2018**.

.. _official UC Davis policy: http://catalog.ucdavis.edu/academicinfo/exams.html
.. _Student Disability Center: https://sdc.ucdavis.edu/

Academic Misconduct
--------------------

Academic misconduct is a serious issue.
You can find the official UC Davis policy on the `Office of Student Support and Judicial Affairs`_ website.

You are expected to *cite all of the work you reference*.
Any ideas that are not specifically yours or generally known (e.g., caches hold data) should have a citation.
When in doubt, cite.

Any violations of this policy will result in reporting the violating student(s) to the Office of Student Support and Judicial Affairs.

.. _`Office of Student Support and Judicial Affairs`: http://sja.ucdavis.edu/

Prerequisites
-------------

ECS 154A; or both EEC 170 and EEC 180A.

Assignments and Tests
---------------------

Grading Breakdown
~~~~~~~~~~~~~~~~~

=============  ===
Participation  10%

Labs (5x)      40%

-------------  ---

Quizzes (3x)   15%

Midterm        15%

Final          20%
=============  ===

Participation
~~~~~~~~~~~~~

10% of your grade comes from actively participating in class (defined broadly).
You are expected to participate on Piazza_ (e.g., at least 10 contributions), lecture discussions, discussion section discussions, and/or office hours.

Labs
~~~~

You will complete five lab assignments throughout this course.
The labs can be found via the links below.
All together, the labs are worth 40% of your final grade.
Each lab is weighted based on the amount of time you are given to complete the lab.

Labs are due at 9 AM on Mondays.

* `Lab 1`_ (2 weeks, 8%). Due January 22.
* `Lab 2`_ (2 weeks, 8%). Due February 5.
* `Lab 3`_ (3 weeks, 12%). Due February 26.
* `Lab 4`_ (2 weeks, 8%). Due March 12.
* `Lab 5`_ (1 week, 4%). Due March 19.

For all labs, you will be working with a partner.
You do not have to keep the same partner throughout the whole quarter; you can change who you are working with.
I suggest using Piazza to find partners.

All labs except lab 5 *require* interactive grading.
Half of your lab grade will come from a **one-on-one** interactive grading session with a TA.
You can sign up for interactive grading times once you have submitted your assignment for sometime the week of the submission deadline.
Failure to sign up for an interactive grading time will result in a 0% for the assignment.

.. _Lab 1: https://github.com/jlpteaching/ECS154B/blob/master/lab1/lab1.rst
.. _Lab 2: https://github.com/jlpteaching/ECS154B/blob/master/lab2/lab2.rst
.. _Lab 3: https://github.com/jlpteaching/ECS154B/blob/master/lab3/lab3.rst
.. _Lab 4: https://github.com/jlpteaching/ECS154B/blob/master/lab4/lab4.rst
.. _Lab 5: https://github.com/jlpteaching/ECS154B/blob/master/lab5/lab5.rst

Late Assignments
****************

If you turn in a lab late, you will lose points. The percentage of points you will lose is given by the equation below.
This will give you partial points up to 72 hours after the due date and penalizes you less if you barely miss the deadline.

.. GitHub doesn't like to render the above.
    fraction\ of\ points = -1 \times \frac{{hours\ late}^2}{72^2} + 1

.. image:: http://latex.codecogs.com/gif.latex?fraction%5C%20of%5C%20points%20%3D%20-1%20%5Ctimes%20%5Cfrac%7B%7Bhours%5C%20late%7D%5E2%7D%7B72%5E2%7D%20&plus;%201
    :width: 40%

.. image:: late_policy.png
    :width: 50%
    :align: center

Quizzes
~~~~~~~

There will be quizzes during some discussion sections.
The quizzes will be in a similar style to the midterm and the final, except they will be shorter (25 minutes).

Midterm: Thursday, February 15th at 12:10 PM
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The midterm will cover chapters 1, 2, and 4 from the book.
This includes technology, measuring system performance, instruction sets, single cycle architecture, and pipeline architecture.

You are allowed one 8.5x11 sheet of *handwritten* notes.

Final: Tuesday, March 20, 2018 at 8 AM
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The final will cover chapters 5 and 6 from the book.
This includes memory technology, cache design, virtual memory, parallel programming, and parallel architectures.

You are allowed one 8.5x11 sheet of *handwritten* notes.

.. _schedule:

Reading List and Schedule
-------------------------

Textbook
~~~~~~~~

In this class, we'll be closely following *Computer Organization and Design MIPS Edition, Fifth Edition: The Hardware/Software Interface* by D. A. Patterson and J. L. Hennessy.

Importantly, you should get the *MIPS edition*, not the ARM edition.
The correct version is white with a picture of an abacus on a tablet.
You can find the book at the `university bookstore`_ or through various sites online.

.. _university bookstore: http://ucdavisstores.com/SelectTermDept

Schedule
~~~~~~~~

https://github.com/jlpteaching/ECS154B/blob/master/syllabus/schedule.csv

.. csv-table:: Schedule
    :file: schedule.csv
    :header-rows: 1
    :widths: 10, 10, 25, 12, 10
