---
execute: true
---

## What It Does

`std::initializer_list<T>` allows functions and constructors to accept brace-enclosed lists of values.
Brace initialization (`{}`) can construct objects, initialize containers, and pass argument lists.
The initializer list references a temporary array created by the compiler.

## Why It Matters

Before initializer lists, constructing a container with specific values required repeated `push_back()`
calls or initialization from a pre-existing array.

Brace initialization allows direct construction from a list of values in a single expression.

## Example

```cpp
#include <print>
#include <vector>
#include <initializer_list>
#include <string>

int sum(std::initializer_list<int> values) {
    auto total = 0;

    for (auto v : values) {
        total += v;
    }

    return total;
}

class Sensor {
public:
    Sensor(std::string name, std::initializer_list<double> readings)
        : name_(std::move(name))
        , readings_(readings)
    {}

    void report() const {
        std::println("sensor '{}' has {} readings", name_, readings_.size());
    }

private:
    std::string name_;
    std::vector<double> readings_;
};

int main() {
    auto v = std::array{10, 20, 30, 40};
    std::println("vector size: {}", v.size());

    std::println("sum: {}", sum({1, 2, 3, 4, 5}));

    auto s = Sensor("temperature", {36.5, 37.0, 36.8});
    s.report();
}
```
