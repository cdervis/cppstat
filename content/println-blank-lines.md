## What It Does

`std::println()` gains overloads that accept no format string argument, allowing direct output of a blank line. Three new signatures are provided:
`std::println()` writes to `stdout`, `std::println(std::FILE*)` writes to a
C file stream, and `std::println(std::ostream&)` writes to a C++
output stream. Each outputs a single newline character.

## Why It Matters

Before this addition, printing a blank line required passing an empty format
string: `std::println("")`. This works but involves format string parsing
machinery for what is conceptually a parameterless operation.
The zero-argument overloads express the intent directly and allow
implementations to optimize the common case of outputting a newline.

## Example

```cpp
#include <print>
#include <fstream>

int main() {
    std::println("Section 1");
    std::println("Content here...");

    std::println();  // Blank line to stdout

    std::println("Section 2");

    // Write blank line to a file
    auto file = std::fopen("output.txt", "w");
    std::println(file, "Line 1");
    std::println(file);
    std::println(file, "Line 2");
    std::fclose(file);

    // Write blank line to an ostream
    auto ofs = std::ofstream("log.txt");
    std::println(ofs, "Entry 1");
    std::println(ofs);
    std::println(ofs, "Entry 2");
}
```
