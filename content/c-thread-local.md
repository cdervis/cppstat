---
execute: true
show_assembly: true
flags: "-std=c11"
---

## What It Does

`_Thread_local` specifies that a variable has thread storage duration. Each thread has its
own instance of the variable, initialized independently. The `<threads.h>` header provides
the alternative spelling `thread_local`.

## Why It Matters

Global variables are shared across threads, requiring synchronization for safe access.
Thread-local variables provide per-thread storage without synchronization overhead, useful
for thread-specific state like error codes, random number generators, or caches.

## Example

```c
#include <stdio.h>
#include <threads.h>

_Thread_local int thread_id = 0;
_Thread_local char thread_name[32] = "";

int worker(void *arg) {
    thread_id = *(int*)arg;
    snprintf(thread_name, sizeof(thread_name), "Worker-%d", thread_id);

    printf("%s: thread_id = %d\n", thread_name, thread_id);
    return 0;
}

int main(void) {
    thrd_t t1, t2;
    int id1 = 1, id2 = 2;

    thrd_create(&t1, worker, &id1);
    thrd_create(&t2, worker, &id2);

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);
}
```
