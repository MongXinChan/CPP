
# Assert in C/C++

## 1. What is `assert`?
- `assert` is a macro defined in `<assert.h>` (C) or `<cassert>` (C++).
- It is used to check conditions during debugging.
- If the condition is **true**, `assert` does nothing.
- If the condition is **false**, `assert` outputs diagnostic information and calls `abort()` to terminate the program.

## 2. Implementation of `assert`
```c
#ifdef NDEBUG
# define assert(condition) ((void)0)  // No action if NDEBUG is defined
#else
# define assert(condition) /* implementation-defined */
#endif
```
- **`NDEBUG` Macro**: If `NDEBUG` is defined, `assert` is disabled and does nothing.
- **Usage**: `assert` is typically used only for debugging and can be removed by defining `NDEBUG` before releasing the program.

## 3. Example of Using `assert`
```c
#include <assert.h>
#include <stdio.h>

int main() {
    int x = 10;
    assert(x > 0);  // Condition is true, no action taken
    assert(x < 0);  // Condition is false, assert triggers

    return 0;
}
```
- **Output**: If the second `assert` fails, the program will print diagnostic information (e.g., file name, line number) and terminate.

## 4. Custom Assert Macros
- Many applications define their own `assert` macros to provide more specific behavior.
- Example from OpenCV:
```c
#define CV_Assert(expr) \
    do { \
        if (!(expr)) { \
            cv::error(cv::Error::StsAssert, #expr, CV_Func, __FILE__, __LINE__); \
        } \
    } while (0)
```
- **Behavior**: Checks a condition at runtime and throws an exception if it fails.
- **Advantages**: More flexible and can integrate with custom error handling mechanisms.

## 5. Benefits of Using `assert`
- **Debugging**: Helps catch logical errors early during development.
- **Documentation**: Acts as a form of documentation, indicating assumptions and invariants.
- **Safety**: Ensures that invalid states are not silently ignored.

## 6. Limitations of `assert`
- **Performance**: Can be disabled in release builds by defining `NDEBUG`.
- **Runtime Overhead**: Adds runtime checks, which may be undesirable in performance-critical code.
- **Not Suitable for Production**: Should not be used for error handling in production code.
