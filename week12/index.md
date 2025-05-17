---
title: CS205 Lab12 Class Inheritance & Polymorphism
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

Welcome to the Lab 12 study notes! This lab delves into two core concepts of object-oriented programming: inheritance and polymorphism. We will learn how to create class hierarchies through inheritance to achieve code reuse and understand access permissions under different inheritance types. More importantly, we will explore how polymorphism is achieved through virtual functions, allowing us to treat objects of different derived classes in a uniform manner. Additionally, we will discuss the importance of correctly managing dynamic memory and using virtual destructors in an inheritance hierarchy.

**Important Note:** This manual aims to emulate the style of `index.pdf`. Images from the slides will be replaced with textual descriptions in this Markdown version.

## I. Class Inheritance

Inheritance is a mechanism in object-oriented programming that allows a class (called a derived class or subclass) to acquire the properties and methods of another class (called a base class or parent class).

### 1.1 Basic Syntax of Inheritance

In C++, the syntax for inheritance is as follows:

```
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

```
[Image of class inheritance syntax diagram]
```

### 1.2 The `is-a` Relationship

Public inheritance establishes an "is-a" relationship. This means an object of the derived class is also an object of its base class. For example, if a `Student` class publicly inherits from a `Person` class, then a `Student` object *is a* `Person` object. This allows us to treat derived class objects as base class objects, which is fundamental to polymorphism.

### 1.3 Order of Constructor and Destructor Calls

When a derived class object is created:

1. The base class's constructor is called first to initialize the base class part of the derived class object.
2. Then, the derived class's constructor is called to initialize the members defined in the derived class itself.

When a derived class object is destroyed, the order is reversed:

1. The derived class's destructor is called first.
2. Then, the base class's destructor is called.

**Note**:

- A derived class constructor can explicitly call a specific base class constructor using its member initializer list. If not explicitly called, the base class's default constructor will be invoked.
- Destructor calls are automatic; you cannot explicitly call a base class destructor in a derived class destructor.

```
[Image of constructor and destructor call order example code output]
```

### 1.4 Access Control and Inheritance

The following table summarizes the access permissions of base class members in the derived class under different inheritance modes:

| **Base Class Member Access** | **Access in Derived Class (after public inheritance)** | **Access in Derived Class (after protected inheritance)** | **Access in Derived Class (after private inheritance)** |
| ---------------------------- | ------------------------------------------------------ | --------------------------------------------------------- | ------------------------------------------------------- |
| `public`                     | `public`                                               | `protected`                                               | `private`                                               |
| `protected`                  | `protected`                                            | `protected`                                               | `private`                                               |
| `private`                    | Not directly accessible in derived class               | Not directly accessible in derived class                  | Not directly accessible in derived class                |

- Private members of the base class are never directly accessible by the derived class, regardless of the inheritance type. Derived classes can only indirectly access private members of the base class through the base class's public or protected interface (if provided).

## II. Polymorphism

Polymorphism (from Greek, meaning "many forms") is one of the core features of object-oriented programming. It allows us to treat objects of different types in a uniform way. In C++, polymorphism is primarily achieved through virtual functions and dynamic binding.

### 2.1 Static Binding vs. Dynamic Binding

- **Static Binding (Early Binding)**: The function call is resolved at compile time. Non-virtual function calls, as well as virtual function calls made through an object (rather than a pointer or reference), use static binding. The compiler determines which function to call based on the static type of the calling expression (the type the variable is declared as).
- **Dynamic Binding (Late Binding)**: The function call is resolved at runtime. When a virtual function is called through a base class pointer or reference, dynamic binding is used. The program determines which version of the virtual function to call based on the dynamic type of the object pointed to or referenced (the actual type of the object).

### 2.2 Virtual Functions

By declaring a member function as `virtual` in a base class, it can be overridden in derived classes, and dynamic binding can be achieved through base class pointers or references.

- **Declaration**: Add the `virtual` keyword before the function declaration in the base class.

    ```
    class Base {
    public:
        virtual void show() { /* Base class implementation */ }
        // ...
    };
    ```

- **Overriding**: A derived class can provide a function with the same signature (name, parameter list, and `const` qualifier) as a virtual function in the base class. In C++11 and later, it is recommended to add the `override` keyword after the function signature in the derived class to help the compiler check if the signature matches.

    ```
    class Derived : public Base {
    public:
        void show() override { /* Derived class specific implementation */ }
        // ...
    };
    ```

- **How it Works**: When a virtual function is called through a base class pointer or reference, the program looks up the actual type of the object being pointed to/referenced and calls the version of the virtual function corresponding to that type. This is typically implemented using a virtual function table (vtable) mechanism.

```
[Image of Employee and SalariedEmployee classes using virtual function show() example code and polymorphic call result]
```

### 2.3 Pure Virtual Functions and Abstract Base Classes

- **Pure Virtual Function**: A virtual function that is declared in a base class but has no definition provided in the base class. It tells the compiler that the function must be implemented in derived classes. A pure virtual function is declared by appending `= 0` to its declaration.

    ```
    class Shape {
    public:
        virtual double area() const = 0; // Pure virtual function
        virtual ~Shape() {} // Abstract classes should also have a virtual destructor
    };
    ```

- **Abstract Base Class (ABC)**: A class containing at least one pure virtual function is called an abstract base class. Abstract base classes cannot be instantiated (i.e., you cannot create objects of an ABC). They primarily serve as interfaces, defining functionality that derived classes must implement. If a derived class fails to implement all pure virtual functions from its base class, it too becomes an abstract class.

## III. Destructors in Inheritance

### 3.1 Importance of Virtual Destructors

When deleting a derived class object through a base class pointer, if the base class's destructor is not virtual, only the base class's destructor will be called. The derived class's destructor will not be invoked. This can lead to resources allocated in the derived class (such as dynamic memory) not being properly released, causing resource leaks.

**Rule**: If a class is intended to be a base class, and instances of its derived classes might be deleted through a base class pointer, its destructor **should** be declared `virtual`.

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

```[Image comparing behavior when deleting a derived object via base pointer with non-virtual vs. virtual base class destructor]`

---

## IV. Inheritance and Dynamic Memory Allocation

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

`[Image of Parent and Child classes, both using dynamic memory, with example implementations of copy constructor and assignment operator]`

---

## V. Exercises

### Exercise 1

Point out the errors in the following code and explain why to the TA.

```cpp
// Code from the slides
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
        // ++x;       // Error: x is private in Base
        ++y;       // OK: y is protected in Base, Derived is a subclass
        ++z;       // OK: z is public in Base
        // ++b.x;     // Error: Cannot access private member x of arbitrary Base object b
        // ++b.y;     // Error: Cannot access protected member y of arbitrary Base object b (unless Derived is a friend of b)
        ++b.z;     // OK: Can access public member z of arbitrary Base object b
        // ++d.x;     // Error: x is private in Base
        ++d.y;     // OK: d is a Derived object, can access its inherited protected member y
        ++d.z;     // OK: d is a Derived object, can access its inherited public member z
    }
};

