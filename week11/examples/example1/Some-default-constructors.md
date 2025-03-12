# Some-default-constructors
## Default Constructors
- Default constructor: a constructor which can be called without any arguments.
- if you define no constructors, the compiler will define a default constructor for you.
    ```cpp
    MyTime::Mytime(){}
    ```
    ```tex
    MyTime mt;//no appropriate constructor for initialization
    ```
- if you define constructors, the compiler will not define a default constructor for you.
    ```cpp
    MyTime::Mytime(int h,int m){
        this->hours=h;
        this->minutes=m;
    }
    ```
    ```tex
    Mytime mt;//which constructor should be called?
    ```
- To avoid ambiguousity, you should define both constructors.
    ```cpp
    class Mytime{
        public:
            Mytime(){}
            Mytime(int h,int m=0){}
    }
    ```
## Implicity-defined Destructor
- if no default constructor is defined, you can't create an object without arguments.
    ```cpp
    Mytime::~Mytime(){}
    ```

- Memory allocated in constructor is normally released in destructor.


## Default Copy Constructors
- A copy constructors.Only one parameter, or the rest have default values
    ```cpp
    MyTime::MyTime(const MyTime& t){...}
    
    MyTime t1(1,59);
    MyTime t2=t1;//copy constructor
    MyTime t3(t1);//copy constructor
    ```
- Default copy constructor:
    - if no user-defined copy constructors,the compiler will define a default copy constructor for you.
    - Copy all non-static data members.


## Default Copy Assignment
- Assignment operators:=,+=,-=,...
- Copy assignment operator
    ```cpp
    Mytime & Mytime::operator=(const Mytime& t){...}

    MyTime t1(1,59);
    MyTime t2=t1;//copy constructor
    t2=t1;//copy assignment operator
    ```

- Default copy assignment operator
    - if no user-defined copy assignment operators,the compiler will define a default copy assignment operator for you.
    - Copy all non-static data members.

> [!tip]
> if we forget releasing the memory，there will be a memory leak.So in the next lecture, we will learn how to release the memory.
> [Dynamic-memory](../example2/an-example-with-dynamic-memory.md)