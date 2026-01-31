---
execute: true
---

## What It Does

Generic lambdas declare parameters with `auto`, producing a function call operator template. The compiler instantiates the appropriate specialization based on the argument types at each call site, so you don't need explicit template syntax in the lambda definition.

## Why It Matters

Prior to C++14, lambdas required explicit parameter types. Implementing type-generic behavior necessitated separate template functions. Generic lambdas integrate template instantiation directly into lambda expressions, enabling polymorphic inline function objects without separate template definitions.

## Example

```cpp
#include <vector>
#include <string>
#include <algorithm>
#include <print>

using namespace std::string_literals;

int main() {
    // Works with any type
    auto print = [](const auto& x) {
        std::println("{}", x);
    };

    print(42);      // int
    print(3.14);    // double
    print("hello"); // const char*

    // Useful in algorithms
    auto twice = [](auto x) { return x + x; };

    std::println("{}", twice(5));          // 10
    std::println("{}", twice(2.5));        // 5.0
    std::println("{}", twice("ab"s));      // "abab"

    // Multiple auto parameters
    auto add = [](auto a, auto b) { return a + b; };

    auto nums = std::vector{3, 1, 4, 1, 5};
    std::sort(nums.begin(), nums.end(), [](auto a, auto b) { return a > b; });

    std::println("nums: {:n}", nums);
}
```
