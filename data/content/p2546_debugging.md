This feature allows you to perform operations that target the debugger, such as triggering
a break point programmatically.

Three new functions are added to the standard library.

- `std::is_debugger_present() -> bool`
    - Allows you to detect whether the program is running in a debugger.

- `std::breakpoint()`
    - Triggers a breakpoint in the program, which results in the debugger pausing the program's execution.

- `std::breakpoint_if_debugging()`
    - Same as `std::breakpoint()` when the program is running in a debugger; otherwise a no-op.

---

### Related libraries:

- [scottt/debugbreak (GitHub)](https://github.com/scottt/debugbreak)
- [grafikrobot/debugging (GitHub)](https://github.com/grafikrobot/debugging)
