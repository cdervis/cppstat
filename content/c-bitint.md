---
execute: true
show_assembly: true
---

## What It Does

`_BitInt(N)` defines an integer type with exactly N bits of precision. Both signed and
unsigned variants are supported (`unsigned _BitInt(N)`). Bit-precise integer constants
use the `wb` or `uwb` suffix. The maximum supported width is implementation-defined but
at least `BITINT_MAXWIDTH` bits.

## Why It Matters

Standard integer types have implementation-defined sizes, requiring careful selection based
on range requirements. Cryptographic algorithms, hardware interfaces, and arbitrary-precision
arithmetic often need specific bit widths. `_BitInt` provides integers with exact precision,
independent of the platform's native word sizes.

## Example

```c
#include <stdio.h>

int main(void) {
    _BitInt(128) large = 12345678901234567890123456789012345wb;
    unsigned _BitInt(7) small = 100uwb;  // Fits in 7 bits (0-127)

    _BitInt(256) huge = large * 2;

    printf("small = %d\n", (int)small);
    printf("large fits in 128 bits\n");
}
```
