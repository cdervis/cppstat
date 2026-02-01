---
execute: true
show_assembly: true
---

## What It Does

`true`, `false`, and `bool` are predefined keywords in C23. `bool` is a standard type,
and `true` and `false` are constants of type `bool` with values 1 and 0 respectively.
Including `<stdbool.h>` is no longer necessary.

## Why It Matters

Prior to C23, using boolean types required including `<stdbool.h>`, which defined `bool`
as a macro for `_Bool` and `true`/`false` as macros for 1 and 0. Making these keywords
simplifies boolean usage and aligns C with other languages.

## Example

```c
#include <stdio.h>

bool is_even(int n) {
    return n % 2 == 0;
}

int main(void) {
    bool flag = true;
    bool result = is_even(42);

    printf("flag: %s\n", flag ? "true" : "false");
    printf("42 is even: %s\n", result ? "true" : "false");
    printf("sizeof(bool): %zu\n", sizeof(bool));
}
```
