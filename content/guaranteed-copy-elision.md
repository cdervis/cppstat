---
execute: true
---

## What It Does

In C++17 and newer, returning a [prvalue](https://en.cppreference.com/w/cpp/language/value_category.html) of the same type as the function return type,
or initializing an object from a prvalue, is guaranteed to construct the object directly in its destination.
No copy or move constructor is called or required to exist.

## Why It Matters

Before C++17, copy elision was an optimization that compilers were permitted but not required to perform.
Code relying on elision could fail to compile if the copy/move constructor was deleted or inaccessible.
C++17 mandates elision in these cases, making prvalue semantics part of the language definition.

## Example

```cpp
#include <print>

struct Widget {
    Widget() { std::println("constructed"); }
    Widget(const Widget&) = delete;
    Widget(Widget&&) = delete;
};

Widget make() {
    return Widget();
}

int main() {
    auto w = make();
    std::println("done");
}
```
