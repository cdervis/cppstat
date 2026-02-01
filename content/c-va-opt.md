---
execute: true
show_assembly: true
---

## What It Does

`__VA_OPT__(content)` is a function-like macro that expands to its argument if `__VA_ARGS__`
is non-empty, and expands to nothing if `__VA_ARGS__` is empty. It appears only within the
replacement list of variadic macros.

## Why It Matters

Variadic macros that need to handle both zero and non-zero arguments required compiler-specific
extensions or awkward workarounds to handle the trailing comma problem. `__VA_OPT__` provides
a standard way to conditionally include content based on whether variadic arguments are present.

## Example

```c
#include <stdio.h>

#define LOG(fmt, ...) printf("[LOG] " fmt __VA_OPT__(,) __VA_ARGS__)

int main(void) {
    LOG("Starting program\n");     // No extra args
    LOG("Value: %d\n", 42);        // With args
}
```
