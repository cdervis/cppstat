---
execute: true
flags: "-freflection"
---

## What It Does

Reflection provides compile-time introspection and manipulation of program structure.
Through the `<meta>` header, metaprogramming constructs can query type information including
non-static data members, enumerators, function signatures, and cv-qualifiers.
The resulting metadata can be used in template metaprogramming to generate code via
compile-time iteration.

## Why It Matters

Reflection exposes compiler-internal type information to metaprograms, eliminating the
requirement for manual boilerplate or external preprocessing tools for tasks that
consume type structure (serialization, diagnostic output, binding generation).

## Example

```cpp
#include <meta>
#include <optional>
#include <array>
#include <print>
#include <string>

using namespace std;
using namespace std::meta;

enum class Color { Red, Green, Blue };
struct Point { float x, y, z; };

template <typename E> requires is_enum_v<E>
consteval string_view enum_to_string(E value) {
    // Get the members of enum E
    constexpr auto members = define_static_array(enumerators_of(^^E));

    for (auto i = 0uz; i < members.size(); ++i) {
        if (value == extract<E>(members[i])) {
            return identifier_of(members[i]);
        }
    }

    return "<unnamed>";
}

template <typename E> requires is_enum_v<E>
consteval optional<E> string_to_enum(string_view name) {
    constexpr auto enums = define_static_array(enumerators_of(^^E));

    for (auto i = 0uz; i < enums.size(); ++i) {
        if (name == identifier_of(enums[i])) {
            return extract<E>(enums[i]);
        }
    }

    return nullopt;
}

template <typename T>
consteval auto get_member_names() {
    constexpr auto ctx = access_context::unchecked();
    constexpr auto m = define_static_array(nonstatic_data_members_of(^^T, ctx));

    auto names = array<string_view, m.size()>();

    for (auto i = 0uz; i < m.size(); ++i) {
        names[i] = identifier_of(m[i]);
    }

    return names;
}

int main() {
    // Can use reflection results in static assertions.
    static_assert(enum_to_string(Color::Red) == "Red");
    
    std::println("Color::Blue's name: '{}'", enum_to_string(Color::Blue));

    constexpr auto names = get_member_names<Point>();    
    std::println("Point members: {:n}", names);
}
```
