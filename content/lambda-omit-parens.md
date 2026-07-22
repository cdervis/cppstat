## What It Does

A lambda that takes no parameters may omit the empty parameter list even when it carries a
specifier. `[]{ }` was always valid, but `[] mutable { }` was not, because adding `mutable` made the
parentheses mandatory again. The relaxation covers lambda template parameters, `constexpr`,
`mutable`, `consteval`, exception specifications and `noexcept`, attributes, trailing return types,
and `requires` clauses.

## Why It Matters

A lambda with no parameters may already omit the parameter list, because a lambda without a
declarator behaves as if it were `()`. Adding a specifier such as `mutable` used to reverse that and
require the empty `()` again, an inconsistency that was a frequent source of syntax errors. Making
the parentheses optional in every case, not only when no specifier is present, removes the special
case. Existing code is unaffected.

## Example

```cpp
#include <print>
#include <string>

int main()
{
    auto grow = [s = std::string("abc")] mutable {
        s += "d";
        return s;
    };

    auto answer = [] noexcept { return 42; };

    std::println("{}", grow());
    std::println("{}", answer());
}
```
