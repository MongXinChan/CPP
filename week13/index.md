---
title: "CS205 Lab13 Class Composition & Templates"
published: 2025-05-31
updated: 2025-06-02
description: '本实验将探讨C++中两种重要的代码组织和复用技术：类的组合和模板。我们将学习如何通过在一个类中包含另一个类的对象来实现组合（“has-a”关系），并理解其构造和析构顺序。随后，我们将深入研究模板，特别是类模板，了解如何创建可用于多种数据类型的通用类。我们还将讨论模板的特化，包括完全特化和部分特化，以及何时选择使用模板而非继承。'
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

![image-20250602102102027](./images/image-20250602102102027.png)

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

**Construction Order**: When an object of the container class is created:

1. First, the constructors of the member objects are called in the order they are declared within the container class. Arguments for the member objects' constructors are typically provided in the container class's constructor initializer list.
2. Then, the body of the container class's own constructor is executed.

| Images |                             is-a                             |                            has-a                             |
| ------ | :----------------------------------------------------------: | :----------------------------------------------------------: |
| Output | ![image-20250602103114067](./images/image-20250602103114067.png) | ![image-20250602102532894](./images/image-20250602102532894.png) |
| Order  |           1.~derived class()<br />2.~base class()            |            1.~Car class()<br />2.~Enginec class()            |
| Differ |                       **Inheritance**                        |                       **Composition**                        |

**Destruction Order**: When an object of the container class is destroyed, the order is reversed:

1. First, the body of the container class's own destructor is executed.
2. Then, the destructors of the member objects are called in the reverse order of their declaration within the container class.

> [!TIP]
>
> 【重用接口，实现的重用】
>
> ![image-20250602110134312](./images/image-20250602110134312.png)
>
> 对象的思想是一种很方便的工具。它允许我们将数据和功能通过概念封装在一起，使得我们能描述合适的问题空间思想，而不是被强调使用底层机器的用于。通过使用class关键字，这些概念呗表示为程序设计语言中的基本单元。
>
> 然而，克服许多困难去创建一个类，并随后强制性地创造一个有类似功能的全新的类，似乎并不是一个很好的方法。如果能选取已存在的类，克隆它，然后对这个克隆增加和修改，则是再好不过的事情。这是继承（Inheritance）带来的好处，例外的情况是，如果原来的类（称之为基类、超类或父类）呗修改，则这个修改过的“克隆”（称为派生类、继承类或子类）也会表现出这些改变。
>
> 在上面的UML图片中，我们可以发现，箭头从派生类指向基类。正如你看到的，可以有多个派生类。
>
> `is-a`是一种继承关系，**重用接口**，假设`Teacher`在听到上课铃后，更具体的有些教师会去上课，有些则是在办公室呆着。而`Student`在听到上课铃声后，会回到自己的班级去，而`Parent`听到铃声，只有到周五或者周六最后一节课才会知晓`Student`放学了；
>
> ![image-20250602110226898](./images/image-20250602110226898.png)
>
> 而`has-a`是一种组合关系，就是类包裹类，也称作聚合（Aggregation），通过组合得到新类所希望的功能。因为这是由于已经存在的类组成新类，所以称为组成组合关系，比如“在小汽车中有发动机”一样。
>
> 组合带来很大的灵活性，新类的成员对象通常是私有的，使用这个类的客户程序员不能访问它们。这种特点允许我们改变这些成员而不会干扰已存在的客户代码。我们还可以在运行时改变这些成员对象，动态地改变程序的行为。但是继承没有这种灵活性，因为编译器必须在用类继承方法创造的类上加入编译时限制。
>
> 因为继承在面向对象的程序设计中很重要，所以它常常得到高度重视，并且新程序员可能会产生在任何地方都是用继承的相关法。这回形成笨拙和极度复杂的涉及。实际上，当创建新类时，程序员应当首先考察组合，因为它更简单和更灵活。如果采用组合的方法，设计将变得清晰。一旦我们具备一些经验之后，就很能明显地知道什么时候需要采用继承方法。

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


