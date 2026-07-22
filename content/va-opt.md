## What It Does

`__VA_OPT__(content)` may appear in the replacement list of a variadic macro. It expands to
`content` when the variable arguments, after substitution, consist of at least one preprocessing
token, and to nothing otherwise. Its usual job is to emit a separating comma only when arguments
actually follow it. The condition is about tokens, not about whether an argument was written. An
argument that is present but substitutes to nothing still suppresses the expansion.

## Why It Matters

A variadic macro that places `__VA_ARGS__` after a fixed argument needs a comma before it, but that
comma is wrong when no variable arguments follow. Take `#define F(X, ...) f(X, __VA_ARGS__)`. The
call `F(a, )` expands to `f(a, )`, whose trailing comma is a syntax error. The older rule that an
invocation supply at least as many commas as the macro has mandatory parameters made `F(a)`
ill-formed outright, so a macro like `ERROR(msg, ...)` could not be called with only its message.
`__VA_OPT__` ties the separator to whether the variable arguments expand to any tokens, so the comma
appears only when something follows it.

## Example

```cpp
#include <print>

#define LOG(fmt, ...) std::println("[log] " fmt __VA_OPT__(, ) __VA_ARGS__)

int main()
{
    LOG("starting up");
    LOG("loaded {} items", 7);
    LOG("{} of {} done", 3, 10);
}
```
