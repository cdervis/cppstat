## What It Does

Initializers for block-scope arrays, structures, and unions may use non-constant expressions
evaluated at run time, such as variables, arithmetic on them, and function calls. A whole-structure
expression, such as a call returning the appropriate structure type, is accepted as an automatic
structure initializer. Objects with static storage duration keep the older rule, so their
initializers must be constant expressions or string literals.

## Why It Matters

A block-scope aggregate is initialized when its block is entered, so generated code can compute the
initializer at run time, exactly like the element-by-element assignments a programmer would
otherwise write by hand. Nothing about that timing requires the values to be known during
translation, so a constant-expression restriction serves no purpose there and only forces verbose
assignment after the declaration. The restriction survives for static-storage objects because they
are initialized before program startup, where only translation-time-computable values exist. Earlier
C had confined automatic aggregates to constant initializers out of caution about pathological
cases; that caution proved unnecessary.

## Example

```c
#include <stdio.h>

struct point
{
    int x, y;
};

struct point make(int a, int b)
{
    return (struct point){a + b, a - b};
}

int main(void)
{
    int a = 3, b = 7;
    int arr[3] = {a, b, a + b};
    struct point p = {a * 2, b - 1};
    struct point q = make(a, b);

    printf("%d %d %d\n", arr[0], arr[1], arr[2]);
    printf("%d %d\n", p.x, p.y);
    printf("%d %d\n", q.x, q.y);
    return 0;
}
```
