---
execute: true
---

## What It Does

`consteval` declares an immediate function that must produce a compile-time constant.
Unlike `constexpr` functions, which may execute at runtime, a `consteval` function is guaranteed
to be evaluated during compilation. Calling a `consteval` function with non-constant arguments is a compile-time error.

## Why It Matters

`constexpr` functions can execute at either compile time or runtime depending on context.
When compile-time evaluation is required (e.g. for computing lookup tables, enforcing compile-time validation, or embedding computed values),
`consteval` enforces that the function is never called at runtime.

## Example

```cpp
#include <print>

consteval int square(int n) {
    return n * n;
}

consteval int factorial(int n) {
    auto result = 1;

    for (int i = 2; i <= n; ++i) {
        result *= i;
    }

    return result;
}

int main() {
    constexpr auto sq = square(7);
    constexpr auto fact = factorial(10);

    // auto x = 5;
    // auto y = square(x);  // error: x is not a constant expression

    std::println("square(7) = {}", sq);
    std::println("factorial(10) = {}", fact);
}
```
