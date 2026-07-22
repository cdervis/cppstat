## What It Does

A function parameter written with array syntax is adjusted to a pointer. Inside the square brackets
of the outermost array derivation, C99 permits the keyword `static` followed by a size, and the
qualifiers `const`, `volatile`, and `restrict`. Writing `double a[static 10]` tells the compiler the
argument points to the first element of an array holding at least ten elements. A qualifier in the
brackets applies to the adjusted pointer, so `double a[const]` means `double *const a`, and
`restrict` marks it as a restricted pointer.

## Why It Matters

Because an array parameter decays to a plain pointer, the declaration loses any record of how many
elements the caller must supply and any qualification on the pointer itself. Without that
information a translator cannot assume a minimum extent, so it cannot prefetch or vectorize loads of
the elements at function entry. Placing `static N` in the brackets records that at least N elements
are accessible, that the pointer is non-null, and that it points to an object of the appropriate
effective type. The qualifiers let the adjusted pointer be `const`, `volatile`, or `restrict`, and
`restrict` in particular tells the optimizer the named arrays do not overlap, enabling loop
unrolling and reordering of loads and stores. The restriction to the outermost derivation reflects
that only there does the syntax describe the pointer the parameter becomes.

## Example

```c
#include <stdio.h>

double average(const double a[static const 3])
{
    return (a[0] + a[1] + a[2]) / 3.0;
}

int main(void)
{
    double values[3] = {4.0, 6.0, 8.0};
    printf("average = %.2f\n", average(values));
    return 0;
}
```
