## What It Does

This feature introduces the `0o` and `0O` prefixes for octal integer literals as the preferred
syntax, marking the traditional leading-zero octal notation (e.g., `0755`) as obsolescent.
It also adds delimited escape sequences using braces, such as `\x{1F600}` for hexadecimal and `\o{755}` for octal escapes.

## Why It Matters

The traditional octal syntax where a leading zero indicates base 8 (e.g., `0777`) is a common source of
errors, as decimal numbers with leading zeros are misinterpreted.
The explicit `0o` prefix matches the binary `0b` prefix and indicates base 8 unambiguously.
Delimited escape sequences resolve parsing ambiguity when escape sequences are followed by valid hex or octal digits.

## Example

```c
#include <stdio.h>

int main(void) {
    // Explicit octal prefix (preferred)
    int permissions = 0o755;
    int old_style = 0755;  // Obsolescent, but still valid

    printf("permissions = %d (octal %o)\n", permissions, permissions);

    // Delimited escape sequences
    char hex_delim[] = "\x{48}ello";      // 'H' via hex
    char octal_delim[] = "\o{110}ello";   // 'H' via octal

    printf("%s\n", hex_delim);
    printf("%s\n", octal_delim);

    // Resolves ambiguity: \x1 followed by 'F', not \x1F
    char ambiguous[] = "\x{1}F";
    printf("Length: %zu\n", sizeof(ambiguous) - 1);  // 2 characters
}
```
