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

## Topic Overview

- **Class in C++**:
    - Class constructor and destructor
    - Static member variables and static member functions
    - Const member variables and const member functions
    - `this` pointer
    - Class, object, member variable, member function, static variable & memory Management
- **Class in Python vs Class in C++**:
    - constructor and destructor
    - static members
    - const members
    - `self` pointer
- **Practice Exercises**

##  Foreword

Welcome to the Lab 9 study notes! This lab primarily introduces the basic concepts and usage of classes in C++, including constructors, destructors, static members, const members, and the `this` pointer. We will also compare the similarities and differences between classes in `C++` and `Python`.



#  C++ Class Basics

## 1.1 Static Member Variables

Static member variables are shared among all objects of a class. This means that no matter how many objects of the class are created, there is only one copy of the static member variable in memory.

- **Characteristics**:

    - Shared by all objects of the class.
    - Only one copy exists in memory.
    - Must be explicitly defined and initialized outside the class definition (unless it is `static const` of an integral or enumeration type, which can be initialized within the class).
    - Its name needs to be qualified with the class scope resolution operator `::`.

- **Definition and Initialization**:

    ```CPP
    // Declare in class definition
    class StaticTest {
    private:
        static int m_value; // Declare static member variable
    public:
        // ...
    };
    
    // Define and initialize static member variable outside class definition
    int StaticTest::m_value = 12;
    ```

    ![image-20250523155255197](./images/image-20250523155255197-1747992907410-10.png)

## 1.2 Static Member Functions

Static member functions can be called independently of any object of the class. A member function can only be declared as static if it does not access any non-static class members (i.e., it does not depend on members of a specific object).

- **Characteristics**:

    - Can be called directly using the class name, or through an object.
    - Cannot access non-static member variables or non-static member functions (because they do not have a `this` pointer).
    - Can access static member variables and other static member functions.
    - Declared using the `static` keyword.

- **Definition and Invocation**:

    ```CPP
    class StaticTest {
    private:
        static int m_value;
    public:
        static int getValue() { // Define static member function
            return m_value;
        }
    };
    int StaticTest::m_value = 12;
    
    // Invocation methods
    // StaticTest t;
    // int val1 = t.getValue(); // Call via object
    // int val2 = StaticTest::getValue(); // Call via class name
    ```

    ![image-20250523155306035](./images/image-20250523155306035-1747992907410-11.png)
    
    ![image-20250523155157647](./images/image-20250523155157647-1747992907410-12.png)
    
    > [!TIP]
    >
    > You can use **object** or **class** to access the **<u>static members</u>**.

## 1.3 Const Member Variables

The `const` keyword specifies that a variable's value is constant and tells the compiler to prevent the programmer from modifying it. If some member variables do not need to be modified during the object's lifetime, they can be defined as `const`.

- **Characteristics**:

    - Value cannot be modified after initialization.
    - Must be initialized in the constructor's member initializer list.

- **Definition and Initialization**:

    ```cpp
    class MyClass {
    private:
        const int x; // const member variable
    public:
        MyClass(int a) : x(a) { // Initialize const member via initializer list
            // constructor body
        }
        void show_x() {
             std::cout << "Value of constant x: " << x;
        }
    };
    ```

    ![image-20250523172826600](./images/image-20250523172826600.png)

- **Static Const Member Variable**:

    - If it's an integral or enumeration type, it can be initialized directly within the class definition.
    - Other types of `static const` member variables are usually initialized outside the class (but still declared inside).

    ~~~cpp
    class Person {
    private:
        static const int Len = 30; // In-class initialization for static const int
        char name[Len];
    public:
        // ...
    };
    
    //const int Person::Len;
    ~~~
    
    For non-integral types or those needing more complex initialization,define `static const` outside the class.
    
    `const int Person::Len;` 
    
    If **not** initialized in-class, **<u>define outside</u>**.
    
    Alternatively, an enumeration can be used to define an in-class constant:
    ```cpp
    class Person {
    private:
        enum { Len = 30 }; // Using enum to define a constant
        char name[Len];
    public:
        // ...
    };
    ```

## 1.4 Const Member Functions

