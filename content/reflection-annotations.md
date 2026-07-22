## What It Does

An annotation attaches a compile-time value to a declaration where reflection can read it back. It
is written inside attribute brackets with a leading `=`, as in `[[= 1]] void f();`. Annotations may
be applied to a declaration of a type, type alias, variable, function, namespace, enumerator,
base-specifier, or non-static data member. The value is the result of `std::meta::reflect_constant`
applied to the given constant expression, and `std::meta::annotations_of` retrieves the annotations
of a reflected entity.

## Why It Matters

Reflection can enumerate what a class contains, but not what its members are intended for. It cannot
tell which field is a command-line flag, or which function is a test to parametrize. Ordinary
attributes appear to be the place to record that, but they are ignorable, so an implementation may
discard them, and they carry no value that reflection could return. An annotation is therefore a
distinct construct whose value is preserved and readable through reflection. It is written as an
attribute of the form `= expr`, so it reuses attribute placement but stays separate from attributes
proper.

## Example

```cpp
#include <meta>
#include <print>

struct Column
{
    int width;
};

struct Row
{
    [[= Column(8)]] int id;
    [[= Column(24)]] int name;
};

int main()
{
    template for (constexpr auto member : define_static_array(std::meta::nonstatic_data_members_of(
                      ^^Row, std::meta::access_context::current())))
    {
        constexpr auto anns = define_static_array(std::meta::annotations_of(member));
        constexpr auto col = std::meta::extract<Column>(anns[0]);
        std::println("{} -> width {}", std::meta::identifier_of(member), col.width);
    }
}
```
