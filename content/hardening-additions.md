---
execute: false
---

## What It Does

Additional standard library functions now have hardened preconditions that perform runtime
bounds and validity checks. This includes `std::basic_stacktrace` access operations,
`std::shared_ptr<T[N]>` array subscript, `std::view_interface::front()` and `back()`, and
iterator operations on `std::counted_iterator` and `std::common_iterator`.
Violations trigger a defined failure rather than undefined behavior.

## Why It Matters

The initial hardening proposal ([P3471](https://wg21.link/P3471)) covered core containers but omitted several library
components. This follow-up ensures consistent safety guarantees across related types.
Checking bounds on stacktrace access, validating iterator state, and verifying range
emptiness before `front()`/`back()` calls prevents memory safety violations from precondition
misuse.

## Example

```cpp
#include <iterator>
#include <vector>
#include <print>

int main() {
    auto v = std::vector{1, 2, 3};

    // counted_iterator with length tracking
    auto it = std::counted_iterator(v.begin(), 3);

    std::println("First: {}", *it);
    ++it;
    std::println("Second: {}", *it);

    // Attempting to advance beyond count would be caught by hardening
}
```
