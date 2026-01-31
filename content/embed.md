---
show_only: true
---

## What It Does

`#embed` is a preprocessor directive that embeds the contents of a binary file as a comma-separated list of integer literals.
The directive specifies a file path; an optional `limit(N)` parameter restricts the number of bytes embedded.

## Why It Matters

Binary resource embedding previously required external tools to convert files to C array syntax, or runtime file I/O.
`#embed` integrates resource embedding into the translation process, ensuring embedded data is synchronized with source files at compile time without, external tooling.

## Example

```cpp
#include <cstdint>
#include <span>

// Embed an entire file
const std::uint8_t icon[] = {
    #embed "icon.png"
};

// Embed with a size limit
const std::uint8_t header[] = {
    #embed "large_file.bin" limit(256)
};

std::span<const std::uint8_t> get_icon() {
    return icon;
}
```
