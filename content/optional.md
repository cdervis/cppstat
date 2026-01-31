---
execute: true
---

## What It Does

`std::optional<T>` is a class template containing either a value of type `T` or no value.
It provides a type-safe representation of an optional value without pointer semantics,
sentinel values, or output parameters. Member functions `has_value()` and `value()` provide
value checking and access, with `value()` throwing `std::bad_optional_access` if no value is present.

## Why It Matters

Nullable pointers shift null-check responsibility to each use site without compile-time enforcement.
Sentinel values overload the value domain of a type and require convention-based interpretation.
`std::optional` encodes value presence or absence in the type itself, enabling static analysis
and compile-time verification of access patterns.

## Example

```cpp
#include <optional>
#include <string>
#include <map>
#include <print>

std::optional<std::string> find_user(int id) {
    static auto users = std::map<int, std::string>{{1, "Alice"}, {2, "Bob"}};

    auto it = users.find(id);
    if (it != users.end()) {
        return it->second;
    }

    return std::nullopt;  // no value
}

int main() {
    if (auto user = find_user(1)) {
        std::println("Found: {}", *user);
    }

    // Or use value_or for a default
    std::println("{}", find_user(99).value_or("Unknown"));

    auto maybe_number = std::optional<int>();
    std::println("Has value: {}", maybe_number.has_value());  // false
    maybe_number = 42;
    std::println("Value: {}", *maybe_number);  // 42
}
```
