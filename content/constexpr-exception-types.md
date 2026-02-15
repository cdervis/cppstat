---
execute: false
---

## What It Does

Standard library exception types are now `constexpr`-compatible.
This includes `std::logic_error`, `std::runtime_error`, `std::out_of_range`,
`std::invalid_argument`, `std::bad_optional_access`, `std::bad_variant_access`,
`std::bad_expected_access`, `std::format_error`, and their related exception classes.
Their constructors, destructors, and member functions are marked `constexpr`.

## Why It Matters

With `constexpr` exceptions enabled ([P3068](https://wg21.link/P3068)), code can throw
and catch exceptions during constant evaluation. However, using standard exception types
in such code was not possible because their constructors were not `constexpr`.
This change enables standard exceptions types to be thrown and caught during compile-time
evaluation.

## Example

```cpp
#include <stdexcept>
#include <optional>

constexpr int safe_access(int index) {
    if (index < 0) {
        throw std::out_of_range("negative index");
    }
    return index;
}

constexpr int test() {
    try {
        return safe_access(-1);
    } catch (const std::out_of_range&) {
        return -1;
    }
}

static_assert(test() == -1);

int main() {}
```
