## What It Does

`[[nodiscard]]` marks a function whose return value is not meant to be ignored; it may also be
applied to a structure, union, or enumeration definition. When a call to such a function appears as
a discarded-value expression, the implementation is encouraged to emit a diagnostic. That
encouragement excludes an explicit cast to `void`, which gives callers a way to mark the omission as
deliberate.

## Why It Matters

A declaration cannot express that ignoring a function's result is a mistake, and the function's
author is generally the one positioned to know whether it is. Some results are safe to drop, like
the character count from `printf`; others likely signal a bug when discarded, like the pointer from
`malloc`. Diagnosing every ignored result would produce too many false positives to be on by
default, so the check is opt-in. The author marks the specific functions where discarding the result
is probably an error. Casting the call to `void` lets a caller drop the result deliberately without
the diagnostic.

## Example

```c
#include <stdio.h>

[[nodiscard]] int compute(int x)
{
    return x * 2;
}

int main(void)
{
    int value = compute(21);
    printf("%d\n", value);

    (void)compute(10); // deliberate: the cast suppresses the diagnostic
    compute(5);        // diagnosed: result silently dropped
}
```
