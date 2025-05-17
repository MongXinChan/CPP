---
title: CS205 Lab
published: 2025-04-27
updated: 2025-04-28
description: ''
image: ''
tags: [ComputerScience,ProgramDesign,Cpp,Ubuntu,Linux ]
category: 'ComputerScience-En'
draft: false 
lang: en
---

> [!TIP]
>
> Welcome to my CS205 lecture notes! Because the lecture is not in English, I will try my best to translate it.
>
> And at the same time, the `PPT`,`lab-file` also use the English,I will write **the English notes but not all.**

>[!NOTE]
>
>If you have a passion to konw more about the course, you can click the link below to learn more about the course.
>Read the repo.
>
>::github{repo="MongxinChan/CPP"}

> [!IMPORTANT]
>
> 由于本文篇幅过长，个人会添加适当的中文注解在里面。

## **主题概览 (Topic Overview)**

- ***\*类继承 (Class Inheritance)\****:
    - 继承的基本语法和概念 (Basic syntax and concepts of inheritance)
    - `is-a` 关系 (`is-a` relationship)
    - 构造函数和析构函数的调用顺序 (Order of constructor and destructor calls)
    - 访问控制与继承 (Access control and inheritance) (`public`, `protected`, `private`)
- ***\*多态性 (Polymorphism)\****:
    - 静态绑定与动态绑定 (Static binding vs. Dynamic binding)
    - 虚函数 (Virtual functions)
    - 纯虚函数与抽象基类 (Pure virtual functions and abstract base classes)
- ***\*继承中的析构函数 (Destructors in Inheritance)\****:
    - 虚析构函数的重要性 (Importance of virtual destructors)
- ***\*继承与动态内存分配 (Inheritance and Dynamic Memory Allocation)\****:
    - 当基类和/或派生类使用动态内存时如何正确管理资源 (Proper resource management when base and/or derived classes use dynamic memory)
- ***\*实验练习 (Exercises)\****

## **壹只半解 (前言)**

欢迎来到实验十二的学习笔记！本实验将深入探讨面向对象编程的两个核心概念：继承和多态性。我们将学习如何通过继承来创建类层次结构，实现代码重用，并理解不同继承方式下的访问权限。更重要的是，我们将探索多态性如何通过虚函数实现，从而允许我们以统一的方式处理不同派生类的对象。此外，我们还将讨论在继承体系中正确管理动态内存和使用虚析构函数的重要性。

***\*重要提示：\**** 本手册力求模仿 `index.pdf` 的风格。幻灯片中的图片在本 Markdown 版本中将以文字描述替代。

## **一、类继承 (Class Inheritance)**

继承是面向对象编程中的一种机制，它允许一个类（称为派生类或子类）获取另一个类（称为基类或父类）的属性和方法。

### **1.1 继承的基本语法**

在C++中，继承的语法如下：

```
class DerivedClassName : access-specifier BaseClassName {
    // 派生类成员
};
```

- `DerivedClassName` 是派生类的名称。
- `BaseClassName` 是基类的名称。
- `access-specifier` (访问修饰符)可以是 `public`, `protected`, 或 `private`。它决定了基类成员在派生类中的访问级别。
    - **`public` \**继承\****: 基类的 `public` 成员在派生类中仍然是 `public`，`protected` 成员在派生类中仍然是 `protected`。这是最常用的继承方式，它建立了 "is-a"（是一种）关系。
    - **`protected` \**继承\****: 基类的 `public` 和 `protected` 成员在派生类中都变成 `protected`。
    - **`private` \**继承\****: 基类的 `public` 和 `protected` 成员在派生类中都变成 `private`。这通常表示 "is-implemented-in-terms-of"（依据...来实现）关系。

```
[Image of 类继承语法图示]
```

### **1.2** `is-a` **关系 (The** `is-a` **Relationship)**

公有继承 (`public` inheritance) 建立了 "is-a" 关系。这意味着派生类的对象也是基类的一个对象。例如，如果 `Student` 类公有继承自 `Person` 类，那么一个 `Student` 对象 **is a** `Person` 对象。这允许我们将派生类对象当做基类对象来使用，这是多态性的基础。

### **1.3 构造函数和析构函数的调用顺序**

当创建派生类对象时：

1. 首先调用基类的构造函数，初始化派生类对象中的基类部分。
2. 然后调用派生类的构造函数，初始化派生类自己定义的成员。

