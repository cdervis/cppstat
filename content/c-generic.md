---
execute: true
show_assembly: true
flags: "-std=c11"
---

## What It Does

`_Generic(expression, type1: result1, type2: result2, ..., default: resultN)` selects one
of several expressions based on the type of the controlling expression. The result type must
match exactly (no implicit conversions). An optional `default` case handles unmatched types.

## Why It Matters

C lacks function overloading, so type-generic operations required separate function names
or macro tricks. `_Generic` enables type-safe generic macros that select the appropriate
implementation based on argument type, providing a form of compile-time polymorphism.

## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define abs(x) _Generic((x),    \
    int: abs,                   \
    long: labs,                 \
    float: fabsf,               \
    double: fabs                \
)(x)

#define print_type(x) _Generic((x),     \
    int: "int",                         \
    double: "double",                   \
    char*: "char*",                     \
    default: "unknown"                  \
)

int main(void) {
    printf("abs(-5) = %d\n", abs(-5));
    printf("abs(-3.14) = %f\n", abs(-3.14));

    int i = 42;
    double d = 3.14;
    printf("i is %s, d is %s\n", print_type(i), print_type(d));
}
```
