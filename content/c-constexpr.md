---
execute: true
show_assembly: true
---

## What It Does

`constexpr` specifies that an object's value is a constant expression and must be computable
at compile time. Unlike `const`, which permits runtime initialization, `constexpr` objects
must be initialized with values known during compilation. The initializer must consist of
constant expressions only.

## Why It Matters

`const` objects in C can be initialized at runtime, so they cannot be used in contexts
requiring compile-time constants (array sizes in some contexts, case labels). `constexpr`
guarantees compile-time evaluation, making objects usable wherever constant expressions
are required.

## Example

```c
#include <stdio.h>

constexpr int array_size = 10;
constexpr double pi = 3.14159265358979;

int main(void) {
    int arr[array_size];  // OK: array_size is a constant expression

    constexpr int doubled = array_size * 2;
    printf("Array size: %d, doubled: %d\n", array_size, doubled);
    printf("Pi: %f\n", pi);
}
```
