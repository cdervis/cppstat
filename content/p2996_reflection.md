This feature adds static reflection capabilities to C++.
Static reflection allows a program to inspect its own structure at compile-time.

This adds a new operator `^^` to the language that reflects a type and produces a reflection value
of type `std::meta::info`, which is an opaque type (implementation is only known to the compiler).

A reflection value can be used to produce grammatical elements using a new construct called *splicer*,
which follows the form `[: refl :]`.

In addition, a new header `<meta>` is added that provides a number of `consteval` functions to work
with `std::meta::info` objects, for example obtaining the name or members of a type.

---

### Examples

```
constexpr auto r     = ^^int;  // Reflect the type int
typename[:r:] x      = 42;     // Same as: int x = 42;
typename[:^^char:] c = '*';    // Same as: char c = '*';
```

---

```
// Modify members of a struct via reflection
struct S { int i, int j; };

// Gets the field of S by name at compile-time:
consteval auto member_named(std::string_view name) {
    auto ctx = std::meta::access_context::current();
    
    // Loop through all fields of S:
    for (std::meta::info field : nonstatic_data_members_of(^^S, ctx)) {
        // If the name of the field matches the specified name, return the
        // reflection value of the field:
        if (has_identifier(field) && identifier_of(field) == name) {
          return field;
        }
    }
}

// ...

auto s = S();
s.[:member_named("j"):] = 42;  // Same as: s.j = 42;
s.[:member_named("x"):] = 0;   // Error (member_named("x") is not a constant).
```

---

```
// Convert an enum to a string
template<typename E>
  requires std::is_enum_v<E>
constexpr std::string_view enum_to_string(E value) {
    // is_enumerable_type() checks if the type is indeed enumerable.
    // For example, if E is a forward-declared enum type (incomplete) from the
    // standpoint of the caller, it will not count as enumerable.
    if constexpr (std::meta::is_enumerable_type(^^E))
    {
        // Iterate through all the members of E:
        template for (constexpr auto e :
                      std::define_static_array(std::meta::enumerators_of(^^E)))
        {
          // '[:e:]' accesses the value of the member, which is then compared against
          // the value we're searching for. If they're equal, we found the member and
          // can return its name.
          if (value == [:e:]) {
              return std::meta::identifier_of(e);
          }
        }
    }

    return "<unnamed>";
}

// ...

enum Color : int; // forward declare some enum (counts as incomplete)
static_assert(enum_to_string(Color(0)) == "<unnamed>"); // constant evaluation possible
std::println("Color 0: {}", enum_to_string(Color(0)));  // prints '<unnamed>'

enum Color : int { red, green, blue }; // define the enum
static_assert(enum_to_string(Color::red) == "red");
static_assert(enum_to_string(Color(42)) == "<unnamed>");
std::println("Color 0: {}", enum_to_string(Color(0)));  // prints 'red'
```

---

### Related pages:

- [P2996](https://wg21.link/P2996)
- [Gazing Beyond Reflection for C++26 (YouTube)](https://youtu.be/wpjiowJW2ks)

---

### Related libraries:

- [Neargye/magic_enum](https://github.com/Neargye/magic_enum)
- [getml/reflect-cpp](https://github.com/getml/reflect-cpp)
