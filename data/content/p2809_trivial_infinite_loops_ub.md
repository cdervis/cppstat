This feature forbids compilers to optimize out trivial infinite loops, i.e. infinite loops without
side effects.

Example (*from proposal*):

```
#include <iostream>

int main() {
    while (true)
        ;
}

void unreachable() {
    std::cout << "Hello world!" << std::endl;
}
```

This program prints `"Hello world!"`, because the optimizer detects the loop to be without side effects
and infinitely-running, and subsequently optimizing it out. This also optimizes out the `ret` instruction
(return statement of `main()`).

Therefore, the program continues to fall through into the instructions of `unreachable()`.

[Example on Compiler Explorer](https://godbolt.org/z/e3coW9cPE)