当销毁派生类对象时，顺序相反：

1. 首先调用派生类的析构函数。
2. 然后调用基类的析构函数。

***\*注意\****：

- 派生类的构造函数可以通过其成员初始化列表显式地调用基类的特定构造函数。如果不显式调用，基类的默认构造函数将被调用。
- 析构函数的调用是自动的，不能在派生类析构函数中显式调用基类析构函数。

```
[Image of 构造函数和析构函数调用顺序示例代码输出]
```

### **1.4 访问控制与继承**

下表总结了不同继承方式下基类成员在派生类中的访问权限：

| **基类成员访问权限** | **public 继承后在派生类中的权限** | **protected 继承后在派生类中的权限** | **private 继承后在派生类中的权限** |
| -------------------- | --------------------------------- | ------------------------------------ | ---------------------------------- |
| `public`             | `public`                          | `protected`                          | `private`                          |
| `protected`          | `protected`                       | `protected`                          | `private`                          |
| `private`            | 在派生类中不可直接访问            | 在派生类中不可直接访问               | 在派生类中不可直接访问             |

- 基类的 `private` 成员永远不能被派生类直接访问，无论采用何种继承方式。派生类只能通过基类的 `public` 或 `protected` 接口（如果提供）间接访问基类的私有成员。

## **二、多态性 (Polymorphism)**

多态性（Polymorphism，源于希腊语，意为“多种形态”）是面向对象编程的核心特性之一。它允许我们以统一的方式处理不同类型的对象。在C++中，多态性主要通过虚函数和动态绑定来实现。

### **2.1 静态绑定与动态绑定 (Static Binding vs. Dynamic Binding)**

- ***\*静态绑定 (Static Binding / Early Binding)\****: 函数调用在编译时确定。对于非虚函数调用以及通过对象（而不是指针或引用）进行的虚函数调用，使用的是静态绑定。编译器根据调用表达式的静态类型（变量声明的类型）来决定调用哪个函数。
- ***\*动态绑定 (Dynamic Binding / Late Binding)\****: 函数调用在运行时确定。当通过基类指针或引用调用虚函数时，使用的是动态绑定。程序会根据指针或引用实际指向的对象的动态类型（对象的实际类型）来决定调用哪个版本的虚函数。

### **2.2 虚函数 (Virtual Functions)**

通过在基类中将成员函数声明为 `virtual`，可以使其在派生类中被重定义 (override)，并允许通过基类指针或引用实现动态绑定。

- ***\*声明\****: 在基类函数声明前加上 `virtual` 关键字。

    ```
    class Base {
    public:
        virtual void show() { /* 基类实现 */ }
        // ...
    };
    ```

- ***\*重定义 (Overriding)\****: 派生类可以提供一个与基类虚函数具有相同签名（名称、参数列表和 `const` 修饰符）的函数。在C++11及以后版本，建议在派生类重定义的函数后加上 `override` 关键字，以帮助编译器检查签名是否匹配。

    ```
    class Derived : public Base {
    public:
        void show() override { /* 派生类特定实现 */ }
        // ...
    };
    ```

- ***\*工作原理\****: 当通过基类指针或引用调用虚函数时，程序会查找该指针/引用实际指向的对象的类型，并调用该类型对应的虚函数版本。这是通过虚函数表（vtable）机制实现的。

```
[Image of Employee 和 SalariedEmployee 类使用虚函数 show() 的示例代码和多态调用结果]
```

### **2.3 纯虚函数与抽象基类 (Pure Virtual Functions and Abstract Base Classes)**

- ***\*纯虚函数 (Pure Virtual Function)\****: 是一个在基类中声明但没有定义的虚函数。它告诉编译器该函数必须在派生类中被实现。纯虚函数的声明方式是在函数声明末尾加上 `= 0`。

    ```
    class Shape {
    public:
        virtual double area() const = 0; // 纯虚函数
        virtual ~Shape() {} // 抽象类也应该有虚析构函数
    };
    ```

- ***\*抽象基类 (Abstract Base Class - ABC)\****: 包含至少一个纯虚函数的类称为抽象基类。抽象基类不能被实例化（即不能创建其对象）。它主要用作接口，定义派生类必须实现的功能。派生类如果未能实现基类中的所有纯虚函数，那么它本身也将成为抽象类。

## **三、继承中的析构函数 (Destructors in Inheritance)**

### **3.1 虚析构函数的重要性 (Importance of Virtual Destructors)**

