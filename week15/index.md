---
title: CS205 Lab 15: Friend Classes, Nested Classes & Run-Time Type Identification (RTTI)
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

- **Friend Classes**:
    - Declaring friend classes 
    - Characteristics of friend relationships (not symmetric, not transitive) 
    - When to use friend classes
- **Nested Classes**:
    - Definition and scope 
    - Access rights of nested classes 
    - Impact of different declaration locations (public, private, protected) 
- **Run-Time Type Identification (RTTI)**:
    - Type casting (C-style vs. C++ style)
    - `static_cast`
    - `dynamic_cast`: Safe downcasting or cross-casting, behavior with pointers and references
    - `typeid` operator: Getting runtime type information of an object
- **Exercises**

## Foreword

Welcome to the Lab 15 study notes! This lab will introduce some advanced class features in C++, including friend classes, nested classes, and Run-Time Type Identification (RTTI). We will learn how to use friend classes to allow one class to access the private and protected members of another, explore the definition and use cases of nested classes, and how to query and convert object types at runtime using RTTI mechanisms like `dynamic_cast` and `typeid`.

#  Friend Classes

Friend classes allow one class (the friend class) to access the `private` and `protected` members of another class (the class granting friendship).

## 1.1 Declaring Friend Classes

To declare `ClassTwo` as a friend of `ClassOne`, include the following declaration within `ClassOne`'s definition:

```
class ClassOne {
    friend class ClassTwo; // ClassTwo is a friend of ClassOne
private:
    int private_data;
protected:
    int protected_data;
public:
    ClassOne() : private_data(1), protected_data(2) {}
};

class ClassTwo {
public:
    void accessClassOneMembers(ClassOne& obj1) {
        // ClassTwo can access ClassOne's private and protected members
        // std::cout << "Accessing ClassOne private_data: " << obj1.private_data << std::endl;
        // std::cout << "Accessing ClassOne protected_data: " << obj1.protected_data << std::endl;
    }
};
```

This means all member functions of `ClassTwo` have the right to access the private and protected members of `ClassOne`. The friend declaration can appear anywhere in a class definition and is not affected by `public`, `private`, or `protected` access specifiers.

`[Image of friend class declaration and access example code]`

Forward Declaration:

If a class is referenced in a friend declaration before it is fully defined, a forward declaration might be necessary. For example, if class Point declares class Circle as a friend, and Circle's definition appears later, or if Circle uses Point objects as members (as in composition examples), Circle might need to be forward-declared (class Circle;) before Point's definition.

## 1.2 Characteristics of Friend Relationships

- **Not Symmetric**: If class A is a friend of class B, it does not imply that class B is also a friend of class A.
- **Not Transitive**: If class A is a friend of class B, and class B is a friend of class C, it does not imply that class A is also a friend of class C.

## 1.3 When to Use Friend Classes

Friend classes can be considered when two classes are tightly coupled but inheritance (`is-a` relationship) or composition (`has-a` relationship, where one class is a component of the other) are not suitable. 

This allows one class to grant another selective access to its internal implementation without breaking encapsulation for the rest of the world.

For instance, in class composition, if the container class needs frequent access to its member object's private data to function and providing unnecessary public interfaces for the member object class is undesirable, the container class can be declared a friend of the member object class.

#  Nested Classes

A nested class is a class declared within another class (called the enclosing class).

## 2.1 Definition and Scope

A nested class can be a `public`, `protected`, or `private` member of the enclosing class. Its scope is limited by the enclosing class.

```cpp
class Outer {
public:
    int outer_public_data;

    class Inner { // Nested class
    public:
        int inner_public_data;
        void display(const Outer& outer_obj) {
            // std::cout << "Inner accessing Outer's public data: " << outer_obj.outer_public_data << std::endl;
            // Nested class cannot directly access non-static members of Outer
            // unless it has a reference/pointer to an Outer object.
        }
        // void someInnerMethod(); // Declaration
    };

    // void Outer::Inner::someInnerMethod() { /* Definition */ } // Defining nested class member function outside Outer

    void useInner() {
        Inner in_obj;
        in_obj.inner_public_data = 10;
        // ...
    }
};

// Outer::Inner global_inner_obj; // If Inner is public, an object can be created like this externally
```

