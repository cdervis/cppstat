---
execute: true
---

## What It Does

`std::format()` performs type-safe string formatting using replacement fields with format specifications.
Format specifiers control field width, alignment, precision, and numeric base.
Argument types are verified at compile time against the format string.

## Why It Matters

`printf()` format specifiers are not type-checked, resulting in undefined behavior when specifiers mismatch argument types.
`std::stringstream` requires explicit stream insertion operations and state management.
`std::format()` combines type safety with a declarative format string syntax.

## Example

```cpp
#include <format>
#include <string>
#include <print>

int main() {
    // Basic formatting
    auto s = std::format("Hello, {}!", "world");

    // Positional arguments
    auto msg = std::format("{1} before {0}", "second", "first");

    // Format specifiers
    std::println("{:>10}", "right");    // "     right"
    std::println("{:<10}", "left");     // "left      "
    std::println("{:^10}", "center");   // "  center  "

    // Numbers
    std::println("{:08}", 42);          // "00000042"
    std::println("{:.2f}", 3.14159);    // "3.14"
    std::println("{:#x}", 255);         // "0xff"
    std::println("{:#b}", 7);           // "0b111"
}
```
