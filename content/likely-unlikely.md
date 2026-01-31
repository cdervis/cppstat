---
execute: false
show_assembly: true
---

## What It Does

The `[[likely]]` and `[[unlikely]]` attributes indicate to the compiler the relative probability
of branch execution. The compiler may utilize these attributes to optimize code layout and branch
prediction hints.

## Why It Matters

Modern CPU architectures employ branch prediction; mispredictions incur significant pipeline stalls.
These attributes enable the compiler to order generated code such that the predicted-hot path falls
through sequentially while the predicted-cold path requires a branch instruction, reducing branch
misprediction penalties.

## Example

```cpp
#include <print>

int process(int value) {
    if (value > 0) [[likely]] {
        // This branch is expected to be taken most often
        return value * 2;
    } else [[unlikely]] {
        // Rare case: error handling
        std::println("Warning: non-positive value");
        return 0;
    }
}

int handle_success()      { return 1; }
int handle_not_found()    { return 2; }
int handle_server_error() { return 3; }
int handle_unknown()      { return 4; }

int parse_status(int status) {
    switch (status) {
        [[likely]] case 200:
            return handle_success();
        case 404:
            return handle_not_found();
        [[unlikely]] case 500:
            return handle_server_error();
        default:
            return handle_unknown();
    }
}
```
