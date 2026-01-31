---
execute: true
---

## What It Does

`views::enumerate()` produces a range of tuples where each tuple contains an index and the corresponding element from the source range.
The view generates indices starting from zero and pairs them with elements from the adapted range.

## Why It Matters

Indexed iteration previously required explicit counter variables or calls to `std::distance()`.
`views::enumerate()` automates index generation and is compatible with any range, including those without random access or a known size.

## Example

```cpp
#include <ranges>
#include <string>
#include <vector>
#include <print>

using namespace std::string_literals;
using namespace std::string_view_literals;

int main() {
    auto names = std::vector{"Alice"s, "Bob"s, "Charlie"s};

    for (const auto& [index, name] : std::views::enumerate(names)) {
        std::println("{}: {}", index, name);
    }

    // Works with any range
    for (const auto& [i, c] : std::views::enumerate("Hello"sv)) {
        std::println("Character {} is '{}'", i, c);
    }
}
```
