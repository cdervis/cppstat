## What It Does

The `<uchar.h>` header declares two unsigned integer types. `char16_t` (the same type as
`uint_least16_t`) holds 16-bit characters, and `char32_t` (the same type as `uint_least32_t`) holds
32-bit characters. The `u` and `U` prefixes create character constants and string literals of these
types. `u'x'` and `u"..."` produce `char16_t` data, while `U'x'` and `U"..."` produce `char32_t`
data. The header also declares restartable conversion functions (`mbrtoc16`, `c16rtomb`, `mbrtoc32`,
`c32rtomb`) between multibyte sequences and these types.

## Why It Matters

The only prior wide type, `wchar_t`, has an implementation-defined width (16-bit on some platforms,
32-bit on others) and an unspecified encoding, which makes it unusable when code needs a definite
Unicode representation. `char16_t` and `char32_t` guarantee widths of at least 16 and 32 bits,
giving named targets for UTF-16 and UTF-32 that do not depend on how `wchar_t` is configured. The
`u`/`U` prefixes let source text be stored directly in those types without manual encoding. Because
the encoding of these types remains technically implementation-defined, the `__STDC_UTF_16__` and
`__STDC_UTF_32__` macros, when defined as 1, let a program confirm that the UTF encodings are in
effect. The conversion functions carry an `mbstate_t` so fragmented multibyte input can be decoded
incrementally.

## Example

```c
#include <stdint.h>
#include <stdio.h>

/* char16_t/char32_t from <uchar.h> are the same types as
   uint_least16_t/uint_least32_t, used directly here. */
int main(void)
{
    uint_least16_t u16[] = u"C11";
    uint_least32_t u32[] = U"C11";
    uint_least32_t ch = U'*';

    printf("u16:");
    for (int i = 0; u16[i]; i++)
        printf(" %u", (unsigned)u16[i]);
    printf("\nu32:");
    for (int i = 0; u32[i]; i++)
        printf(" %u", (unsigned)u32[i]);
    printf("\nchar: %u\n", (unsigned)ch);

#ifdef __STDC_UTF_16__
    printf("UTF-16 guaranteed: %d\n", __STDC_UTF_16__);
#endif
    return 0;
}
```
