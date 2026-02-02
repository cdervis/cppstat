## What It Does

The `__COUNTER__` predefined macro expands to an integer literal that starts at 0
and increments by 1 each time it is expanded within a translation unit.
Each expansion produces a unique value, enabling generation of distinct identifiers or values at compile time.

## Why It Matters

Generating unique identifiers in macros previously required manual numbering or reliance on
`__LINE__`, which fails when multiple expansions occur on the same line.
`__COUNTER__` provides a reliable mechanism for creating unique names in macro-generated code.

## Example

```c
#include <stdio.h>

#define CONCAT_IMPL(a, b) a ## b
#define CONCAT(a, b) CONCAT_IMPL(a, b)
#define UNIQUE_NAME(prefix) CONCAT(prefix, __COUNTER__)

#define MAKE_TEMP(value) \
    int UNIQUE_NAME(temp_) = (value)

int main(void) {
    MAKE_TEMP(10);  // Creates temp_0
    MAKE_TEMP(20);  // Creates temp_1
    MAKE_TEMP(30);  // Creates temp_2

    printf("temp_0 = %d\n", temp_0);
    printf("temp_1 = %d\n", temp_1);
    printf("temp_2 = %d\n", temp_2);
}
```
