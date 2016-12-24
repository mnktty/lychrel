# Overview

An example for verifying Lychrel numbers, written before watching Robert
Martin's screen cast on Lychrel numbers. You may find details about Lychrel
numbers in https://en.wikipedia.org/wiki/Lychrel_number

I think the C code is quite succint and compact, it was developed with algorithm
and data structures in mind rather than TDD. Of course, tests were written to
get it to work...

The code can be tested in two ways:

1. From C itself: through a couple of functions
2. From Python: using ctypes
3. From Python: using Boost Python, especially while interfacing at low level
   with C++ (not shown in this example)

A small test data table that can be driven using Robot Framework
http://robotframework.googlecode.com/ is also written. 

The (almost) same table is available in `.tsv` and `.txt` (pipe separated)
format for illustration. (I find the former easier for text editing and probably
the latter with excel)

# Pre-requisites

You will need robotframework to be installed - see its user page for
instructions. An idea of how to write keywords for Robot is also expected - see
http://robotframework.org/robotframework/latest/RobotFrameworkUserGuide.html#creating-user-keywords

# Usage

The algorithm (.so) and C test code can be built with the `Makefile`. Do not
forget to set `.so` in the `LD_LIBRARY_PATH` - you can `source setenv.sh` for
this. `CheckLychrel.py` shows how to test it directly (in a data driven manner)
with python. The same tests can be run using Robot (choose either `.tsv` or
`.robot` file as you please) as follows:

    # for running all test cases
    pybot CheckLychrel.robot

    # for using a specific tag
    pybot --include sanity CheckLychrel.robot
    
    # for running a specific testcase by name
    pybot --test "Run Unit Tests Written in C" CheckLychrel.robot

If you like GUI, consider using RIDE (Robot IDE). It offers a nice GUI interface
for test management, editing, search, execution and reporting.

# Tips and Tricks

1. Writing robot-ified python scripts is quite straight forward once python
   calls work. (This can be done either with ctypes or Boost). Note: args (in
   the test file) are strings and should be converted to actual types before
   calling the script.

2. Writing the test file in txt + pipes is better than using tsv. With a tsv
   file tabs have to be exact. It is much better to use the pipe format (I use
   emacs org mode) or RIDE (the Robot IDE) if you are unfamiliar. 

3. The key word that takes args should match a function - e.g. Check Lychrel
   matchs check_lychrel along with parameter positions. See Robot User Guide :
   http://robotframework.googlecode.com/hg/doc/userguide/RobotFrameworkUserGuide.html?r=2.7.6#creating-static-keywords

4. With custom test libs and extended keywords (like what we have here), it can
   become tricky when execution fails. Check if the python script works from the
   command line and if it matches the keyword *before* blaming
   robot. e.g. `run_unit_tests_from_executable` requires valgrind and robot to
   be installed. And the the python code sets `LD_LIBRARY_PATH` with the
   assumption that `.so` is available in current working directory.

5. Bug: RIDE (The Robot IDE) can screw up your test files in txt + pipes - by
   altering the format - if you change the preferences. This was experienced
   while editing `.txt` files with RIDE and saving them as back (in v2.7.7)