`[Image of Outer and Inner nested class definition example code]`

When defining a member function of a nested class outside the enclosing class, a class qualifier is needed, e.g., void Outer::Inner::someInnerMethod() { /* ... */ }.

## 2.2 Access Rights of Nested Classes

- A nested class is a member of the enclosing class and thus has the same access rights to the enclosing class's members as any other member (i.e., it can access all members of the enclosing class, including `private` members, if the nested class can obtain a reference or pointer to an object of the enclosing class).
- Members of an enclosing class have no special access to members of a nested class; the usual access rules must be obeyed (i.e., they can only access `public` members of the nested class, unless the enclosing class is a friend of the nested class).

## 2.3 Impact of Different Declaration Locations

- **`public` Nested Class**: Available to the enclosing class, classes derived from it, and, because it’s public, to the outside world (when used externally, it needs to be qualified with the class scope: `Outer::Inner`).
- **`private` Nested Class**: Known only to the enclosing class itself. Derived classes and the outside world do not know of its existence.
- **`protected` Nested Class**: Visible to the enclosing class and its derived classes, but invisible to the outside world. Derived classes can directly create objects of that nested type.

# Run-Time Type Identification (RTTI)

RTTI is a mechanism that allows a program to determine the dynamic type of an object (i.e., the actual type of the object, not the static type of the pointer or reference to it) at runtime. This is primarily used when dealing with objects in a class hierarchy.

## 3.1 Type Casting

C++ supports several type casting operators.

- **C-style cast**: `(new_type)expression` or `new_type(expression)`. Powerful but unsafe.
- **C++-style casts**:
    - `static_cast<new_type>(expression)`: Used for "relatively safe" conversions that can be determined at compile time, such as conversions between numeric types, pointer upcasting (derived to base), pointer downcasting (base to derived, but without runtime checks, unsafe), and conversions between `void*` and other pointer types. Cannot remove `const`ness.
    - `dynamic_cast<new_type>(expression)`: Used for safe downcasting or cross-casting within a class hierarchy.
    - `const_cast<new_type>(expression)`: Used to add or remove `const` or `volatile` qualifiers from an expression.
    - `reinterpret_cast<new_type>(expression)`: Used for low-level, often implementation-dependent, bit pattern conversions; very unsafe.

`[Image of C-style cast and C++ static_cast example code]`

Upcasting: Converting a pointer or reference of a derived class object to a base class pointer or reference. This is safe and usually done implicitly.

Downcasting: Converting a base class pointer or reference to a derived class pointer or reference. This often requires an explicit cast and can be unsafe (if the base class pointer does not actually point to a derived class object). 

Using C-style casts or static_cast for downcasting does not perform runtime safety checks.

## 3.2 `dynamic_cast`

`dynamic_cast` is used to perform safe downcasts or cross-casts within an inheritance hierarchy at runtime. It requires the type being operated on to have at least one virtual function (i.e., the type must be polymorphic).

- **Syntax**: `dynamic_cast<TargetType>(expression)`

- **Behavior**:

    - **Pointer Conversion**: If `expression` (a pointer) can be safely converted to `TargetType*` (i.e., `expression` actually points to a `TargetType` object, or a derived class of `TargetType`, or an accessible base class of `TargetType` that points to a `TargetType`), the cast succeeds and returns a `TargetType*` pointer to the object. If the cast fails (e.g., a base class pointer does not actually point to the target derived class object), it returns `nullptr` (or 0).

        ```cpp
        class Base { public: virtual ~Base() {} /* ... */ };
        class Derived : public Base { /* ... */ };
        Base* pb = new Derived;
        Base* pb2 = new Base;
        Derived* pd = dynamic_cast<Derived*>(pb);   // OK, pd points to Derived object
        Derived* pd2 = dynamic_cast<Derived*>(pb2); // Fails, pb2 points to Base object, pd2 is nullptr
        ```

    - **Reference Conversion**: If `expression` (a reference) can be safely converted to `TargetType&`, the cast succeeds. If the cast fails, it throws a `std::bad_cast` exception (defined in the `<typeinfo>` header).

