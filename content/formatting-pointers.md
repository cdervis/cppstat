## What It Does

`std::format()` now supports formatting options for pointer types that were previously available only
for integers. Pointers can use zero-padding (`{:018}`), uppercase hex output (`{:P}`), and the
alternate form to omit the `0x` prefix. Additionally, any pointer type can now be formatted, not
just `void*`, `const void*`, and `std::nullptr_t`.

## Why It Matters

Formatting arbitrary pointer types previously required casting to `uintptr_t` or writing a custom
formatter. Controlling the output format (padding, case, prefix) was not possible without similar
workarounds. These options are now available directly, matching the existing integer formatting
capabilities.

## Example

```cpp
#include <format>
#include <print>

int main() {
    int x = 42;
    int* ptr = &x;

    std::println("Default:    {}", static_cast<void*>(ptr));
    std::println("Padded:     {:018}", static_cast<void*>(ptr));
    std::println("Uppercase:  {:P}", static_cast<void*>(ptr));
}
```
