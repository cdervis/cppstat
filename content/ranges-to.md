---
execute: true
---

## What It Does

`ranges::to()` materializes a range into a concrete container of the specified type.
It accepts any range as input and constructs the target container from the range's elements via
the container's range constructor or iterator pair insertion.

## Why It Matters

Range adaptors produce lazy views computed on demand during iteration. Many interfaces require
materialized containers with owned storage. Converting views to containers previously required
explicit construction with iterator pairs or `ranges::copy()` with `std::back_inserter`.
`ranges::to()` encapsulates this conversion within the range pipeline.

## Example

```cpp
#include <ranges>
#include <vector>
#include <set>
#include <string>
#include <print>

int main() {
    auto numbers = std::views::iota(1, 10)
                 | std::views::filter([](int n) { return n % 2 == 0; })
                 | std::views::transform([](int n) { return n * n; })
                 | std::ranges::to<std::vector>();

    std::println("numbers: {}", numbers);

    // Convert to different container types
    auto as_set = numbers | std::ranges::to<std::set>();

    std::println("as_set: {}", as_set);

    // Works with strings too
    auto upper = std::string_view("hello")
               | std::views::transform(::toupper)
               | std::ranges::to<std::string>();

    std::println("upper: {}", upper);
}
```