当通过基类指针删除一个派生类对象时，如果基类的析构函数不是虚函数，则只会调用基类的析构函数，派生类的析构函数不会被调用。这会导致派生类中分配的资源（如动态内存）无法被正确释放，从而引发资源泄漏。

***\*规则\****: 如果一个类可能作为基类，并且其实例可能通过基类指针被删除，那么它的析构函数***\*应该\****声明为 `virtual`。

```cpp
class Base {
public:
    Base() { /* ... */ }
    virtual ~Base() { /* 基类清理 */ } // 虚析构函数
};

class Derived : public Base {
private:
    int* data;
public:
    Derived() { data = new int[10]; /* ... */ }
    ~Derived() override { delete[] data; /* 派生类清理 */ } // 析构函数也会被调用
};

// Base* ptr = new Derived();
// delete ptr; // 正确调用 Derived::~Derived() 然后 Base::~Base()
```

```[Image of 基类析构函数非虚与虚函数情况下，delete 基类指针指向的派生类对象的行为对比]`

---

## 四、继承与动态内存分配 (Inheritance and Dynamic Memory Allocation)
当基类或派生类（或两者都）使用动态内存分配时，需要特别注意拷贝控制成员（拷贝构造函数、拷贝赋值运算符）和析构函数的正确实现。
* **如果派生类不使用动态内存分配**:
    * 通常不需要为派生类显式定义拷贝控制成员和析构函数，编译器生成的版本会正确调用基类的相应版本。
* **如果派生类也使用动态内存分配**:
    * 派生类**必须**显式定义自己的析构函数、拷贝构造函数和拷贝赋值运算符。
    * **派生类的析构函数**: 负责清理派生类自己分配的资源。它会自动调用基类的析构函数。
    * **派生类的拷贝构造函数**:
        * 必须显式调用基类的拷贝构造函数来处理基类部分的拷贝（通过成员初始化列表）。
        * 然后负责深拷贝派生类自己定义的动态分配的成员。
    * **派生类的拷贝赋值运算符**:
        * 必须显式调用基类的拷贝赋值运算符来处理基类部分的赋值。
        * 需要处理自赋值。
        * 释放派生类当前持有的动态资源。
        * 然后负责深拷贝派生类自己定义的动态分配的成员。

`[Image of Parent 和 Child 类均使用动态内存分配的拷贝构造函数和赋值运算符实现示例]`

---

## 五、实验练习 (Exercises)

### 练习 1
指出以下代码中的错误，并向助教解释原因。
```cpp
// 幻灯片中的代码
class Base {
private:
    int x;
protected:
    int y;
public:
    int z;
    void funBase(Base& b) {
        ++x; ++y; ++z;
        ++b.x; ++b.y; ++b.z; // Base对象可以访问另一个Base对象的私有和保护成员
    }
};

class Derived : public Base {
public:
    void funDerived(Base& b, Derived& d) {
        // ++x;       // 错误: x 在 Base 中是 private
        ++y;       // 正确: y 在 Base 中是 protected, Derived 是子类
        ++z;       // 正确: z 在 Base 中是 public
        // ++b.x;     // 错误: 不能访问任意 Base 对象 b 的私有成员 x
        // ++b.y;     // 错误: 不能访问任意 Base 对象 b 的保护成员 y (除非 Derived 是 b 的友元)
        ++b.z;     // 正确: 可以访问任意 Base 对象 b 的公有成员 z
        // ++d.x;     // 错误: x 在 Base 中是 private
        ++d.y;     // 正确: d 是 Derived 对象,可以访问其继承的 protected 成员 y
        ++d.z;     // 正确: d 是 Derived 对象,可以访问其继承的 public 成员 z
    }
};

void fun(Base& b, Derived& d) {
    // ++x; ++y; ++z; // 错误: 非成员函数不能直接访问任何类的成员
    // ++b.x; ++b.y;   // 错误: 不能访问 Base 对象 b 的私有或保护成员
    ++b.z;           // 正确
    // ++d.x; ++d.y;   // 错误: 不能访问 Derived 对象 d 的私有或保护成员 (x 是 Base 的 private, y 是 Base 的 protected)
    ++d.z;           // 正确
}
```

```[Image of 练习1的C++代码，包含访问控制问题]`

