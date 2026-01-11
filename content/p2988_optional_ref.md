This library feature adds a specialization for `std::optional<T>` that is able to store **non-owning** references.

With this, you're able to improve code that relies on pointers to signal nullability.

For example:

```
auto find_object(std::string_view name) -> Object*;

auto* obj = find_object("Some Object");

if (obj != nullptr) {
    print(*obj);
}
```

It might not be clear to the reader whether `find_object()` always returns a valid pointer or `nullptr`.
Additionally, the caller might forget to perform a null-check for the returned value.

With `std::optional<T&>`, this can be improved:

```
auto find_object(std::string_view name) -> std::optional<Object&>;

auto maybe_obj = find_object("Some Object");

// More apparent: value must be unwrapped first
if (maybe_obj) {
    print(*maybe_obj);
}

// Alternatively: use monadic operations
maybe_obj.and_then(print);
```

Together with a hardened standard library ([P3471](https://wg21.link/P3471)), `std::optional<T&>` offers
a clearer and safer alternative to raw pointers.

---

### Related libraries:

- [bemanproject/optional (GitHub)](https://github.com/bemanproject/optional)
