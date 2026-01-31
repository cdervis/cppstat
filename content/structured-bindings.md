---
execute: true
---

## What It Does

Structured bindings decompose tuples, pairs, arrays, and structs into named identifiers
within a single declaration. This mechanism extracts elements without explicit accessor
syntax (`.first`, `.second`, `std::get<N>()`).

## Why It Matters

Accessing decomposable types via `.first`, `.second`, or `std::get<N>()` obscures the
semantic meaning of each element. Structured bindings bind identifiers to components at the
declaration site, making data member intent explicit.

## Example

```cpp
#include <map>
#include <string>
#include <tuple>
#include <print>

using namespace std::string_literals;

struct Point {
    int x;
    int y;
};

std::tuple<int, std::string, double> get_data() {
    return {42, "hello", 3.14};
}

int main() {
    // Unpack tuple
    auto [id, name, value] = get_data();

    // Iterate map with clear names
    auto scores = std::map<std::string, int>{
        {"Alice", 95},
        {"Bob", 87},
    };

    for (const auto& [player, score] : scores) {
        std::println("{}: {}", player, score);
    }

    // Works with arrays
    int arr[] = {1, 2, 3};
    auto [a, b, c] = arr;

    // Works with structs
    auto p = Point{.x = 10, .y = 20};
    auto [x, y] = p;

    std::println("a={}, b={}, c={}", a, b, c);
    std::println("x={}, y={}", x, y);
}
```
