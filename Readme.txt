Overview
--------

An example for verifying Lychrel numbers, written before watching Robert
Martin's screen cast on Lychrel numbers -
https://en.wikipedia.org/wiki/Lychrel_number

I think the C code is quite succint and compact, it was developed with algorithm
and data structures in mind rather than TDD. Of course, tests were written to
get it to work...

The code can be tested in two ways:

1. From C itself: through a couple of functions
2. From Python: using ctypes

A small test data table that can be driven using Robot Framework
http://robotframework.googlecode.com/ is also written. 

Comments
--------

1. Writing robot-ified scripts is quite straight forward once python calls
   work. (This can be done either with ctypes or Boost). The only caveat is that
   args are strings and hence need conversion to actual types.

2. Writing the TSV file is a little tricky at first - tabs have to be exact.

3. The key word that takes args should match a function - e.g. Check Lychrel
   matchs check_lychrel along with parameter positions. See Robot User Guide :
   http://robotframework.googlecode.com/hg/doc/userguide/RobotFrameworkUserGuide.html?r=2.7.6#creating-static-keywords

