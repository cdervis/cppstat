---
execute: true
---

## What It Does

`std::span` is a non-owning view over a contiguous sequence of elements.
It abstracts any contiguous storage (arrays, vectors, pointers with size) without copying.
The number of elements may be specified at compile time (`std::span<T, N>`) or
determined at runtime (`std::span<T>`).

## Why It Matters

Functions accepting pointer and size parameters lack bounds enforcement.
Functions accepting `std::vector&` are constrained to that specific container type.
`std::span` abstracts any contiguous range while carrying its extent, decoupling
interfaces from concrete container implementations.

## Example

```cpp
#include <span>
#include <vector>
#include <array>
#include <print>

// Works with any contiguous data
void process(std::span<const int> data) {
    std::println("{:n}", data);
    std::println("Size: {}", data.size());
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    auto vec = std::vector{6, 7, 8};
    auto stdArr = std::array{9, 10, 11};

    process(arr);      // C array
    process(vec);      // vector
    process(stdArr);   // std::array

    // Subspans
    auto s = std::span(arr);
    std::println("first two: {:n}", s.first(2));
    std::println("last two: {:n}", s.last(2));
    std::println("middle: {:n}", s.subspan(1, 3));
}
```
