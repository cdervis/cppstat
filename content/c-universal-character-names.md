## What It Does

C99 lets identifiers contain characters outside the basic source set through universal character
names. A universal character name is a backslash followed by `u` and four hexadecimal digits
(`\uXXXX`), or `U` and eight hexadecimal digits (`\UXXXXXXXX`), each naming an ISO/IEC 10646 code
point. A universal character name may appear anywhere in an identifier, except that an identifier
may not begin with an extended digit. Only the code points in the ranges listed in Annex D are
permitted. An implementation may also accept the corresponding raw native character directly, but
that acceptance is implementation-defined; the escape spelling is the portable form.

## Why It Matters

Through C95 the source character set for identifiers was effectively English, and a name using
national characters was not strictly conforming. Multibyte characters already allowed non-English
text in string literals and character constants, but that mechanism was implementation-dependent,
did not travel between heterogeneous environments, and did not cover identifiers at all. A universal
character name gives a spelling for any permitted code point using only basic source characters, so
a name such as größe reads the same regardless of source encoding or local character set.

## Example

```c
#include <stdio.h>

int main(void)
{
    int \u00FCber = 7; /* U+00FC: 'u' with diaeresis */
    printf("value = %d\n", \u00FCber);
    return 0;
}
```
