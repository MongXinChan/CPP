
# More About Exceptions

## 1. Exception Propagation
- When an exception is thrown, it propagates up the call stack until it is caught by a matching `catch` block.
- If no matching `catch` block is found, the program terminates and calls `std::terminate()`.

### Example
```cpp
void func() {
    throw std::runtime_error("Error in func");
}

void wrapper() {
    func();  // Exception propagates from here
}

int main() {
    try {
        wrapper();
    }
    catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
```

## 2. Catching Exceptions by Reference
- It is recommended to catch exceptions by **const reference** to avoid slicing and improve performance.
- Catching by value can lead to slicing if the thrown object is of a derived class.

### Example
```cpp
class Base {};
class Derived : public Base {};

void throwDerived() {
    throw Derived();
}

int main() {
    try {
        throwDerived();
    }
    catch (const Base& e) {  // Catch by const reference
        std::cerr << "Caught Base" << std::endl;
    }
    return 0;
}
```

## 3. Catch-All Handler
- A catch-all handler (`catch (...)`) can catch any type of exception.
- It is useful for handling unexpected exceptions, but should be used cautiously to avoid hiding bugs.

### Example
```cpp
int main() {
    try {
        // Code that might throw an exception
        throw 42;
    }
    catch (...) {
        std::cerr << "Caught an unexpected exception" << std::endl;
    }
    return 0;
}
```

## 4. Re-throwing Exceptions
- You can re-throw an exception to propagate it further up the call stack.
- Use `throw;` without an argument to re-throw the current exception.

### Example
```cpp
void func() {
    try {
        throw std::runtime_error("Error in func");
    }
    catch (const std::exception& e) {
        std::cerr << "Caught in func: " << e.what() << std::endl;
        throw;  // Re-throw the exception
    }
}

int main() {
    try {
        func();
    }
    catch (const std::exception& e) {
        std::cerr << "Caught in main: " << e.what() << std::endl;
    }
    return 0;
}
```

## 5. Exception Safety
- **Strong Exception Safety**: Operations either complete successfully or leave the program in a consistent state (e.g., using RAII).
- **Basic Exception Safety**: Operations leave the program in a valid state, but changes may not be fully applied.
- **No Exception Safety**: Operations may leave the program in an inconsistent state.

### Example of Strong Exception Safety
```cpp
class Resource {
public:
    Resource() { std::cout << "Resource acquired" << std::endl; }
    ~Resource() { std::cout << "Resource released" << std::endl; }
};

void test() {
    Resource r;
    throw std::runtime_error("Exception thrown");
}

int main() {
    try {
        test();
    }
    catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
```

## 6. Exception Specifications (Deprecated)
- In C++11 and later, exception specifications using `throw()` are deprecated.
- Use `noexcept` instead to indicate that a function will not throw exceptions.

### Example
```cpp
void safeFunction() noexcept {
    // This function will not throw exceptions
}
```

## 7. `std::exception` and Custom Exceptions
- `std::exception` is the base class for standard exceptions.
- You can derive custom exception classes from `std::exception` or other standard exceptions.

### Example
```cpp
class MyException : public std::exception {
public:
    const char* what() const noexcept override {
        return "My custom exception";
    }
};

void throwMyException() {
    throw MyException();
}

int main() {
    try {
        throwMyException();
    }
    catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
```

## 8. `std::terminate` and `std::unexpected`
- `std::terminate()` is called if:
  - An exception is thrown but not caught.
  - An exception is thrown during stack unwinding (e.g., from a destructor).
- `std::unexpected()` is called if an exception is thrown that does not match any catch block (deprecated in C++11).

### Example
```cpp
void func() {
    throw std::runtime_error("Error in func");
}

int main() {
    try {
        func();
    }
    catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
```

## 9. Exception Handling Best Practices
- **Use Specific Catch Blocks**: Catch specific exceptions first, then use catch-all handlers if necessary.
- **Avoid Catching by Value**: Catch exceptions by const reference to avoid slicing.
- **Use `noexcept` for Performance-Critical Code**: Indicate that functions will not throw exceptions.
- **Provide Meaningful Error Messages**: Override `what()` in custom exceptions to provide useful information.
