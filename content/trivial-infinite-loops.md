---
execute: false
show_assembly: true
---

## What It Does

Trivial infinite loops (iteration statements with empty or side-effect-free bodies) are no
longer undefined behavior. A loop such as `while (true) {}` has defined semantics; the compiler
cannot assume such loops terminate.

## Why It Matters

Prior to this change, trivial infinite loops had undefined behavior, permitting compilers to optimize
them under the assumption that they would not execute indefinitely. This transformation eliminated
valid patterns such as spinlocks and interrupt-driven event loops.
The change guarantees that such loops are preserved in the generated code.

## Example

```cpp
#include <atomic>

auto ready = std::atomic<bool>(false);

void wait_for_signal() {
    // This is now guaranteed to actually loop
    // Previously, compilers could optimize this away
    while (!ready.load(std::memory_order_relaxed)) {
        // busy wait
    }
}

void embedded_main_loop() {
    while (true) {
        // Process events - guaranteed to run forever
        // Compiler cannot assume this loop terminates
    }
}

int main() {
    return 0;
}
```