A const member function promises not to modify any data members of the object that calls it (unless a member is declared `mutable`). The `const` modifier follows the function's parameter list.

- **Characteristics**:

    - The `const` keyword must be specified in both the function's declaration and definition (if defined outside the class).
    - Cannot modify non-static data members of the object.
    - Cannot call non-`const` member functions of the object.
    - Can be called by both `const` and non-`const` objects.

- **Definition**:

    ```cpp
    // complex.h
    class Complex {
    private:
        double real;
        double imag;
    public:
        // ...
        void Show() const; // Declare const member function
    };
    
    // complex.cpp
    
    void Complex::Show() const { // Define const member function
         std::cout << real << " + " << imag << "i" << std::endl;
    }
    ```

    ![image-20250523162045625](./images/image-20250523162045625-1747992907410-13.png)

## 1.5 `this` Pointer

Each class has only one copy of its member functions, but there can be many objects of that class. Each object can access its own address through a special pointer called `this`. The `this` pointer is passed by the compiler as an implicit argument to each of the object's non-static member functions.

- **Characteristics**:

    - Inside a **non-static** member function, the `this` pointer points to the object that invoked the member function.
    - `this` is a constant pointer; you **<u>CANNOT change</u>** the value of the `this` pointer itself, but you can modify the content of the object it points to (unless in a `const` member function).
    - Its type is `ClassName* const` (for non-`const` member functions) or `const ClassName* const` (for `const` member functions).
    - Often used to return a reference or pointer to the object itself, or to distinguish between member variables and parameters with the same name within a member function.

- **Usage Example**:

    ```cpp
    class Box {
        double length, breadth, height;
    public:
        Box(double length, double breadth, double height) {
            this->length = length; // Use this to distinguish member variable and parameter
            this->breadth = breadth;
            this->height = height;
        }
        Box& copy(const Box& rhs) {
            this->length = rhs.length;
            this->breadth = rhs.breadth;
            this->height = rhs.height;
            return *this; // Return a reference to the calling object
        }
    };
    
    ```

    ![image-20250523160137921](./images/image-20250523160137921-1747992907410-14.png)

#  C++ Class Constructors

A class constructor is a special member function used to create and initialize objects of the class.

- **Characteristics**:

    1. Has the exact **<u>same name</u>** as the class.
    2. Has **`no`** return type (not even `void`).
    3. Is typically a `public` member function of the class.
    4. Is **invoked automatically** whenever **<u>an object of that class is created</u>**.
    5. Can be overloaded (i.e., a class can have multiple constructors with the same name, but their parameter lists must differ).
    6. Can have default arguments.

- **Default Constructor**:

    - A constructor that takes no arguments, or one where all arguments have default values.
    - If the programmer provides **<u>no</u>** constructors for a class, the C++ **<u>compiler automatically generates a default constructor</u>**. This implicit default constructor does nothing (member variables are not initialized to specific values unless they have in-class initializers).
    - If the programmer defines any constructor (with or without parameters), the compiler will **<u>no longer automatically generate a default constructor</u>**. If a way to create an object without arguments is still needed, a default constructor must be explicitly defined.
    - A class can have only one default constructor.

- **Parameterized Constructor**:

    - Accepts parameters to initialize the object's data members.

- **Member Initialization List**:

    - Follows the constructor's parameter list, before the function body, starting with a colon `:`, used to initialize member variables.
    - Mandatory for `const` members, reference members, and member objects that do not have a default constructor.
    - Generally more efficient for other members than assignment within the constructor body.
    - The order of initialization is determined by the order in which members are declared in the class, not by their order in the initializer list.

    ```cpp
    class Box {
    private:
        double length;
        double breadth;
        double height;
    public:
        // Default constructor (using initializer list)
        Box() : length(3.0), breadth(4.0), height(5.0) {}
    
        // Parameterized constructor (using initializer list and this pointer)
        Box(double len, double bre, double hei) : length(len), breadth(bre), height(hei) {
            // Alternatively, assign in the function body: this->length = len; etc.
        }
    };
    
    ```

    ![image-20250523173037871](./images/image-20250523173037871.png)
    
