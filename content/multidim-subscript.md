---
execute: true
---

## What It Does

The subscript operator `operator[]` accepts multiple arguments. The syntax `m[i, j]` performs direct multidimensional indexing without chained bracket operations or function call syntax. Within brackets, the comma functions as a parameter separator rather than the comma operator.

## Why It Matters

Chained subscript syntax `[i][j]` requires intermediate proxy objects with indirection overhead. Multi-argument subscript enables direct index calculation within a single function call. The syntax corresponds to standard mathematical notation for matrix and tensor element access.

## Example

```cpp
#include <vector>
#include <print>

template <typename T>
class Matrix {
    std::vector<T> data_;
    size_t rows_, cols_;

public:
    Matrix(size_t rows, size_t cols)
        : data_(rows * cols), rows_(rows), cols_(cols) {}

    T& operator[](size_t row, size_t col) {
        return data_[row * cols_ + col];
    }

    const T& operator[](size_t row, size_t col) const {
        return data_[row * cols_ + col];
    }
};

int main() {
    auto m = Matrix<int>(3, 4);
    m[1, 2] = 42;
    std::println("m[1,2] = {}", m[1, 2]);
}
```
