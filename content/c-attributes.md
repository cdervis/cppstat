---
execute: true
show_assembly: true
---

## What It Does

C23 introduces standard attributes using the `[[attribute]]` syntax. Standard attributes
include `[[nodiscard]]`, `[[maybe_unused]]`, `[[deprecated]]`, `[[fallthrough]]`, and
`[[noreturn]]`. The `__has_c_attribute` preprocessor operator tests for attribute support.

## Why It Matters

Compiler-specific attributes like `__attribute__` (GCC/Clang) and `__declspec` (MSVC)
are not portable. Standard attributes provide a uniform syntax across compilers, enabling
portable code that communicates intent to the compiler for diagnostics and optimization.

## Example

```c
#include <stdio.h>
#include <stdlib.h>

[[nodiscard]] int compute(int x) {
    return x * 2;
}

[[deprecated("use new_function instead")]]
void old_function(void) {}

[[noreturn]] void fatal_error(const char* msg) {
    fprintf(stderr, "Fatal: %s\n", msg);
    exit(1);
}

int main(void) {
    [[maybe_unused]] int unused_var = 10;

    int result = compute(5);  // OK: result is used
    // compute(5);            // Warning: nodiscard value ignored

    printf("Result: %d\n", result);
}
```
