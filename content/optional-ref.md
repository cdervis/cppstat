---
execute: true
---

## What It Does

`std::optional<T&>` is a specialization of `std::optional` containing either a reference to an object
of type `T` or no value. Prior to its introduction, `std::optional` supported only value semantics,
necessitating workarounds such as raw pointers or `std::reference_wrapper` for optional reference
semantics.

## Why It Matters

Functions returning optional references to existing objects previously relied on raw pointers
(`nullptr` for absence) or `std::optional<std::reference_wrapper<T>>` (verbose wrapper).
`std::optional<T&>` encodes optional reference semantics directly in the type system with
consistent `std::optional` interface semantics.

## Example

```cpp
#include <optional>
#include <print>
#include <vector>
#include <string>

using namespace std::string_literals;

std::optional<std::string&> find_by_name(
    std::vector<std::string>& names,
    std::string_view target
) {
    for (auto& name : names) {
        if (name == target) {
            return name;  // returns reference to actual element
        }
    }

    return {}; // not found, return empty optional
}

int main() {
    auto names = std::vector{"Alice"s, "Bob"s, "Charlie"s};

    if (auto found = find_by_name(names, "Bob")) {
        *found = "Robert";  // modifies the original vector element
    }

    std::println("names: {:n}", names);
}
```
