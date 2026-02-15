## What It Does

`std::complex` now satisfies the tuple protocol. Specializations of `std::tuple_size`,
`std::tuple_element`, and overloads of `std::get()` are provided for `std::complex<T>`.
`tuple_size` is 2, `tuple_element` yields `T` for both indices, and `get<0>` / `get<1>`
return references to the real and imaginary parts respectively. This enables structured
bindings for `std::complex`.

## Why It Matters

Accessing the real and imaginary parts of a `std::complex` required calling the `.real()`
and `.imag()` member functions. Structured bindings and generic tuple-based algorithms
did not work with `std::complex`. The tuple protocol makes `std::complex` usable in
contexts that operate on tuple-like types, including structured bindings and `std::apply()`.

## Example

```cpp
#include <complex>
#include <print>
#include <tuple>

template<typename T>
void print_components(const T& tuple_like) {
    std::println("first: {}, second: {}",
        std::get<0>(tuple_like),
        std::get<1>(tuple_like));
}

int main() {
    auto z = std::complex<double>(3.0, 4.0);

    auto [re, im] = z;
    std::println("real: {}, imag: {}", re, im);  // real: 3, imag: 4

    static_assert(std::tuple_size_v<std::complex<double>> == 2);

    print_components(z);  // first: 3, second: 4
}
```
