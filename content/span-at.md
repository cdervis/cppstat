## What It Does

`std::span` now has an [`at()`](https://en.cppreference.com/w/cpp/container/span/at.html) member function that performs bounds checking.
It returns a reference to the element at the given index, or throws `std::out_of_range`
if the index is out of bounds. The function is `constexpr` and has constant time complexity.

## Why It Matters

`std::span::operator[]` does not perform bounds checking, leading to undefined behavior
on out-of-bounds access. Other standard containers and views
(`std::vector`, `std::array`, `std::string_view`) provide both unchecked `operator[]` and checked `at()`.
Adding `at()` to `std::span` provides consistency and a bounds-checked access option.

With standard library hardening ([P3471](https://wg21.link/P3471)) enabled, the `operator[]` of `std::span` will perform
bounds checking as well. However, the throwing of a `std::out_of_range` is not guaranteed.
Instead, the hardened standard library mechanism for violations will be used, which typically
is a fast fail or contract violation call.

## Example

```cpp
#include <span>
#include <print>
#include <stdexcept>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    auto s = std::span(arr);

    std::println("Element at 2: {}", s.at(2));

    try {
        s.at(10);  // Out of bounds
    } catch (const std::out_of_range& e) {
        std::println("Caught: {}", e.what());
    }
}
```
