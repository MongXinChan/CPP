---
title: CS205 Lab12 Class Inheritance & Polymorphism
description: ''
published: 2025-05-27
updated: 2025-06-01
description: '本实验将深入探讨面向对象编程的两个核心概念：继承和多态性。我们将学习如何通过继承来创建类层次结构，实现代码重用，并理解不同继承方式下的访问权限。更重要的是，我们将探索多态性如何通过虚函数实现，从而允许我们以统一的方式处理不同派生类的对象。此外，我们还将讨论在继承体系中正确管理动态内存和使用虚析构函数的重要性。'
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
>::github{repo="MongxinChan/cpp"}

> [!IMPORTANT]
>
> 由于本文篇幅过长，个人会添加适当的中文注解在里面。

## Topic Overview

- **Class Inheritance**:
    - Basic syntax and concepts of inheritance
    - `is-a` relationship
    - Order of constructor and destructor calls
    - Access control and inheritance (`public`, `protected`, `private`)
- **Polymorphism**:
    - Static binding vs. Dynamic binding
    - Virtual functions
    - Pure virtual functions and abstract base classes
- **Destructors in Inheritance**:
    - Importance of virtual destructors
- **Inheritance and Dynamic Memory Allocation**:
    - Proper resource management when base and/or derived classes use dynamic memory
- **Exercises**

## Foreword

Welcome to the Lab 12 study notes! This lab delves into two core concepts of object-oriented programming: inheritance and polymorphism. 

We will learn how to create class hierarchies through inheritance to achieve code reuse and understand access permissions under different inheritance types. 

More importantly, we will explore how polymorphism is achieved through virtual functions, allowing us to treat objects of different derived classes in a uniform manner. 

Additionally, we will discuss the importance of correctly managing dynamic memory and using virtual destructors in an inheritance hierarchy.

#  Class Inheritance

Inheritance is a mechanism in object-oriented programming that allows a class (called a derived class or subclass) to acquire the properties and methods of another class (called a base class or parent class).

## 1.1 Basic Syntax of Inheritance

In C++, the syntax for inheritance is as follows:

```cpp
class DerivedClassName : access-specifier BaseClassName {
    // Derived class members
};
```

- `DerivedClassName` is the name of the derived class.
- `BaseClassName` is the name of the base class.
- `access-specifier` can be `public`, `protected`, or `private`. It determines the access level of the base class members in the derived class.
    - **`public` inheritance**: Public members of the base class remain `public` in the derived class, and `protected` members remain `protected`. This is the most common type of inheritance and establishes an "is-a" relationship.
    - **`protected` inheritance**: Public and `protected` members of the base class become `protected` in the derived class.
    - **`private` inheritance**: Public and `protected` members of the base class become `private` in the derived class. This usually represents an "is-implemented-in-terms-of" relationship.

![image-20250601221626055](./images/image-20250601221626055.png)

## 1.2 The `is-a` Relationship

Public inheritance establishes an "is-a" relationship. This means an object of the derived class is also an object of its base class. For example, if a `Student` class publicly inherits from a `Person` class, then a `Student` object *is a* `Person` object. This allows us to treat derived class objects as base class objects, which is fundamental to polymorphism.

![image-20250601221710553](./images/image-20250601221710553.png)

## 1.3 Order of Constructor and Destructor Calls

When a derived class object is created:

1. The base class's constructor is called first to initialize the base class part of the derived class object.
2. Then, the derived class's constructor is called to initialize the members defined in the derived class itself.

When a derived class object is destroyed, the order is reversed:

1. The derived class's destructor is called first.
2. Then, the base class's destructor is called.

> [!NOTE]
>
> A derived class constructor can explicitly call a specific base class constructor using its member initializer list. If not explicitly called, the base class's default constructor will be invoked.
>
> Destructor calls are automatic; you cannot explicitly call a base class destructor in a derived class destructor.

![image-20250601215359962](./images/image-20250601215359962.png)

## 1.4 Access Control and Inheritance

The following table summarizes the access permissions of base class members in the derived class under different inheritance modes:

| **Base Class Member Access** | **Access in Derived Class (after public inheritance)** | **Access in Derived Class (after protected inheritance)** | **Access in Derived Class (after private inheritance)** |
| ---------------------------- | ------------------------------------------------------ | --------------------------------------------------------- | ------------------------------------------------------- |
| `public`                     | `public`                                               | `protected`                                               | `private`                                               |
| `protected`                  | `protected`                                            | `protected`                                               | `private`                                               |
| `private`                    | **Not directly accessible in derived class**           | **Not directly accessible in derived class**              | **Not directly accessible in derived class**            |

