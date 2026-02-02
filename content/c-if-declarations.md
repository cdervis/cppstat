## What It Does

If declarations allow a variable declaration with initialization in the condition of an `if` statement.
The declared variable's scope extends through the entire `if`/`else` block,
and its initialized value serves as the controlling expression.

## Why It Matters

Declaring a variable and testing it previously required either a separate declaration before the
`if` or an additional scope block.
If declarations reduce variable scope to where it is actually needed and eliminate the pattern of
declaring, initializing, and testing in three separate steps.

## Example

```c
#include <stdio.h>
#include <stdlib.h>

int get_value(void) {
    return 42;
}

int main(void) {
    // Variable 'x' exists only within the if/else block
    if (int x = get_value()) {
        printf("Got non-zero value: %d\n", x);
    } else {
        printf("Got zero\n");
    }
    // 'x' is not accessible here

    // Works with pointers too
    if (char *env = getenv("HOME")) {
        printf("HOME = %s\n", env);
    }
}
```
