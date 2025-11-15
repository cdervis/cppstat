This feature allows you to pass a string-like object to `static_assert`'s message (second argument).

Previously, it was limited to string literals, which could only provide limited information about the error.

Example previously (*from proposal*):

```
template <typename T, auto Expected, unsigned long Size = sizeof(T)>
constexpr bool ensure_size() {
    static_assert(sizeof(T) == Expected, "Unexpected sizeof");
    return true;
}

static_assert(ensure_size<S, 1>());
```

```raw
error: static assertion failed due to requirement 'sizeof(S) == 1':
    Unexpected sizeof
static_assert(sizeof(T) == Expected, "Unexpected sizeof");
^             ~~~~~~~~~~~~~~~~~~~~~
note: in instantiation of function template specialization
    'ensure_size<S, 1, 4ULL>' requested here
static_assert(ensure_size<S, 1>());
^
note: expression evaluates to '4 == 1'
static_assert(sizeof(T) == Expected, "Unexpected sizeof");
~~~~~~~~~~^~~~~~~~~~~
```

---

With this feature:

```
static_assert(sizeof(S) == 1,
              fmt::format("Unexpected sizeof: expected 1, got {}", sizeof(S)));
```

```raw
error: static assertion failed due to requirement 'sizeof(S) == 1':
    Unexpected sizeof: expected 1, got 4
static_assert(sizeof(S) == 1,
^             ~~~~~~~~~~~~~~
note: expression evaluates to '4 == 1'
static_assert(sizeof(S) == 1,
              ~~~~~~~~~~^~~~
```


