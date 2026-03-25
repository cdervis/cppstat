## What It Does

`std::any` holds a single value of any copy-constructible type, with type-safe access via `std::any_cast()`.
Small objects may be stored inline (small-buffer optimization), larger objects are heap-allocated.

## Why It Matters

`void*` can hold a pointer to any type but provides no type safety and no ownership.
`std::any` owns the stored value, manages its lifetime, and throws `std::bad_any_cast` on type mismatch.

## Example

```cpp
#include <any>
#include <print>
#include <string>

int main() {
    auto a = std::any(42); // a is of type std::any
    std::println("int: {}", std::any_cast<int>(a));

    a = std::string("hello");
    std::println("string: {}", std::any_cast<std::string>(a));

    try {
        std::any_cast<double>(a);
    } catch (const std::bad_any_cast& e) {
        std::println("bad cast: {}", e.what());
    }
}
```
