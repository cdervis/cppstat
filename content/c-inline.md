---
execute: true
show_assembly: true
flags: "-std=c99"
---

## What It Does

`inline` serves two purposes: it suggests that the compiler substitute the function body at
call sites rather than performing a function call, and it controls the linkage of functions
defined in headers. An inline function definition allows multiple translation units to share
the same function definition without causing "multiple definition" linker errors.
The compiler may ignore the inlining hint.

## Why It Matters

Function calls have overhead: saving registers, pushing arguments, jumping, and returning.
For small, frequently called functions, this overhead can dominate. Inlining eliminates this
overhead and enables further optimizations by exposing the function body to the calling
context.
Without `inline`, placing a function definition in a header file causes linker errors when
multiple translation units include that header. `inline` allows functions to be defined in
headers and shared across translation units while maintaining proper linkage.

## Example

```c
#include <stdio.h>

static inline int max(int a, int b) {
    return a > b ? a : b;
}

static inline int square(int x) {
    return x * x;
}

int main(void) {
    int a = 10;
    int b = 20;

    // Compiler may inline these calls
    printf("max(%d, %d) = %d\n", a, b, max(a, b));
    printf("square(%d) = %d\n", a, square(a));

    // Expression using inline functions
    printf("max of squares: %d\n", max(square(a), square(b)));
}
```
