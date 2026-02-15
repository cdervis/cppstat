## What It Does

`std::submdspan()` creates a sub-view of an `std::mdspan` by selecting a subset of elements along
each dimension. Slice specifiers include integral values (reducing rank by selecting a single index),
index pairs (specifying a range), `std::full_extent` (including the entire dimension), and
`std::strided_slice` (selecting regularly-spaced elements with a given offset, extent, and stride).

## Why It Matters

Multidimensional algorithms often operate on sub-regions of arrays, such as matrix blocks or
boundary surfaces. Without `submdspan`, code would need to manually compute offsets and strides
or maintain separate data structures. `submdspan` provides a standard way to create views of
arbitrary rectangular or strided regions.

## Example

```cpp
#include <mdspan>
#include <print>
#include <array>

int main() {
    auto data = std::array{
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12
    };

    auto matrix = std::mdspan(data.data(), /*rows:*/ 3, /*columns*/ 4);

    // Extract the second row
    auto row = std::submdspan(matrix, 1, std::full_extent);

    std::print("Row 1: ");
    for (size_t i = 0; i < row.extent(0); ++i) {
        std::print("{} ", row[i]);
    }
    std::println("");

    // Extract a 2x2 submatrix from top-left
    auto block = std::submdspan(matrix, std::pair(0, 2), std::pair(0, 2));
    std::println("Block [0:2, 0:2]: {}x{}", block.extent(0), block.extent(1));
}
```