> [!NOTE]
>
> 注意，在类外定义模板类的成员函数时，需要在函数定义前加上 `template <typename T>`，并且类名后需要跟上 `<T>`。

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

> [!NOTE]
>
> 假设我们有一个模板类用于存储和打印值：
> ```cpp
> template <typename T>
> class Print {
> public:
>     void print(T value) {
>         std::cout << value << std::endl;
>     }
> };
> ```
> 现在，我们希望为`std::string`类型提供一个特殊的实现，打印时加上引号：
> ```cpp
> #include <iostream>
> #include <string>
> 
> template <typename T>
> class Print {
> public:
>     void print(T value) {
>         std::cout << value << std::endl;
>     }
> };
> 
> // 全特化
> template <>
> class Print<std::string> {
> public:
>     void print(const std::string& value) {
>         std::cout << "\"" << value << "\"" << std::endl;
>     }
> };
> 
> int main() {
>     Print<int> p1;
>     p1.print(42);  // 调用普通模板类
> 
>     Print<std::string> p2;
>     p2.print("Hello, World!");  // 调用全特化版本
>     return 0;
> }
> ```
> **输出结果：**
>
> ```TEX
> 42
> "Hello, World!"
> ```

## 3.2 Partial Specialization

When only some of the template parameters are specialized, or when a specialization is made for a characteristic of a parameter (like being a pointer or reference), it's called partial specialization. The result of a partial specialization is still a template.

**Case 1: Multiple type parameters, some specialized**

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

**Case 2: Partial specialization for pointer types**

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

> [!NOTE]
>
> 假设我们有一个模板类用于存储两个值，现在希望为第二个参数为`int`时提供特殊实现：
> ```cpp
> #include <iostream>
> #include <string>
> 
> template <typename T, typename U>
> class Pair {
> public:
>     T first;
>     U second;
> 
>     void print() {
>         std::cout << first << ", " << second << std::endl;
>     }
> };
> 
> // 偏特化
> template <typename T>
> class Pair<T, int> {
> public:
>     T first;
>     int second;
> 
>     void print() {
>         std::cout << first << " (int) " << second << std::endl;
>     }
> };
> 
> int main() {
>     Pair<std::string, double> p1{"Hello", 3.14};
>     p1.print();  // 调用普通模板类
> 
>     Pair<std::string, int> p2{"World", 42};
>     p2.print();  // 调用偏特化版本
>     return 0;
> }
> ```
> **输出结果：**
>
> ```tex
> Hello, 3.14
> World (int) 42
> ```

## 3.3 Differences Between Function Template Specialization and Class Template Specialization

### 3.3.1. **Target**

- **Function Template Specialization**: Targets function templates to provide specialized function implementations.
- **Class Template Specialization**: Targets class templates to provide specialized class implementations.

### 3.3.2. **Syntax**

**Function Template Specialization**:

```cpp
template <>
return_type function_name<specific_type>(parameter_list);
```

**Class Template Specialization**:

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

### 3.3.3. **Use Cases**

**Function Template Specialization**: Used when you need to customize the behavior of a function for specific types.

**Class Template Specialization**:

- **Full Specialization**: Used when you need to provide a completely different implementation for a specific type combination.
- **Partial Specialization**: Used when you need to customize the implementation for a subset of types.

### 3.3.4. **Flexibility**

**Function Template Specialization**: Only allows customization of function behavior.

**Class Template Specialization**: Allows customization of both member variables and member functions, offering greater flexibility.

---

### 3.3.4. Summary

Function and class template specialization are powerful features in C++ that allow you to provide customized implementations for specific types. Here are the main differences and use cases:

| Feature                | Function Template Specialization                     | Class Template Specialization                     |
|------------------------|------------------------------------------------------|--------------------------------------------------|
| **Target**             | Function templates                                   | Class templates                                   |
| **Syntax**             | `template <> return_type function_name<type>()`      | Full: `template <> Class_name<type>`<br>Partial: `template <typename T> Class_name<T, specific_type>` |
| **Use Cases**          | Customizing function behavior for specific types     | Customizing class behavior for specific types     |
| **Flexibility**        | Only function behavior                               | Both member variables and functions               |
| **Priority**           | Specialized versions have the highest priority       | Specialized versions have the highest priority    |

