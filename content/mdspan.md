---
execute: true
---

## What It Does

`std::mdspan` is a non-owning view over contiguous data providing multidimensional array access semantics. It encapsulates a pointer to data with layout mapping that translates multidimensional indices to memory offsets. The layout policy determines the memory access pattern (row-major or column-major).

## Why It Matters

Scientific computing, image processing, and linear algebra require manipulation of multidimensional data. Prior to `mdspan`, multidimensional access required manual pointer arithmetic (error-prone and opaque) or external matrix libraries. `mdspan` provides a zero-overhead abstraction for multidimensional views without dynamic allocation or indirection.

## Example

```cpp
#include <mdspan>
#include <vector>
#include <print>

int main() {
    auto data = std::vector<int>(12);  // 12 elements

    // View as 3x4 matrix
    auto matrix = std::mdspan(data.data(), 3, 4);

    // Fill with row*10 + col
    for (auto row = 0uz; row < matrix.extent(0); ++row) {
        for (auto col = 0uz; col < matrix.extent(1); ++col) {
            matrix[row, col] = row * 10 + col;
        }
    }

    std::println("Element at (1,2): {}", matrix[1, 2]);  // 12

    // Works with any contiguous data
    int raw[6] = {1, 2, 3, 4, 5, 6};
    auto vec = std::mdspan(raw, 2, 3);  // 2x3 view
}
```
