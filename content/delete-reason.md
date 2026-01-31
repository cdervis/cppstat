---
execute: true
---

## What It Does

Deleted functions may specify a message string as an argument to the `delete` specifier.
When a deleted function is selected by overload resolution, the compiler emits the specified message in the diagnostic.

## Why It Matters

Function deletion prevents unintended operations, but standard error messages provide no context regarding the rationale.
A user-specified message conveys the reason for deletion and may suggest alternative operations.

## Example

```cpp
class NonCopyable {
public:
    NonCopyable() = default;

    NonCopyable(const NonCopyable&)
        = delete("copying is expensive; use clone() for explicit copies");

    NonCopyable& operator=(const NonCopyable&)
        = delete("copying is expensive; use clone() for explicit copies");

    NonCopyable clone() const { return NonCopyable(*this, 0); }

private:
    NonCopyable(const NonCopyable&, int) {}  // internal copy
};

int main() {
    auto a = NonCopyable();

    // Error: can't copy NonCopyables via copy ctor or assignment:
    auto b = a;
}
```
