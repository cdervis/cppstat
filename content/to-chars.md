---
execute: true
---

## What It Does

`std::to_chars()` and `std::from_chars()` in `<charconv>` convert between numeric values and character sequences.
They perform no memory allocation, take no locale into account, and do not write a null terminator.
They return a result struct indicating success and the position past the last written/read character.

## Why It Matters

`std::stoi()`/`std::stod()` and `std::to_string()` perform locale-dependent formatting and may allocate memory.
`sprintf()`/`sscanf()` require format strings and null-terminated buffers.
`to_chars()`/`from_chars()` provide locale-independent, allocation-free conversion with explicit error reporting.

## Example

```cpp
#include <charconv>
#include <print>
#include <string_view>
#include <system_error>

int main() {
    char buf[32];
    auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), 3.14159);
    std::println("to_chars: {}", std::string_view(buf, ptr));

    auto val = 0.0; // double
    auto input = std::string_view("2.71828");
    auto [p, e] = std::from_chars(input.data(), input.data() + input.size(), val);

    if (e == std::errc{}) {
        std::println("from_chars: {}", val);
    }
}
```
