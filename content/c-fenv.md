## What It Does

`<fenv.h>` gives a program execution-time access to the floating-point environment. That environment
holds the status flags that record exceptions (invalid, division-by-zero, overflow, underflow,
inexact) and the control modes, chiefly the rounding direction. `feclearexcept`, `fetestexcept`,
`feraiseexcept`, and `fegetexceptflag`/`fesetexceptflag` inspect and manipulate the exception flags;
`fegetround`/`fesetround` read and change the rounding direction among `FE_TONEAREST`,
`FE_TOWARDZERO`, `FE_UPWARD`, and `FE_DOWNWARD`; `fegetenv`, `fesetenv`, `feholdexcept`, and
`feupdateenv` save, restore, and combine the whole environment. `#pragma STDC FENV_ACCESS ON` tells
the translator that code may test flags or depend on non-default modes.

## Why It Matters

IEC 60559 arithmetic defines sticky exception flags and a dynamic rounding direction that hardware
keeps in control registers, but the language had no portable way to reach them. The rounding mode is
inherently dynamic, since a function must inherit its caller's mode, so a static translator-declared
model was rejected. Dynamic modes conflict with optimization, because the translator otherwise
cannot know which rounding is active or whether flags are read. The `FENV_ACCESS` pragma marks the
regions where the environment must be respected and leaves the compiler free elsewhere. `fexcept_t`
is deliberately opaque so implementations can attach extra per-exception information; its values
come only from `fegetexceptflag`.

## Example

```c
#include <fenv.h>
#include <math.h>
#include <stdio.h>

#pragma STDC FENV_ACCESS ON

int main(void)
{
    feclearexcept(FE_ALL_EXCEPT);
    volatile double z = 0.0;
    volatile double q = 1.0 / z;
    (void)q;
    if (fetestexcept(FE_DIVBYZERO))
        printf("divide-by-zero flag raised\n");

    fesetround(FE_DOWNWARD);
    printf("rint(2.5) downward = %.1f\n", rint(2.5));
    fesetround(FE_UPWARD);
    printf("rint(2.5) upward = %.1f\n", rint(2.5));
}
```
