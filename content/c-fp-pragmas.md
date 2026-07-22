## What It Does

C99 reserves the pragma namespace whose first preprocessing token is `STDC` for standard directives
and defines three pragmas that control how the translator handles floating-point code.
`#pragma STDC FP_CONTRACT` sets whether expressions may be contracted, for example into a fused
multiply-add that rounds once. `#pragma STDC FENV_ACCESS` sets whether the program may access the
floating-point environment, meaning rounding modes and exception flags.
`#pragma STDC CX_LIMITED_RANGE` sets whether the shorter complex multiply and divide formulas may be
used. Each takes an on-off-switch of `ON`, `OFF`, or `DEFAULT`. Each must appear at file scope or at
the start of a compound statement, before any statement or declaration, and its effect runs to the
end of that scope.

## Why It Matters

These settings are directions to the compiler about code generation, not runtime operations, so they
must live in the translation unit and be known at compile time. The lexical, scoped placement lets
the compiler bound exactly which regions of code each mode governs. A reserved `STDC` namespace
keeps standard directives from colliding with the vendor-specific pragmas compilers already defined.
Under `FENV_ACCESS OFF` the implementation need not maintain the exception flags, so aggressive
optimization stays available where the program does not inspect them.

## Example

```c
#include <fenv.h>
#include <stdio.h>

#pragma STDC FENV_ACCESS ON
#pragma STDC FP_CONTRACT OFF

int main(void)
{
    volatile double num = 1.0, den = 3.0;
    feclearexcept(FE_ALL_EXCEPT);
    volatile double x = num / den;
    int inexact = fetestexcept(FE_INEXACT) != 0;
    printf("1.0/3.0 = %.17g (%s)\n", x, inexact ? "FE_INEXACT raised" : "exact");
    return 0;
}
```
