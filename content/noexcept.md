---
execute: true
---

## What It Does

The `noexcept` specifier declares that a function does not throw exceptions.
`noexcept(expr)` conditionally applies based on a compile-time boolean expression.
The `noexcept` operator tests whether an expression is declared non-throwing,
returning a `bool` usable in compile-time contexts.

## Why It Matters

Before `noexcept`, the dynamic exception specification `throw()` had runtime overhead:
violating it called `std::unexpected` rather than enabling compiler optimizations.
`noexcept` allows the compiler and user code to omit exception handling infrastructure
entirely for marked functions.

For example, standard containers like `std::vector` query `noexcept` on move constructors to decide
between moving and copying during reallocation.

**Note**: When a noexcept function throws an exception, `std::terminate()` is called immediately.
The runtime does not attempt to propagate the exception up the call stack.
Instead, it is treated as a fatal, unrecoverable error.

## Example

```cpp
#include <print>
#include <type_traits>
#include <vector>

struct Widget {
    Widget() = default;
    Widget(Widget&&) noexcept = default;
    Widget(const Widget&) = default;
};

template <typename T>
T add(T a, T b) noexcept(std::is_nothrow_move_constructible_v<T>) {
    return a + b;
}

int main() {
    std::println("Widget move is noexcept: {}",
        std::is_nothrow_move_constructible_v<Widget>);

    std::println("add<int> is noexcept: {}",
        noexcept(add(1, 2)));

    std::println("add<std::vector<int>> is noexcept: {}",
        noexcept(add(std::vector<int>{}, std::vector<int>{})));
}
```