- Private members of the base class are never directly accessible by the derived class, regardless of the inheritance type. Derived classes can only indirectly access private members of the base class through the base class's public or protected interface (if provided).

# Polymorphism

Polymorphism (from Greek, meaning "many forms") is one of the core features of object-oriented programming. It allows us to treat objects of different types in a uniform way. In C++, polymorphism is primarily achieved through virtual functions and dynamic binding.

## 2.1 Static Binding vs. Dynamic Binding

- **Static Binding (Early Binding)**: The function call is resolved at compile time. Non-virtual function calls, as well as virtual function calls made through an object (rather than a pointer or reference), use static binding. The compiler determines which function to call based on the static type of the calling expression (the type the variable is declared as).
- **Dynamic Binding (Late Binding)**: The function call is resolved at runtime. When a virtual function is called through a base class pointer or reference, dynamic binding is used. The program determines which version of the virtual function to call based on the dynamic type of the object pointed to or referenced (the actual type of the object).

## 2.2 Virtual Functions

By declaring a member function as `virtual` in a base class, it can be overridden in derived classes, and dynamic binding can be achieved through base class pointers or references.

- **Declaration**: Add the `virtual` keyword before the function declaration in the base class.

    ```cpp
    class Base {
    public:
        virtual void show() { /* Base class implementation */ }
        // ...
    };
    ```

- **Overriding**: A derived class can provide a function with the same signature (name, parameter list, and `const` qualifier) as a virtual function in the base class. In C++11 and later, it is recommended to add the `override` keyword after the function signature in the derived class to help the compiler check if the signature matches.

    ```cpp
    class Derived : public Base {
    public:
        void show() override { /* Derived class specific implementation */ }
        // ...
    };
    ```

> [!TIP]
>
> 当通过基类指针或引用调用虚函数时，程序会查找该指针/引用实际指向的对象的类型，并调用该类型对应的虚函数版本。这是通过虚函数表（vtable）机制实现的。

```

```

## 2.3 Pure Virtual Functions and Abstract Base Classes

- **Pure Virtual Function**: A virtual function that is declared in a base class but has no definition provided in the base class. It tells the compiler that the function must be implemented in derived classes. A pure virtual function is declared by appending `= 0` to its declaration.

    ```cpp
    class Shape {
    public:
        virtual double area() const = 0; // Pure virtual function
        virtual ~Shape() {} // Abstract classes should also have a virtual destructor
    };
    ```

- **Abstract Base Class (ABC)**: A class containing at least one pure virtual function is called an abstract base class. Abstract base classes cannot be instantiated (i.e., you cannot create objects of an ABC). They primarily serve as interfaces, defining functionality that derived classes must implement. If a derived class fails to implement all pure virtual functions from its base class, it too becomes an abstract class.

> [!NOTE]
>
> 抽象基类不能被实例化，它主要用作接口，定义派生类必须实现的功能。派生类如果未能实现基类中的所有纯虚函数，那么它本身也将成为抽象类。

#  Destructors in Inheritance

## 3.1 Importance of Virtual Destructors

When deleting a derived class object through a base class pointer, if the base class's destructor is not virtual, only the base class's destructor will be called. The derived class's destructor will not be invoked. This can lead to resources allocated in the derived class (such as dynamic memory) not being properly released, causing resource leaks.

> [!NOTE]
>
> 当通过基类指针删除一个派生类对象时，如果基类的析构函数不是虚函数，则只会调用基类的析构函数，派生类的析构函数不会被调用。这会导致派生类中分配的资源（如动态内存）无法被正确释放，从而引发资源泄漏。
>
> 如果一个类可能作为基类，并且其实例可能通过基类指针被删除，那么它的析构函数**应该**声明为 `virtual`。

```cpp
class Base {
public:
    Base() { /* ... */ }
    virtual ~Base() { /* Base class cleanup */ } // Virtual destructor
};

class Derived : public Base {
private:
    int* data;
public:
    Derived() { data = new int[10]; /* ... */ }
    ~Derived() override { delete[] data; /* Derived class cleanup */ } // Destructor will also be called
};

// Base* ptr = new Derived();
// delete ptr; // Correctly calls Derived::~Derived() then Base::~Base()
```

![image-20250601220325171](./images/image-20250601220325171.png)

---

#  Inheritance and Dynamic Memory Allocation

## 4.1 Dynamic Memory Allocation in Cpp

