---
execute: true
---

## What It Does

Class template argument deduction (CTAD) allows the compiler to deduce template arguments for
a class template from constructor arguments.
Deduction guides, either implicit (generated from constructors) or user-defined, control
how constructor arguments map to template parameters.

## Why It Matters

Before CTAD, constructing class templates required explicit template arguments
(e.g. `std::pair<int, double>(1, 2.0)`) or helper functions like `std::make_pair()`.
CTAD allows `std::pair(1, 2.0)` to deduce the template arguments directly from the constructor call.

## Example

```cpp
#include <array>
#include <mutex>
#include <print>
#include <tuple>
#include <vector>

template <typename T>
struct Wrapper {
    T value;
    Wrapper(T v) : value(v) {}
};

// User-defined deduction guide: string literals deduce as std::string
Wrapper(const char*) -> Wrapper<std::string>;

int main() {
    auto p = std::pair(1, 2.5);        // std::pair<int, double>
    auto t = std::tuple(1, 'a', 3.0);  // std::tuple<int, char, double>
    auto a = std::array{1, 2, 3, 4};   // std::array<int, 4>

    auto mtx = std::mutex();
    auto lock = std::lock_guard(mtx);  // std::lock_guard<std::mutex>

    auto w = Wrapper("hello");         // Wrapper<std::string> via deduction guide

    std::println("pair: ({}, {})", p.first, p.second);
    std::println("tuple element 0: {}", std::get<0>(t));
    std::println("array size: {}", a.size());
    std::println("wrapper: {}", w.value);
}
```
