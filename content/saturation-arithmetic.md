## What It Does

The `<numeric>` header adds five saturation arithmetic function templates: `std::add_sat()`,
`std::sub_sat()`, `std::mul_sat()`, `std::div_sat()`, and `std::saturate_cast()`.
These functions clamp results to the representable range of the type instead of wrapping
(for unsigned) or causing undefined behavior (for signed). All are `constexpr` and `noexcept`.

## Why It Matters

Arithmetic overflow on unsigned types wraps modulo 2^N, and signed overflow is undefined
behavior. Applications such as audio processing, image manipulation, and fixed-point
arithmetic require results to clamp to minimum or maximum representable values.
These functions provide that behavior portably without manual range checking.

## Example

```cpp
#include <numeric>
#include <print>
#include <cstdint>

int main() {
    uint8_t a = 250;
    uint8_t b = 10;

    std::println("Wrapped: {}", static_cast<int>(a + b));                     // 4
    std::println("Saturated: {}", static_cast<int>(std::add_sat(a, b)));      // 255

    int8_t c = 100;
    int8_t d = 50;
    std::println("Saturated add: {}", static_cast<int>(std::add_sat(c, d)));  // 127

    std::println("Saturate cast: {}", std::saturate_cast<std::uint8_t>(-5));  // 0
    std::println("Saturate cast: {}", std::saturate_cast<std::uint8_t>(300)); // 255
}
```
