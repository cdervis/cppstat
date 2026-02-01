---
execute: true
show_assembly: true
---

## What It Does

Empty initializers `{}` zero-initialize an object. For structures and arrays, all members
and elements are zero-initialized. For unions, the first member is zero-initialized.
This applies to both scalar and aggregate types.

## Why It Matters

Zero-initializing aggregates previously required explicit `{0}`, which triggers warnings
in some compilers when applied to structures whose first member is itself an aggregate.
Empty braces provide unambiguous zero-initialization for any type without such warnings.

## Example

```c
#include <stdio.h>

struct Point {
    int x, y;
};

int main(void) {
    struct Point p = {};   // Both members zero-initialized
    int arr[5] = {};       // All elements zero-initialized
    int scalar = {};       // Zero-initialized

    printf("Point: (%d, %d)\n", p.x, p.y);
    printf("Array[0]: %d\n", arr[0]);
    printf("Scalar: %d\n", scalar);
}
```
