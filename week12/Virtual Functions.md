# Virtual Functions

Let’s look at the example first, what will be the output?

```cpp
class Person
{
  public:
    void print()
    {
        cout << "Name: " << name << endl;
    }
};
class Student: public Person
{
  public:
    void print()
    {
        cout << "Name: " << name;
        cout << ". ID: " << id << endl;
    }
};

```

if you wanna visit the complete code you can [click here](./examples/virtual.cpp)

## `Virtual` Functions implementation

- But if we define print() function as a virtual function, the output will be different.
- **Static binding**: the compiler decides which function to call
  -We notice the `reference` if we just use `Person` to define the object, the `print()` function will be called.
  -If we use `Student` to define the object, the `print()` function will be called.
- **Dynamic binding**: the called function is decided at runtime.
  - We notice the `statement` if we just use `Person` to define the object, the `print()` function will be called.
  - If we use `Student` to define the object, the `print()` function will be called.

- Keyword virtual makes the function virtual for the base and all derived classes.


### Static Binding vs. Dynamic Binding

#### Static Binding

Static binding (also known as early binding) occurs when the compiler determines which function to call at compile time. This is typically the case with non-virtual functions in C++.

- **Example:**

  ```cpp
  class Person {
  public:
      void print() {
          cout << "Person::print()" << endl;
      }
  };

  class Student : public Person {
  public:
      void print() {
          cout << "Student::print()" << endl;
      }
  };

  int main() {
      Person p;
      Student s;

      p.print();  // Calls Person::print()
      s.print();  // Calls Student::print()
  }
  ```

- **Explanation:**
  - When we use `Person` to define the object (`Person p;`), the `Person::print()` function is called.
  - When we use `Student` to define the object (`Student s;`), the `Student::print()` function is called.
  - This behavior is due to static binding, where the compiler resolves the function call based on the declared type of the object.

#### Dynamic Binding

Dynamic binding (also known as late binding) occurs when the called function is determined at runtime. This is achieved using virtual functions in C++.

- **Example:**

  ```cpp
  class Person {
  public:
      virtual void print() {
          cout << "Person::print()" << endl;
      }
  };

  class Student : public Person {
  public:
      void print() override {
          cout << "Student::print()" << endl;
      }
  };

  int main() {
      Person* p1 = new Person();
      Person* p2 = new Student();

      p1->print();  // Calls Person::print()
      p2->print();  // Calls Student::print()
  }
  ```

- **Explanation:**
  - When we use `Person` to define the object (`Person* p1 = new Person();`), the `Person::print()` function is called.
  - When we use `Student` to define the object (`Person* p2 = new Student();`), the `Student::print()` function is called.
  - This behavior is due to dynamic binding, where the actual function called is determined at runtime based on the object's actual type, not just its declared type.

### Corrected and Complete Description

- **Static Binding**: The compiler decides which function to call based on the declared type of the object.
  - If we use `Person` to define the object, the `Person::print()` function will be called.
  - If we use `Student` to define the object, the `Student::print()` function will be called.
  
- **Dynamic Binding**: The called function is decided at runtime based on the actual type of the object.
  - If we use `Person` to define the object (e.g., `Person* p = new Person();`), the `Person::print()` function will be called.
  - If we use `Student` to define the object (e.g., `Person* p = new Student();`), the `Student::print()` function will be called.

---

### Summary

- **Static Binding**: The function call is resolved at compile time based on the declared type of the object.
- **Dynamic Binding**: The function call is resolved at runtime based on the actual type of the object, using virtual functions.


>[!tip]
>
> If you notcied the `virtual void print()=0`, it means the function is pure virtual function, **which means the function is *not* implemented in the `base` class, but it is *implemented* in the `derived` class.**
>
> Yep,You found that the `Person2` is the `base` class,it only is used to herit for the `derived` class.
>
> In `Cpp` language, the `pure virtual function` is used to define the `interface` for the `derived` class.
---

## Virtual Destructors

If a destructor is not virtual, only the destructor of the base class is executed in the follow examples.
If we not use the `virtual` in the base class, the `derived` class will not be destructed , which will cause the memory leak.

```cpp
Person * p = new Student("xue", "2020");
p->print(); 
...
...
delete p; //if its destructor is not virtual
```

so the `destructor` must be `virtual` function.

```cpp
class Person {
public:
    virtual ~Person() {
        // the virtual base class destructor
    }
};
```
