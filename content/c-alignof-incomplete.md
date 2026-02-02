## What It Does

The `alignof` operator can now be applied to incomplete array types.
The alignment of an incomplete array type is the same as the alignment of its element type.

## Why It Matters

Previously, `alignof` required a complete type, which prevented querying the alignment
of array types with unknown bounds at the point of use.
Since array alignment depends only on the element type, this restriction was unnecessary.

## Example

```c
#include <stdio.h>
#include <stdalign.h>

extern int incomplete_array[];

int main(void) {
    // Alignment of incomplete array equals element alignment
    printf("alignof(int[]) = %zu\n", alignof(int[]));
    printf("alignof(int) = %zu\n", alignof(int));

    printf("alignof(double[]) = %zu\n", alignof(double[]));
    printf("alignof(double) = %zu\n", alignof(double));

    // Works with extern declarations
    printf("alignof(incomplete_array) = %zu\n", alignof(incomplete_array));
}
```
