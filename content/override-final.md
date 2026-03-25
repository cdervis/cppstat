---
execute: true
---

## What It Does

`override` explicitly marks a member function as overriding a virtual function in a base class;
the compiler issues an error if no matching base function exists.
`final` prevents further overriding of a virtual function or derivation from a class.

## Why It Matters

Without `override`, a signature mismatch (wrong parameter type, missing `const`) silently declares a
new function instead of overriding the base version.
`override` converts this silent error into a compile-time diagnostic.
`final` allows a class hierarchy to close extension points explicitly.

## Example

```cpp
#include <print>

struct Base {
    virtual int compute(int x) const { return x; }
    virtual ~Base() = default;
};

struct Derived : Base {
    int compute(int x) const override { return x * 2; }
    // int compute(double x) const override;  // error: no matching base function
};

struct Final : Derived {
    int compute(int x) const final { return x * 3; }
};

// struct Beyond : Final {
//     int compute(int x) const override;  // error: overriding final function
// };

int main() {
    auto d = Derived();
    Base& ref = d;
    std::println("Derived::compute(5) = {}", ref.compute(5));  // 10

    auto f = Final();
    Base& ref2 = f;
    std::println("Final::compute(5) = {}", ref2.compute(5));   // 15
}
```
