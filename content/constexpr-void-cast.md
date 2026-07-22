## What It Does

During constant evaluation, a `void*` may be converted to `T*` when it holds a null pointer value,
or points to an object whose type is *similar* to `T`, meaning the same type up to cv-qualification,
so a `Cow` can be recovered as `const Cow*`. Pointer-interconvertible types, base classes, and
unrelated types remain rejected.

## Why It Matters

Storing data behind a `void*` is a common type-erasure technique. Member functions moved into a
non-template base that holds a `void*` are instantiated once instead of once per specialization,
reducing template instantiations and symbol count. Recovering the original pointer needs a cast that
constant evaluation used to reject, so facilities built this way could not be `constexpr`;
permitting the cast lets types such as `std::format` and `std::any` be made `constexpr`. The two
exclusions have distinct reasons. Reinterpreting an object as an unrelated type is generally not
implementable, because constexpr evaluators model values rather than memory. Base classes are
excluded even though casting to a base is allowed during constant evaluation, because going to a
derived type and then its base need not yield the same address as casting to the base directly.

## Example

```cpp
#include <print>
#include <string_view>

struct Sheep
{
    constexpr std::string_view speak() const
    {
        return "Baaaaaa";
    }
};
struct Cow
{
    constexpr std::string_view speak() const
    {
        return "Mooo";
    }
};

class AnimalView
{
    const void *animal;
    std::string_view (*speak_fn)(const void *);

  public:
    template <typename A>
    constexpr AnimalView(const A &a)
        : animal(&a), speak_fn([](const void *o) { return static_cast<const A *>(o)->speak(); })
    {
    }

    constexpr std::string_view speak() const
    {
        return speak_fn(animal);
    }
};

int main()
{
    static_assert(AnimalView(Cow()).speak() == "Mooo");
    std::println("{}", AnimalView(Sheep()).speak());
}
```
