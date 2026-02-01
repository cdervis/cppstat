---
execute: true
show_assembly: true
---

## What It Does

`#elifdef` and `#elifndef` are preprocessor directives that combine `#elif` with `#ifdef`
and `#ifndef` respectively. `#elifdef X` is equivalent to `#elif defined(X)`, and
`#elifndef X` is equivalent to `#elif !defined(X)`.

## Why It Matters

Conditional compilation chains testing macro definitions required the verbose `#elif defined()`
form. The new directives provide concise syntax matching the existing `#ifdef` and `#ifndef`
directives, improving readability of preprocessor conditionals.

## Example

```c
#include <stdio.h>

// #define USE_FEATURE_A
#define USE_FEATURE_B

int main(void) {
#ifdef USE_FEATURE_A
    printf("Feature A enabled\n");
#elifdef USE_FEATURE_B
    printf("Feature B enabled\n");
#elifndef USE_FEATURE_C
    printf("Feature C not defined, using default\n");
#else
    printf("No features\n");
#endif
}
```