When base classes, derived classes, or both use dynamic memory allocation, special attention must be paid to the correct implementation of copy control members (copy constructor, copy assignment operator) and destructors.

* **If the Derived Class Does Not Use Dynamic Memory Allocation**:
    * Usually, no explicit definition of copy control members or destructor is needed for the derived class; compiler-generated versions will correctly call the base class versions.

* **If the Derived Class Also Uses Dynamic Memory Allocation**:
    * The derived class **must** explicitly define its own destructor, copy constructor, and copy assignment operator.
    * **Derived Class Destructor**: Responsible for cleaning up resources allocated by the derived class itself. It will automatically call the base class destructor.
    * **Derived Class Copy Constructor**:
        * Must explicitly call the base class's copy constructor to handle copying the base class part (via the member initializer list).
        * Then responsible for deep copying the dynamically allocated members defined by the derived class itself.
    * **Derived Class Copy Assignment Operator**:
        * Must explicitly call the base class's copy assignment operator to handle assignment of the base class part.
        * Needs to handle self-assignment.
        * Release dynamic resources currently held by the derived class.
        * Then responsible for deep copying the dynamically allocated members defined by the derived class itself.

```cpp
#include <iostream>
#include <cstring>
using namespace std;
class Parent{
private:
    int id;
    char* name;

public:
    Parent(int i=0, const char* n="null");
    Parent(const Parent& p);
    virtual ~Parent();
    Parent& operator=(const Parent& prhs);

    friend ostream& operator<<(ostream& os, const Parent& p){
        os<<"Parent:"<<p.id<<", "<<p.name<<endl;
        return os;
    } 
};

class Child: public Parent{
private:
    char* style;
    int age; 

public:
    Child(int i=0, const char* n="null", const char* s="null", int a=0);
    Child(const Child& c);
    ~Child();
    Child& operator=(const Child& crhs);
    friend ostream& operator<<(ostream& os, const Child& c){
        os<<(Parent&)c<<"Child:"<<c.style<<", "<<c.age<<endl;
        return os;
    } 
};

Parent::Parent(int i, const char* n){
    cout<<"calling Parent defautl constructor Parent()\n";
    id = i;
    name = new char[strlen(n) + 1];
    //strcpy_s(name,strlen(n)+1, n);
    strncpy(name, n,strlen(n)+1);
}

Child::Child(int i, const char* n, const char* s, int a): Parent(i,n){
    cout<<"call Child default constructor Child()\n";
    style = new char[strlen(s) + 1];
    //strcpy_s(style,strlen(s)+1, s);
    strncpy(style, s,strlen(s)+1);
    age=a;
}

Parent:: ~Parent(){
    cout<< "call Parent destructor.\n";
    delete [] name;
}
Child::~Child(){
    cout<<"call Child destructor.\n";
    delete[] style;
}

Parent::Parent(const Parent& p){
    cout<<"calling Parent copy constructor Parent(const Parent&)\n";
    id = p.id;
    name = new char[strlen(p.name)+1];
    //strcpy_s(name, strlen(p.name)+1, p.name);
    strncpy(name, p.name,strlen(p.name)+1);
}

Child::Child(const Child& c):Parent(c){
    cout<<"calling Child copy constructor Child(const Child&)\n";
    age = c.age;
    style = new char[strlen(c.style)+1];
    //strcpy_s(style, strlen(c.style)+1, c.style);
    strncpy(style, c.style, strlen(c.style)+1);
}

Parent& Parent::operator=(const Parent& prhs){
    cout<<"call Parent assignment operator:\n";
    if(this == &prhs)
        return *this;

    delete []name;
    this->id = prhs.id;
    name = new char[strlen(prhs.name)+1];
    //strcpy_s(name,strlen(prhs.name)+1, prhs.name);
    strncpy(name,prhs.name,strlen(prhs.name)+1);
    return *this;    
}

Child& Child::operator=(const Child& crhs){
    cout<<"call Child assignment operator:\n";
    if(this == &crhs)
        return *this;
    Parent::operator=(crhs);

    delete []style;
    style = new char[strlen(crhs.style)+1];
    //strcpy_s(style,strlen(crhs.style)+1,crhs.style);
    strncpy(style,crhs.style,strlen(crhs.style)+1);
    age = crhs.age;

    return *this;    
}

int main(){
    Parent p1;
    cout<< "value in p1\n"<<p1<<endl;

    Parent p2(101, "Liming");
    cout<< "value in p2\n"<<p2<<endl;

    Parent p3(p1);
    cout<< "value in p3\n"<<p3<<endl;
    p1 = p2;
    cout<< "value in p1\n"<<p1<<endl;

    Child c1;
    cout<<"value in c1\n"<<c1<<endl;

    Child c2(201, "Wuhong","teenager",15);
    cout<<"value in c2\n"<<c2<<endl;

    Child c3(c1);
    cout<< "value in c3\n"<<c3<<endl;
    c1=c2;
    cout<<"value in c1\n"<<c1<<endl;

    return 0;
}
```

