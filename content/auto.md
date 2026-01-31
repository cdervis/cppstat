---
execute: true
---

## What It Does

The `auto` keyword specifies that a variable's type is deduced from its initializer.
The compiler performs type deduction at the point of declaration, making explicit type names unnecessary.

## Why It Matters

Certain types are verbose or unnameable (e.g. lambda closure types and nested container iterators).
Automatic type deduction eliminates redundant type declarations, prevents implicit conversion errors, and reduces
maintenance overhead when initializer types change.

## Example

```cpp
#include <vector>
#include <map>
#include <print>

using namespace std;

int main() {
    // Instead of: vector<int>::iterator it = vec.begin();
    auto vec = vector{1, 2, 3, 4, 5};
    auto it = vec.begin();

    // Complex types become manageable
    auto data = map<string, vector<int>>{
        {"scores", {1, 2, 3}},
    };

    for (auto& [key, values] : data) {
        println("{}: {}", key, values);
    }

    // Required for lambdas (their type is unnameable)
    auto greet = [](string_view name) {
        println("Hello, {}!", name);
    };

    greet("world");

    // Function return type deduction
    auto multiply = [](auto a, auto b) { return a * b; };

    println("Product: {}", multiply(4, 2));
}
```
