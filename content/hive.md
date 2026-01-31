---
execute: true
---

## What It Does

`std::hive` is a container designed for high-frequency insertion and erasure operations.
Element erasure does not invalidate iterators or relocate other elements, providing iterator stability comparable to node-based containers. Elements are stored in contiguous blocks, maintaining cache locality absent in linked structures.

The implementation maintains a free list of erased slots for reuse during subsequent insertions, combining iterator stability with block-contiguous storage.

## Why It Matters

Game engines, simulations, and entity-component systems frequently perform object insertion and removal. `std::vector` necessitates element relocation upon erasure; `std::list` exhibits suboptimal cache performance. `std::hive` provides iterator stability combined with block-contiguous element storage.

## Example

```cpp
#include <hive>
#include <print>

struct Entity {
    int id;
    float x;
    float y;
};

int main() {
    auto entities = std::hive<Entity>();

    auto it1 = entities.insert({1, 0.0f, 0.0f});
    auto it2 = entities.insert({2, 1.0f, 1.0f});
    auto it3 = entities.insert({3, 2.0f, 2.0f});

    entities.erase(it2);  // it1 and it3 remain valid

    for (const auto& e : entities) {
        std::println("Entity {}: ({}, {})", e.id, e.x, e.y);
    }
}
```