![image-20250601220929610](./images/image-20250601220929610.png)

## 4.2 class inheritance in Python

1. Inheritance in Python is **public inheritance**, providing flexible data access
2. The inheritance mechanism in Python is **explicit** and **requires calling the constructor of the parent class during initialization**, which can be implemented through **super**()
3. Assignment in Python is usually a reference, and deep copy requires the **deepcopy** method of the copy module
4. Python **does not allow overloading operator**, using method instead( **assign**, **__str__** here)
5. Destructors in Python rely on garbage collection mechanisms.

6. Rewriting __del__ requires caution and attention to potential memory risks.

```python
import copy

class Parent:
    def __init__(self, i=0, n="null"):
        print("calling Parent default constructor Parent()")
        self.id = i
        self.name = n  # Python 字符串不可变，无需手动内存管理

    def __deepcopy__(self, memo):
        print("calling Parent copy constructor Parent(const Parent&)")
        new_obj = self.__class__(self.id, self.name)
        memo[id(self)] = new_obj
        return new_obj

    def assign(self, other):
        print("call Parent assignment operator:")
        if self is other:
            return self
        self.id = other.id
        self.name = other.name
        return self

    def __del__(self):
        print("call Parent destructor.")  # 实际无需手动释放资源

    def __str__(self):
        return f"Parent:{self.id}, {self.name}\n"

class Child(Parent):
    def __init__(self, i=0, n="null", s="null", a=0):
        super().__init__(i, n)
        print("call Child default constructor Child()")
        self.style = s
        self.age = a

    def __deepcopy__(self, memo):
        print("calling Child copy constructor Child(const Child&)")
        new_obj = self.__class__(self.id, self.name, self.style, self.age)
        memo[id(self)] = new_obj
        return new_obj

    def assign(self, other):
        print("call Child assignment operator:")
        if self is other:
            return self
        super().assign(other)
        self.style = other.style
        self.age = other.age
        return self

    def __del__(self):
        super().__del__()
        print("call Child destructor.")  # 父类 __del__ 会自动调用

    def __str__(self):
        #parent_str = super().__str__().replace("Parent:", "Child:", 1)
        parent_str = super().__str__()
        return f"{parent_str}Child:{self.style}, {self.age}\n"

if __name__ == "__main__":
    # 模拟 C++ 对象构造
    p1 = Parent()
    print("value in p1\n", p1)

    p2 = Parent(101, "Liming")
    print("value in p2\n", p2)

    p3 = copy.deepcopy(p1)
    print("value in p3\n", p3)

    p1.assign(p2)
    print("value in p1\n", p1)

    # 子类测试
    c1 = Child()
    print("value in c1\n", c1)

    c2 = Child(201, "Wuhong", "teenager", 15)
    print("value in c2\n", c2)

    c3 = copy.deepcopy(c1)
    print("value in c3\n", c3)

    c1.assign(c2)
    print("value in c1\n", c1)

    # 手动触发析构（Python 垃圾回收时机不确定）
    del  c3, c2, c1, p3, p2, p1


```



---

# Exercises

## Exercise 1

Point out the errors in the following code and explain why to the TA.

```cpp
#include <iostream>


class Base
{
private:
    int x;
protected:
    int y;
public:
    int z;
    void funBase (Base& b){
    ++x;
    ++y;
    ++z;
    ++b.x;
    ++b.y;
    ++b.z;
    }
};

class Derived:public Base
{
public:
    void funDerived (Base& b, Derived& d){
        ++x;
        ++y;
        ++z;
        ++b.x;
        ++b.y;
        ++b.z;
        ++d.x;
        ++d.y;
        ++d.z;
    }
};


void fun(Base& b, Derived& d){
    ++x;
    ++y;
    ++z;
    ++b.x;
    ++b.y;
    ++b.z;
    ++d.x;
    ++d.y;
    ++d.z;
}

```

![image-20250601211711843](./images/image-20250601211711843.png)

