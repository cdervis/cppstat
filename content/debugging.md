---
executable: false
flags: "-lstdc++exp"
---

## What It Does

The `<debugging>` header provides portable utilities for debugger interaction.
`std::breakpoint()` triggers a debugger breakpoint; `std::is_debugger_present()`
queries whether a debugger is attached to the process.

## Why It Matters

Prior to this facility, triggering a breakpoint programmatically required
platform-specific intrinsics (e.g., `__debugbreak()`, `__builtin_trap()`, `raise(SIGTRAP)`).
The standard debugging utilities provide a portable interface with defined behavior
when no debugger is attached.

## Example

```cpp
#include <debugging>
#include <print>

void validate(int value) {
    if (value < 0) {
        std::println("Invalid value: {}", value);

        if (std::is_debugger_present()) {
            std::breakpoint();  // pause here for inspection
        }
    }
}

int main() {
    // Unconditional breakpoint - useful for "stop here" debugging
    std::breakpoint_if_debugging();

    validate(-5);
}
```