**解答提示**:
* 仔细分析每个 `++` 操作尝试访问的成员以及访问上下文（是在基类成员函数、派生类成员函数还是全局函数中）。
* 回顾 `private`, `protected`, `public` 成员的访问规则，以及它们在继承后的访问权限变化。
* 一个类的成员函数可以访问该类*任何*对象的私有和保护成员，而不仅仅是调用该函数的对象 (`this` 所指向的对象)。

### 练习 2
运行以下程序，并向助教解释结果。
```cpp
#include <iostream>
// using namespace std; // 避免在全局作用域使用

class Polygon {
protected:
    int width, height;
public:
    void set_values(int a, int b) {
        width = a; height = b;
    }
    // 非虚函数
    int area() {
        return 0;
    }
};

class Rectangle : public Polygon {
public:
    int area() { // 隐藏了基类的 area()
        return width * height;
    }
};

class Triangle : public Polygon {
public:
    int area() { // 隐藏了基类的 area()
        return width * height / 2;
    }
};

int main() {
    Rectangle rect;
    Triangle trgl;
    Polygon* ppoly1 = &rect;
    Polygon* ppoly2 = &trgl;

    ppoly1->set_values(4, 5);
    ppoly2->set_values(2, 5);

    std::cout << rect.area() << std::endl;   // 调用 Rectangle::area()
    std::cout << trgl.area() << std::endl;   // 调用 Triangle::area()
    std::cout << ppoly1->area() << std::endl; // 调用 Polygon::area() 因为 area() 非虚
    std::cout << ppoly2->area() << std::endl; // 调用 Polygon::area() 因为 area() 非虚
    return 0;
}

```

```[Image of 练习2的C++代码，演示未使用虚函数的情况]```

**解答提示**:
* 由于 `Polygon::area()` 不是虚函数，通过基类指针 `ppoly1` 和 `ppoly2` 调用 `area()` 将始终调用 `Polygon` 类中定义的版本（静态绑定）。
* 直接通过 `rect` 和 `trgl` 对象调用 `area()` 则会调用各自类中定义的版本。
* 思考如何修改代码以实现多态行为（即让 `ppoly1->area()` 调用 `Rectangle::area()`）。

### 练习 3
运行以下程序，并向助教解释结果。程序中是否存在任何问题？
```cpp
// dynamic allocation and polymorphism
#include <iostream>
// using namespace std;

class Polygon {
protected:
    int width, height;
public:
    Polygon(int a, int b) : width(a), height(b) {}
    virtual int area(void) = 0; // 纯虚函数
    void printarea() {
        std::cout << this->area() << '\n'; // this-> 可选
    }
    // 缺少虚析构函数!
};

class Rectangle : public Polygon {
public:
    Rectangle(int a, int b) : Polygon(a, b) {}
    int area(void) override { // C++11: 使用 override
        return width * height;
    }
};

class Triangle : public Polygon {
public:
    Triangle(int a, int b) : Polygon(a, b) {}
    int area(void) override { // C++11: 使用 override
        return width * height / 2;
    }
};

int main() {
    Polygon* ppoly1 = new Rectangle(4, 5); // 指针变量名修改以避免与后续重用冲突
    ppoly1->printarea();
    delete ppoly1; // 问题点1：如果析构函数非虚，可能导致资源泄漏

    Polygon* ppoly2 = new Triangle(2, 5);
    ppoly2->printarea();
    delete ppoly2; // 问题点2：同上

    return 0;
}

```

```[Image of 练习3的C++代码，包含纯虚函数和动态分配]```

**解答提示**:
* `Polygon` 是一个抽象基类，因为它包含纯虚函数 `area()`。不能创建 `Polygon` 类型的对象。
* `printarea()` 函数通过 `this->area()` 调用，由于 `area()` 是虚函数，这里会发生动态绑定，正确调用派生类的 `area()` 实现。
* **潜在问题**: `Polygon` 类没有声明虚析构函数。当执行 `delete ppoly1;` 和 `delete ppoly2;` 时，如果 `Polygon::~Polygon()` 不是虚函数，则只会调用基类的析构函数，而派生类 `Rectangle` 和 `Triangle` 的析构函数（即使是默认生成的）可能不会被调用。如果派生类在其析构函数中有重要的清理工作（例如释放动态分配的资源），这将导致资源泄漏。
* **修正**: 应为 `Polygon` 类添加一个虚析构函数：`virtual ~Polygon() {}`。

---
*CC BY NC SA (内容改编自课程材料)*
