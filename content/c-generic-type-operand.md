## What It Does

Generic selection with a type operand extends `_Generic` to accept a type name directly,
in addition to the existing expression form.
The syntax `_Generic(type-name, ...)` selects an association based on the provided type
without requiring a value of that type.

## Why It Matters

The original `_Generic` required an expression operand, forcing macros to manufacture a
value (often via a cast or compound literal) when only type-based dispatch was needed.
Type operands enable `_Generic` selection based purely on type information, supporting
metaprogramming patterns that operate on types rather than values.

## Example

```c
#include <stdio.h>

#define type_name(T) _Generic(T,           \
    int:          "int",                   \
    unsigned int: "unsigned int",          \
    float:        "float",                 \
    double:       "double",                \
    default:      "unknown")

#define alignment_of(T) _Generic(T,        \
    char:   1,                             \
    short:  _Alignof(short),               \
    int:    _Alignof(int),                 \
    double: _Alignof(double),              \
    default: 0)

int main(void) {
    printf("Type name: %s\n", type_name(int));
    printf("Type name: %s\n", type_name(double));
    printf("Alignment of int: %d\n", alignment_of(int));
}
```
