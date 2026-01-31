---
execute: true
---

## What It Does

`char8_t` is a distinct fundamental type representing UTF-8 encoded character data.
String literals with the `u8` prefix have type `const char8_t[]` rather than `const char[]`,
establishing UTF-8 as a distinct type in the type system.

## Why It Matters

The `char` type conflates encoding-agnostic bytes with text data.
`char8_t` encodes UTF-8 explicitly in the type system, enabling APIs to enforce
UTF-8 input requirements and permitting the compiler to detect encoding mismatches at compile time.

## Example

```cpp
#include <string>
#include <print>

void process_utf8(std::u8string_view text) {
    std::println("Length in code units: {}", text.size());
}

int main() {
    // UTF-8 literals have type char8_t
    auto greeting = u8"Hello, 世界!";

    process_utf8(greeting);
    process_utf8(u8"UTF-8 string");

    // Can't mix with char accidentally
    // const char* p = u8"text";  // Error!

    // Convert when needed
    auto as_chars = reinterpret_cast<const char*>(greeting);
}
```
