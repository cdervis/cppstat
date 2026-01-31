---
execute: true
---

## What It Does

Lambda expressions define anonymous function objects inline. They capture variables from the enclosing scope for use within the function body, and are employed in callbacks, algorithms, and contexts requiring locally-scoped function objects.

The syntax `[captures](parameters) { body }` specifies which enclosing variables are accessible within the lambda's scope.

## Why It Matters

Prior to lambdas, algorithms such as `std::sort()` with custom comparison logic required the definition of separate function objects or free functions. Lambdas enable the definition of comparison logic at the call site, placing implementation near the usage context.

## Example

```cpp
#include <vector>
#include <algorithm>
#include <print>

int main() {
    auto nums = std::vector{3, 1, 4, 1, 5, 9, 2, 6};

    // Simple lambda in algorithm
    std::ranges::sort(nums, [](int a, int b) {
        return a > b;
    });

    // Capture by reference
    auto sum = 0;
    std::for_each(nums.begin(), nums.end(), [&sum](int n) { sum += n; });
    std::println("Sum: {}", sum);

    // Capture by value
    auto factor = 10;
    auto scale = [factor](int n) { return n * factor; };
    std::println("{}", scale(5));  // 50

    // Capture all by reference [&] or by value [=]
    auto printer = [&]() { std::println("Sum is {}", sum); };
    printer();
}
```
