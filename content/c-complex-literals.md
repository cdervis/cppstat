## What It Does

Complex literals allow imaginary numbers to be written directly using the
`i`, `I`, `j`, or `J` suffix on floating-point constants.
The suffix indicates an imaginary value with a real part of zero.
Combined with real constants via addition, this forms complete complex numbers.

## Why It Matters

Constructing complex numbers previously required the `CMPLX` macro or arithmetic operations.
Complex literals enable direct notation that matches mathematical convention and can appear in
contexts requiring constant expressions, such as static initializers.

## Example

```c
#include <stdio.h>
#include <complex.h>

int main(void) {
    // Imaginary literals
    double complex z1 = 3.14i;         // 0 + 3.14i
    float complex z2 = 2.0fi;          // 0 + 2.0i (float)

    // Full complex numbers via addition
    double complex z3 = 2.0 + 3.0i;    // 2 + 3i
    float complex z4 = 1.5f + 0.5fi;   // 1.5 + 0.5i (float)

    printf("z1 = %.2f + %.2fi\n", creal(z1), cimag(z1));
    printf("z3 = %.2f + %.2fi\n", creal(z3), cimag(z3));

    // Constant expressions allowed
    static double complex table[] = {1.0 + 2.0i, 3.0 + 4.0i};
}
```
