---
execute: true
---

## What It Does

`std::execution` defines a framework for asynchronous and parallel computation based on three core abstractions: senders (represent deferred work), receivers (consume results), and schedulers (control execution context).

Operations are composed by connecting senders through pipe operators, constructing a computation graph that remains deferred until connected to a receiver and started.

## Why It Matters

Asynchronous programming involves resource lifetime management, error propagation paths, and cancellation semantics.
`std::execution` specifies ownership semantics, defines cancellation behavior, and enables operation composition within a unified conceptual framework.

## Example

```cpp
#include <execution>
#include <print>

using namespace std::execution;

int main() {
    auto work = just(42)                          // start with a value
              | then([](int x) { return x * 2; }) // transform it
              | then([](int x) {
                    std::println("Result: {}", x);
                    return x;
                });

    // Execute synchronously and get the result
    auto [result] = std::this_thread::sync_wait(work).value();
}
```
