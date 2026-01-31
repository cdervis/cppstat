---
execute: true
---

## What It Does

Concepts are named predicates that constrain template parameters.
Constraints are expressed as requirements on type properties, replacing SFINAE-based
constraint checking. The compiler validates these constraints at the point of instantiation
and produces diagnostic messages when constraints are violated.

Standard concepts are provided in `<concepts>`; user-defined concepts are specified
using `requires` expressions.

## Why It Matters

Template instantiation errors without concepts manifest as verbose, deeply nested
template backtraces through library implementation details.
Concepts shift constraint checking to the call site with direct diagnostic messages
(e.g., "type X does not satisfy Sortable").
Additionally, concepts enable function overloading and partial ordering based on type properties.

## Example

```cpp
#include <concepts>
#include <print>

// Using standard concepts
template <std::integral T>
auto double_it(T value) {
    return value * 2;
}

// Custom concept
template <typename T>
concept Printable = requires(T t) {
    // States that the following expression must be valid for T:
    std::println("{}", t);
};

template <Printable T>
void log(const T& value) {
    std::println("[LOG] {}", value);
}

int main() {
    double_it(42);       // OK
    // double_it(3.14);  // Error: double doesn't satisfy std::integral

    log("hello");  // OK
    log(123);      // OK
}
```
