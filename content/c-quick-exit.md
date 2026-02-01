---
execute: true
show_assembly: true
flags: "-std=c11"
---

## What It Does

`quick_exit()` terminates the program, calling functions registered with `at_quick_exit()`
but not `atexit()` handlers or signal handlers. It provides a faster termination path than
`exit()` when cleanup registered with `atexit()` is unnecessary or harmful.

## Why It Matters

`exit()` runs all `atexit()` handlers, which may be undesirable when terminating from a
signal handler or when rapid shutdown is needed. `quick_exit()` provides controlled
termination that skips potentially problematic cleanup while still running handlers
specifically registered for quick termination.

## Example

```c
#include <stdio.h>
#include <stdlib.h>

void normal_cleanup(void) {
    printf("Normal cleanup (atexit)\n");
}

void quick_cleanup(void) {
    printf("Quick cleanup (at_quick_exit)\n");
}

int main(void) {
    atexit(normal_cleanup);
    at_quick_exit(quick_cleanup);

    printf("Program running...\n");

    // quick_exit(0);  // Only calls quick_cleanup
    exit(0);           // Only calls normal_cleanup
}
```
