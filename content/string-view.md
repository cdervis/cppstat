---
execute: true
---

## What It Does

`std::string_view` is a non-owning reference to a contiguous character sequence.
It holds a pointer and a length, providing read-only access to string data without allocation.
It can refer to `std::string`, string literals, or substrings.

## Why It Matters

Functions accepting `const std::string&` require callers with C strings or substrings to construct a
temporary `std::string`, which allocates memory.
`std::string_view` accepts any contiguous character range without allocation.

**Note**: Passing a `std::string_view` does not guarantee to point to a null-terminated string.
This matters, for example, when calling a C API function that expects a `const char*`.
In such a case, passing the value of `.data()` to such a function may cause an out-of-bounds violation.

A workaround is to construct a temporary `std::string`, and passing that string's `.c_str()` to the C function.

For C++29, a new type `std::zstring_view` (P3655) is planned, which guarantees a null-terminated string.

## Example

```cpp
#include <print>
#include <string>
#include <string_view>

void greet(std::string_view name) {
    std::println("Hello, {}!", name);
}

int main() {
    greet("world");

    auto s = std::string("Alice");
    greet(s);

    greet(std::string_view(s).substr(0, 3));
}
```
