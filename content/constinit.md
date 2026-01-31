---
execute: true
---

## What It Does

`constinit` specifies that a variable with static or thread-local storage duration
is initialized by constant initialization. Unlike `constexpr`, the variable is **not**
`const`-qualified and may be modified at runtime; only the initialization is guaranteed
to occur at compile time.

## Why It Matters

The static initialization order fiasco occurs when global variables with dynamic
initializers have dependencies on each other.
`constinit` ensures constant initialization precedes dynamic initialization,
eliminating undefined behavior from initialization order dependencies.

## Example

```cpp
#include <array>
#include <print>

// Guaranteed compile-time initialization
constinit auto global_count = 42;
constinit auto some_array   = std::array{1, 2, 3};

// NOT constexpr - can be modified at runtime
void increment() {
    ++global_count;
}

// Error: not a constant expression
// constinit int x = some_runtime_function();

// Thread-local works too
constinit thread_local int per_thread_id = 0;

int main() {
    increment();  // global_count is now 43
    std::println("global_count: {}", global_count);
    std::println("some_array: {}", some_array);
}
```
