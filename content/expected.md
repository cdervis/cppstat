---
execute: true
---

## What It Does

`std::expected<T, E>` is a class template that stores either a value of type `T` or an error of type `E`.
The type provides monadic operations (`and_then()`, `or_else()`, `transform()`) for composing computations that may fail.

## Why It Matters

Exceptions propagate outside the standard function return mechanism; error codes require explicit checking at each call site.
`std::expected` encodes error conditions in the return type and supports composition of error-handling operations through monadic member functions.

## Example

```cpp
#include <expected>
#include <print>
#include <string>
#include <charconv>

enum class ParseError { empty, invalid, overflow };

std::expected<int, ParseError> parse_int(std::string_view s) {
    if (s.empty()) {
        return std::unexpected(ParseError::empty);
    }

    auto value = 0;
    auto [ptr, ec] = std::from_chars(s.begin(), s.end(), value);

    if (ec == std::errc::result_out_of_range) {
        return std::unexpected(ParseError::overflow);
    }

    if (ec != std::errc() || ptr != s.end()) {
        return std::unexpected(ParseError::invalid);
    }

    return value;
}

int main() {
    const auto result = parse_int("42")
                        .transform([](int n) { return n * 2; })
                        .value_or(-1);

    std::println("Result: {}", result);
}
```
