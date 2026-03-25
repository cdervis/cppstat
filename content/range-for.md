---
execute: true
---

## What It Does

`for (auto& x : container)` iterates over all elements of a range.
The compiler expands it to a begin/end iterator loop.
It works with arrays, standard containers, and any type that provides `begin()` and `end()`
member functions or free functions found via [ADL](https://en.cppreference.com/w/cpp/language/adl.html).

## Why It Matters

Before range-for, iterating required explicit iterator type declarations or index-based loops
with manual bounds management.
Range-for provides iteration without exposing iterator types or requiring the user to specify
container sizes or end conditions.

## Example

```cpp
#include <print>
#include <vector>
#include <map>
#include <string>

int main() {
    auto numbers = std::vector{10, 20, 30, 40, 50};

    for (const auto& n : numbers) {
        std::println("{}", n);
    }

    // Works with built-in arrays
    int arr[] = {1, 2, 3};
    auto total = 0;

    for (auto x : arr) {
        total += x;
    }

    std::println("array sum = {}", total);

    // With structured bindings over a map
    auto ages = std::map{
        {std::string_view("Alice"), 30},
        {std::string_view("Bob"), 25}
    };

    for (const auto& [name, age] : ages) {
        std::println("{} is {}", name, age);
    }
}
```
