---
execute: true
---

## What It Does

Fold expressions apply a binary operator to all elements of a parameter pack in a single expression.
The four forms are:
- unary left fold `(... op pack)`
- unary right fold `(pack op ...)`
- binary left fold `(init op ... op pack)`
- binary right fold `(pack op ... op init)`

## Why It Matters

Before fold expressions, expanding a parameter pack with a binary operator required recursive template
instantiation with a base case specialization.
Fold expressions express the reduction directly in a single expression without recursion or helper functions.

## Example

```cpp
#include <print>
#include <string>

template <typename... Args>
auto sum(Args... args) {
    return (... + args);  // unary left fold
}

template <typename... Args>
bool all_true(Args... args) {
    return (true && ... && args);  // binary left fold
}

template <typename... Args>
void print_all(Args&&... args) {
    ((std::println("{}", args)), ...);  // unary right fold with comma operator
}

int main() {
    std::println("sum: {}", sum(1, 2, 3, 4, 5));
    std::println("all_true: {}", all_true(true, true, false));
    print_all(42, 3.14, std::string("hello"));
}
```
