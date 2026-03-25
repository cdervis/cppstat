---
execute: true
---

## What It Does

The `inline` specifier can be applied to variables, giving them the same linkage semantics as inline functions.
An inline variable can be defined in a header and included in multiple translation units without causing
multiple-definition errors. The linker merges all definitions into a single instance.

## Why It Matters

Before inline variables, defining a constant or static data member in a header required a separate definition
in exactly one source file, or workarounds like function-local statics or template tricks.
Inline variables allow header-only definitions of global constants and static data members with
guaranteed single initialization.

## Example

```cpp
#include <print>

struct Config {
    static inline int max_retries = 3;
    static inline const char* app_name = "game";
};

inline constexpr double pi = 3.14159265358979323846;

int main() {
    std::println("app: {}", Config::app_name);
    std::println("max retries: {}", Config::max_retries);
    std::println("pi: {}", pi);
}
```
