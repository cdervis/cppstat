---
execute: true
show_assembly: true
flags: "-std=c99"
---

## What It Does

Compound literals create unnamed objects of a specified type using the syntax
`(type){initializer}`. The object has automatic storage duration when created in block
scope and static storage duration at file scope. They can be used wherever an lvalue
of that type is expected.

## Why It Matters

Passing structures or arrays to functions previously required declaring named variables.
Compound literals allow creating temporary aggregates inline, simplifying function calls
and reducing the need for intermediate variables.

## Example

```c
#include <stdio.h>

struct Point { int x, y; };

void print_point(struct Point p) {
    printf("(%d, %d)\n", p.x, p.y);
}

int sum_array(int* arr, int n) {
    int total = 0;

    for (int i = 0; i < n; i++) {
        total += arr[i];
    }

    return total;
}

int main(void) {
    // Compound literal as function argument
    print_point((struct Point){10, 20});

    // Compound literal array
    int total = sum_array((int[]){1, 2, 3, 4, 5}, 5);
    printf("Sum: %d\n", total);

    // Taking address of compound literal
    int* ptr = (int[]){100, 200, 300};
    printf("Second element: %d\n", ptr[1]);
}
```
