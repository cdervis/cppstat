---
execute: true
---

## What It Does

`if consteval` detects whether the current execution context is compile-time evaluation.
The `if consteval` branch is evaluated only during constant evaluation, permitting the use of `consteval` functions and compile-time-only constructs.
The `else` branch is evaluated during runtime execution.

## Why It Matters

Certain algorithms require distinct implementations for compile-time versus runtime contexts. For example, a portable `constexpr` loop for constant evaluation versus a hardware-optimized intrinsic for runtime execution. `if consteval` provides compile-time context dispatch without template specialization or tag dispatching.

## Example

```cpp
#include <cmath>
#include <bit>
#include <print>

constexpr int count_bits(unsigned int n) {
    if consteval {
        // Compile-time: use a simple loop
        auto count = 0;
        while (n) {
            count += n & 1;
            n >>= 1;
        }
        return count;
    } else {
        // Runtime: use hardware instruction
        return std::popcount(n);
    }
}

int main() {
    constexpr auto compile_time = count_bits(0b10110);  // 3

    auto some_runtime_value = 0b10110;
    auto runtime = count_bits(some_runtime_value);

    std::println("compile_time: {}", compile_time);
    std::println("runtime: {}", runtime);
}
```