Function and class template specialization are very useful in template programming, especially when dealing with special cases or optimizing performance. Using them wisely can enhance the flexibility and efficiency of your code, but it is important to avoid over-complicating the code structure.

#  Bringing it All Together & Comparison

## 4.1 Template Definition Location

Class templates and their member function templates should generally be declared and defined in header files (`.h` or `.hpp`). This is because the compiler needs to see the full definition of the template when it instantiates it.

## 4.2 Template vs. Inheritance

- **Templates**: Used to generate a set of classes where the object type does not affect the functional behavior of the class (i.e., the algorithm is generic, only the data type it operates on differs). Focuses on algorithmic generality.
- **Inheritance**: Used for a set of classes where the object type *does* affect the functional behavior of the class (via virtual functions for polymorphism). Focuses on achieving different behaviors through a common interface.

# Exercises

## Exercise 1

The declarations of `Point` class and `Line` class are as follows. **Implement the member functions of these two classes and then run the program to test the classes**.

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
int main() {
      Point a(8, 9),b(1,2);
      Point c = a;
      // ... output coordinates of points a, b, c ...
      Line line1(a, b);
      // ... output distance of line1 ...
      Line line2(line1);
      // ... output distance of line2 ...
     return 0;
}
```

**Hint**: The constructor of `Line` needs to calculate the distance between the two points and store it in the `distance` member. Distance formula: `sqrt((x2-x1)^2 + (y2-y1)^2)`.

**Implement:**

```cpp
/**Point.h*/
#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <cmath>

class Point {
private:
     double x, y;

 public:
     Point(double newX, double newY) ;
	
     Point(const Point& p);

     double getX() const; 	
     double getY() const; 	

};

class Line{
private:
     Point p1, p2;
     double distance;

public:
     Line(Point xp1, Point xp2);
     Line(const Line& q);
     double getDistance() const;
};

#endif // POINT_H

/**Point.cpp*/
#include "Point.h"

Point::Point(double newX, double newY) : x(newX), y(newY) {}
Point::Point(const Point& p) : x(p.x), y(p.y) {}
double Point::getX() const {
     return x;
}
double Point::getY() const {
     return y;
}

Line::Line(Point xp1, Point xp2) : p1(xp1), p2(xp2) {
     double dx = p2.getX() - p1.getX();
     double dy = p2.getY() - p1.getY();
     distance = sqrt(dx * dx + dy * dy);
}

Line::Line(const Line& q) : p1(q.p1), p2(q.p2), distance(q.distance) {}

double Line::getDistance() const {
     return distance;
}
/**main.cpp*/
#include <iostream>
#include <cmath>
#include "Point.h"

int main(){
     Point a(8, 9),b(1,2);
     Point c = a;
     std::cout << "point a: x = " << a.getX() << ", y = " << a.getY() << std::endl;
     std::cout << "point b: x = " << b.getX() << ", y = " << b.getY() << std::endl;
     std::cout << "point c: x = " << c.getX() << ", y = " << c.getY() << std::endl;

     std::cout << "------------------------------------------" << std::endl;
     Line line1(a, b);
     std::cout << "line1's distance:" << line1.getDistance() << std::endl;

     Line line2(line1);
     std::cout << "line2's distance:" << line2.getDistance() << std::endl;

     std::cout << "------------------------------------------" << std::endl;

     return 0;
}

```



## Exercise 2

A template class named `Pair` is defined as follows. Please implement the overloaded `operator<` which compares the value of the `key`. If `this->key` is smaller than `p.key`, return `true`. Then define a friend function to overload the `<<` operator which displays the `Pair`’s data members. Finally, run the program. The output sample is as follows.

```cpp
#include <iostream>
#include <string>
using namespace std;
template <class T1,class T2>
class Pair{
public:
    T1 key; 
    T2 value; 
    Pair(T1 k,T2 v):key(k),value(v) { };
    bool operator < (const Pair<T1,T2> & p) const;
};

