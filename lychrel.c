#include "lychrel.h"
#include <stdio.h>
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

typedef struct { 
    u32 buffer[MAX_SIZE];
    u32 size;
} Stack;

static void init_stack(Stack* const restrict s) {
    memset (s, 0, sizeof(Stack));
}

static inline void push_stack(Stack* const restrict s, const u64 elem) {
    /* stack grows from index 0 */
    assert(s && s->size < MAX_SIZE);
    s->buffer[s->size++] = elem;
}

static void split_digits(Stack* const restrict s, u64 input) {
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

void lychrel(const u64 input, Result* const r) {

    assert(r);
    r->output = -1;
    r->iterations = 0;
    r->converged = false;

    u64 next, current;
    next = current = input;     /* next and current numbers in the chain */

    while(1) {
        if (is_palindrome(next)) {
            r->output = next;
            r->converged = true;
            break;
        }

        next = next_number(current);
        ++r->iterations;

        /* handle u64 overflow */
        if ((ULLONG_MAX - current < next)) {
            r->output = next;
            break;
        }

        // printf("%lld --> %lld : %d\n", current, next, r->iterations);
        current = next;
    }    
}

/* eof */
