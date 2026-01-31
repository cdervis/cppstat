---
show_only: true
---

## What It Does

Modules provide an encapsulation mechanism that replaces textual inclusion of header files with explicit interface declarations. An `export` declaration specifies the module's public interface; `import` declarations make these declarations available to consuming translation units. Modules are compiled once, cached as binary metadata, and provide namespace isolation that prevents macro leakage and implementation detail exposure.

## Why It Matters

Header files require textual re-parsing for each translation unit, impose macro pollution and include-order dependencies, and expose implementation details through textual inclusion. Modules eliminate redundant parsing via precompiled metadata, enforce interface boundaries at the language level, and improve build performance through on-demand symbol loading.

## Example

```cpp
// math.ixx (module interface)
export module math;

export int add(int a, int b) {
    return a + b;
}

export namespace geometry {
    double circle_area(double radius) {
        return 3.14159 * radius * radius;
    }
}

// Internal helper - not exported
int internal_helper() { return 42; }
```

```cpp
// main.cpp
import math;
import std;

int main() {
    std::println("{}", add(2, 3));
    std::println("{}", geometry::circle_area(5.0));
    // internal_helper();  // Error: not exported
}
```
