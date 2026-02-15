---
execute: false
---

## What It Does

`std::make_format_args()` now accepts only lvalue references instead of forwarding references.
Passing a temporary directly to `std::make_format_args()` becomes ill-formed.
This change applies retroactively to C++23 as a defect report.

## Why It Matters

`std::make_format_args()` stores references to its arguments. When a temporary was passed,
the temporary would be destroyed before the format arguments were used, resulting in
undefined behavior from dangling references. Requiring lvalues prevents this class of
errors at compile time.

## Example

```cpp
#include <format>
#include <print>
#include <string>

int main() {
    auto str = std::string("hello");
    auto value = 123;

    // OK: lvalue references
    auto args = std::make_format_args(str, value);

    // Ill-formed in C++26: temporary would dangle
    // auto bad = std::make_format_args(std::string("temp"));

    std::println("{} {}", str, value);
}
```
