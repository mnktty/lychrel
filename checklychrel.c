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
