## What It Does

C99 permits the first clause of a `for` statement to be a declaration rather than an expression.
Identifiers declared there are scoped to the loop alone, covering the controlling expression, the
update expression, and the body, and they cease to exist once the loop ends. A loop may contain one
such declaration, which can introduce several comma-separated variables, and those variables must
have automatic storage, so only `auto` or `register` are allowed, never `static`, `extern`, or
`typedef`.

## Why It Matters

A loop counter is usually set up at the top of the loop and never used afterward. Under C89 it had
to be declared at the start of the enclosing block, where it stayed in scope for the rest of that
block, inviting accidental reuse and name clashes with unrelated variables. Declaring the counter
inside the `for` statement confines it to a narrower scope covering only the loop, so it does not
modify any outer variable of the same name and is destroyed at loop end, which also gives the
compiler room to optimize. Restricting the clause to a single declaration of automatic-storage
objects keeps the syntax simple.

## Example

```c
#include <stdio.h>

int main(void)
{
    int i = 99; /* outer i, untouched by the loop */

    for (int i = 0, j = 10; i < 3; i++, j--)
        printf("i=%d j=%d\n", i, j);

    printf("outer i is still %d\n", i);
    return 0;
}
```
