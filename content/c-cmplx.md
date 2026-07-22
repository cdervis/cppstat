## What It Does

`CMPLX(x, y)` is a function-like macro in `<complex.h>` that builds a `double complex` value whose
real part is `x` and whose imaginary part is `y`, each converted to `double`. `CMPLXF` and `CMPLXL`
do the same for `float complex` and `long double complex`. Each may appear in a static initializer
whenever both arguments could themselves initialize the corresponding real type statically.

## Why It Matters

There was no portable expression that constructs an arbitrary complex value component by component.
The idiomatic `x + y*I` breaks when `I` has complex type, which is the usual case because imaginary
types are optional. If `y` is an infinity or a NaN, `y*I` yields a complex value whose real part is
NaN rather than zero, and adding `x` then contaminates the real part, so the result is not `x + iy`.
The macros behave as if `I` were purely imaginary, routing each argument into exactly one component.
That keeps infinities and NaNs confined to the part they belong to, and makes construction usable in
static initializers, which the earlier form could not reliably support.

## Example

```c
#include <complex.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    double complex a = CMPLX(3.0, INFINITY);
    double complex b = 3.0 + INFINITY * I;

    printf("CMPLX: re=%g im=%g\n", creal(a), cimag(a));
    printf("naive: re=%g im=%g\n", creal(b), cimag(b));
    return 0;
}
```
