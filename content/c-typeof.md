---
execute: true
show_assembly: true
---

## What It Does

`typeof` and `typeof_unqual` are operators that yield the type of an expression or type name.
`typeof` preserves all qualifiers (const, volatile, restrict), while `typeof_unqual` removes
the top-level cv-qualifiers. Both can be used wherever a type name is expected.

## Why It Matters

Declaring variables with the same type as another expression previously required manual type
specification or compiler-specific extensions like `__typeof__`. The standard `typeof` operator
provides a portable way to derive types from expressions, and `typeof_unqual` addresses the
common need to obtain the unqualified version of a type.

## Example

```c
#include <stdio.h>

int main(void) {
    const int x = 42;

    typeof(x) y = 10;              // y has type const int
    typeof_unqual(x) z = 20;       // z has type int (no const)

    // z = 30;  // OK: z is not const
    // y = 30;  // Error: y is const

    printf("y = %d, z = %d\n", y, z);
}
```
