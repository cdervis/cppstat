---
execute: true
---

## What It Does

The function call operator `operator()` may be declared `static`. Stateless function
objects thereby avoid the implicit `this` parameter. Lambdas without captures implicitly
generate a static call operator.

## Why It Matters

Stateless function objects (comparators, hash functions, predicates) previously incurred
the overhead of an implicit `this` parameter despite having no instance state to access.
Static call operators eliminate this indirection.

## Example

```cpp
#include <algorithm>
#include <vector>
#include <print>

struct IsEven {
    static bool operator()(int n) {  // no 'this' needed
        return n % 2 == 0;
    }
};

int main() {
    auto nums = std::vector{1, 2, 3, 4, 5, 6};

    // Custom predicate with static operator()
    auto count = std::ranges::count_if(nums, IsEven());
    std::println("Even count: {}", count);  // 3

    // Captureless lambdas benefit automatically
    auto is_positive = [](int n) { return n > 0; };
    // Compiler generates: static bool operator()(int n)

    // Can call without an instance
    auto result = IsEven::operator()(42);
    std::println("result: {}", result);
}
```
