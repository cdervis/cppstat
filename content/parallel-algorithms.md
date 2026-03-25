---
execute: false
---

## What It Does

Standard algorithms in `<algorithm>`, `<numeric>`, and `<memory>` accept an execution policy as their first argument.
`std::execution::seq` runs sequentially, `std::execution::par` allows parallel execution across threads, and
`std::execution::par_unseq` allows both parallel and vectorized execution.

## Why It Matters

Before execution policies, parallelizing standard algorithms required manual thread management or
third-party libraries.
Execution policies allow existing algorithm calls to opt into parallel execution by adding a single argument.

## Example

```cpp
#include <algorithm>
#include <execution>
#include <numeric>
#include <print>
#include <vector>

int main() {
    auto v = std::vector<int>(1000);
    std::iota(v.begin(), v.end(), 1);

    std::sort(std::execution::par, v.begin(), v.end(), std::greater{});
    std::println("largest: {}", v.front());

    auto sum = std::reduce(std::execution::par, v.begin(), v.end(), 0LL);
    std::println("sum: {}", sum);
}
```
