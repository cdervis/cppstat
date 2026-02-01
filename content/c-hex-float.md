---
execute: true
show_assembly: true
flags: "-std=c99"
---

## What It Does

Hexadecimal floating-point constants use the format `0xH.HHHpE` where `H` represents hexadecimal
digits, `p` introduces the binary exponent, and `E` is a decimal exponent applied to power of 2.
The value is `mantissa × 2^exponent`.

## Why It Matters

Decimal floating-point literals cannot represent all binary floating-point values exactly.
Hexadecimal floating-point literals specify the exact bit pattern, enabling precise
representation of specific floating-point values without rounding errors from decimal conversion.

## Example

```c
#include <stdio.h>
#include <float.h>

int main(void) {
    double one = 0x1.0p0;           // 1.0 × 2^0 = 1.0
    double two = 0x1.0p1;           // 1.0 × 2^1 = 2.0
    double half = 0x1.0p-1;         // 1.0 × 2^-1 = 0.5
    double pi_approx = 0x1.921fb54442d18p+1;  // Close to π

    printf("one = %f\n", one);
    printf("two = %f\n", two);
    printf("half = %f\n", half);
    printf("pi_approx = %.15f\n", pi_approx);

    // Exact representation of specific values
    double smallest_normal = 0x1.0p-1022;  // DBL_MIN
    printf("Smallest normal: %e\n", smallest_normal);
}
```
