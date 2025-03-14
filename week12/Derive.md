# Derive
## Inheritance
- Inherit members (attributes and methods) from another class.
- **Base class**(Parent)
- **Derived class**(Child)

Such as:
```cpp
class Base{
    public:
    int a;
    int b;
};

class Derived:public Base{
    public:
    int c;
};
```

## Constructors
- To instantiate a derived class object
- Allocate memory
- Derived constructor is invoked
    - Base object is constructed by a base constructor
    - Member initializer list initializes members
    - To execute tthe body of the derived constructor
```cpp
class Derived : public Base {
   public:
   int c;
   Derived(int c):Base(c-2,c-1),c(c){
       cout<<"Derived constructor"<<endl;
   } 
}
```
if we not define the constructor, the compiler will define a default constructor for us(the constructor is the default constructor in the base class).

And if we wanna use the `same name function(Base's)` in `derived` class, we could use the `::` operator to access the base class function. It means we use the `base` class function.