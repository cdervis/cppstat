---
execute: false
---

## What It Does

`std::filesystem` provides facilities for path manipulation, file status queries, directory iteration, and file system modification operations.
The library abstracts platform-specific file system interfaces into a portable API.

## Why It Matters

File system operations previously required platform-specific APIs or third-party libraries such as [Boost](https://www.boost.org/).
`std::filesystem` standardizes file system access, derived from Boost.Filesystem, eliminating external dependencies for portable file manipulation.

## Example

```cpp
#include <filesystem>
#include <print>

// Shortcut so that we don't have to always type std::filesystem
namespace fs = std::filesystem;

int main() {
    auto p = fs::path("/home/user/documents/report.txt");

    std::println("Filename: {}", p.filename().string());    // report.txt
    std::println("Extension: {}", p.extension().string());  // .txt
    std::println("Parent: {}", p.parent_path().string());   // /home/user/documents

    // Check existence and properties
    if (fs::exists(p)) {
        std::println("Size: {} bytes", fs::file_size(p));
    }

    // Iterate directory
    for (const auto& entry : fs::directory_iterator(".")) {
        std::println("{}", entry.path().filename().string());
    }

    // Common operations
    fs::create_directories("a/b/c");
    fs::copy("source.txt", "dest.txt");
    fs::remove("temp.txt");
}
```
