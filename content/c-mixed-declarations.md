## What It Does

Inside a block, declarations and statements may appear in any order, freely interleaved. C89
required every declaration in a block to precede all statements; C99 removes that restriction. A
compound statement becomes a sequence of block items, each of which is either a declaration or a
statement. The scope of a declared identifier still begins at its declaration, so code preceding the
declaration cannot refer to the identifier by name even though the object exists once the block is
entered.

## Why It Matters

C89's rule forced all locals to the top of a block, before any code could produce a meaningful value
to initialize them with. Declaring at the point of first use lets initialization sit next to the
computation that supplies the value, and keeps each variable's live region as small as the code that
needs it. Scope beginning at the declaration is what makes this safe. Earlier code cannot
accidentally name an identifier before it is introduced. It also composes with variable-length
arrays, whose size expression is evaluated when the declaration is reached during execution.

## Example

```c
#include <stdio.h>

int main(void)
{
    int values[] = {3, 7, 2, 8};
    int n = 4;

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += values[i];

    /* declaration appears after statements in the same block */
    double average = (double)sum / n;
    printf("sum = %d, average = %.2f\n", sum, average);

    return 0;
}
```
