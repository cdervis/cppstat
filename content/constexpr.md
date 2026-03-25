---
execute: true
---

## What It Does

`constexpr` declares that a function or variable can be evaluated at compile time.
In C++11, constexpr functions are limited to a single return statement (plus `static_assert` and `typedef`),
and constexpr variables must be initialized with constant expressions.
The compiler evaluates constexpr functions when all arguments are constant expressions.

## Why It Matters

Before `constexpr`, compile-time computation required template metaprogramming with recursive template
instantiation. `constexpr` allows writing computation in ordinary function syntax that the compiler
evaluates during compilation, using the same language constructs as runtime code.

## Example

```cpp
#include <print>

constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

constexpr auto grid_size = 8;
constexpr auto total_cells = grid_size * grid_size;

int main() {
    constexpr auto f5 = factorial(5);
    static_assert(f5 == 120, "factorial(5) must be 120");

    std::println("factorial(5) = {}", f5);
    std::println("total cells in {}x{} grid = {}", grid_size, grid_size, total_cells);

    // Also callable at runtime
    auto n = 7;
    std::println("factorial({}) = {}", n, factorial(n));
}
```
