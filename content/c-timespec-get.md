## What It Does

`timespec_get` fills a `struct timespec` with the current calendar time in a given time base,
returning that base on success and zero on failure. With the base `TIME_UTC`, `tv_sec` receives the
number of seconds since an implementation-defined epoch, truncated to a whole value, and `tv_nsec`
receives the nanoseconds, rounded to the resolution of the system clock.

## Why It Matters

C's other time facilities do not provide portable sub-second calendar time. The value from `time()`
has an unspecified encoding, and the range and precision of `time_t` are implementation-defined, so
portable code cannot rely on sub-second resolution or name its units. Obtaining a known resolution
required a platform-specific call such as POSIX `clock_gettime(CLOCK_REALTIME, ts)`. `timespec_get`
standardizes calendar time with an explicit nanoseconds field, and its `base` parameter allows an
implementation to offer time bases beyond the required `TIME_UTC` without a new function.

## Example

```c
#include <stdio.h>
#include <time.h>

int main(void)
{
    struct timespec ts;

    if (timespec_get(&ts, TIME_UTC) == TIME_UTC)
    {
        printf("seconds:     %lld\n", (long long)ts.tv_sec);
        printf("nanoseconds: %ld\n", (long)ts.tv_nsec);
    }
    else
    {
        printf("timespec_get failed\n");
    }
}
```
