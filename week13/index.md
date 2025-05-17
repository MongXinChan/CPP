---
title: CS205 Lab13: Class Composition & Templates
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

- **Class Containment (Composition)**:
    - Definition and "has-a" relationship
    - Construction and destruction order of member objects
- **Templates**:
    - Basic concepts and advantages of class templates
    - Definition and instantiation of class templates
    - Multiple template parameters
    - Non-type template parameters
    - Default template parameters
- **Template Specialization**:
    - Complete specialization
    - Partial specialization
- **Template vs. Inheritance Comparison**
- **Exercises**

## Foreword

Welcome to the Lab 13 study notes! This lab will explore two important C++ techniques for code organization and reuse: class composition and templates. 

We will learn how to implement composition (the "has-a" relationship) by including objects of one class as members within another and understand the order of their construction and destruction. 

Subsequently, we will delve into templates, particularly class templates, to see how to create generic classes usable with various data types. We will also discuss template specialization, including complete and partial specialization, and when to choose templates over inheritance.

# Class Containment (Composition)

Class composition refers to a class having members that are objects of another class. This relationship typically represents a "has-a" connection. For example, a "Car" class might "have an" "Engine" class object as one of its members.

## 1.1 Definition and "has-a" Relationship

Composition occurs when a class (the container class) includes an object of another class as one of its members.

```cpp
class Engine {
public:
    Engine(int nc) : cylinder(nc) { std::cout << "Constructor:Engine(int)\n"; }
    void start() { std::cout << getCylinder() << " cylinder engine started\n"; }
    int getCylinder() { return cylinder; }
    ~Engine() { std::cout << "Destructor:~Engine()\n"; }
private:
    int cylinder;
};

class Car {
private:
    Engine eng; // Car "has-an" Engine
public:
    Car(int n = 4) : eng(n) { std::cout << "Constructor:Car(int)\n"; } // Initialize member object via initializer list
    void start() {
        std::cout << "car with " << eng.getCylinder() << " cylinder engine started\n";
        eng.start();
    }
    ~Car() { std::cout << "Destructor:~Car()\n"; }
};
```

In the example above, the `Car` class contains an `Engine` object named `eng`.

## 1.2 Construction and Destruction Order of Member Objects

- **Construction Order**: When an object of the container class is created:
    1. First, the constructors of the member objects are called in the order they are declared within the container class. Arguments for the member objects' constructors are typically provided in the container class's constructor initializer list.
    2. Then, the body of the container class's own constructor is executed.
- **Destruction Order**: When an object of the container class is destroyed, the order is reversed:
    1. First, the body of the container class's own destructor is executed.
    2. Then, the destructors of the member objects are called in the reverse order of their declaration within the container class.

#  Templates

Templates are a powerful feature in C++ that enable functions and classes to operate on generic types. This means they can work with a variety of data types without needing to be rewritten for each type.

## 2.1 Basic Concepts and Advantages of Class Templates

Class templates allow us to define a generic class blueprint.

- **Advantages**:
    - **Code Reusability**: Write code once for multiple types.
    - **Type Safety**: The compiler performs type checking at compile time.
    - **Flexibility and Versatility**: Easy to create general-purpose containers or algorithms applicable to different data structures.

## 2.2 Definition and Instantiation of Class Templates

- **Definition Syntax**:

    ```cpp
    template <typename T> // Or template <class T>
    class ClassName {
        // Class definition using T as a generic type
    private:
        T member;
    public:
        ClassName(T val) : member(val) {}
        T getMember() const { return member; }
    };
    ```

- **Member Function Definition Outside the Class**:

    ```cpp
    template <typename T>
    T ClassName<T>::getMember() const {
        return member;
    }
    ```

    Note that when defining a member function of a template class outside the class, you need to prefix the definition with `template <typename T>` and qualify the class name with `<T>`.

- **Instantiation**: When we create an object of a template class using a specific type, it's called instantiation.

    ```cpp
    ClassName<int> intObject(10);
    ClassName<double> doubleObject(20.5);
    // std::cout << intObject.getMember() << std::endl;
    // std::cout << doubleObject.getMember() << std::endl;
    ```

    `Matrix<int> m;` makes `Matrix<int>` the name of a new class.

## 2.3 Multiple Template Parameters

Class templates can have multiple type parameters.

