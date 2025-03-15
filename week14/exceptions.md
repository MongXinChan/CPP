
# Exception Handling in C++

## 1. Why Use Exceptions?
- Exceptions provide a way to handle errors and unexpected situations in a controlled manner.
- They allow the program to separate error handling code from normal execution logic, making the code cleaner and more maintainable.

## 2. Basic Concepts of Exceptions

### 2.1 Throwing Exceptions
- Use the `throw` statement to raise an exception.
- An exception can be any type (e.g., `int`, `char*`, `std::string`, custom objects).
- Example:
  ```cpp
  if (condition) {
      throw "Error message";
  }
  ```

### 2.2 Catching Exceptions
- Use a `try` block to enclose code that might throw an exception.
- Use `catch` blocks to handle specific exceptions.
- Example:
  ```cpp
  try {
      // Code that might throw an exception
  }
  catch (const char* msg) {
      // Handle char* exceptions
  }
  catch (int eid) {
      // Handle int exceptions
  }
  catch (...) {
      // Catch-all handler for any other exceptions
  }
  ```

### 2.3 Stack Unwinding
- If an exception is not handled in the current function, it propagates up the call stack until it is caught.
- If no `catch` block is found, the program terminates and calls `std::terminate()`.

## 3. Error Handling Strategies

### 3.1 Solution 1: Abort on Error
- Terminate the program immediately when an error occurs.
- Example:
  ```cpp
  float ratio(float a, float b) {
      if (fabs(a + b) < FLT_EPSILON) {
          std::cerr << "Error: Division by zero" << std::endl;
          std::abort();
      }
      return (a - b) / (a + b);
  }
  ```
- **Disadvantage**: Not user-friendly; no way to recover from the error.

### 3.2 Solution 2: Return Error Status
- Use return values or parameters to indicate errors.
- Example:
  ```cpp
  bool ratio(float a, float b, float& result) {
      if (fabs(a + b) < FLT_EPSILON) {
          std::cerr << "Error: Division by zero" << std::endl;
          return false;
      }
      result = (a - b) / (a + b);
      return true;
  }
  ```
- **Disadvantage**: Code becomes more complex; error handling logic is mixed with normal logic.

### 3.3 Solution 3: Throw Exceptions
- Use exceptions to handle errors in a more structured way.
- Example:
  ```cpp
  float ratio(float a, float b) {
      if (fabs(a + b) < FLT_EPSILON) {
          throw std::runtime_error("Error: Division by zero");
      }
      return (a - b) / (a + b);
  }

  try {
      float z = ratio(x, y);
      std::cout << z << std::endl;
  }
  catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
  }
  ```
- **Advantage**: Cleaner code; separates error handling from normal execution.

## 4. Exception Propagation
- If an exception is not handled in the current function, it propagates up the call stack.
- Example:
  ```cpp
  float ratio(float a, float b) {
      if (a < 0) throw 1;
      if (b < 0) throw 2;
      if (fabs(a + b) < FLT_EPSILON) throw "Error: Division by zero";
      return (a - b) / (a + b);
  }

  float ratio_wrapper(float a, float b) {
      try {
          return ratio(a, b);
      }
      catch (int eid) {
          std::cerr << "Caught integer exception: " << eid << std::endl;
          return 0;
      }
  }

  try {
      float z = ratio_wrapper(x, y);
  }
  catch (const char* msg) {
      std::cerr << msg << std::endl;
  }
  ```

## 5. Catch-All Handler
- Use a catch-all handler (`catch (...)`) to catch any type of exception.
- Example:
  ```cpp
  int main() {
      try {
          // Code that might throw an exception
      }
      catch (...) {
          std::cerr << "Unrecognized exception caught" << std::endl;
      }
      return 0;
  }
  ```
- **Note**: Catch-all handlers should be used sparingly to avoid masking unexpected errors.

## 6. Exceptions and Inheritance
- If an object is thrown, and its class is derived from another class, a base class handler can catch the exception.
- Example:
  ```cpp
  class Base {};
  class Derived : public Base {};

  try {
      throw Derived();
  }
  catch (const Base& base) {
      std::cerr << "Caught Base" << std::endl;
  }
  catch (const Derived& derived) {
      std::cerr << "Caught Derived" << std::endl;  // Never reached
  }
  ```

## 7. Standard Exceptions
- The C++ Standard Library provides a hierarchy of exception classes derived from `std::exception`.
- Example:
  ```cpp
  try {
      throw std::runtime_error("Runtime error occurred");
  }
  catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
  }
  ```

## 8. Exception Specifications and `noexcept`
- Exception specifications indicate whether a function can throw exceptions.
- `noexcept` indicates that a function will not throw any exceptions.
- Example:
  ```cpp
  void foo() noexcept {
      // This function is guaranteed not to throw exceptions
  }
  ```

## 9. `nothrow` New
- `std::nothrow` is used to allocate memory without throwing exceptions.
- Example:
  ```cpp
  int* p = new (std::nothrow) int[10];
  if (p == nullptr) {
      std::cerr << "Memory allocation failed" << std::endl;
  }
  ```
