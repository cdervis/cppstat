---
show_only: true
---

## What It Does

`#embed` is a preprocessor directive that includes the contents of a binary file as a
comma-separated list of integer values. It supports parameters like `limit()` to restrict
the number of bytes, `prefix()` and `suffix()` to add surrounding elements, and `if_empty()`
to provide a fallback when the file is empty.

## Why It Matters

Embedding binary data (images, fonts, firmware) into C programs previously required external
tools to convert files into C arrays or the use of compiler-specific extensions. `#embed`
provides a standard, portable mechanism to include binary resources directly, with control
over how the data is incorporated.

## Example

```c
#include <stdio.h>

static const unsigned char icon[] = {
#embed "icon.png" limit(64) if_empty(0)
};

int main(void) {
    printf("First %zu bytes of icon: ", sizeof(icon));
    for (size_t i = 0; i < sizeof(icon) && i < 8; ++i) {
        printf("%02x ", icon[i]);
    }
    printf("\n");
}
```