```cpp
template <typename T1, typename T2>
class Pair {
public:
    T1 key;
    T2 value;
    Pair(T1 k, T2 v) : key(k), value(v) {}
    void display() {
        // std::cout << "Key: " << key << ", Value: " << value << std::endl;
    }
};

// Pair<std::string, int> p1("Age", 30);
// p1.display();
```

## 2.4 Non-Type Template Parameters

Class templates can accept not only types as parameters but also non-type parameters, such as integral constants, pointers, references, etc. These parameters must be compile-time constants.

```cpp
template <typename T, size_t SIZE>
class Array {
private:
    T arr[SIZE]; // SIZE is a compile-time constant
public:
    void insert() { /* ... */ }
    void display() { /* ... */ }
    // ...
};

// Array<int, 10> intArray; // Creates an Array object containing 10 integers
```

Non-type template parameters can be strings, constant expressions, and built-in types.

``

## 2.5 Default Template Parameters

Default values can be provided for template parameters.

```cpp
template <typename T, typename U, typename V = char>
class MultipleParameters {
private:
    T var1;
    U var2;
    V var3;
public:
    MultipleParameters(T v1, U v2, V v3) : var1(v1), var2(v2), var3(v3) {}
    // ...
};

// MultipleParameters<int, double> obj1(7, 7.7, 'c'); // V uses default value char
// MultipleParameters<double, char, bool> obj2(8.8, 'a', false); // V is specified as bool
```

# Template Specialization

Sometimes, a generic template definition may not be optimal or applicable for certain specific types. Template specialization allows us to provide a dedicated template implementation for a particular type or combination of types.

- A specialized template class behaves like a new class; it does not inherit anything from the primary template (except the name). Any and all methods and members will have to be re-implemented.

## 3.1 Complete Specialization

When all template parameters are specified as concrete types, it's called a complete specialization.

```cpp
// Primary template
template <typename Z>
class Test {
public:
    Test() { /* std::cout << "It is a General template object\n"; */ }
};

// Complete specialization for int type
template <>
class Test<int> {
public:
    Test() { /* std::cout << "It is a Specialized template object for int\n"; */ }
};

// Test<char> q; // Uses the general template
// Test<int> p;  // Uses the int specialization
```

### 3.2 Partial Specialization

When only some of the template parameters are specialized, or when a specialization is made for a characteristic of a parameter (like being a pointer or reference), it's called partial specialization. The result of a partial specialization is still a template.

- **Case 1: Multiple type parameters, some specialized**

    ```cpp
    // Primary template
    template <typename T1, typename T2>
    class Data {
    public:
        Data(T1 m, T2 n) { /* ... */ }
        void display() { /* ... */ }
    };
    
    // Partial specialization: when T2 is char
    template <typename T1>
    class Data<T1, char> {
    public:
        Data(T1 m, char c) { /* ... */ }
        void display() { /* ... */ }
    };
    ```

- **Case 2: Partial specialization for pointer types**

    ```cpp
    // Primary template
    template <typename T>
    class Bag {
        T elem;
        // ...
    public:
        void add(T t) { /* ... */ }
    };
    
    // Partial specialization: when T is a pointer type T*
    template <typename T>
    class Bag<T*> {
        T* elem; // Stores a pointer
        // ...
    public:
        void add(T* t) { // Parameter is a pointer
            // Could store the pointer itself, or dereference and store the value
            // The slide example stores the dereferenced value
            if (t != nullptr) {
                // elem[size++] = *t; // Assuming elem is an array of T
            }
        }
    };
    ```

    The Bag<T*> example from the slides demonstrates that if the template argument is T* (a pointer), the add method takes a T* and internally stores the value pointed to by dereferencing *t. Without partial specialization, only the pointers themselves would be added.

#  Bringing it All Together & Comparison

## 4.1 Template Definition Location

Class templates and their member function templates should generally be declared and defined in header files (`.h` or `.hpp`). This is because the compiler needs to see the full definition of the template when it instantiates it.

## 4.2 Template vs. Inheritance

- **Templates**: Used to generate a set of classes where the object type does not affect the functional behavior of the class (i.e., the algorithm is generic, only the data type it operates on differs). Focuses on algorithmic generality.
- **Inheritance**: Used for a set of classes where the object type *does* affect the functional behavior of the class (via virtual functions for polymorphism). Focuses on achieving different behaviors through a common interface.

# Exercises

## Exercise 1

The declarations of `Point` class and `Line` class are as follows. Implement the member functions of these two classes and then run the program to test the classes.

