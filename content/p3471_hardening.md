Standard library hardening adds certain safety checks to various types, such as
`std::vector`, `std::string` and `std::optional`.

This prevents common cases of undefined behavior such as out-of-bounds and null pointer accesses.

**Note** that standard library hardening is designed to also be enabled in production code. It's **not** only a debug-mode
feature.

---

### Enabling

#### With libstdc++ (GCC)

Standard library hardening is controlled via the `_GLIBCXX_ASSERTIONS` macro, which has to be defined to enable it.
**Note** when compiling with optimizations disabled, this is enabled implicitly, by default.

libstd++ provides multiple macros and compiler flags that enable additional checks.
For more information, see [libstdc++ Macros](https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html).

---

#### With libc++ (Clang and Apple Clang)

Standard library hardening is controlled via multiple macros, each categorized by
the amount of checks performed:

- `_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_NONE`
- `_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_FAST`
- `_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE`
- `_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_DEBUG`

```cmake
# CMake example

# Enable standard library hardening for target 'MyApp' (recommended)
target_compile_definitions(MyApp PRIVATE -D_LIBCPP_HARDENING_MODE_FAST)

# Or enable for all targets
add_compile_definitions(-D_LIBCPP_HARDENING_MODE_FAST)
```

For a description of all modes, see [libc++ Hardening Modes](https://libcxx.llvm.org/Hardening.html).

---

#### With MSVC STL

Standard library hardening is controlled via the `_MSVC_STL_HARDENING` macro, which has to be set
to `1` to enable it. A value of `0` disables it.

The MSVC STL provides multiple macros that enable additional checks, such as `_MSVC_STL_DESTRUCTOR_TOMBSTONES`.
For more information, see [MSVC STL Hardening](https://github.com/microsoft/STL/wiki/STL-Hardening).

---

### Related pages:

- [libstdc++ Macros](https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html)
- [libc++ Hardening Modes](https://libcxx.llvm.org/Hardening.html)
- [MSVC STL Hardening](https://github.com/microsoft/STL/wiki/STL-Hardening)
- [Compiler Options Hardening Guide for C and C++](https://best.openssf.org/Compiler-Hardening-Guides/Compiler-Options-Hardening-Guide-for-C-and-C++.html)
- [What’s New for C++ Developers in Visual Studio 2022 17.14](https://devblogs.microsoft.com/cppblog/whats-new-for-cpp-developers-in-visual-studio-2022-17-14/)
- [cppreference](https://en.cppreference.com/w/cpp/standard_library.html)
