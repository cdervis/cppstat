---
execute: false
---

## What It Does

With this, exceptions may be thrown and caught during constant expression evaluation.
If an exception is not caught within the constant expression context, the result
is a compile-time error. If caught within the evaluation context, evaluation continues.

## Why It Matters

`constexpr` functions previously required distinct error-handling mechanisms for
compile-time versus runtime evaluation contexts.
Exception support in constant expressions unifies error handling, permitting identical
code to operate in both compile-time and runtime contexts.

## Example

```cpp
#include <stdexcept>

constexpr int safe_divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("division by zero");
    }

    return a / b;
}

constexpr int safe_compute(int x, int y) {
    try {
        return safe_divide(x, y);
    } catch (const std::invalid_argument&) {
        return 0;  // fallback for division by zero
    }
}

// Works at compile time
static_assert(safe_compute(10, 2) == 5);
static_assert(safe_compute(10, 0) == 0);  // caught and handled

// This would fail to compile (uncaught exception):
// constexpr int bad = safe_divide(1, 0);
```
