## What It Does

`_Pragma(string-literal)` is a unary preprocessor operator. The operand is destringized. An `L`
prefix is dropped, the surrounding double-quotes are removed, and `\"` and `\\` become `"` and `\`.
The resulting characters are rescanned as preprocessing tokens and executed as if they formed the
tokens of a `#pragma` directive. The original four tokens (`_Pragma`, `(`, the string, `)`) are then
removed. Because it is an operator taking a string argument rather than a line-oriented directive,
it can appear in a macro replacement list and be produced by macro expansion.

## Why It Matters

A `#pragma` is a preprocessing directive, so it must occupy its own logical line, and the
preprocessor never emits directive lines from a macro body. That makes it impossible to wrap a
pragma inside a macro or build one from macro arguments. `_Pragma` expresses the same effect as an
operator whose operand is a string. Because macros can expand to operator expressions and can
stringize their arguments with `#`, a pragma can be packaged in a macro and parameterized. The
destringization rules exist so a pragma's own tokens, including quotes and backslashes, survive
inside the string literal and are recovered exactly before being processed. Which pragmas do
anything remains implementation-defined.

## Example

```c
#include <stdio.h>

#define DIAG(x) _Pragma(#x)

int main(void)
{
    DIAG(GCC diagnostic push)
    DIAG(GCC diagnostic ignored "-Wunused-variable")
    int unused = 42;
    DIAG(GCC diagnostic pop)

    printf("built cleanly with _Pragma from inside a macro\n");
    return 0;
}
```
