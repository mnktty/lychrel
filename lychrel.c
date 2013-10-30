#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <limits.h>
#include <assert.h>

/* Written in C, against Bob Martin's screencast assignment *PRIOR* to viewing
 * the screen cast. Took approximately 1 hr to get it working and may be another
 * 1hour to finish it completely (extend to u64 and stuff like that). Maximum
 * time was spent in deciding the algorithm - split digits, reverse digits and
 * whether to use a stack datastructure and ensuring tests for those work
 *
 * Written in C++, it would have a couple of nicer interfaces (e.g. Stack as a
 * class). Perhaps also extensible to work with a test table and robot  */


/* u64 will not need more than 32 digits */
#define MAX_SIZE (32)

typedef unsigned long long u64;
typedef unsigned int u32;

typedef struct { 
    u32 buffer[MAX_SIZE];
    u32 size;
} Stack;

typedef struct {
    u64 output;
    u32 iterations;
    bool converged;
} Result;


void init_stack(Stack* const restrict s) {
    memset (s, 0, sizeof(Stack));
}

static inline void push_stack(Stack* const restrict s, const u64 elem) {
    /* stack grows from index 0 */
    assert(s && s->size < MAX_SIZE);
    s->buffer[s->size++] = elem;
}

void split_digits(Stack* const restrict s, u64 input) {
    assert(s && s->size < MAX_SIZE);
    u32 rem = 0;

    /* least significant digits will be pushed first */
    while(input) {
        rem = input % 10;
        push_stack(s, rem);
        input /= 10;
    }
}

bool is_palindrome(const u64 input) {
    static Stack s;
    init_stack(&s);
    split_digits(&s, input);

    int i;
    for (i = 0; i < s.size/2; ++i) {
        if (s.buffer[i] != s.buffer[s.size-1-i])
            return false;
    }
    return true;
}

u64 reverse(u64 input) {
    u64 output = 0;
    while (input) {
        output = output * 10 + input % 10;
        input /= 10;
    }
    return output;
}

static inline u64 next_number(const u64 input) {
    return input + reverse(input);
}

Result lychrel(const u64 input) {
    Result r = {.output = -1, .iterations = 0, .converged = false};
    u64 next, current;
    next = current = input;     /* next and current numbers in the chain */

    while(1) {
        if (is_palindrome(next)) {
            r.output = next;
            r.converged = true;
            break;
        }

        next = next_number(current);
        ++r.iterations;

        /* handle u64 overflow */
        if ((ULLONG_MAX - current < next)) {
            r.output = next;
            break;
        }

        // printf("%lld --> %lld : %d\n", current, next, r.iterations);
        current = next;
    }    
    return r;
}

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
        Result r = lychrel(input_vector[i]);
        char *message = r.converged ? 
            "Lychrel Number, converges after %d iterations: %lld --> %lld\n" : 
            "NOT Lychrel Number, no convergence after %d iterations (u64 overflows): %lld --> %lld\n";
        printf(message, r.iterations, input_vector[i], r.output);
    }
}


int main(int argc, char *argv[]) {
    // testAllHelpers();
    testLychrel();
    return 0;
}

/* eof */
