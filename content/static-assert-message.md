---
execute: false
---

## What It Does

`static_assert` can now accept a user-generated message instead of requiring a string literal.
The message can be any constant expression that provides `size()` and `data()` member functions,
where `size()` returns a value convertible to `size_t` and `data()` returns a value
convertible to `const char*`.

## Why It Matters

String literals in `static_assert` cannot incorporate compile-time computed values.
Reusing the same diagnostic message across multiple assertions required duplicating
the literal at each location. With user-generated messages, assertions can include
dynamic information such as type sizes or template parameter values, and message
strings can be defined once and reused.

## Example

```cpp
#include <string_view>

template<typename T>
constexpr void check_size() {
    constexpr std::string_view msg = "Type must be at least 4 bytes";
    static_assert(sizeof(T) >= 4, msg);
}

struct SmallType { char c; };
struct LargeType { int data[4]; };

int main() {
    check_size<LargeType>();   // OK
    // check_size<SmallType>(); // error: static assertion failed: Type must be at least 4 bytes
}
```
