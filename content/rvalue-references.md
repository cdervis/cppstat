---
execute: true
---

## What It Does

Rvalue references (`T&&`) distinguish temporary objects from lvalues.
They enable move semantics, allowing resources to be transferred from expiring objects instead of copied.
`std::move()` casts an lvalue to an rvalue reference, indicating that its resources may be taken.

## Why It Matters

Before rvalue references, passing or returning large objects always involved copying, which requires
allocating new resources and deallocating the originals.
Move semantics allow resource transfer from temporaries, avoiding the allocation and deallocation
overhead associated with deep copies.

## Example

```cpp
#include <print>
#include <string>
#include <utility>

class Buffer {
public:
    Buffer(std::string s)
        : data_(std::move(s))
    {}

    // Move constructor: transfers resources from other
    Buffer(Buffer&& other) noexcept
        : data_(std::move(other.data_))
    {
        std::println("move constructor called");
    }

    // Move assignment: transfers resources from other
    Buffer& operator=(Buffer&& other) noexcept
    {
        std::println("move assignment called");

        // prevent self-assignment, e.g. buff = std::move(buff)
        if (std::addressof(other) != this) {
            // move over the data members
            data_ = std::move(other.data_);
        }

        return *this;
    }

    Buffer(const Buffer&) = default;
    Buffer& operator=(const Buffer&) = default;

    const std::string& data() const { return data_; }

private:
    std::string data_;
};

int main() {
    auto a = Buffer("hello world");
    auto b = std::move(a);  // invokes move constructor

    std::println("b.data() = {}", b.data());

    auto c = Buffer("temporary");
    c = std::move(b);  // invokes move assignment

    std::println("c.data() = {}", c.data());
}
```
