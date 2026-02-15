## What It Does

Unions now have trivial default constructors and destructors in more cases. If the first alternative
is an implicit-lifetime type (such as an array of trivially-constructible elements), its lifetime
begins automatically. This makes unions usable as uninitialized storage in `constexpr` contexts
without requiring user-provided special member functions.

## Why It Matters

Before this change, a union containing a non-trivially constructible or destructible type had its
default constructor and destructor implicitly deleted. This prevented using unions as storage for
types like `std::string` in `constexpr std::inplace_vector`. The new rules allow unions to serve
as uninitialized storage during constant evaluation, enabling `constexpr` implementations of
containers that manage their own object lifetimes.

## Example

```cpp
#include <string>
#include <new>

template<typename T, int N>
struct FixedStorage {
    union { T data[N]; };  // Trivial constructor/destructor now

    constexpr FixedStorage() {}
    constexpr ~FixedStorage() {}

    constexpr void construct(int i, const T& value) {
        std::construct_at(&data[i], value);
    }
};

int main() {
    auto storage = FixedStorage<int, 4>();
    storage.construct(0, 42);
}
```
