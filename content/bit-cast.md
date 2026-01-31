---
execute: true
---

## What It Does

`std::bit_cast()` reinterprets the object representation of one type as another type.
Both source and destination types must be trivially copyable and have the same size.
The operation is well-defined and permitted in constant expressions.

## Why It Matters

Type punning is accessing an object's raw bytes as if they were a different type.
Traditional type punning via unions or pointer casts invokes undefined behavior.
`std::bit_cast()` provides a portable, well-defined mechanism for bit reinterpretation
that is valid in `constexpr` contexts.

## Example

```cpp
#include <bit>
#include <cstdint>
#include <print>

int main() {
    // View float's bits as integer
    auto f = 1.5f;
    auto bits = std::bit_cast<uint32_t>(f);
    std::println("1.5f as bits: {:#010x}", bits);

    // Convert back
    auto f2 = std::bit_cast<float>(bits);
    std::println("1.5f restored from bits: {}", f2);

    // Works at compile time
    constexpr auto pi_bits = std::bit_cast<uint64_t>(3.14159265358979);
    static_assert(pi_bits == 4614256656552045841);
}
```
