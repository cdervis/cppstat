---
execute: true
---

## What It Does

`std::jthread` is a thread wrapper that automatically joins upon destruction.
It incorporates cooperative cancellation through `std::stop_token`, enabling threads to query stop requests and terminate execution accordingly.

## Why It Matters

A `std::thread` (**not** `std::jthread`) destroyed without a prior call to `join()` or `detach()` invokes `std::terminate`. Manual stop flag implementations require explicit synchronization. `std::jthread` addresses both concerns: its destructor issues a stop request and performs an automatic join, while `std::stop_token` provides a standardized cancellation interface.

## Example

```cpp
#include <thread>
#include <stop_token>
#include <print>
#include <chrono>

void worker(std::stop_token token) {
    while (!token.stop_requested()) {
        std::println("Working...");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::println("Stopping gracefully");
}

int main() {
    // open a scope
    {
        auto t = std::jthread(worker);  // starts thread

        std::this_thread::sleep_for(std::chrono::milliseconds(350));

        t.request_stop();  // ask thread to stop
        // destructor joins automatically
    }

    std::println("Thread finished");
}
```
