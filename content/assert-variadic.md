## What It Does

The `assert()` macro is redefined using a variadic parameter (`__VA_ARGS__`) instead of a
single macro parameter. This allows expressions containing unparenthesized commas to be
passed directly to `assert()` without requiring extra parentheses.

## Why It Matters

Because `assert()` was defined with a single macro parameter, expressions containing commas
(such as `std::is_same_v<int, float>` or compound literals in C) were interpreted as
multiple macro arguments, causing a compilation error. Users had to wrap such expressions
in an extra set of parentheses. The variadic definition accepts the entire expression
regardless of commas.

## Example

```cpp
#include <cassert>
#include <type_traits>

int main() {
    // Previously required extra parentheses: assert((std::is_same_v<int, int>))
    assert(std::is_same_v<int, int>);

    using Int = int;
    assert(std::is_same_v<int, Int>);

    assert(1 + 1 == 2);
}
```
