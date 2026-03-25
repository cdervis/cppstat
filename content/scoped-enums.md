---
execute: true
---

## What It Does

`enum class` (scoped enumeration) defines enumerators that are scoped to the enum type and do not
implicitly convert to integers. The underlying type can be explicitly specified.
Accessing an enumerator requires the enum name as a qualifier.

## Why It Matters

Traditional unscoped enums leak their enumerator names into the enclosing scope and implicitly convert
to `int`, permitting unintended arithmetic and comparisons between unrelated enum types.
Scoped enums restrict both name visibility and implicit conversions, requiring `static_cast`
for integer conversion.

## Example

```cpp
#include <cstdint>
#include <print>
#include <utility>

enum class Color : uint8_t {
    Red,
    Green,
    Blue
};

enum class Permission : unsigned {
    Read = 1,
    Write = 2,
    Execute = 4
};

int main() {
    auto c = Color::Green;
    // int x = c;  // error: no implicit conversion

    auto underlying = static_cast<uint8_t>(c);
    std::println("Color::Green underlying value: {}", underlying);

    auto p = Permission::Read;
    std::println("Permission::Read underlying value: {}", static_cast<unsigned>(p));

    // With C++23's std::to_underlying():
    std::println("With std::to_underlying: {}", std::to_underlying(p));
}
```