- **Object Creation and Constructor Invocation**:

    ```CPP
    Box first(5.0, 6.0, 9.0); // Calls parameterized constructor
    Box second;            // Implicitly calls default constructor
    Box third = Box();      // Explicitly calls default constructor
    Box *pbox = new Box;     // Dynamically creates object, implicitly calls default constructor
    ```
    
    > [!CAUTION]
    >
    > `Box fourth();` declares a function `fourth` that returns a `Box` object, not an object named `fourth` created by the default constructor. 
    >
    > To create an object using the default constructor, do not use parentheses.
    
    > [!TIP]
    >
    > 参数化构造函数用于初始化对象时提供具体的参数。
    >
    > 默认构造函数用于在没有提供参数时初始化对象。
    >
    > 动态创建对象时，使用`new`操作符，会隐式调用默认构造函数。
    >
    > 显式调用默认构造函数可以通过`Box()`的形式实现。

# C++ Class Destructors

A class destructor is a special member function that is automatically called when an object of the class ceases to exist (e.g., when the object goes out of scope, or when a dynamically allocated object is deleted using `delete`). Destructors are typically used to perform cleanup tasks, such as releasing resources allocated by the object during its construction.

- **Characteristics**:
    1. The destructor's name is the class name preceded by a tilde `~` (e.g., `~Box`).
    2. Has no return type (not even `void`).
    3. Has no arguments.
    4. A class can have only one destructor.
    5. If the programmer does not provide a destructor, the compiler automatically generates a default destructor. This default destructor usually does nothing.
    6. Invoked when an object goes out of scope or `delete` is applied to a pointer to the object.
    7. Destructors cannot be overloaded.
- **Purpose**:
    - Release dynamically allocated memory.
    - Close files.
    - Release other system resources.

```cpp
class MyResource {
private:
    int* data;
public:
    MyResource(int size) {
        data = new int[size];
        // std::cout << "Resource allocated." << std::endl;
    }
    ~MyResource() { // Destructor
        delete[] data; // Release dynamically allocated memory
        // std::cout << "Resource deallocated." << std::endl;
    }
};
```

#  C++ Class vs. Python Class Comparison

| **Feature**                       | **C++**                                                      | **Python**                                                   |
| --------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **Access Control, Encapsulation** | Controls member access through `public`, `private`, and `protected`. | No strict access control; privacy is simulated through naming conventions (e.g., `_` or `__`). |
| **Constructors, Destructor**      | Explicitly define constructor (same name as class) and destructor (`~ClassName`), controllable memory release. | Use `__init__` constructor and `__del__` destructor, but `__del__` call is determined by garbage collection. |
| **Method invocation, self/this**  | Implicit use of `this` pointer without explicit declaration. | Methods need to explicitly declare the `self` parameter to represent the object itself. |
| **Static methods, class methods** | Directly declare static member functions.                    | Use `@staticmethod` or `@classmethod` decorators.            |
| **Dynamics, Metaprogramming**     | Class structure is fixed at compile time and cannot be dynamically modified. | Classes and objects can be dynamically modified (e.g., adding methods at runtime). |

![image-20250523173454946](./images/image-20250523173454946.png)

**Python Code Example Explanation (Demo(1) and Demo(2) from slides)**:

- Class variables are similar to static member variables in C++.
- `__init__` is the constructor, used to initialize member variables.
- The `@property` decorator can turn a method into a read-only attribute, partially similar to the effect of `const` members in C++.
- `__del__` is the destructor.
- Regular methods are member functions; the first parameter is typically `self`.
- The `@classmethod` decorator creates methods similar to static methods in C++, where the first parameter is the class itself (usually named `cls`).

#  Exercises

## Exercise 1

1. Can the program below be run successfully? Why?
2. Modify the program to:
    - 2-1) Fix the grammar errors.
    - 2-2) Make the function invoked by an object display the value of the `this` pointer and the member variable `id`.
    - 2-3) Make the function invoked by the class display the value of the static variable `num`.

You need to explain the reason to a TA to pass the test.

