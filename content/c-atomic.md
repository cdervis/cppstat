---
execute: true
show_assembly: true
flags: "-std=c11"
---

## What It Does

`_Atomic` qualifies a type to enable atomic operations without data races. The `<stdatomic.h>`
header provides atomic types, operations (`atomic_load()`, `atomic_store()`, `atomic_fetch_add()`, etc.),
and memory ordering specifications. Atomic operations are indivisible with respect to concurrent
access.

## Why It Matters

Concurrent access to shared variables without synchronization causes data races and undefined
behavior. Atomic types and operations provide lock-free synchronization primitives that are
guaranteed to execute as indivisible units, enabling correct concurrent programming.

## Example

```c
#include <stdio.h>
#include <stdatomic.h>

int main(void) {
    _Atomic int counter = 0;

    atomic_store(&counter, 10);
    int old = atomic_fetch_add(&counter, 5);

    printf("Old value: %d\n", old);
    printf("New value: %d\n", atomic_load(&counter));

    // Compare-and-swap
    int expected = 15;
    if (atomic_compare_exchange_strong(&counter, &expected, 20)) {
        printf("CAS succeeded, counter = %d\n", atomic_load(&counter));
    }
}
```