void fun(Base& b, Derived& d) {
    // ++x; ++y; ++z; // Error: Non-member function cannot directly access members of any class
    // ++b.x; ++b.y;   // Error: Cannot access private or protected members of Base object b
    ++b.z;           // OK
    // ++d.x; ++d.y;   // Error: Cannot access private or protected members of Derived object d (x is Base's private, y is Base's protected)
    ++d.z;           // OK
}

```

`[Image of Exercise 1 C++ code with access control issues]`

**Hints for Solution**:
* Carefully analyze what member each `++` operation attempts to access and the context of the access (is it in a base class member function, derived class member function, or global function?).
* Recall the access rules for `private`, `protected`, and `public` members, and how their access permissions change upon inheritance.
* A member function of a class can access the private and protected members of *any* object of that class, not just the object that called the function (`this` points to).

### Exercise 2

Run the following program and explain the result to the TA.

```cpp
#include <iostream>
// using namespace std; // Avoid in global scope

class Polygon {
protected:
    int width, height;
public:
    void set_values(int a, int b) {
        width = a; height = b;
    }
    // Non-virtual function
    int area() {
        return 0;
    }
};

class Rectangle : public Polygon {
public:
    int area() { // Hides base class area()
        return width * height;
    }
};

class Triangle : public Polygon {
public:
    int area() { // Hides base class area()
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

    std::cout << rect.area() << std::endl;   // Calls Rectangle::area()
    std::cout << trgl.area() << std::endl;   // Calls Triangle::area()
    std::cout << ppoly1->area() << std::endl; // Calls Polygon::area() because area() is non-virtual
    std::cout << ppoly2->area() << std::endl; // Calls Polygon::area() because area() is non-virtual
    return 0;
}

```

`[Image of Exercise 2 C++ code demonstrating non-virtual function behavior]`

**Hints for Solution**:
* Since `Polygon::area()` is not a virtual function, calling `area()` through the base class pointers `ppoly1` and `ppoly2` will always invoke the version defined in the `Polygon` class (static binding).
* Calling `area()` directly through the `rect` and `trgl` objects will invoke the versions defined in their respective classes.
* Consider how to modify the code to achieve polymorphic behavior (i.e., to make `ppoly1->area()` call `Rectangle::area()`).

### Exercise 3

Run the following program and explain the result to the TA. Are there any problems in the program?

```cpp
// dynamic allocation and polymorphism
#include <iostream>
// using namespace std;

class Polygon {
protected:
    int width, height;
public:
    Polygon(int a, int b) : width(a), height(b) {}
    virtual int area(void) = 0; // Pure virtual function
    void printarea() {
        std::cout << this->area() << '\n'; // this-> is optional
    }
    // Missing virtual destructor!
};

class Rectangle : public Polygon {
public:
    Rectangle(int a, int b) : Polygon(a, b) {}
    int area(void) override { // C++11: use override
        return width * height;
    }
};

class Triangle : public Polygon {
public:
    Triangle(int a, int b) : Polygon(a, b) {}
    int area(void) override { // C++11: use override
        return width * height / 2;
    }
};

int main() {
    Polygon* ppoly1 = new Rectangle(4, 5); // Renamed pointer to avoid conflict
    ppoly1->printarea();
    delete ppoly1; // Potential issue 1: Resource leak if destructor is non-virtual

    Polygon* ppoly2 = new Triangle(2, 5);
    ppoly2->printarea();
    delete ppoly2; // Potential issue 2: Same as above

    return 0;
}

```

`[Image of Exercise 3 C++ code with pure virtual functions and dynamic allocation]`

**Hints for Solution**:
* `Polygon` is an abstract base class because it contains the pure virtual function `area()`. Objects of type `Polygon` cannot be created.
* The `printarea()` function calls `this->area()`. Since `area()` is virtual, dynamic binding occurs here, correctly calling the derived class's implementation of `area()`.
* **Potential Problem**: The `Polygon` class does not declare a virtual destructor. When `delete ppoly1;` and `delete ppoly2;` are executed, if `Polygon::~Polygon()` is not virtual, only the base class's destructor will be called. The destructors of the derived classes `Rectangle` and `Triangle` (even if default-generated) might not be called. If the derived classes have important cleanup work in their destructors (e.g., releasing dynamically allocated resources), this will lead to resource leaks.
* **Correction**: A virtual destructor should be added to the `Polygon` class: `virtual ~Polygon() {}`.

---
*CC BY NC SA (Content adapted from course materials)*