```cpp
#include<iostream>
using namespace std;
class Demo{
    private:
        int id;
        void display(){
        cout<<"this is: "<<this<<", id is:"<<this->id<<endl;
        }
    public :
        Demo(int cid){
        this->id=cid;
        }
    static int num; 
    void display()
    {
        cout<<"The value of the static num is: "<<num<<endl;
    }
}; 
int main() 
{
  Demo obj;
  Demo obj1(1);

  obj.display();
  obj1.display();

  Demo::display();

  return 0;
}

```

My implement：

```cpp
#include<iostream>
using namespace std;
class Demo{
private:
    int id;
public :
    Demo() : id(0){
        cout<<"Default constructor called"<<endl;
    }
    Demo(int cid){
        this->id=cid;
        cout<<"Parameterized constructor called"<<endl;
    }
    static int num; 
    static void display(){
        cout<<"The value of the static num is: "<<num++<<endl;
        // Note: A static function cannot access non-static members like 'this->id'
    }
};

int Demo::num = 10; // Definition and initialization of static member variable

int main() 
{
    Demo obj;
    Demo obj1(1);

    obj.display();
    obj1.display();

    Demo::display();

    return 0;
}

```

![image-20250523171023524](./images/image-20250523171023524-1747992907410-15.png)

## Exercise 2

What is the result of the program below? What happens if you uncomment the commented line in the `main()` function? Why? You need to explain the reason to a TA to pass the test.

```cpp
#include <iostream>
using namespace std;
class ConstMember
{
private:
  const int m_a;
public:
  ConstMember(int a) : m_a(a) {}
  void display() const
  {
    cout << "The value of the const member variable m_a is: " << m_a << endl;
  }
};

int main()
{
  ConstMember o1{666};
  ConstMember o2{42};
  o1.display();
  o2.display();
//  o1 = o2; // 如果o1=o2,表示值拷贝
  return 0;
}

```

The results:

![image-20250523171535132](./images/image-20250523171535132-1747992907410-16.png)

![image-20250523171622694](./images/image-20250523171622694-1747992907410-17.png)

> [!TIP]
>
> 编译器会尝试为 `ConstMember` 类生成一个默认的赋值运算符函数 (`operator=`)。
>
> 默认的赋值运算符会尝试逐成员赋值，即尝试执行 `o1.m_a = o2.m_a;`。
>
> 但是，`m_a` 是一个 `const` 成员变量，它的值在初始化后不能被修改。因此，对其进行赋值操作是非法的。

## Exercise 3

Define a class called Complex for performing arithmetic with complex numbers. Write a program to test your class. Complex numbers have the form realPart + imaginaryPart * i.

Use two member variables to represent the private data of the class. Provide a constructor that enables an object of this class to be initialized when it’s declared. The constructor should contain default values in case no initializers are provided. Provide public member functions that perform the following tasks:

- a) `add`—Adds two Complex numbers: The real parts are added together and the imaginary parts are added together.
- b) `subtract`—Subtracts two Complex numbers: The real part of the right operand is subtracted from the real part of the left operand, and the imaginary part of the right operand is subtracted from the imaginary part of the left operand.
- c) `display`—Displays a Complex number in the form of `a + bi` or `a - bi`, where `a` is the real part and `b` is the imaginary part.

> [!TIP]
>
> If a member function does not modify the member variables, define it as a `const` member function.

- **Class Definition**:

    ```cpp
    class Complex {
    private:
        double real;
        double imag;
    public:
        // Constructor (with default arguments)
        Complex(double re = 0.0, double im = 0.0);
    
        // Addition
        Complex add(const Complex& other) const;
    
        // Subtraction
        Complex subtract(const Complex& other) const;
    
        // Display (const member function)
        void display() const;
    };
    ```

- **Constructor Implementation**: Use a member initializer list.

- **`add` and `subtract` Implementation**: Create a new `Complex` object as the result and return it. These functions should be `const` as they don't modify the calling object.

- **`display` Implementation**: Pay attention to the output format, especially when the imaginary part is negative.

Click here to read these code.

![image-20250523172601189](./images/image-20250523172601189-1747992907410-18.png)

---

*CC BY NC SA (Content adapted from course materials)*
