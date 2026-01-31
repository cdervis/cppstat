---
execute: true
---

## What It Does

`std::source_location` encapsulates source code metadata
(file name, line number, column, and function name) at the point of construction.
It provides a type-safe alternative to the `__FILE__` and `__LINE__` preprocessor macros.

## Why It Matters

Preprocessor macros `__FILE__` and `__LINE__` expand at the point of use,
requiring manual propagation through call hierarchies.
When `std::source_location::current()` is specified as a default function parameter,
the source location of the caller is captured automatically without explicit arguments at the call site.

## Example

```cpp
#include <source_location>
#include <print>

void log(std::string_view message,
         std::source_location loc = std::source_location::current()) {
    std::println("[{}:{}] {}: {}",
        loc.file_name(),
        loc.line(),
        loc.function_name(),
        message);
}

void do_work() {
    log("Starting work");  // automatically captures this location
}

int main() {
    log("Application started");
    do_work();
}
```
