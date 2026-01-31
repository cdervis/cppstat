## What It Does

Member functions may declare an explicit `this` parameter that deduces the type and value category of the object expression.
A single function template with an explicit `this` parameter replaces separate `const` and non-`const` overloads.

The syntax declares `this auto&& self` as the first parameter, making the implicit `this` pointer explicit and enabling type deduction.

## Why It Matters

Separate `const` and non-`const` overloads require duplicate function bodies or [CRTP](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern) patterns with additional template infrastructure.
An explicit `this` parameter removes this duplication and enables recursive lambdas and CRTP-based designs without auxiliary templates.

## Example

```cpp
#include <print>
#include <string>
#include <vector>

struct Widget {
    std::string name;

    // One function handles both const and non-const
    auto&& get_name(this auto&& self) {
        return std::forward_like<decltype(self)>(self.name);
    }

    // Recursive lambda now works naturally
    void traverse(this auto const& self, int indentation, auto&& fn) {
        fn(self, indentation);

        for (auto& child : self.children) {
            child.traverse(indentation + 1, fn);
        }
    }

    std::vector<Widget> children;
};

int main() {
    auto widget = Widget {
        .name = "SomeWidget",
        .children = {
            Widget { .name = "SomeChild1" },
            Widget {
                .name = "SomeChild2",
                .children = {
                    Widget { .name = "SomeChildChild" },
                },
            },
        },
    };

    std::println("Widget name: {}", widget.get_name());

    widget.traverse(0, [](const Widget& w, int indentation) {
        std::println("{}{}", std::string(indentation, ' '), w.get_name());
    });
}
```
