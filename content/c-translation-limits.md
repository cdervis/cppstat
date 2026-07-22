## What It Does

C99 specifies the minimum capacities a conforming implementation must be able to translate and
execute in at least one program. These cover nesting depths, identifier significance, parameter and
argument counts, case labels, structure members, string literal length, object size, and more. C99
raised most of these minima above their C89 values. Case labels in a switch went from 257 to 1023,
block nesting from 15 to 127, significant characters in an external identifier from 6 to 31,
characters in a string literal (after concatenation) from 509 to 4095, and bytes in a single object
from 32767 to 65535. Implementations should avoid imposing fixed limits whenever possible.

## Why It Matters

These minima define the largest program a portable source may assume every conforming compiler
accepts, so authors can size code to a known floor without testing each toolchain. They are
guarantees, not hard ceilings. The standard requires only that one program reaching each limit
translate and execute. Because resources like memory come from a shared pool, not all limits need
hold at once. The values are compromises between allowing reasonably large portable programs and not
burdening small implementations. C99 could raise them because the assumed minimum target memory rose
from 64K to 512K, and because small and embedded targets are now usually built with cross compilers
hosted on workstations.

## Example

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* ~600-char literal: portable under C99 (min 4095), not C89 (509). */
    const char *s = "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789"
                    "0123456789012345678901234567890123456789";

    printf("length = %zu\n", strlen(s));
    return 0;
}
```
