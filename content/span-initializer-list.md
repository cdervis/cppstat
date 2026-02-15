## What It Does

`std::span<const T>` can now be constructed from a braced initializer list such as `{1, 2, 3}`.
The constructor accepts `std::initializer_list<value_type>` and is available only when the element
type is const-qualified. For static-extent spans, the initializer list size must match the extent.

## Why It Matters

Functions accepting `std::span<const T>` could not be called with inline brace-enclosed lists,
unlike functions accepting `std::vector` or `std::string_view`. Callers had to create a temporary
array or container. This constructor aligns `std::span` with other vocabulary types that accept
initializer lists directly.

## Example

```cpp
#include <span>
#include <print>

void process(std::span<const int> data) {
    std::println("{:n}", data);
}

int main() {
    process({1, 2, 3, 4, 5});  // Direct initializer list

    auto fixed = std::span<const int, 3>{10, 20, 30};  // Static extent
    std::println("{:n}", fixed);
}
```
