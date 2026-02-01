---
execute: true
show_assembly: true
---
## What It Does

`nullptr` is a null pointer constant with type `nullptr_t`. It implicitly converts to any
pointer type but not to integer types. The type `nullptr_t` is defined in `<stddef.h>`.

## Why It Matters

The macro `NULL` is defined as an integer constant (typically `0` or `(void*)0`), which
can match integer parameters in overloaded or generic contexts. `nullptr` has a distinct
type that converts only to pointers, eliminating ambiguity in type-generic code and
improving type safety.

## Example

```c
#include <stdio.h>
#include <stddef.h>

void process(int *ptr) {
    if (ptr == nullptr) {
        printf("Received null pointer\n");
    } else {
        printf("Value: %d\n", *ptr);
    }
}

int main(void) {
    int x = 42;
    process(&x);
    process(nullptr);
}
```
