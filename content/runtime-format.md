## What It Does

`std::runtime_format()` wraps a format string that is known only at runtime, allowing it
to be used with `std::format()` and related functions. Without this wrapper, format strings
must be compile-time constants for format checking. The returned object cannot be copied
or moved, preventing accidental lifetime issues.

## Why It Matters

Compile-time format string checking rejects strings that are not constants, including
translated strings from localization systems. The previous workaround using
`std::vformat()` with `std::make_format_args()` was verbose and prone to lifetime errors.
`std::runtime_format()` provides a clear, safe way to opt into runtime format strings.

## Example

```cpp
#include <format>
#include <print>
#include <string>

std::string get_localized_format() {
    // In practice, this would come from a translation system
    return "Value: {}";
}

int main() {
    auto fmt = get_localized_format();

    // Use runtime_format to mark the string as runtime-determined
    auto result = std::format(std::runtime_format(fmt), 42);
    std::println("{}", result);
}
```
