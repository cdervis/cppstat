## What It Does

When the return type of `main` is compatible with `int`, reaching the closing brace that terminates
`main` without executing a `return` statement returns a value of `0` to the host environment,
exactly as if `return 0;` had run. Zero denotes successful termination. A return from the initial
call to `main` is equivalent to calling `exit` with the returned value as its argument. If `main`'s
return type is not compatible with `int`, the status returned to the host environment is
unspecified, and this guarantee does not apply.

## Why It Matters

Without the rule, a `main` that ends without an explicit `return` would hand an indeterminate exit
status to the host environment, so even short programs had to write `return 0;` purely to obtain a
deterministic, successful status. Fixing the implicit value at `0` matches the common intent and
removes that boilerplate. The behavior is restricted to `main` whose return type is compatible with
`int` because a fixed integer `0` is meaningful only for an `int`-returning function; for any other
return type the standard leaves the status unspecified rather than inventing a conversion.

## Example

```c
#include <stdio.h>

int main(void)
{
    printf("reached the end of main\n");
    /* No return statement: the exit status is implicitly 0 (success). */
}
```
