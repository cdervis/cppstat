## What It Does

This proposal removes the restriction that prevented `constexpr` member functions in classes
with virtual base classes. Previously, constructors, destructors, and other member functions
in virtually-inheriting classes could not be declared `constexpr`. Now all such functions
are eligible for constant evaluation.

## Why It Matters

For example, virtual inheritance is used in the standard library's iostream hierarchy. The restriction
blocked `constexpr std::stringstream` and compile-time stream-based parsing. Removing this
limitation enables constant evaluation for any class hierarchy, regardless of whether it
uses virtual inheritance.

## Example

```cpp
#include <print>

struct Base {
    int value;
    constexpr Base(int v) : value(v) {}
    constexpr virtual int get() const { return value; }
};

struct Left : virtual Base {
    constexpr Left(int v) : Base(v) {}
};

struct Right : virtual Base {
    constexpr Right(int v) : Base(v) {}
};

struct Diamond : Left, Right {
    constexpr Diamond(int v) : Base(v), Left(v), Right(v) {}
    constexpr int get() const override { return value * 2; }
};

int main() {
    constexpr auto d = Diamond(21);
    static_assert(d.get() == 42);
    std::println("Diamond value: {}", d.get());
}
```
