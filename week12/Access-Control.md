# Access-Control
## Member Access
- Public member
    - Accessible anywhere
- Private member
    - Only accessible within the class(Or describe that only accessible to the members and friends of that class)
```cpp
class Person {
private:
    int n; // private member
public:
    // this->n is accessible 
    Person(): n(10) {}
    // other.n is accessible and friends of that class
    Person(const Person& other) : n(other.n) {}
    // this->n is accessible
    void set(int n) {this->n = n;}
    // this->n and other.n are accessible
    void set(const Person& other) {this->n = other.n;}
 };
```

- Protected members
    - Accessible to the members and friends of that class
    - Accessible to the members and friends of the **derived** class 
```cpp
class Base 
{
  protected:
    int n;
  private:
    void foo1(Base& b)
    {
        n++; // Okay
        b.n++; // Okay
    }
};
```

```cpp
class Derived : public Base 
{
    void foo2(Base& b, Derived& d) 
    {
        n++; //Okay
        this->n++; //Okay
        //b.n++; //Error. 
        d.n++; //Okay
    }
};
```


```cpp

// a non-member non-friend function 
void compare(Base& b, Derived& d)
{
    // b.n++; // Error
    // d.n++; // Error
}
/****
 * 
 * As a drive class,if wanna visit the protected 
 * member function of the base class, we should use
 * the public member function of the base class,
 * or use the friend function of the base class,
 * or use the derived class's object to visit the
 * protected member function of the base class.
 *
 * ***/
```


### Complete Description

As a derived class, if we want to access the protected member function of the base class, we can do so in the following ways:

1. **Using the public member function of the base class:**  
   If the `base` class provides a `public` member function that internally calls the `protected` member function, the `derived` class can indirectly access the `protected` function by calling this `public` member function. This is the most common and safest approach as it maintains encapsulation and controls access to the `protected` members.

2. **Using the friend function of the base class:**  
   If the `base` class has a `friend` function, this `friend` function can directly access the `protected` members of the `base` class. The derived class can then call this `friend` function to access the `protected` member function. However, this approach is less recommended because `friend` functions break encapsulation and can lead to tighter coupling between classes.

3. **Accessing through an object of the derived class:**  
   If the `protected` member function is inherited by the `derived` class and is exposed (e.g., declared as `public` or accessed through `public` methods in the `derived` class), it can be accessed directly through an object of the `derived` class. This approach relies on the `derived` class properly managing the access permissions for the inherited members.

---

#### Example Code
```cpp
#include <iostream>
using namespace std;

class Base {
protected:
    void protectedFunction() {
        cout << "Protected function in Base" << endl;
    }
};

class Derived : public Base {
public:
    void callProtectedFunction() {
        protectedFunction();  // Derived class can directly access the protected member
    }
};

int main() {
    Derived obj;
    obj.callProtectedFunction();  // Accessing the protected function through a derived class object
    return 0;
}
```

#### Summary
- **Using the public member function of the base class:** The safest and most common approach.
- **Using the friend function of the base class:** Not recommended due to encapsulation concerns.
- **Accessing through a derived class object:** Feasible, but requires proper management of access permissions in the `derived` class.
## Public Inheritance
- Public members of the base class
    - Still be public in the `derived` class
    - Accessible anywhere
- Protected members of the base class
    - Still be protected in the `derived` class
    - Accessible in the `derived` class only
- `Private` members of the `base` class
Not accessible in the `derived` class

~~~cpp
class Derived : public Base 
{
    ...
}
~~~


## Protected Inheritance 
- Public members and protected members of the base class
    - Be protected in the derived class
    - Accessible in the derived class only
- Private members of the base class
    - Not accessible in the derived class
```cpp
class Derived : protect Base 
{
    ...
}
```

##  Private Inheritance

- Public members and protected members of the base class
    - Be private in the derived class
    - Accessible in the derived class only
- Private members of the base class
    - Not accessible in the derived class


