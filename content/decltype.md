---
execute: true
---

## What It Does

`decltype(expr)` yields the type of its operand expression **without evaluating it**.
For an identifier or class member access, it gives the declared type.
For other expressions, it produces the type including [value category](https://en.cppreference.com/w/cpp/language/value_category.html): lvalue expressions
yield a reference type, xvalues yield an rvalue reference, and prvalues yield the non-reference type.

## Why It Matters

Before `decltype`, expressing the return type of a function in terms of its parameters or
capturing the type of a complex expression required manual specification or type traits.
`decltype` allows the compiler to deduce the exact type from an expression, which is essential
for generic code and trailing return types.

## Example

```cpp
#include <print>
#include <type_traits>

template <typename A, typename B>
auto multiply(A a, B b) -> decltype(a * b) {
    return a * b;
}

int main() {
    auto x = 123;
    decltype(x) y = 10;       // int (declared type of identifier)
    decltype((x)) z = x;      // int& (lvalue expression)

    auto result = multiply(3, 2.5);

    std::println("y = {}", y);
    std::println("result type is double: {}", std::is_same_v<decltype(result), double>);
    std::println("result = {}", result);
}
```
