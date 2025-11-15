This feature allows you to use `_` as a placeholder name multiple times, for example in variable
declarations and structured bindings.

Previously, `_` was treated as an identifier, meaning it could only be used once within a scope.

With this feature, the following is possible, all within the same scope:

```
// Resource guards often have no name, since they
// only exist to perform cleanup at the end of a scope.
auto _ = std::lock_guard(mutex);


// Sometimes we're not interested in all elements of a tuple.
auto [x, y, _] = f();


// Lambdas may not need to use an argument that is passed to them.
// Using _ marks the parameter with [[maybe_unused]] implicitly.
callback([&](auto _) {
    something_that_does_not_use_the_argument(x, y);
});


// Alternative to std::views::values:
for (const auto& [_, value] : map) {
    std::println("value: {}", value);
}
```

Using the `_` placeholder implicitly gives the declaration a `[[maybe_unused]]` attribute.

```
auto _ = f(); // Equivalent to [[maybe_unused]] auto _ = f();
```
