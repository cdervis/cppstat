---
execute: true
---

## What It Does

`using enum EnumType;` introduces all enumerators of a scoped enumeration into the current scope,
allowing them to be used without the enum type prefix.
Individual enumerators can also be introduced with `using EnumType::enumerator;`.

## Why It Matters

Scoped enumerations require the type prefix on every use (e.g., `Color::Red`).
In contexts like switch statements where the enum type is known, the repeated prefix adds verbosity
without disambiguation. `using enum` removes the prefix within a limited scope.

## Example

```cpp
#include <print>
#include <string_view>

enum class Color { Red, Green, Blue };

std::string_view to_string(Color c) {
    switch (c) {
        using enum Color;
        case Red:   return "red";
        case Green: return "green";
        case Blue:  return "blue";
    }

    return "unknown";
}

int main() {
    std::println("{}", to_string(Color::Green));
}
```
