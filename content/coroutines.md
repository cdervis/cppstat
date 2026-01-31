---
execute: true
---

## What It Does

Coroutines are functions that can suspend execution and resume at a later point.
Suspension points are indicated by `co_await` (awaiting a value), `co_yield` (producing
a value to the caller), and `co_return` (completing execution).
The compiler transforms coroutines into state machine implementations.

## Why It Matters

Asynchronous programming without coroutines requires callback nesting or explicit
state machine management.
Coroutines enable sequential structuring of asynchronous control flow,
making asynchronous logic explicit and composable.

## Example

```cpp
#include <coroutine>
#include <print>

struct Task {
    struct promise_type {
        auto get_return_object() { return Task(); }
        auto initial_suspend() { return std::suspend_never(); }
        auto final_suspend() noexcept { return std::suspend_never(); }
        void return_void() {}
        void unhandled_exception() {}
    };
};

struct Awaiter {
    auto await_ready() {
        return false;
    }

    auto await_suspend(std::coroutine_handle<> h) {
        std::println("Suspended...");
        return h;
    }

    auto await_resume() {
        std::println("Resumed!");
        return 42;
    }
};

Task example() {
    std::println("Starting");
    auto result = co_await Awaiter();
    std::println("Got: {}", result);
}

int main() {
    example();
}
```
