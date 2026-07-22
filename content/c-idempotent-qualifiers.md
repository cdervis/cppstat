## What It Does

A type qualifier (`const`, `volatile`, or `restrict`) may appear more than once when qualifying a
single type, whether written directly or introduced through one or more typedefs. The redundant
occurrences carry no additional meaning. The resulting type is the same as if the qualifier appeared
only once. In C89, duplicating a qualifier was a constraint violation that required a diagnostic.

## Why It Matters

The rule lets qualification compose safely when part of a type comes from a typedef. When a
qualifier is hidden inside a typedef defined in a header, code that wants to add that qualifier
cannot tell whether it is already present short of trial and error. Under the C89 one-qualifier-only
constraint, applying `const` or `volatile` to such a type could produce a spurious diagnostic
depending on the header's internals. Collapsing duplicates to a single occurrence lets a typedef'd
type be further qualified unconditionally. It also lets an implementation make a typedef carry a
qualifier, such as defining `sig_atomic_t` as a volatile type, without breaking callers that also
apply the qualifier.

## Example

```c
#include <stdio.h>

typedef const int cint;

/* const appears once via the typedef and once directly */
const cint x = 42;

int main(void)
{
    printf("%d\n", x);
    return 0;
}
```
