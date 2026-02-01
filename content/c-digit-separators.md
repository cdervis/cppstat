---
execute: true
show_assembly: true
---

## What It Does

Single quote characters (`'`) can appear within integer and floating-point constants to
separate digit groups. The separators are ignored during compilation and serve only to
improve readability.

## Why It Matters

Large numeric constants are difficult to read without visual separation. Digit separators
allow grouping digits by thousands, bytes, or any logical boundary, making constants like
memory sizes, timestamps, or financial values self-documenting.

## Example

```c
#include <stdio.h>

int main(void) {
    long population = 8'000'000'000;
    int memory_size = 0x0100'0000;           // 16 MB in hex
    int permissions = 0b111'101'101;         // rwxr-xr-x
    double avogadro = 6.022'140'76e23;

    printf("Population: %ld\n", population);
    printf("Memory: %d bytes\n", memory_size);
    printf("Permissions: %o (octal)\n", permissions);
    printf("Avogadro: %e\n", avogadro);
}
```
