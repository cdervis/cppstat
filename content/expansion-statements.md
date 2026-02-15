---
execute: true
flags: "-freflection"
---

## What It Does

`template for` is a new statement that iterates over compile-time ranges, expanding the loop
body once for each element. It works with pack expansions (`{xs...}`), constant expression
ranges (`std::array{1, 2, 3}`), and tuple-like types. Unlike a regular `for` loop, each
iteration can have a different type, and the loop body is instantiated separately for each
element.

## Why It Matters

Iterating over heterogeneous collections like tuples previously required recursive templates
or library utilities like `std::apply()`. These approaches cannot use `return`, `break`, or
`continue` naturally and cannot appear in coroutines. `template for` provides direct
iteration syntax with proper control flow semantics.

## Example

```cpp
#include <tuple>
#include <print>

int main() {
    auto tup = std::tuple{1, 3.14, "hello"};

    template for (const auto& elem : tup) {
        std::println("{}", elem);
    }

    // With pack expansion
    auto print_all = []<typename... Ts>(Ts... args) {
        template for (auto x : {args...}) {
            std::println("{}", x);
        }
    };

    print_all(10, 20, 30);
}
```
