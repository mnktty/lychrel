#ifndef _LYCHREL_H_
#define _LYCHREL_H_

#include <stdbool.h>            /* requires std=gnu99 */

typedef unsigned long long u64;
typedef unsigned int u32;

typedef struct {
    u64 output;
    u32 iterations;
    bool converged;
} Result;

bool is_palindrome(const u64 input);
u64 reverse(u64 input);
void lychrel(const u64 input, Result* const r);

#endif /* _LYCHREL_H_ */
