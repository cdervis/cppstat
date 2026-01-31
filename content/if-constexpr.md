---
execute: true
---

## What It Does

`if constexpr` evaluates a boolean condition at compile time and discards the non-selected branch.
Statements within the discarded branch are not instantiated, removing the requirement for them to be valid for the given template arguments.
This mechanism enables type-dependent code selection without runtime overhead.

## Why It Matters

Prior to `if constexpr`, type-dependent branching required SFINAE or tag dispatching, both utilizing indirect syntactic patterns. `if constexpr` enables compile-time branch selection using standard conditional syntax within the same function body.

## Example

```cpp
#include <type_traits>
#include <string>
#include <vector>
#include <print>

template <typename T>
auto stringify(const T& value) {
    if constexpr (std::is_arithmetic_v<T>) {
        return std::to_string(value);
    } else if constexpr (std::is_same_v<T, std::string>) {
        return value;
    } else {
        return std::string("[object]");
    }
}

// Helper to detect reserve() capability
template <typename T, typename = void>
struct has_reserve : std::false_type {};

template <typename T>
struct has_reserve<T, std::void_t<decltype(std::declval<T>().reserve(0))>> : std::true_type {};

template <typename T>
void process(T& container) {
    if constexpr (has_reserve<T>::value) {
        container.reserve(100);  // only for containers with reserve()
    }
    // ... rest of processing
}

int main() {
    using namespace std::string_literals;
    std::println("{}", stringify(42));       // "42"
    std::println("{}", stringify(3.14));     // "3.140000"
    std::println("{}", stringify("hello"s)); // "hello"
}
```
