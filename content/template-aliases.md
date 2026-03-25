---
execute: true
---

## What It Does

`template <typename T> using Name = ...;` creates a template alias, a new name for an existing template or
type expression parameterized by template arguments.
Unlike `typedef`, alias templates can be templated and participate in template argument deduction.

## Why It Matters

`typedef` cannot be parameterized by template arguments.
Creating a type alias that depends on a template parameter required a wrapper struct with a nested
`type` member and the `typename` keyword at each use site.
Template aliases provide direct parameterized type naming without wrapper structs.

## Example

```cpp
#include <map>
#include <print>
#include <string>
#include <vector>

template <typename T>
using Vec = std::vector<T>;

template <typename V>
using StringMap = std::map<std::string, V>;

int main() {
    auto numbers = Vec{1, 2, 3};
    std::println("numbers: {:}", numbers);

    auto prices = StringMap<double>();
    prices["apple"] = 1.50;
    prices["orange"] = 1.20;
    std::println("prices: {:}", prices);
}
```
