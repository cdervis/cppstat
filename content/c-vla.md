---
execute: true
show_assembly: true
flags: "-std=c99"
---

## What It Does

Variable-length arrays (VLAs) have a size determined at runtime rather than compile time.
The array is allocated on the stack with automatic storage duration. VLAs can be declared
in block scope with sizes computed from runtime expressions.

## Why It Matters

Fixed-size arrays require compile-time constants, often leading to oversized allocations
or dynamic allocation with `malloc()`. VLAs provide stack-allocated arrays with sizes known
only at runtime, useful for algorithms where the size depends on function parameters.

## Example

```c
#include <stdio.h>

void print_matrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int n = 3;
    int arr[n];  // VLA with runtime size

    for (int i = 0; i < n; i++)
        arr[i] = i * 10;

    printf("VLA contents: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
    print_matrix(2, 3, matrix);
}
```
