A core language feature that adds a literal suffix for `size_t` and its associated
signed type.

Example:

```
// Instead of writing:
auto num  = size_t(0);
auto diff = ptrdiff_t(0);

// You can now write:
auto num = 0uz; // num is of type size_t
auto diff = 0t; // diff is of type ptrdiff_t
```

Note that the literal suffix `zu` is also possible and equivalent to `uz`.
