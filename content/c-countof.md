## What It Does

The `_Countof` operator returns the number of elements in an array.
It takes either an array expression or an array type as its operand and evaluates to a constant
of type `size_t` representing the array's element count.

## Why It Matters

Computing array length previously required the idiom `sizeof(arr) / sizeof(arr[0])`, which
produces incorrect results when applied to a pointer instead of an array.
`_Countof` only accepts array types, providing a compile-time error when misused with pointers,
and directly expresses the intent of obtaining element count.

## Example

```c
#include <stdio.h>

int main(void) {
    int numbers[10];
    char message[] = "Hello";

    printf("numbers has %zu elements\n", _Countof(numbers));  // 10
    printf("message has %zu elements\n", _Countof(message));  // 6 (includes '\0')

    // Works with typedefs
    typedef double vec3[3];
    printf("vec3 has %zu elements\n", _Countof(vec3));  // 3

    // Compile-time constant
    _Static_assert(_Countof(numbers) == 10, "expected 10 elements");
}
```
