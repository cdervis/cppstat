---
execute: true
---

## What It Does

`std::variant` is a type-safe [tagged union](https://en.wikipedia.org/wiki/Tagged_union) that holds a
value of one of its alternative types at any time.
Access is through `std::get()`, `std::get_if()`, or `std::visit()`.
It stores the value in-place without heap allocation.

## Why It Matters

C unions do not track which member is active and permit reading the wrong member.
`std::variant` tracks the active alternative and throws `std::bad_variant_access`
(or returns `nullptr` via `get_if()`) on type mismatch.

## Example

```cpp
#include <print>
#include <string>
#include <variant>

int main() {
    auto v = std::variant<int, double, std::string>(42);
    
    // Direct access (throws on type mismatch):
    std::println("int: {}", std::get<int>(v));

    v = std::string("hello");

    // Access using std::visit:
    std::visit([](const auto& val) {
        std::println("value: {}", val);
    }, v);

    // Access using get_if:
    if (const auto* p = std::get_if<double>(&v)) {
        std::println("double: {}", *p);
    } else {
        std::println("not a double");
    }
}
```
