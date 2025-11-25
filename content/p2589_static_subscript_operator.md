This feature allows you to define `static` subscript operators, which makes it possible to
index into a type instead of an object.

Example:

```
struct Test {
    static int operator[](int i) {
        return i * 2;
    }
    
    // Multidimensional indexing is possible as well.
    static int operator[](float f1, float f2) {
        return f1 * f2;
    }
};

// ...

auto result  = Test::operator[](10);         // = 20
auto result2 = Test::operator[](2.0f, 3.0f); // = 6
```
