## What It Does

Case range expressions allow a `case` label to match a contiguous range of integer values
using the syntax `case low ... high:`.
Both endpoints are inclusive, and the range covers all integer values from `low` to `high`.

## Why It Matters

Matching multiple consecutive values in a `switch` previously required listing each value
as a separate `case` label.
Case ranges express the intent directly and reduce repetition when handling contiguous value sets.

## Example

```c
#include <stdio.h>

const char *classify_char(char c) {
    switch (c) {
        case 'a' ... 'z':
            return "lowercase letter";
        case 'A' ... 'Z':
            return "uppercase letter";
        case '0' ... '9':
            return "digit";
        case ' ':
        case '\t':
        case '\n':
            return "whitespace";
        default:
            return "other";
    }
}

int main(void) {
    printf("'g' is a %s\n", classify_char('g'));
    printf("'M' is a %s\n", classify_char('M'));
    printf("'7' is a %s\n", classify_char('7'));
    printf("'@' is a %s\n", classify_char('@'));
}
```