- **Checking if Cast Succeeded**:

    ```cpp
    Base* bp = /* ... */;
    if (Derived* dp = dynamic_cast<Derived*>(bp)) {
        // Cast succeeded, dp now points to a Derived object, Derived-specific members can be used
        // dp->derived_specific_function();
    } else {
        // Cast failed, bp does not point to a Derived object
    }
    ```

    `[Image of dynamic_cast checking for successful cast in an if statement example]`

    `[Image of dynamic_cast for upcasting and downcasting, and calling base/derived show() function example]`

- `dynamic_cast` cannot remove `const`ness. The type of `expression` must be a class type that is publicly derived from `type-name`, a public base class of `type-name` which points to `type-name`, or the same as `type-name`

## 3.3 `typeid` Operator

The `typeid` operator returns a reference to a `std::type_info` object, which represents type information for an expression. The `type_info` class is defined in the `<typeinfo>` header.

- **Syntax**: `typeid(expression)` or `typeid(type-name)` 
- **Behavior**:
    - If the type of the expression is a class and contains at least one virtual function (i.e., a polymorphic type), and the expression is a reference or a dereferenced pointer, `typeid` returns the **dynamic type** of the expression.
    - Otherwise, it provides **static type** information.
- The `type_info` class overloads the `==` and `!=` operators, which can be used to compare types.
- The `type_info` class has a `name()` member function that returns a string representing the type name (often a mangled name).

```cpp
#include <typeinfo> // Required header

class Base { public: virtual ~Base() {} };
class Derived : public Base {};

// Base* bp = new Derived();
// Derived* dp = new Derived();

// if (typeid(*bp) == typeid(*dp)) { /* Compare runtime types of two objects */ } 
// if (typeid(*bp) == typeid(Derived)) { /* Test if runtime type is a specific type */ } 
// std::cout << typeid(*bp).name() << std::endl; // Output mangled type name
```

`[Image of typeid usage example code and output showing type names]`

`[Image of typeid output example, showing different type encodings (P=pointer, K=const, number=char count)]`

# Exercises

## Exercise 1

There are two classes, Car and Driver. Assume the car can drive automatically, and a driver can also drive the car. The declarations for Car and Driver are as follows. Implement all member functions of the two classes and make Driver a friend class of Car so that it can access Car's members. Write a program to test the two classes.

[Image of Car and Driver class declaration code]

[Image of Exercise 1 expected program output sample]

**Car Class Declaration (Partial)**

```
class Driver; // Forward declaration
class Car {
private:
    enum {Off, On}; // Off - non-automatic drive, On - automatic drive
    enum {Minvel = 0, Maxvel = 200}; // Velocity range
    int mode;     // Car mode, Off or On
    int velocity;
public:
    friend class Driver; // Driver is a friend of Car
    Car(int m = On, int v = 50):mode(m),velocity(v){}
    bool velup(int v);   // Increase velocity by v
    bool veldown(int v); // Decrease velocity by v
    bool ison() const;   // Check if mode is On
    int getvel() const;  // Get velocity
    void showinfo() const; // Show car's mode and velocity
};
```

**Driver Class Declaration (Partial)**

```
class Driver {
public:
    bool velup(Car& car, int v);   // Increase velocity by v
    bool veldown(Car& car, int v); // Decrease velocity by v
    void setmode(Car& car);        // If mode is On, set to Off, otherwise set to On
    bool ison(Car& car) const;     // Check if mode is On
};
```

## Exercise 2

There are two class declarations for `Base` and `Derived`. You are required to implement three kinds of functions:

1. The equality operator `==` is declared as a friend function of the `Base` class. Two objects are equal if they have the same type and the same value for a given set of their data members. If two objects have different types, throw a message "The two objects have different types, they cannot be compared." as an exception.

2. Virtual `equal` member functions in `Base` and `Derived` classes which check whether the data members have the same values in their own objects respectively.

3. A void process(const Base&, const Base&) function, which is a normal function that checks if the two objects are equal and handles the exception.

    Run the main function to check your defined functions.

`[Image of Base and Derived class declarations and main test function code]` 

*CC BY NC SA (Content adapted from course materials)*
