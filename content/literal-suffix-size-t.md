---
execute: true
---

## What It Does

The literal suffixes `uz` (or `UZ`) and `z` (or `Z`) produce values of type `size_t` and the corresponding
signed type (`ptrdiff_t` or the signed counterpart of `ssize_t`), respectively.
These suffixes apply to integer literals, complementing the existing `u`, `l`, `ll`, and other suffixes.

## Why It Matters

Before these suffixes, writing a loop counter or variable of type `size_t` from a literal required a cast
or a separate declaration.
Comparing a signed literal like `0` with `container.size()` produced signed/unsigned mismatch warnings.
The `uz` and `z` suffixes allow `size_t` and its signed counterpart to be expressed directly as literals.

## Example

```cpp
#include <vector>
#include <print>

int main() {
    auto v = std::vector{10, 20, 30, 40, 50};

    // uz suffix: literal is size_t, no signed/unsigned mismatch
    for (auto i = 0uz; i < v.size(); ++i) {
        std::println("v[{}] = {}", i, v[i]);
    }

    // z suffix: signed counterpart of size_t
    auto offset = -1z;
    std::println("offset value: {}, type size: {} bytes", offset, sizeof(offset));
}
```
