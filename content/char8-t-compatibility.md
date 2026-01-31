## What It Does

This allows UTF-8 string literals (`u8"..."`) to initialize arrays of `char`, `unsigned char`, and `signed char`.
This restores initialization patterns that were valid before C++20 introduced
`char8_t`. The fix applies only to array initialization, **not** pointer conversions.

## Why It Matters

C++20 changed `u8"..."` literals from `const char[]` to `const char8_t[]`, breaking existing code
that initialized character arrays from UTF-8 literals. Code such as `const char s[] = u8"text";`
became ill-formed, requiring workarounds like compiler flags or shim layers. This proposal
restores the array initialization while preserving the type distinction in other contexts.

## Example

```cpp
#include <print>

int main() {
    // Array initialization from u8 literals (restored by P2513)
    const char utf8[] = u8"Hello, 世界";
    const unsigned char raw[] = u8"\xC2\xA9";  // copyright symbol

    std::println("UTF-8 string: {}", utf8);
    std::println("Raw bytes: {} {}", raw[0], raw[1]);  // 194 169
}
```
