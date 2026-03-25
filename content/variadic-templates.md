---
execute: true
---

## What It Does

Variadic templates accept an arbitrary number of template parameters using `...` pack syntax.
Parameter packs can be expanded in various contexts including function arguments, base class lists, and initializer lists.
Fold expressions (C++17) or recursive instantiation consume the pack elements.

## Why It Matters

Before variadic templates, handling a variable number of template arguments required a fixed set of overloads
or preprocessor macros, neither of which provided type safety across all arguments.
Variadic templates allow a single definition to handle any number of arguments with full type checking at
each position.

## Example

```cpp
#include <print>
#include <string>

// Recursive base case
void print_all() {}

// Recursive variadic function
template <typename T, typename... Args>
void print_all(const T& first, const Args&... rest) {
    std::println("{}", first);
    print_all(rest...);
}

// Variadic sum using fold expression (C++17)
template <typename... Args>
auto sum(Args... args) {
    return (args + ...);
}

int main() {
    print_all(1, 3.14, std::string("hello"), 'c');

    std::println("sum = {}", sum(1, 2, 3, 4, 5));
}
```
