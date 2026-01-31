---
execute: true
---

## What It Does

Designated initializers initialize aggregate members by name using `.member = value` syntax.
Members may be omitted from the initializer list and are default-initialized; the syntax explicitly associates each initializer with its corresponding member.

## Why It Matters

Positional initialization is sensitive to member order; adding or reordering members changes the mapping of initializers without diagnostic.
Designated initializers are insensitive to member reordering and document the mapping between initializers and members explicitly.
The syntax is compatible with C99 designated initializers, with the additional constraint that designators must appear in declaration order in C++.

## Example

```cpp
#include <string>
#include <print>

struct Config {
    std::string host = "localhost";
    int port = 8080;
    bool ssl = false;
    int timeout_ms = 5000;
};

struct Point { int x, y, z; };

int main() {
    // Clear what each value means
    auto cfg = Config{
        .host = "example.com",
        .port = 443,
        .ssl = true
        // timeout_ms uses default (0, because of int)
    };

    // More explicit than:
    // auto cfg = Config{"example.com", 443, true, 5000};

    std::println("cfg: {}; {}; {}; {}", cfg.host, cfg.port, cfg.ssl, cfg.timeout_ms);

    auto p = Point{.x = 1, .z = 3};  // y is default-initialized

    std::println("p: {}; {}; {}", p.x, p.y, p.z);
}
```
