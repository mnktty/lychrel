#!/usr/bin/env python

# Copyright (c) 2013, apillai
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE. 


import ctypes

# converged is a C99 bool type - hence 4 bytes
class Result(ctypes.Structure):
    _fields_ = [ ('output',     ctypes.c_ulonglong),
                 ('iterations', ctypes.c_uint),
                 ('converged',  ctypes.c_uint) ]

    pass


buftype_t = (Result*1) # (ctypes.c_uint*4)

def check_lychrel(num):
    """Python wrapper to C function lychrel(u64 num, Result* r)"""
    lib = ctypes.cdll.LoadLibrary('./liblychrel.so')
    buf = buftype_t()
    lib.lychrel(ctypes.c_ulonglong(num), buf)
    r = buf[0]
    return r.output, r.iterations, r.converged

def check_lychrel_many():
    "Helper function for manual checking"
    for num in (1, 2, 11, 21, 32, 89, 121, 156, 195, 196, 197, 246):
        output, iterations, converged = check_lychrel(num)
        if converged:
            print 'After {0} iterations: {1} --> {2}'.format(iterations, num, output)
        else:
            print 'NO CONVERGENCE after {0} iterations: {1} --> {2}'.format(iterations, num, output)

def verify_lychrel(num, expected_output, expected_iterations):
    """Implements Verify Lychrel Number for Robot-ification."""

    # Robot reads in args as strings, hence converted to int or whatever is
    # appropriate !
    output, iterations, converged = check_lychrel(int(num))
    if (not converged):
        raise AssertionError('No convergence after {0} iterations'.format(iterations))

    if (output != int(expected_output) and 
        iterations != int(expected_iterations)):
        raise AssertionError('Expected: {0} --> {1} after {2} iterations'
                             ', Got {3} after {4} iterations'.format(num, expected_output, expected_iterations,
                                                                     output, iterations))

def run_unit_tests_from_executable():
    "Trigger unit tests written in C"
    import subprocess
    from robot.api import logger

    # if you do this, things will fail (since liblychrel.so cannot be found)
    # subprocess.check_call(['./checklychrel'])
    
    # but calling this is fine since we set the LD_LIBRARY_PATH
    v = subprocess.check_output(['env', 'LD_LIBRARY_PATH=:/home/precise/svn/experiment/lychrel', 'valgrind', './checklychrel'], stderr=subprocess.STDOUT)

    # let us also log the output in the report
    logger.info('Output of C unit tests: {0} '.format(v))
    if not v.find('All heap blocks were freed -- no leaks are possible'):
        raise AssertionError('Valgrind tests failed - check logs to see memory leak details')

# ------------------------------------------------------------

if __name__ == '__main__':
    # verify the programmer's way
    # check_lychrel_many()
    
    # quick check to ensure script called by Robot works 
    # verify_lychrel('1', '1', '0')

    # quick check to verify triggering native executable's execution
    run_unit_tests_from_executable()

    pass

# eof

