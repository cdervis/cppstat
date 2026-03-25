---
execute: true
---

## What It Does

`nullptr` is a keyword of type `std::nullptr_t` that represents a null pointer.
It is implicitly convertible to any pointer type but not to integral types.
`std::nullptr_t` can be used as a function parameter type to accept a `nullptr` value.

## Why It Matters

The `NULL` macro is defined as an integer constant (typically `0`), which causes ambiguity when
overloading functions that accept both pointer and integer parameters.
`nullptr` is unambiguously a pointer value, so overload resolution selects the pointer
overload without ambiguity.

## Example

```cpp
#include <print>
#include <cstddef>

void process(int value) {
    std::println("process(int): {}", value);
}

void process(int* ptr) {
    if (ptr) {
        std::println("process(int*): pointing to {}", *ptr);
    } else {
        std::println("process(int*): null pointer");
    }
}

void accepts_any_null(std::nullptr_t) {
    std::println("received a null pointer value");
}

int main() {
    process(0);          // calls process(int)
    process(nullptr);    // calls process(int*)

    auto x = 42;
    auto* p = &x;
    process(p);          // calls process(int*) with non-null pointer

    p = nullptr;         // assign null to pointer
    process(p);          // calls process(int*) with null pointer

    accepts_any_null(nullptr);
}
```
