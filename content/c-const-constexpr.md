## What It Does

Const integer declarations with constant expression initializers are implicitly treated
as `constexpr`. A `const`-qualified integer variable initialized with a constant expression
in the same declaration becomes a compile-time constant, usable in contexts requiring
constant expressions such as array bounds and `_Static_assert`.

## Why It Matters

In C23, `const int n = 10; int arr[n];` created a variable-length array because `n` was
not a constant expression despite its constant initializer.
This conflicted with decades of existing practice where compilers treated such declarations
as compile-time constants. The change aligns the standard with existing implementations.

## Example

```c
#include <stdio.h>

int main(void) {
    const int size = 10;          // Implicitly constexpr
    int array[size];              // Fixed-size array, not VLA

    const int doubled = size * 2; // Also constexpr
    _Static_assert(doubled == 20, "should be 20");

    // Chained constants work
    const int a = 1;
    const int b = a + 1;
    const int c = b + 1;
    _Static_assert(c == 3, "should be 3");

    printf("Array has %d elements\n", size);
}
```