```cpp
class Point {
private:
     double x, y;
public:
     Point(double newX, double newY);
     Point(const Point& p);
     double getX() const;
     double getY() const;
};

class Line {
private:
     Point p1, p2; // Composition: Line class contains two Point objects
     double distance;
public:
      Line(Point xp1, Point xp2);
      Line(const Line& q);
     double getDistance() const;
};

// main function test code
// int main() {
//       Point a(8, 9),b(1,2);
//       Point c = a;
//       // ... output coordinates of points a, b, c ...
//       Line line1(a, b);
//       // ... output distance of line1 ...
//       Line line2(line1);
//       // ... output distance of line2 ...
//      return 0;
// }
```

**Hint**: The constructor of `Line` needs to calculate the distance between the two points and store it in the `distance` member. Distance formula: `sqrt((x2-x1)^2 + (y2-y1)^2)`.

## Exercise 2

A template class named `Pair` is defined as follows. Please implement the overloaded `operator<` which compares the value of the `key`. If `this->key` is smaller than `p.key`, return `true`. Then define a friend function to overload the `<<` operator which displays the `Pair`’s data members. Finally, run the program. The output sample is as follows.

```cpp
#include <iostream>
#include <string>
// using namespace std; // Avoid in header or global scope

template <class T1, class T2>
class Pair {
public:
    T1 key;
    T2 value;
    Pair(T1 k, T2 v) : key(k), value(v) {}
    bool operator<(const Pair<T1, T2>& p) const;
    // Declare friend function to overload <<
    friend std::ostream& operator<<(std::ostream& os, const Pair<T1, T2>& p) {
        os << "Key: " << p.key << ", Value: " << p.value; // Example output format
        return os;
    }
};

template <class T1, class T2>
bool Pair<T1, T2>::operator<(const Pair<T1, T2>& p) const {
    return this->key < p.key;
}

// main function test code
// int main() {
//     Pair<std::string, int> one("Tom", 19);
//     Pair<std::string, int> two("Alice", 20);
//     if (one < two) // one.key ("Tom") > two.key ("Alice") is false
//         std::cout << one << std::endl;
//     else
//         std::cout << two << std::endl; // Should output Alice 20
//     return 0;
// }
```

## Exercise 3

There is a definition of a template class `Dictionary`. Please write a template partial specialization for the `Dictionary` class where the `Key` is specified to be `int`. In this specialized version, add a member function named `sort()` which sorts the elements in the dictionary in ascending order (based on keys). Finally, run the program. The output sample is as follows.

```cpp
// Primary template Dictionary (from slides)
template <class Key, class Value>
class Dictionary {
    Key* keys;
    Value* values;
    int size;
    int max_size;
public:
    Dictionary(int initial_size) : size(0) { /* ... implement as per slides ... */ }
    void add(Key key, Value value) { /* ... implement as per slides ... */ }
    void print() {
        for (int i = 0; i < size; i++)
            std::cout << "{" << keys[i] << ", " << values[i] << "}" << std::endl;
    }
    ~Dictionary() { delete[] keys; delete[] values; }
};

// Partial specialization for Key as int
template <class Value> // Value is still a template parameter
class Dictionary<int, Value> {
    int* keys; // Key is now int
    Value* values;
    int size;
    int max_size;
public:
    Dictionary(int initial_size) : size(0) { /* ... similar implementation to primary ... */ }
    void add(int key, Value value) { /* ... similar implementation to primary ... */ }
    void print() {
        for (int i = 0; i < size; i++)
            std::cout << "{" << keys[i] << ", " << values[i] << "}" << std::endl;
    }
    void sort() {
        // Implement sorting logic, e.g., simple selection or bubble sort
        // Sort keys and values arrays synchronously based on keys[i]
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (keys[j] > keys[j + 1]) {
                    // Swap keys
                    int tempKey = keys[j];
                    keys[j] = keys[j + 1];
                    keys[j + 1] = tempKey;
                    // Swap corresponding values
                    Value tempValue = values[j];
                    values[j] = values[j + 1];
                    values[j + 1] = tempValue;
                }
            }
        }
    }
    ~Dictionary() { delete[] keys; delete[] values; }
};

// main function test code (from slides)
// int main() {
//     Dictionary<const char*, const char*> dict(10);
//     // ... add and print ...
//     Dictionary<int, const char*> dict_specialized(10);
//     // ... add, print, sort, then print again ...
//    return 0;
// }
```

---

*CC BY NC SA (Content adapted from course materials)*
