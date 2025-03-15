# Specialization

[点击这里跳转到中文版本](./specialization_cn.md)
---

## 1. Function Template Specialization

### Definition
Function template specialization refers to providing a specific implementation for a function template for a particular type or set of types. It allows you to customize the behavior of a function template for specific cases where the general implementation may not be suitable.

### Syntax
```cpp
template <>
return_type function_name<specific_type>(parameter_list) {
    // Specialized implementation
}
```

### Example
Suppose we have a function template for printing values:
```cpp
template <typename T>
void print(T value) {
    std::cout << value << std::endl;
}
```
Now, let's provide a specialized implementation for `std::vector<int>` to print all elements:
```cpp
#include <iostream>
#include <vector>

template <typename T>
void print(T value) {
    std::cout << value << std::endl;
}

// Function template specialization
template <>
void print<std::vector<int>>(const std::vector<int>& value) {
    for (int v : value) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

int main() {
    int a = 42;
    print(a);  // Calls the general template function

    std::vector<int> vec = {1, 2, 3, 4, 5};
    print(vec);  // Calls the specialized function
    return 0;
}
```
**Output:**
```
42
1 2 3 4 5
```

### Characteristics
1. **Explicit Specialization**: Function template specialization is explicitly provided for a specific type.
2. **Highest Priority**: When multiple versions exist (general template, specialization, and overloads), the specialized version has the highest priority.
3. **Not Overloading**: Specialization is not function overloading; it must match the template parameters exactly.

---

## 2. Class Template Specialization

### Definition
Class template specialization allows you to provide a specific implementation for a class template for a particular type or set of types. This is useful for customizing the behavior of a class template for specific cases.

### Syntax
Class template specialization can be divided into **full specialization** and **partial specialization**:

#### Full Specialization
```cpp
template <>
class Class_name<specific_type> {
    // Specialized member variables and functions
};
```

#### Partial Specialization
```cpp
template <typename T, typename U>
class Class_name<T, U> {
    // Original template definition
};

template <typename T>
class Class_name<T, int> {
    // Partially specialized version
};
```

### Example

#### Full Specialization Example
Suppose we have a class template for printing values:
```cpp
template <typename T>
class Print {
public:
    void print(T value) {
        std::cout << value << std::endl;
    }
};
```
Now, let's provide a specialized implementation for `std::string` to print the value with quotes:
```cpp
#include <iostream>
#include <string>

template <typename T>
class Print {
public:
    void print(T value) {
        std::cout << value << std::endl;
    }
};

// Full specialization
template <>
class Print<std::string> {
public:
    void print(const std::string& value) {
        std::cout << "\"" << value << "\"" << std::endl;
    }
};

int main() {
    Print<int> p1;
    p1.print(42);  // Calls the general template class

    Print<std::string> p2;
    p2.print("Hello, World!");  // Calls the fully specialized version
    return 0;
}
```
**Output:**
```
42
"Hello, World!"
```

#### Partial Specialization Example
Suppose we have a class template for storing two values, and we want to provide a specialized implementation when the second parameter is `int`:
```cpp
#include <iostream>
#include <string>

template <typename T, typename U>
class Pair {
public:
    T first;
    U second;

    void print() {
        std::cout << first << ", " << second << std::endl;
    }
};

// Partial specialization
template <typename T>
class Pair<T, int> {
public:
    T first;
    int second;

    void print() {
        std::cout << first << " (int) " << second << std::endl;
    }
};

int main() {
    Pair<std::string, double> p1{"Hello", 3.14};
    p1.print();  // Calls the general template class

    Pair<std::string, int> p2{"World", 42};
    p2.print();  // Calls the partially specialized version
    return 0;
}
```
**Output:**
```
Hello, 3.14
World (int) 42
```

### Characteristics
1. **Full Specialization**: Provides a completely customized implementation for a specific type combination.
2. **Partial Specialization**: Provides a customized implementation for a subset of types.
3. **Priority**: Both full and partial specializations have higher priority than the original template class.
4. **Flexibility**: Class template specialization allows you to customize both member variables and member functions.

---

## 3. Differences Between Function Template Specialization and Class Template Specialization

### 1. **Target**
- **Function Template Specialization**: Targets function templates to provide specialized function implementations.
- **Class Template Specialization**: Targets class templates to provide specialized class implementations.

### 2. **Syntax**
- **Function Template Specialization**:
  ```cpp
  template <>
  return_type function_name<specific_type>(parameter_list);
  ```
- **Class Template Specialization**:
  - **Full Specialization**:
    ```cpp
    template <>
    class Class_name<specific_type>;
    ```
  - **Partial Specialization**:
    ```cpp
    template <typename T>
    class Class_name<T, specific_type>;
    ```

### 3. **Use Cases**
- **Function Template Specialization**: Used when you need to customize the behavior of a function for specific types.
- **Class Template Specialization**:
  - **Full Specialization**: Used when you need to provide a completely different implementation for a specific type combination.
  - **Partial Specialization**: Used when you need to customize the implementation for a subset of types.

### 4. **Flexibility**
- **Function Template Specialization**: Only allows customization of function behavior.
- **Class Template Specialization**: Allows customization of both member variables and member functions, offering greater flexibility.

---

## 4. Summary

Function and class template specialization are powerful features in C++ that allow you to provide customized implementations for specific types. Here are the main differences and use cases:

| Feature                | Function Template Specialization                     | Class Template Specialization                     |
|------------------------|------------------------------------------------------|--------------------------------------------------|
| **Target**             | Function templates                                   | Class templates                                   |
| **Syntax**             | `template <> return_type function_name<type>()`      | Full: `template <> Class_name<type>`<br>Partial: `template <typename T> Class_name<T, specific_type>` |
| **Use Cases**          | Customizing function behavior for specific types     | Customizing class behavior for specific types     |
| **Flexibility**        | Only function behavior                               | Both member variables and functions               |
| **Priority**           | Specialized versions have the highest priority       | Specialized versions have the highest priority    |

Function and class template specialization are very useful in template programming, especially when dealing with special cases or optimizing performance. Using them wisely can enhance the flexibility and efficiency of your code, but it is important to avoid over-complicating the code structure.

