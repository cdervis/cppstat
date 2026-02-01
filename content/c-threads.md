---
execute: true
show_assembly: true
flags: "-std=c11"
---

## What It Does

`<threads.h>` provides thread management (`thrd_create()`, `thrd_join()`), mutexes (`mtx_init()`,
`mtx_lock()`, `mtx_unlock()`), condition variables (`cnd_wait()`, `cnd_signal()`), and thread-specific
storage (`tss_create()`, `tss_get()`, `tss_set()`). This is the standard C threading API.

## Why It Matters

Before C11, threading required platform-specific APIs (pthreads on Unix, Win32 threads on
Windows) or third-party libraries. `<threads.h>` provides a portable threading interface,
enabling concurrent programs without platform dependencies.

## Example

```c
#include <stdio.h>
#include <threads.h>

mtx_t mutex;
int shared_counter = 0;

int increment(void* arg) {
    const int count = *(int*)arg;

    for (int i = 0; i < count; i++) {
        mtx_lock(&mutex);
        shared_counter++;
        mtx_unlock(&mutex);
    }

    return 0;
}

int main(void) {
    thrd_t t1;
    thrd_t t2;
    int count = 10000;

    mtx_init(&mutex, mtx_plain);

    thrd_create(&t1, increment, &count);
    thrd_create(&t2, increment, &count);

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);

    printf("Counter: %d\n", shared_counter);

    mtx_destroy(&mutex);
}
```
