---
execute: true
show_assembly: true
flags: "-std=c99"
---

## What It Does

`restrict` is a type qualifier for pointers that asserts the pointed-to object is accessed
only through that pointer (or pointers derived from it) within its scope. This promise enables
the compiler to perform optimizations that assume no aliasing.

## Why It Matters

When pointers might alias (point to the same memory), the compiler must reload values after
writes through other pointers. The `restrict` qualifier tells the compiler that no aliasing
occurs, enabling optimizations such as keeping values in registers and reordering memory accesses.

## Example

```c
#include <stdio.h>

// Without restrict, compiler assumes a, b, c might overlap
void add_arrays_slow(int* a, int* b, int* c, int n) {
    for (int i = 0; i < n; i++)
        a[i] = b[i] + c[i];
}

// With restrict, compiler assumes no overlap exists
void add_arrays_fast(int* restrict a, int* restrict b, int* restrict c, int n) {
    for (int i = 0; i < n; i++)
        a[i] = b[i] + c[i];
}

int main(void) {
    int x[] = {1, 2, 3};
    int y[] = {4, 5, 6};
    int z[3];

    add_arrays_fast(z, x, y, 3);
    printf("Result: %d %d %d\n", z[0], z[1], z[2]);
}
```
