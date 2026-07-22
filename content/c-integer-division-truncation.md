## What It Does

For the `/` and `%` operators on signed integer operands, the result of `/` is the algebraic
quotient with any fractional part discarded, so it truncates toward zero. The `%` operator is
defined so that `(a/b)*b + a%b == a` holds, which makes the sign of the remainder follow the
dividend. So `-7/3` yields `-2` and `-7%3` yields `-1`, while `7/-3` yields `-2` and `7%-3` yields
`1`. Division by zero remains undefined behavior. The `div`, `ldiv`, and `lldiv` library functions
share the same truncating semantics and return the quotient and remainder together.

## Why It Matters

Previously, when a division was inexact and either operand was negative, an implementation could
round the quotient up or down, and the sign of the remainder was implementation-defined. That
latitude let a compiler map `/` directly onto whatever the target instruction set did natively,
avoiding extra code to normalize the negative cases. The cost was that identical source produced
different results across platforms, and the behavior diverged from Fortran, which always truncates
toward zero. Fixing the result to truncation toward zero makes signed integer division portable and
predictable, and the run-time overhead of enforcing it was judged acceptable.

## Example

```c
#include <stdio.h>

int main(void)
{
    printf("-7/3  = %d, -7%%3  = %d\n", -7 / 3, -7 % 3);
    printf(" 7/-3 = %d,  7%%-3 = %d\n", 7 / -3, 7 % -3);

    int a = -7, b = 3;
    printf("identity holds: %d\n", (a / b) * b + a % b == a);
    return 0;
}
```
