## What It Does

A variable template defines a family of variables parameterized by template arguments. Writing
`template<class T> constexpr T pi = T(3.1415926535897932385L);` gives a distinct `pi` for every type
it is instantiated with. At namespace scope a variable template declares a variable; at class scope
it declares a static data member template.

## Why It Matters

C++ has no other direct way to write a constant that varies by type. Both older workarounds cost
something. A static data member of a class template must be defined a second time outside the class
once the constant is odr-used. A `constexpr` function template fixes how the value is delivered at
the point of definition. A const reference forces the constant into static storage, while returning
by value copies it at every use. Copying is free for builtin types but expensive for large class
types. A variable template defers that choice to each point of use.

## Example

```cpp
#include <print>

template <class T>
constexpr T pi = T(3.1415926535897932385L);

template <class T>
T circular_area(T r)
{
    return pi<T> * r * r;
}

int main()
{
    std::println("{}", circular_area(2.0));
    std::println("{}", circular_area(2.0f));
}
```
