## What It Does

P3795R2 is a cleanup and consistency proposal for the new C++26 reflection facilities. It does
not introduce major new reflection capabilities, but fills gaps and unifies APIs that were left
inconsistent after several reflection-related papers were adopted together.

- `std::meta::current_function()`
- `std::meta::current_class()`
- `std::meta::current_namespace()`
- `std::meta::is_applicable_type()`
- `std::meta::is_nothrow_applicable_type()`
- `std::meta::apply_result()`

## Why It Matters

- Determining the current class or namespace required indirect workarounds through
  `access_context`.
- Some existing type traits had no reflection-time equivalents.
- Reflection error reporting was underspecified and inconsistent.

## Example

```cpp
#include <meta>
#include <print>

int main() {
    std::println("{}", std::meta::identifier_of(std::meta::current_function())); // prints: main
}
```
