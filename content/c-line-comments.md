---
execute: true
show_assembly: true
flags: "-std=c99"
---

## What It Does

Single-line comments beginning with `//` extend to the end of the line. Everything from `//`
to the newline is treated as a comment and ignored by the compiler. This is in addition to
the traditional `/* */` block comment syntax.

## Why It Matters

Block comments (`/* */`) cannot be nested and require matching delimiters. Line comments
are self-terminating at the newline, making them suitable for quick annotations and
end-of-line explanations without the risk of unterminated comments.

## Example

```c
#include <stdio.h>

int main(void) {
    int x = 10;  // Initialize counter

    // Loop from 0 to x-1
    for (int i = 0; i < x; i++) {
        printf("%d ", i);  // Print each value
    }

    printf("\n");

    // Traditional comments still work
    /* This is a
       multi-line comment */

    // int y = 20;  // This line is commented out

    return 0;
}
```
