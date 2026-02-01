---
execute: true
show_assembly: true
---
## What It Does

`[[unsequenced]]` indicates that a function has no side effects and its return value depends
only on its arguments, not on any state. `[[reproducible]]` indicates that consecutive calls
with the same arguments in the same program state return the same value. These attributes
enable compiler optimizations.

## Why It Matters

Compilers cannot always determine whether a function has side effects or depends on external
state. These attributes communicate function properties to the compiler, enabling optimizations
like eliminating redundant calls or reordering operations that would otherwise require
conservative assumptions.

## Example

```c
#include <stdio.h>

[[unsequenced]] int square(int x) {
    return x * x;
}

[[reproducible]] int get_cached_value(int key) {
    static int cache[10] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};
    return cache[key % 10];
}

int main(void) {
    int a = square(5);
    int b = square(5);  // Compiler may optimize to reuse 'a'

    printf("a = %d, b = %d\n", a, b);
    printf("cached: %d\n", get_cached_value(3));
}
```
