---
execute: true
show_assembly: true
---
## What It Does

`__func__` is a predefined identifier that expands to a string literal containing the name
of the enclosing function. It is implicitly declared as `static const char __func__[]`
at the beginning of each function body.

## Why It Matters

Debugging messages and error reports benefit from including the function name. Manually
writing function names in strings requires updating strings when renaming functions.
`__func__` provides the name automatically, keeping error messages synchronized with code.

## Example

```c
#include <stdio.h>

void log_entry(void) {
    printf("Entering: %s\n", __func__);
}

int calculate(int x) {
    printf("[%s] Input: %d\n", __func__, x);
    return x * 2;
}

#define LOG_ERROR(msg) fprintf(stderr, "%s: %s\n", __func__, msg)

void process(int value) {
    if (value < 0) {
        LOG_ERROR("negative value not allowed");
        return;
    }
    printf("%s: processing %d\n", __func__, value);
}

int main(void) {
    log_entry();
    calculate(21);
    process(-1);
    process(5);
}
```
