---
execute: true
---

## What It Does

`std::generator<T>` is a coroutine type for lazy sequence generation.
Each `co_yield` expression suspends the coroutine, resuming when the next element is requested.
Elements are produced incrementally during iteration.

## Why It Matters

Container allocation is avoided for sequential data access.
Memory consumption is bounded by a single element, the type is compatible with range adaptors, and unbounded sequences can be expressed without resource exhaustion.

## Example

```cpp
#include <generator>
#include <print>

std::generator<int> fibonacci(int limit) {
    auto a = 0;
    auto b = 1;

    while (a < limit) {
        co_yield a;
        auto next = a + b;
        a = b;
        b = next;
    }
}

std::generator<int> iota(int start = 0) {
    while (true) {
        co_yield start++;
    }
}

int main() {
    std::println("fib:");
    for (auto n : fibonacci(100)) {
        std::println("{}", n);
    }

    // Take first 5 from infinite sequence
    std::println("first 5, starting with 10:");
    for (auto n : iota(10) | std::views::take(5)) {
        std::println("{}", n);
    }
}
```
