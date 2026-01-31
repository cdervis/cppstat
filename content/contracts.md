---
execute: false
---

## What It Does

Contracts specify function preconditions (requirements on input), postconditions
(guarantees on output), and assertions (invariants at specific program points).
These conditions are declared using `pre`, `post`, and `contract_assert` in function
signatures and bodies. Violations are detected at runtime.

## Why It Matters

Invalid inputs or incorrect outputs may propagate far from their origin before
causing observable failure.
Contracts detect violations at the contract boundary and serve as executable
specifications of function requirements.

## Example

```cpp
#include <contracts>

double square_root(double x)
    pre (x >= 0)          // caller must provide non-negative input
    post (r: r >= 0)      // result will be non-negative
{
    return std::sqrt(x);
}

void process_buffer(int* data, int size)
    pre (data != nullptr)
    pre (size > 0)
{
    contract_assert(size <= 1000);  // internal sanity check
    // ... process data
}
```
