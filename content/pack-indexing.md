---
execute: false
---

## What It Does

Pack indexing provides direct access to individual elements of a parameter pack via the `...[N]` syntax. The index is a compile-time constant expression. This eliminates the need for recursive template instantiation or `std::tuple`-based indirection to extract specific pack elements.

## Why It Matters

Parameter pack element access previously required recursive template metaprogramming or `std::tuple_element` with helper types. Pack indexing provides direct compile-time access to the Nth element of a type or value pack without auxiliary template machinery or runtime overhead.

## Example

```cpp
#include <array>

template <typename... Ts>
struct TypeList {
    static constexpr size_t size = sizeof...(Ts);

    template <size_t N>
    using at = Ts...[N];  // direct access to Nth type
};

template <auto... Values>
constexpr auto get(size_t index) {
    constexpr auto arr = std::array{Values...};
    return arr[index];
}

// Usage
using List = TypeList<int, double, char>;
using Second = List::at<1>;  // double

static_assert(std::is_same_v<Second, double>);
```
