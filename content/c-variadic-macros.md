---
execute: true
show_assembly: true
flags: "-std=c99"
---

## What It Does

Variadic macros accept a variable number of arguments using `...` in the parameter list.
The arguments are accessed through `__VA_ARGS__` in the replacement text. This enables
macros that wrap functions like `printf()` with additional behavior.

## Why It Matters

Fixed-argument macros cannot wrap variadic functions like `printf()` or forward arbitrary
argument lists. Variadic macros enable creating logging wrappers, assertion macros with
formatted messages, and other utilities that accept any number of arguments.

## Example

```c
#include <stdio.h>

#define LOG(fmt, ...) printf("[LOG] " fmt "\n", __VA_ARGS__)

#define DEBUG(fmt, ...) fprintf(stderr, "[DEBUG %s:%d] " fmt "\n", \
                                __FILE__, __LINE__, __VA_ARGS__)

#define PRINT(...) printf(__VA_ARGS__)

#define ERROR(code, fmt, ...) do { \
    fprintf(stderr, "Error %d: " fmt "\n", code, __VA_ARGS__); \
} while (0)

int main(void) {
    int x = 42;
    LOG("Value is %d", x);
    DEBUG("Processing item %d of %d", 5, 10);
    PRINT("Hello, %s!\n", "World");
    ERROR(404, "Resource '%s' not found", "/data");
}
```
