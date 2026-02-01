---
execute: true
show_assembly: true
flags: "-std=c11"
---

## What It Does

Anonymous structures and unions are members without a declared name. Their members are accessed
directly as if they were members of the containing structure or union, without an intermediate
member name.

## Why It Matters

Nested structures and unions normally require accessing members through the intermediate member
name. Anonymous members flatten the access path, simplifying code that accesses nested data
and enabling natural representation of variant types.

## Example

```c
#include <stdio.h>

struct Vector3 {
    union {
        struct { float x, y, z; };      // Anonymous struct
        float components[3];            // Same memory
    };                                  // Anonymous union
};

struct Variant {
    int type;
    union {
        int i;
        double d;
        char s[16];
    };
};

int main(void) {
    struct Vector3 v = {.x = 1.0f, .y = 2.0f, .z = 3.0f};

    printf("v.x = %f\n", v.x);
    printf("v.components[1] = %f\n", v.components[1]);

    struct Variant var = {.type = 0, .i = 42};
    printf("Integer variant: %d\n", var.i);
}
```
