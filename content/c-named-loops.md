## What It Does

Named loops allow `break` and `continue` statements to target a specific enclosing loop or `switch` by name.
A label placed before an iteration statement or `switch` becomes a target that can be referenced by
`break label;` or `continue label;` to exit or continue that specific statement, even from deeply nested code.

## Why It Matters

Breaking out of multiple nested loops previously required a `goto` statement or additional flag variables.
Named loops provide a structured way to exit or continue outer loops directly, matching functionality
available in Java, JavaScript, and Rust.

## Example

```c
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int target = 5;
    bool found = false;
    int row = -1, col = -1;

    search:
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (matrix[i][j] == target) {
                row = i;
                col = j;
                found = true;
                break search;  // exits both loops
            }
        }
    }

    if (found) {
        printf("Found %d at [%d][%d]\n", target, row, col);
    }
}
```