**Hints for Solution**:
* Carefully analyze what member each `++` operation attempts to access and the context of the access (is it in a base class member function, derived class member function, or global function?).
* Recall the access rules for `private`, `protected`, and `public` members, and how their access permissions change upon inheritance.
* A member function of a class can access the private and protected members of *any* object of that class, not just the object that called the function (`this` points to).

**Answer:**

```cpp
class Base {
private:
    int x;
protected:
    int y;
public:
    int z;
    void funBase(Base& b) {
        ++x; ++y; ++z;
        ++b.x; ++b.y; ++b.z; // Base object can access private/protected members of another Base object
    }
};

class Derived : public Base {
public:
    void funDerived(Base& b, Derived& d) {
        ++y;       // OK: y is protected in Base, Derived is a subclass
        ++z;       // OK: z is public in Base
        ++b.z;     // OK: Can access public member z of arbitrary Base object b
        // ++d.x;     // Error: x is private in Base
        ++d.y;     // OK: d is a Derived object, can access its inherited protected member y
        ++d.z;     // OK: d is a Derived object, can access its inherited public member z
    }
};

void fun(Base& b, Derived& d) {
    ++b.z;           // OK
    ++d.z;           // OK
}

```

## Exercise 2

Run the following program and explain the result to the TA.

```cpp
#include<iostream>
using namespace std;

class Polygon{
protected:
    int width,height;
public:
    void set_values(int a,int b){
        width=a;
        height=b;
    }
    int area(){
        return 0;
    }
};

class Rectangle: public Polygon {
public:
    int area(){ 
        return width * height; 
    }
};

class Triangle: public Polygon {
public:
    int area(){ 
        return width*height/2;
    }
};

int main () {
  Rectangle rect;
  Triangle trgl;
  Polygon * ppoly1 = &rect;
  Polygon * ppoly2 = &trgl;
  ppoly1->set_values (4,5);
  ppoly2->set_values (2,5);

  cout << rect.area() << endl;
  cout << trgl.area() << endl;
  cout << ppoly1->area() << endl;
  cout << ppoly2->area() << endl;
  return 0;
}

```

![image-20250601212310743](./images/image-20250601212310743.png)

**Hints for Solution**:
* Since `Polygon::area()` is not a virtual function, calling `area()` through the base class pointers `ppoly1` and `ppoly2` will always invoke the version defined in the `Polygon` class (static binding).
* Calling `area()` directly through the `rect` and `trgl` objects will invoke the versions defined in their respective classes.
* Consider how to modify the code to achieve polymorphic behavior (i.e., to make `ppoly1->area()` call `Rectangle::area()`).

## Exercise 3

Run the following program and explain the result to the TA. Are there any problems in the program?

```cpp
// dynamic allocation and polymorphism
#include <iostream>
using namespace std;
class Polygon 
{
protected:
    int width, height;
public:
    Polygon (int a, int b) : width(a), height(b) {}
    virtual int area (void) =0;
    void printarea(){
        cout << this->area() << '\n';
    }
};

class Rectangle: public Polygon {
public:	
    Rectangle(int a,int b) : Polygon(a,b) {}
    int area(){ 
        return width*height;
    }
};
class Triangle: public Polygon 
{
public:
     Triangle(int a,int b) : Polygon(a,b) {}
     int area()
     { return width*height/2; }
};

int main () {
    Polygon * ppoly = new Rectangle (4,5);
    ppoly->printarea();
    ppoly = new Triangle (2,5);
    ppoly->printarea();

    return 0;
}


```

![image-20250601215128563](./images/image-20250601215128563.png)

![image-20250601215141290](./images/image-20250601215141290.png)

**Hints for Solution**:

* `Polygon` is an abstract base class because it contains the pure virtual function `area()`. Objects of type `Polygon` cannot be created.
* The `printarea()` function calls `this->area()`. Since `area()` is virtual, dynamic binding occurs here, correctly calling the derived class's implementation of `area()`.
* **Potential Problem**: The `Polygon` class does not declare a virtual destructor. When `delete ppoly1;` and `delete ppoly2;` are executed, if `Polygon::~Polygon()` is not virtual, only the base class's destructor will be called. The destructors of the derived classes `Rectangle` and `Triangle` (even if default-generated) might not be called. If the derived classes have important cleanup work in their destructors (e.g., releasing dynamically allocated resources), this will lead to resource leaks.
* **Correction**: A virtual destructor should be added to the `Polygon` class: `virtual ~Polygon() {}`.

---
*CC BY NC SA (Content adapted from course materials)*
