## What It Does

A namespace definition may use a qualified name to open several nested namespaces at once.
`namespace A::B::C { }` is equivalent to three nested `namespace` blocks, and the names behave
identically either way.

## Why It Matters

Writing each level of a deep namespace as its own block requires a separate `namespace` line and a
closing brace for every level. The qualified form expresses the same nesting in a single
declaration. It is defined entirely by that equivalence and adds no new scoping behavior, so the two
forms are interchangeable and code that compiled before is unaffected.

## Example

```cpp
#include <print>

namespace app::net::http
{
int status()
{
    return 200;
}
} // namespace app::net::http

namespace app
{
namespace net
{
namespace ftp
{
int status()
{
    return 220;
}
} // namespace ftp
} // namespace net
} // namespace app

int main()
{
    std::println("{}", app::net::http::status());
    std::println("{}", app::net::ftp::status());
}
```
