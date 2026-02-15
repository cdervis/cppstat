## What It Does

`std::copyable_function` is a polymorphic function wrapper that owns a callable target.
Unlike `std::function`, it correctly propagates `const`, reference qualifiers,
and `noexcept` specifications to the call operator. Unlike `std::move_only_function`,
it requires the stored callable to be copyable.

## Why It Matters

`std::function` has a `const` call operator that invokes non-`const` callables, allowing
mutation through a `const` reference. Its design predates later C++ features like `noexcept`
and ref-qualifiers. `std::copyable_function` addresses these issues while remaining copyable,
serving as the intended replacement for `std::function` in new code.

## Example

```cpp
#include <functional>
#include <print>

int main() {
    int counter = 0;

    // const-qualified: can only be called on const wrapper
    std::copyable_function<int() const> fn = [=]() { return counter + 1; };
    std::println("Result: {}", fn());

    // noexcept-qualified: callable must not throw
    std::copyable_function<int() noexcept> safe_fn = []() noexcept { return 123; };
    std::println("Safe result: {}", safe_fn());
}
```
