---
show_only: true
---

## What It Does

The identifier `_` serves as a placeholder variable name indicating intentional value discard.
Unlike ordinary variables, multiple declarations of `_` within the same scope do not constitute
redeclaration errors; each occurrence denotes an independent placeholder.

## Why It Matters

Certain programming patterns require binding a value solely for side effects (e.g. RAII lock guards)
or structured binding decomposition where only specific elements are utilized.
The placeholder `_` explicitly denotes intentionally unused bindings and suppresses compiler warnings for unused entities.

## Example

```cpp
#include <tuple>

std::tuple<int, std::string, double> get_record();

void process() {
    // Only care about the string, ignore the rest
    auto [_, name, _] = get_record();

    // Lock guard - we need the side effect, not the object
    auto _ = std::lock_guard(mutex);

    // Ignore return value explicitly
    auto _ = some_function_with_nodiscard_return();
}
```
