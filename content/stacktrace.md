---
execute: true
flags: "-lstdc++exp"
---

## What It Does

`std::stacktrace` captures the current call stack at runtime.
The resulting stack trace object provides iteration over stack frames, each containing function
names, source file paths, and line numbers.

## Why It Matters

Call stack inspection previously required platform-specific APIs (e.g., `execinfo.h` on POSIX,
`StackWalk64` on Windows) or third-party libraries. `std::stacktrace` provides a portable
interface to stack unwinding functionality as a standard library facility.

## Example

```cpp
#include <stacktrace>
#include <print>

void inner_function() {
    auto trace = std::stacktrace::current();

    std::println("Stack trace:");
    for (const auto& frame : trace) {
        std::println("  {} at {}:{}",
            frame.description(),
            frame.source_file(),
            frame.source_line());
    }
}

void outer_function() {
    inner_function();
}

int main() {
    outer_function();
}
```
