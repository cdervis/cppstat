---
execute: true
flags: "-D_FORTIFY_SOURCE=3 -D_GLIBCXX_ASSERTIONS"
---

## What It Does

Standard library hardening introduces runtime validation for operations with invalid preconditions. This includes bounds checking for container element access (`std::vector`, `std::span`, `std::string_view`) and state validation for types with invalid access conditions (`std::optional`, `std::expected`). When a contract violation is detected, the program terminates deterministically instead of invoking undefined behavior.

The implementation utilizes C++26 contracts internally while remaining applicable to code without explicit contract annotations.

## Why It Matters

Out-of-bounds access and invalid state access constitute significant categories of security vulnerabilities and runtime failures. Hardening detects these contract violations at the point of occurrence, yielding deterministic program termination in place of undefined behavior.

## Example

```cpp
#include <vector>
#include <span>
#include <optional>

void process(std::span<const int> data) {
    // With hardening enabled, this terminates immediately
    // instead of reading garbage or crashing later,
    // if data has fewer than 101 elements.
    int value = data[100];  
}

int main() {
    auto v = std::vector{1, 2, 3};

    // These would terminate with hardening:
    // v[10];           // out of bounds
    // v.front();       // if v were empty
    // *v.begin() + 10; // iterator past end

    process(v);

    auto opt = std::optional<int>();
    // *opt;            // hardening: accessing empty optional
}
```
