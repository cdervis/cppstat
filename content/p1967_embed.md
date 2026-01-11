This feature adds the `#embed` preprocessor directive that allows you to include
the contents of a file as a byte array (binary resource inclusion).

Example:

```
// Include the contents of my_image.png:
constexpr uint8_t my_image_data[] = {
    #embed "my_image.png"
};

// Example function that loads an image from memory:
Image load_image(std::span<const uint8_t> data);

// ...
auto image = load_image(my_image_data);
```

---

### Related pages:

- [GCC documentation](https://gcc.gnu.org/onlinedocs/cpp/Binary-Resource-Inclusion.html)
- [cppreference](https://en.cppreference.com/w/c/preprocessor/embed)
