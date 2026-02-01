---
execute: true
show_assembly: true
flags: "-std=c99"
---

## What It Does

Designated initializers specify which member or element to initialize using `.member` for
structures/unions or `[index]` for arrays. Unspecified members are zero-initialized.
Initializers can be given in any order and can be mixed with positional initializers.

## Why It Matters

Positional initialization requires remembering member order and initializing all preceding
members. Designated initializers document which field is being set, allow partial initialization
with automatic zeroing, and remain correct when structure layout changes.

## Example

```c
#include <stdio.h>

struct Point {
    int x, y, z;
};

struct Config {
    int timeout;
    int retries;
    char name[32];
};

int main(void) {
    struct Point p = {.y = 10, .x = 5};  // z is zero-initialized

    printf("Point: (%d, %d, %d)\n", p.x, p.y, p.z);

    struct Config cfg = {
        .name = "default",
        .timeout = 30
        // retries is zero-initialized
    };

    printf("Config: %s, timeout=%d, retries=%d\n",
           cfg.name, cfg.timeout, cfg.retries);

    int arr[5] = {[2] = 100, [4] = 200};  // Others are zero

    printf("Array: %d %d %d %d %d\n",
           arr[0], arr[1], arr[2], arr[3], arr[4]);
}
```
