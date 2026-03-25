---
execute: true
---

## What It Does

`std::vector` can be used in `constexpr` context: vectors can be created, modified, and destroyed during
constant evaluation.
The compiler's constexpr evaluator handles dynamic memory allocation and deallocation within the evaluation,
provided no allocation persists to runtime.

## Why It Matters

Before this, compile-time collections required `std::array` with a fixed size known in advance, or manual
constexpr-compatible data structures.
`constexpr` `std::vector` allows variable-length computation during constant evaluation using the same
container used at runtime.

## Example

```cpp
#include <print>
#include <vector>

consteval int sum_first_n(int n) {
    auto v = std::vector<int>();

    for (auto i = 1; i <= n; ++i) {
        v.push_back(i);
    }

    auto total = 0;

    for (auto x : v) {
        total += x;
    }

    return total;
}

int main() {
    constexpr auto result = sum_first_n(10);

    std::println("sum of 1..10 = {}", result);
}
```
