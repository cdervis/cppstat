---
execute: true
show_assembly: true
flags: "-std=c11"
---

## What It Does

`_Static_assert(expression, message)` verifies a condition at compile time. If the expression
evaluates to false, compilation fails with the specified error message. In C23, the message
is optional. The macro `static_assert` from `<assert.h>` provides an alternative spelling.

## Why It Matters

Runtime assertions detect errors only when the assertion executes. Compile-time assertions
catch errors during compilation, before the program runs. This is essential for verifying
type sizes, structure layouts, and other compile-time properties that affect correctness.

## Example

```c
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

struct Packet {
    uint32_t header;
    uint8_t data[12];
};

static_assert(sizeof(struct Packet) == 16, "Packet must be 16 bytes");
static_assert(sizeof(int) >= 4, "int must be at least 32 bits");

int main(void) {
    printf("All static assertions passed\n");
    printf("sizeof(Packet) = %zu\n", sizeof(struct Packet));
}
```
