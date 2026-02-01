---
execute: true
show_assembly: true
---

## What It Does

Enumerations can specify a fixed underlying type using the syntax `enum Name : Type { ... }`.
The underlying type determines the size and signedness of the enumeration.
Without a fixed type, the underlying type is implementation-defined.

## Why It Matters

The size of enumeration types was implementation-defined, complicating binary compatibility
and serialization.
A fixed underlying type guarantees specific storage and range characteristics,
enabling precise control over enumeration layout in structures and data formats.

## Example

```c
#include <stdio.h>
#include <stdint.h>

enum Color : uint8_t {
    RED = 0,
    GREEN = 1,
    BLUE = 2
};

enum LargeValues : int64_t {
    BIG = 1000000000000LL
};

int main(void) {
    printf("sizeof(enum Color) = %zu\n", sizeof(enum Color));
    printf("sizeof(enum LargeValues) = %zu\n", sizeof(enum LargeValues));

    enum Color c = GREEN;
    printf("Color value: %d\n", c);
}
```
