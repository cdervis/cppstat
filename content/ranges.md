---
execute: true
---

## What It Does

Ranges encapsulate sequences of elements as single objects with `begin()` and `end()` accessors.
Range algorithms accept range objects directly rather than iterator pairs. Views provide lazy
range adaptors that compose via the pipe operator `|`, constructing transformation pipelines
evaluated on demand during iteration.

## Why It Matters

Iterator pairs require separate passing of two related arguments without enforcement that they
belong to the same sequence. Ranges encapsulate sequence boundaries as a single object.
View adaptors defer computation until element access, enabling efficient composition of
transformations without intermediate materialization. The pipe operator provides a left-to-right
syntax for adaptor composition.

## Example

```cpp
#include <algorithm>
#include <ranges>
#include <vector>
#include <print>

int main() {
    auto numbers = std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Lazy pipeline: filter, transform, take
    auto result = numbers
        | std::views::filter([](auto n) { return n % 2 == 0; })
        | std::views::transform([](auto n) { return n * n; })
        | std::views::take(3);

    for (auto n : result) {
        std::println("{}", n);
    }

    // Range algorithms work directly with containers
    if (auto it = std::ranges::find(numbers, 4); it != numbers.end()) {
        std::println("range contains 4");
    }

    std::ranges::sort(numbers, std::greater());

    std::println("numbers after sorting: {}", numbers);
}
```
