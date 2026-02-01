---
execute: true
show_assembly: true
---

## What It Does

Integer constants can be written in binary using the `0b` or `0B` prefix followed by binary
digits (0 and 1). Binary literals can include digit separators (single quotes) for readability.

## Why It Matters

Bit manipulation code with hexadecimal or decimal constants requires mental conversion to
understand bit patterns. Binary literals express bit patterns directly, making hardware
register values, masks, and flag combinations self-documenting.

## Example

```c
#include <stdio.h>

int main(void) {
    int mask = 0b11110000;           // 240 in decimal
    int flags = 0b0000'0101;         // With digit separator

    int value = 0b10101010;
    int result = value & mask;

    printf("mask = %d (0x%X)\n", mask, mask);
    printf("flags = %d\n", flags);
    printf("value & mask = %d (0b", result);

    // Print binary representation
    for (int i = 7; i >= 0; i--) {
        printf("%d", (result >> i) & 1);
    }

    printf(")\n");
}
```