int main(){

    Pair<string,int> one("Tom",19); 
    Pair<string,int> two("Alice",20);

    if(one < two){
        cout << one;
    }
    else{
        cout << two;
    }

    return 0;
}
```

**Implement**:

```cpp
#include <iostream>
#include <string>
using namespace std;
template <class T1,class T2>
class Pair{
public:
    T1 key;
    T2 value;
    Pair(T1 k,T2 v):key(k),value(v) { };
    bool operator < (const Pair<T1,T2> & p) const;

    // Declare the friend function for operator<<
    template <class U1, class U2>
    friend ostream& operator<<(ostream& os, const Pair<U1, U2>& p);
};

template <class T1,class T2>
bool Pair<T1,T2>::operator < (const Pair<T1,T2> & p) const {
    return key < p.key;
}

// Define the operator<< function
template <class T1, class T2>
ostream& operator<<(ostream& os, const Pair<T1, T2>& p) {
    os << "Key: " << p.key << ", Value: " << p.value << endl;
    return os;
}

int main(){

    Pair<string,int> one("Tom",19); 
    Pair<string,int> two("Alice",20);

    if(one < two){
        cout << one;
    }
    else{
        cout << two;
    }

    return 0;
}

```



## Exercise 3

There is a definition of a template class `Dictionary`. Please write a template partial specialization for the `Dictionary` class where the `Key` is specified to be `int`. In this specialized version, add a member function named `sort()` which sorts the elements in the dictionary in ascending order (based on keys). Finally, run the program. The output sample is as follows.

```cpp

template <class Key, class Value> 
class Dictionary {
    Key* keys;
    Value* values;
    int size;
    int max_size;
public:
    Dictionary(int initial_size) :   size(0) {
        max_size = 1;
        while (initial_size >= max_size)
        max_size *= 2;
        keys = new Key[max_size];
        values = new Value[max_size];
    }
    void add(Key key, Value value) {
        Key* tmpKey;
        Value* tmpVal;
        if (size + 1 >= max_size) {
        max_size *= 2;
        tmpKey = new Key [max_size];
        tmpVal = new Value [max_size];
        for (int i = 0; i < size; i++) {
            tmpKey[i] = keys[i];
            tmpVal[i] = values[i];
        }
        tmpKey[size] = key;
        tmpVal[size] = value;
        delete[] keys;
        delete[] values;
        keys = tmpKey;
        values = tmpVal;
        }
        else {
        keys[size] = key;
        values[size] = value;
        }
        size++;
    }
    void print() {
        for (int i = 0; i < size; i++)
        cout << "{" << keys[i] << ", " << values[i] << "}" << endl;
    }

    ~Dictionary()
    {
        delete[] keys;
        delete[] values;
    }

};

int main() {
    Dictionary<const char*, const char*> dict(10);
    dict.print();
    dict.add("apple", "fruit");
    dict.add("banana", "fruit");
    dict.add("dog", "animal");
    dict.print();
    Dictionary<int, const char*> dict_specialized(10);
    dict_specialized.print();
    dict_specialized.add(100, "apple");
    dict_specialized.add(101, "banana");
    dict_specialized.add(103, "dog");
    dict_specialized.add(89, "cat");
    dict_specialized.print();
    dict_specialized.sort();
    cout << endl << "Sorted list:" << endl;
    dict_specialized.print();
    return 0;
}
```

**Implement:**

```cpp
void sort(){
    for (int i=0;i<size-1;i++){
        for (int j=i+1;j<size;j++){
            if (keys[i] > keys[j]){
                Key tmpKey = keys[i];
                Value tmpVal = values[i];
                keys[i] = keys[j];
                values[i] = values[j];
                keys[j] = tmpKey;
                values[j] = tmpVal;
            }
        }
    }
}
```

output:

![image-20250602194622344](./images/image-20250602194622344.png)

---

*CC BY NC SA (Content adapted from course materials)*
