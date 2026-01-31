---
execute: false
---

## What It Does

With this, virtual function calls are permitted within constant expressions.
When the dynamic type is known at compile time, the compiler resolves the virtual
dispatch and evaluates the call during constant expression evaluation.

## Why It Matters

`constexpr` evaluation and virtual dispatch were previously mutually exclusive.
`constexpr` virtual functions enable inheritance hierarchies and polymorphic dispatch
in constant expressions, supporting polymorphic algorithms and data structures at compile time.

## Example

```cpp
struct Shape {
    constexpr virtual double area() const = 0;
    constexpr virtual ~Shape() = default;
};

struct Circle : Shape {
    double radius;

    constexpr Circle(double r)
        : radius(r)
    {}

    constexpr double area() const override {
        return 3.14159 * radius * radius;
    }
};

struct Rectangle : Shape {
    double width, height;

    constexpr Rectangle(double w, double h)
        : width(w), height(h)
    {}

    constexpr double area() const override {
        return width * height;
    }
};

constexpr double get_area(const Shape& s) {
    return s.area(); // virtual call at compile time
}

static_assert(get_area(Circle(5.0)) > 78.0);
static_assert(get_area(Rectangle(3.0, 4.0)) == 12.0);
```
