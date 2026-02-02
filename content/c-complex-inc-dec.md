## What It Does

The `++` and `--` operators can now be applied to complex number values.
Incrementing a complex number adds 1 to its real part, and decrementing subtracts 1 from its real part.
The imaginary part remains unchanged.

## Why It Matters

Increment and decrement operators were not defined for complex types in previous C standards.
This addition provides consistency with arithmetic operations on complex numbers, where adding
an integer affects only the real component.

## Example

```c
#include <stdio.h>
#include <complex.h>

int main(void) {
    double complex z = 3.0 + 4.0i;

    printf("Initial: %.1f + %.1fi\n", creal(z), cimag(z));

    ++z;  // Adds 1 to real part
    printf("After ++z: %.1f + %.1fi\n", creal(z), cimag(z));

    z--;  // Subtracts 1 from real part
    printf("After z--: %.1f + %.1fi\n", creal(z), cimag(z));

    // Works in expressions
    double complex w = 1.0 + 2.0i;
    double complex result = ++w + z;
    printf("Result: %.1f + %.1fi\n", creal(result), cimag(result));
}
```
