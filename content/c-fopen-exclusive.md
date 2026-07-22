## What It Does

Appending `x` as the final character of an `fopen()` (or `freopen()`) mode string requests exclusive
creation. The character is valid only with the write modes, giving `"wx"`, `"wbx"`, `"w+x"`, and
`"w+bx"`/`"wb+x"`. If the named file already exists, or cannot be created, the call fails and
returns `NULL`. Otherwise the file is created and opened with exclusive access, to the extent the
underlying system supports it. Read and append modes do not accept `x`.

## Why It Matters

Plain `"w"` truncates an existing file or creates a new one and never reports which happened, so
overwriting an unintended file goes unnoticed. Code that wanted a fresh file used to test for
existence first, then open for writing. Between those two steps another process on a shared system
can create or link the name, and the second open follows or clobbers it. Folding creation-if-absent
into one atomic step closes that race, mirroring POSIX `open()` with `O_CREAT | O_EXCL`.

## Example

```c
#include <stdio.h>

int main(void)
{
    const char *name = "cppstat_excl.tmp";

    FILE *f = fopen(name, "wx");
    if (f)
    {
        fputs("first\n", f);
        fclose(f);
        printf("created\n");
    }

    FILE *g = fopen(name, "wx");
    if (g == NULL)
        printf("refused (file exists)\n");
    else
        fclose(g);

    remove(name);
    return 0;
}
```
