# 模板函数和模板类的特殊化
在C++中，模板函数和模板类的特殊化是模板编程中的重要概念。它们允许程序员为特定的类型或参数组合提供专门的实现，而不是使用模板的一般形式。以下是关于模板函数和模板类特殊化的详细说明，包括它们的定义、语法、示例和区别。

[click here go to the specialization[EN]](./specialization.md)
---

## 1. 模板函数的特殊化

### 定义
模板函数的特殊化是指为模板函数的某个特定类型或参数组合提供一个专门的实现。当模板的一般实现不适用于某些类型时，可以使用特殊化来提供定制的实现。

### 语法
```cpp
template <>
返回类型 函数名<特定类型>(参数列表) {
    // 特殊化的实现
}
```

### 示例
假设我们有一个模板函数用于打印值：
```cpp
template <typename T>
void print(T value) {
    std::cout << value << std::endl;
}
```
现在，我们希望为`std::vector<int>`类型提供一个特殊的实现，打印其所有元素：
```cpp
#include <iostream>
#include <vector>

template <typename T>
void print(T value) {
    std::cout << value << std::endl;
}

// 函数特殊化
template <>
void print<std::vector<int>>(const std::vector<int>& value) {
    for (int v : value) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

int main() {
    int a = 42;
    print(a);  // 调用模板函数的普通版本

    std::vector<int> vec = {1, 2, 3, 4, 5};
    print(vec);  // 调用函数特殊化版本
    return 0;
}
```
**输出结果：**
```
42
1 2 3 4 5
```

### 特点
1. **显式特化**：函数特殊化是显式地为某个特定类型提供实现，而不是通过模板参数推导。
2. **优先级最高**：当模板函数有普通版本、特殊化版本和重载版本时，特殊化版本的优先级最高。
3. **不能重载**：函数特殊化不是函数重载，它必须完全匹配模板参数。

---

## 2. 模板类的特殊化

### 定义
模板类的特殊化是指为模板类的某个特定类型或参数组合提供一个专门的实现。与模板函数类似，模板类的特殊化允许程序员为某些类型提供定制的行为。

### 语法
模板类的特殊化分为**全特化**和**偏特化**：

#### 全特化（Full Specialization）
```cpp
template <>
class 类名<特定类型> {
    // 特殊化的成员变量和成员函数
};
```

#### 偏特化（Partial Specialization）
```cpp
template <typename T, typename U>
class 类名<T, U> {
    // 原始模板定义
};

template <typename T>
class 类名<T, int> {
    // 偏特化版本
};
```

### 示例

#### 全特化示例
假设我们有一个模板类用于存储和打印值：
```cpp
template <typename T>
class Print {
public:
    void print(T value) {
        std::cout << value << std::endl;
    }
};
```
现在，我们希望为`std::string`类型提供一个特殊的实现，打印时加上引号：
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

// 全特化
template <>
class Print<std::string> {
public:
    void print(const std::string& value) {
        std::cout << "\"" << value << "\"" << std::endl;
    }
};

int main() {
    Print<int> p1;
    p1.print(42);  // 调用普通模板类

    Print<std::string> p2;
    p2.print("Hello, World!");  // 调用全特化版本
    return 0;
}
```
**输出结果：**
```
42
"Hello, World!"
```

#### 偏特化示例
假设我们有一个模板类用于存储两个值，现在希望为第二个参数为`int`时提供特殊实现：
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

// 偏特化
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
    p1.print();  // 调用普通模板类

    Pair<std::string, int> p2{"World", 42};
    p2.print();  // 调用偏特化版本
    return 0;
}
```
**输出结果：**
```
Hello, 3.14
World (int) 42
```

### 特点
1. **全特化**：为特定的完整类型组合提供完全定制的实现。
2. **偏特化**：为某些类型的子集提供定制的实现。
3. **优先级**：全特化和偏特化的优先级高于原始模板类。
4. **灵活性**：模板类的特殊化允许对类的成员变量和成员函数进行完全定制。

---

## 3. 模板函数与模板类特殊化的区别

### 1. **作用对象**
- **模板函数特殊化**：针对函数模板，为特定类型提供专门的函数实现。
- **模板类特殊化**：针对类模板，为特定类型提供专门的类实现。

### 2. **语法**
- **模板函数特殊化**：
  ```cpp
  template <>
  返回类型 函数名<特定类型>(参数列表);
  ```
- **模板类特殊化**：
  - **全特化**：
    ```cpp
    template <>
    class 类名<特定类型>;
    ```
  - **偏特化**：
    ```cpp
    template <typename T>
    class 类名<T, 特定类型>;
    ```

### 3. **适用场景**
- **模板函数特殊化**：适用于需要为特定类型提供特殊行为的函数。
- **模板类特殊化**：
  - **全特化**：适用于需要为特定类型组合提供完全不同的实现。
  - **偏特化**：适用于需要为某些类型的子集提供定制实现。

### 4. **灵活性**
- **模板函数特殊化**：只能定制函数的行为。
- **模板类特殊化**：可以定制类的成员变量和成员函数，灵活性更高。

---

## 4. 总结

模板函数和模板类的特殊化是C++模板机制中的重要特性，它们允许程序员为特定类型提供定制的实现。以下是它们的主要区别和适用场景：

| 特性               | 模板函数特殊化                          | 模板类特殊化                          |
|--------------------|----------------------------------------|---------------------------------------|
| **作用对象**       | 函数模板                                | 类模板                                |
| **语法**           | `template <> 返回类型 函数名<类型>()`   | 全特化：`template <> 类名<类型>`<br>偏特化：`template <typename T> 类名<T, 特定类型>` |
| **适用场景**       | 为特定类型提供特殊函数行为              | 为特定类型提供特殊类行为              |
| **灵活性**         | 只能定制函数行为                        | 可以定制类的成员变量和成员函数        |
| **优先级**         | 特殊化版本优先级最高                    | 特殊化版本优先级最高                  |

模板函数和模板类的特殊化在模板编程中非常有用，尤其是在需要处理特殊情况或优化性能时。合理使用它们可以提高代码的灵活性和效率，但同时也需要注意避免过度复杂化代码结构。

