---
execute: true
---

## What It Does

The three-way comparison operator `<=>` computes the ordering relationship between two operands in
a single operation, returning a comparison category type (`std::strong_ordering`, `std::weak_ordering`,
or `std::partial_ordering`).
The compiler can generate the six two-way comparison operators (`<`, `<=`, `>`, `>=`, `==`, `!=`)
from a defaulted `<=>` operator.

## Why It Matters

Defining all six comparison operators requires repetitive boilerplate that must be maintained consistently.
A defaulted `<=>` operator delegates the implementation to the compiler.
The operator also enables single-pass comparison in sorting algorithms, whereas two-way comparisons
may require multiple passes.

## Example

```cpp
#include <compare>
#include <string>
#include <print>

struct Person {
    std::string name;
    int age;

    // Defaulted: compares members in order
    auto operator<=>(const Person&) const = default;
};

struct Version {
    int major, minor, patch;

    auto operator<=>(const Version&) const = default;
    bool operator==(const Version&) const = default;
};

int main() {
    auto alice = Person("Alice", 30);
    auto bob = Person("Bob", 25);

    std::println("alice < bob? {}", alice < bob);   // depends on name comparison
    std::println("alice == bob? {}", alice == bob);  // false

    auto v1 = Version(1, 2, 3);
    auto v2 = Version(1, 2, 4);
    std::println("v1 < v2? {}", v1 < v2);  // true
}
```
