---
execute: true
---

## What It Does

`std::make_unique()` constructs a `std::unique_ptr` by allocating storage, constructing the object
in-place, and wrapping the pointer in a `std::unique_ptr` in a single operation.
Arguments are forwarded to the object's constructor.

## Why It Matters

Prior to `std::make_unique()`, `std::unique_ptr<T>(new T(...))` was the typical pattern.
When multiple allocations occur in a single expression and one throws an exception, memory leaks occur
because the corresponding `std::unique_ptr` destructor is not yet responsible for the allocated object.
`std::make_unique()` eliminates this exception-safety gap while reducing verbosity.

## Example

```cpp
#include <memory>
#include <string>
#include <print>

struct Player {
    Player(std::string n, int s)
        : name(std::move(n))
        , score(s)
    {}

    std::string name;
    int score;
};

int main() {
    // Create unique_ptr directly
    auto player = std::make_unique<Player>("Alice", 100);
    std::println("{}: {}", player->name, player->score);

    // For arrays
    auto numbers = std::make_unique<int[]>(10);  // array of 10 ints
    numbers[0] = 42;

    // Raw new (not recommended since C++14):
    // std::unique_ptr<Player> p(new Player("Bob", 50));

    // No explicit delete needed - RAII handles it
}
```
