---
execute: true
---

## What It Does

`std::inplace_vector<T, N>` is a dynamically-resizable sequence container with a fixed maximum capacity `N`.
All elements are stored within the object itself; no dynamic memory allocation is performed.
The interface matches `std::vector`. However, exceeding the capacity results in `std::bad_alloc` being thrown.

## Why It Matters

In environments where heap allocation is unavailable or prohibited, including embedded systems, real-time contexts, or latency-critical paths, a fixed-capacity container with automatic storage is required. `std::inplace_vector` provides `std::vector`-compatible operations without dynamic memory allocation.

## Example

```cpp
#include <inplace_vector>
#include <print>

int main() {
    // Can hold up to 10 ints, stored inline
    auto numbers = std::inplace_vector<int, 10>();

    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);

    // Works like std::vector
    for (auto n : numbers) {
        std::println("{}", n);
    }

    numbers.resize(5, 0);  // {1, 2, 3, 0, 0}

    // numbers.resize(20);  // throws std::bad_alloc - exceeds capacity
}
```
