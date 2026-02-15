---
execute: true
---

## What It Does

`std::print()` and `std::println()` perform type-safe formatted output using the same format
string syntax as `std::format()`. Output is written directly to `stdout` (or an optional
output stream) without `std::ostream` state management. Format string parsing occurs at compile
time with type verification of arguments.

## Why It Matters

`std::cout` relies on stream insertion operators, maintains mutable global state
(`std::ios_base` flags), and has incomplete Unicode handling. `printf()` provides
format-string syntax but without type safety (undefined behavior on mismatch).
`std::print()` combines format-string notation with compile-time type checking and
proper Unicode support.

## Example

```cpp
#include <print>
#include <string>
#include <vector>
#include <map>

using namespace std::string_literals;

int main() {
    // Basic printing
    std::println("Hello, {}!", "world");

    // Formatted numbers
    std::println("hex: {:#x}, binary: {:#b}", 255, 255);

    // Containers work directly
    auto nums = std::vector{1, 2, 3};
    std::println("numbers: {}", nums);
    std::println("numbers without brackets: {:n}", nums);

    auto ages = std::map<std::string, int>{
        {"Alice"s, 30},
        {"Bob"s, 25},
    };

    std::println("ages: {}", ages);  // {"Alice": 30, "Bob": 25}

    // Print blank line
    std::println();
}
```
