---
execute: true
show_assembly: true
flags: "-std=c99"
---

## What It Does

A flexible array member is an array declared with no size as the last member of a structure.
The structure is allocated with additional space beyond its declared size, and the flexible
array member uses that space. The syntax is `type member[];` as the final member.

## Why It Matters

Variable-size data structures traditionally used a pointer member requiring separate allocation.
Flexible array members allow the variable-size data to be contiguous with the structure header,
improving cache locality and simplifying memory management to a single allocation.

## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Message {
    int type;
    size_t length;
    char data[];  // Flexible array member
};

struct Message* create_message(int type, const char* text) {
    size_t len = strlen(text) + 1;
    struct Message* msg = malloc(sizeof(struct Message) + len);
    msg->type = type;
    msg->length = len;
    memcpy(msg->data, text, len);
    return msg;
}

int main(void) {
    struct Message* msg = create_message(1, "Hello, World!");

    printf("Type: %d\n", msg->type);
    printf("Length: %zu\n", msg->length);
    printf("Data: %s\n", msg->data);

    free(msg);
}
```
