---
execute: true
show_assembly: true
flags: "-std=c11"
---

## What It Does

`_Noreturn` specifies that a function does not return to its caller. In C23, the `[[noreturn]]`
attribute provides an alternative syntax. The `<stdnoreturn.h>` header provides the `noreturn`
macro.

## Why It Matters

Functions that terminate the program (`exit()`, `abort()`) or loop indefinitely never return.
Marking them as noreturn allows the compiler to optimize calling code, eliminating unreachable
code paths and avoiding warnings about missing return statements after such calls.

## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

noreturn void fatal_error(const char *message) {
    fprintf(stderr, "Fatal error: %s\n", message);
    exit(1);
}

int divide(int a, int b) {
    if (b == 0) {
        fatal_error("Division by zero");
        // No return needed here; compiler knows fatal_error doesn't return
    }
    return a / b;
}

int main(void) {
    printf("10 / 2 = %d\n", divide(10, 2));
    // divide(1, 0);  // Would call fatal_error
}
```
