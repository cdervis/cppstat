## What It Does

C99 permits a comma after the final constant in an enumerator list, so
`enum color { RED, GREEN, BLUE, };` is valid. The trailing comma is punctuation only. It introduces
no additional enumerator and leaves the enumeration's values unchanged.

## Why It Matters

With a trailing comma permitted, every enumerator line has the same form, including the last.
Adding, removing, or reordering entries then changes only the lines involved, and code that
generates an enumerator list need not special-case its final element. C already allowed a trailing
comma in initializer lists, so the same treatment for enumerators keeps the two consistent.

## Example

```c
#include <stdio.h>

enum color
{
    RED,
    GREEN,
    BLUE,
};

int main(void)
{
    enum color c = BLUE;
    printf("BLUE = %d\n", c);
    printf("count = %d\n", BLUE + 1);
}
```
