---
execute: false
---

## What It Does

Most standard library containers and container adaptors are now usable in `constexpr` contexts.
This includes `std::deque`, `std::forward_list`, `std::list`, `std::map`, `std::set`,
`std::unordered_map`, `std::unordered_set`, `std::queue`, `std::stack`, `std::priority_queue`,
and the flat container adaptors, and container operations including construction, insertion,
erasure, and iteration.

## Why It Matters

Prior to this change, only `std::vector`, `std::array`, `std::string`, and a few other types
were usable at compile time. Algorithms requiring associative containers, linked lists, or
deques could not be evaluated during compilation. This extension unifies runtime and
compile-time C++ by making most container operations available in both contexts.

## Example

```cpp
#include <map>
#include <set>
#include <deque>

constexpr int compute() {
    std::map<int, int> m;
    m[1] = 10;
    m[2] = 20;

    std::set<int> s = {3, 1, 4, 1, 5};

    std::deque<int> d;
    d.push_back(100);
    d.push_front(50);

    return m.at(1) + static_cast<int>(s.size()) + d.front();
}

static_assert(compute() == 10 + 4 + 50);

int main() {}
```
