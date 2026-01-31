---
execute: true
---

## What It Does

`static operator[]` allows the subscript operator to be declared as a static member function.
This mirrors the capability added for `operator()` in C++23 (P1169).
When declared static, the subscript operator does not receive an implicit object parameter.

## Why It Matters

Function objects and accessor types that hold no state still required a `this` pointer to be
passed when invoking `operator[]`. For stateless types like customization point objects or
index mappers, this implicit parameter serves no purpose but still consumes a register and
prevents certain optimizations. Declaring `operator[]` as static eliminates this overhead.

## Example

```cpp
#include <cstddef>
#include <print>

struct IdentityMapper {
    static constexpr size_t operator[](size_t i) {
        return i;
    }
};

int main() {
    std::println("{}", IdentityMapper()[42]);
    std::println("{}", IdentityMapper::operator[](7));
}
```
