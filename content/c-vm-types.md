---
execute: true
show_assembly: true
flags: "-std=c99"
---

## What It Does

Variably-modified types are types of variable-length arrays or types derived from VLAs,
e.g. pointers to VLAs or multi-dimensional arrays types where some dimension is variable.

## Why It Matters

Variably-modified types encode the number of elements of arrays in their type.  This
allows convenient indexing into multi-dimenional arrays, recovery of the number of
elements from the type, and enables improved static analysis and automatic bounds checking.

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
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
    print_matrix(2, 3, matrix);
}
```
