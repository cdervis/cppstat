---
execute: true
---

## What It Does

`std::flat_map` and `std::flat_set` are associative containers that store elements in contiguous storage (typically `std::vector`) rather than tree nodes.
The containers maintain elements in sorted order and expose an interface compatible with `std::map` and `std::set`.

## Why It Matters

Tree-based containers allocate nodes individually, resulting in non-contiguous storage and decreased cache locality during traversal.
`std::flat_map` and `std::flat_set` store elements contiguously, improving cache performance for lookup operations at the cost of O(n) insertion complexity.

## Example

```cpp
#include <flat_map>
#include <flat_set>
#include <print>

int main() {
    auto scores = std::flat_map<std::string, int>();

    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Charlie"] = 92;

    // Same interface as std::map
    for (const auto& [name, score] : scores) {
        std::println("{}: {}", name, score);
    }

    // Contains: 1, 3, 4, 5 (sorted, unique)
    auto numbers = std::flat_set{3, 1, 4, 1, 5};

    std::println("numbers: {}", numbers);

    // Efficient lookup
    if (numbers.contains(4)) {
        std::println("Found 4");
    }
}
```
