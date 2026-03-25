---
execute: true
---

## What It Does

The compiler can implicitly generate move constructors and move assignment operators that perform
member-wise moves.
`= default` explicitly requests the compiler-generated versions.
These defaulted operations move each non-static data member and base class subobject individually.

## Why It Matters

Before C++11, classes had only copy constructors and copy assignment operators as compiler-generated
special members.
Adding move semantics to a class required manually writing both a move constructor and move assignment operator.
Defaulting them generates member-wise move operations without user-written code.

## Example

```cpp
#include <print>
#include <string>
#include <utility>
#include <vector>

struct Record {
    Record(std::string n, std::vector<int> v)
        : name(std::move(n))
        , values(std::move(v))
    {}

    // Explicitly defaulted copy operations
    Record(const Record&) = default;
    Record& operator=(const Record&) = default;

    // Explicitly defaulted move operations
    Record(Record&&) = default;
    Record& operator=(Record&&) = default;

    std::string name;
    std::vector<int> values;
};

int main() {
    auto a = Record("sensor", {1, 2, 3, 4, 5});
    std::println("a: name={}, values.size()={}", a.name, a.values.size());

    auto b = std::move(a);  // uses defaulted move constructor
    std::println("b: name={}, values.size()={}", b.name, b.values.size());
    std::println("a after move: name={}, values.size()={}", a.name, a.values.size());
}
```
