/* Copyright (c) 2013, apillai
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. 
*/

#include "lychrel.h"
#include <assert.h>
#include <stdio.h>


void testAllHelpers() {
    int input = 12345;
    assert (54321 == reverse(input));
    assert (!is_palindrome(12345));
    assert(is_palindrome(12321));
    assert(is_palindrome(123454321));
    assert(is_palindrome(1));
    assert(is_palindrome(9));
}

void testLychrel() {
    u64 input_vector[] = {1, 2, 11, 21, 32, 89, 121, 156, 195, 196, 197, 246};

    u32 i;
    for (i = 0; i < 12; ++i) {
        Result r;
        lychrel(input_vector[i], &r);
        char *message = r.converged ? 
            "Lychrel Number, converges after %d iterations: %lld --> %lld\n" : 
            "NOT Lychrel Number, no convergence after %d iterations (u64 overflows): %lld --> %lld\n";
        printf(message, r.iterations, input_vector[i], r.output);
    }
}


int main(int argc, char *argv[]) {
    testAllHelpers();
    testLychrel();
    // printf("sizeof(Result): %d\n", sizeof(Result));
    return 0;
}

/* eof */
