---
execute: true
show_assembly: true
---

## What It Does

`auto` in C23 enables type inference for object definitions with initializers. The compiler
deduces the type from the initializer expression. This applies only to object definitions,
not to function parameters or return types.

## Why It Matters

Declaring objects with complex types required writing the full type name, even when the
type was obvious from the initializer. Type inference reduces redundancy and makes code
more concise when the type is clear from context.

## Example

```c
#include <stdio.h>

int main(void) {
    auto x = 42;           // int
    auto pi = 3.14159;     // double
    auto c = 'A';          // int (character constants have type int in C)

    int arr[] = {1, 2, 3};
    auto ptr = arr;        // int*

    printf("x = %d, pi = %f, c = %c\n", x, pi, c);
    printf("First element: %d\n", *ptr);
}
```
