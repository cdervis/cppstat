## What It Does

`contains` reports whether a string holds a given substring, returning `bool`. It is a member of
both `basic_string` and `basic_string_view`, and overloads accept a `basic_string_view`, a pointer
to a null-terminated string, or a single character. The functions are `constexpr`, so the check can
run during constant evaluation.

## Why It Matters

Testing for a substring previously meant `haystack.find(needle) != std::string::npos`, a presence
check written as an inequality against the sentinel for "not found", which the reader has to
translate back. The C function `strstr` works only on null-terminated data. A free function such as
`boost::contains` gives no clue whether the substring or the haystack comes first. A member
`contains` states the intent directly and fixes the order. It searches for a substring, a different
operation from the `contains` added to the associative containers in C++20, where the argument is a
key.

## Example

```cpp
#include <print>
#include <string>
#include <string_view>

int main()
{
    std::string haystack = "no place for needles";

    std::println("{}", haystack.contains("needle"));
    std::println("{}", haystack.contains('z'));

    std::string_view view = haystack;
    std::println("{}", view.contains("place"));

    static_assert(std::string_view("compile time").contains("time"));
}
```
