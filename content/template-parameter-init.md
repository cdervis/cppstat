---
execute: false
---

## What It Does

This change clarifies how class-type non-type template parameters are initialized. A temporary of
the template parameter type is created from the template argument, and the template parameter object
is then copy-initialized from that temporary. Both initializations must be constant expressions and
must produce template-argument-equivalent results.

## Why It Matters

The previous specification referred only to "converted constant expression" without detailing the
initialization process. When template parameter objects have observable addresses during construction,
the underspecification could lead to implementation divergence. This wording resolves ambiguities
and aligns the standard with existing compiler behavior.

## Example

```cpp
struct Wrapper {
    int value;
    constexpr Wrapper(int v) : value(v) {}
};

template<Wrapper W>
constexpr int get_value() {
    return W.value;
}

int main() {
    static_assert(get_value<Wrapper(42)>() == 42);
}
```
