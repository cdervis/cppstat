---
execute: true
show_assembly: true
flags: "-std=c11"
---

## What It Does

`_Alignas(N)` specifies the alignment requirement for a variable or type. `_Alignof(type)`
yields the alignment requirement of a type. The `<stdalign.h>` header provides the alternative
spellings `alignas` and `alignof`.

## Why It Matters

Some hardware operations and data structures require specific alignment for correctness or
performance. SIMD operations may require 16-byte or 32-byte alignment. Memory-mapped hardware
registers may have alignment constraints. These operators provide portable alignment control.

## Example

```c
#include <stdio.h>
#include <stdalign.h>

int main(void) {
    alignas(32) char buffer[64];
    alignas(double) char storage[sizeof(double)];

    printf("Alignment of int: %zu\n", alignof(int));
    printf("Alignment of double: %zu\n", alignof(double));
    printf("Buffer alignment: %zu\n", (size_t)buffer % 32 == 0 ? 32 : 0);
}
```
