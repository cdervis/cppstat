---
execute: false
---

## What It Does

`std::simd` provides portable SIMD (Single Instruction, Multiple Data) vector types.
Operations on `std::simd<T>` objects are mapped by the compiler to architecture-specific
vector instructions (SSE, AVX, NEON) or scalar fallback. The type supports arithmetic
operations, comparisons, and masking with overloaded operators.

## Why It Matters

SIMD instruction sets provide data-level parallelism for numeric computation.
Prior to `std::simd`, portable SIMD required platform-specific intrinsics or dependence
on compiler auto-vectorization heuristics. `std::simd` decouples vectorization logic
from target architecture specifics.

## Example

```cpp
#include <simd>
#include <print>

void add_arrays(float* a, float* b, float* out, size_t n) {
    using simd_t = std::native_simd<float>;

    constexpr auto lanes = simd_t::size();

    for (auto i = 0uz; i + lanes <= n; i += lanes) {
        auto va = simd_t(a + i, std::element_aligned);
        auto vb = simd_t(b + i, std::element_aligned);
        auto result = va + vb;
        result.copy_to(out + i, std::element_aligned);
    }

    // Handle remainder
    for (auto i = 0uz; i < n; ++i) {
        out[i] = a[i] + b[i];
    }
}
```
