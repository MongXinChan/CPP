# C/C++ Program Design Summary

## Friend

### Friend Functions
- **Definition**: A friend function is defined outside the class. It does not require the class scope (`MyTime::`) before its function name.
- **Example**:
    ```cpp
    class MyTime {
        // ...
        public:
        friend MyTime operator+(int m, const MyTime &t);
    };
    MyTime operator+(int m, const MyTime &t) {
        return t + m;
    }
    ```
    if we wanna use the operator+ ,and the operator+ is a friend function, we can use the operator+ to add the int and the MyTime object.

### Friend Classes
- **Access**: A friend class can access all members of another class, including private members.
- **Visibility**: A friend class can be declared as public, protected, or private.
- **Example**:
    ```cpp
    class Sniper {
        private:
        int bullets;
        public:
        Sniper(int bullets = 0);
        friend class Supplier;
    };
    class Supplier {
        int storage;
        public:
        Supplier(int storage = 1000);
        bool provide(Sniper &sniper) {
            // Accessing private member bullets
            if (sniper.bullets < 20) // ...
        }
    };
    /**** 
     * 非继承关系的不同类之间，一方内部调用另一方的私有成员 
     * 父子不可以，好朋友可以
     *****/
    ```

### Friend Member Functions
- **Declaration**: A single member function of a class can be declared as a friend.
- **Declaration Problem**: Similar to a normal friend function, but with specific declaration requirements.
- **Example**:
    ```cpp
    class Supplier;// pre-declaration

    class Sniper {
        private:
        int bullets;
        public:
        Sniper(int bullets = 0) : bullets(bullets) {}
        friend bool Supplier::provide(Sniper &);
        /****
         * minimize the friend function's zone
         * if we wanna invoke the function, 
         * we need to declare the function before the class,
         ****/
    };
    ```
    and we use the form:
    ```cpp
        class Supplier{
        private:
            int storage;
        public:
            Supplier(int storage = 1000);
            bool provide(Sniper &sniper);
        };

    class Sniper {
        private:
        int bullets;
        public:
        Sniper(int bullets = 0) : bullets(bullets) {}
        friend bool Supplier::provide(Sniper &);
        /****
         * minimize the friend function's zone
         * if we wanna invoke the function, 
         * we need to declare the function before the class,
         ****/
    };

    bool Supplier::provide(Sniper &sniper) {
        if (sniper.bullets < 20) //...
    }
    ```
    As the lecture,I learn that we should distinguish the declaration and the definition ,**we prefer to separate them into two files.**


## Nested

### Nested Enumerations (C++11)
- **Scope**: An enumeration can be nested inside a class.
- **Access**: It can be accessed outside the class, but requires the class name scope qualifier.
- **Example**:
    ```cpp
    class Mat {
        public:
        enum DataType {
            TYPE8U, TYPE8S, TYPE32F, TYPE64F
        };
        private:
        DataType type;
        void *data;
        public:
        Mat(DataType type) : type(type), data(NULL) {}
        DataType getType() const { return type; }
    };
    ```
    - Access: `Mat::DataType::TYPE8U`

### Nested Classes
- **Definition**: A class can be declared inside another class.
- **Scope**:
    - **Private**: Only visible to the containing class.
    - **Protected**: Visible to the containing class and its derived classes.
    - **Public**: Visible to the containing class, its derived classes, and the outside world.
- **Example**:
    ```cpp
    class Storage {
        public:
        class Fruit {
            string name;
            int weight;
            public:
            Fruit(string name = "", int weight = 0);
            string getInfo();
        };
        private:
        Fruit fruit;
        public:
        Storage(Fruit f);
    };
    ```

## RTTI and Type Cast Operators

### Runtime Type Identification (RTTI)
- **Purpose**: Determine the type of an object at runtime.
- **Unsafe Conversion**: Explicit conversion of pointers to inappropriate types can be dangerous.
    ```cpp
    class Person;
    class Student : public Person;
    Person person("Yu");
    Student student("Sam", "20210212");
    Person *pp = &student;
    Student *ps = (Student *)&person; // Dangerous!
    ```

### Type Cast Operators
- **dynamic_cast**:
    - **Purpose**: Safely convert pointers or references of polymorphic types.
    - **Usage**: Invokes the correct version of a class method.
    - **Example**:
        ```cpp
        Person person("Yu");
        Student student("Sam", "20210212");
        Person *pp = NULL;
        Student *ps = NULL;
        ps = dynamic_cast<Student *>(&person); // NULL
        pp = dynamic_cast<Person *>(&student);
        ```
- **typeid operator**
    - determine whether two objects are the same type
    - Accept: the name of a class, an expression that evaluates to an object
- **type_info class**
    - The typeid operator returns a reference to a type_info object
    - Defined in the <typeinfo> header file
    - Comparing type using the overloaded == and != operators
        ```cpp
        typeid(Student) == typeid(Person); // false
        ```
- **dynamic_cast**
    - It can safely assign the address of an object to a pointer of a particular type.
    - Invoke the correct version of a class method (remember virtual functions)
    ```cpp
    Person person("Yu");
    Student student("Sam", "20210212");
    Person* pp = NULL;
    Student * ps = NULL; 
    ps = dynamic_cast<Student*>(&person); // NULL
    pp = dynamic_cast<Person*>(&student);
    ```

### More Type Operators

- Three more operators
    - const_cast: Type cast for const or volatile value

    - static_cast: 
        - It’s valid only if type_name can be converted implicitly to the same type that expression has, or vice versa
        - Otherwise, the type cast is an error
        ```cpp
        Base * pB = static_cast<Base*>(derived); //valid
        Derived * pD = static_cast<Derived*>(base); //valid
        UnRelated * pU = static_cast<UnRelated*>(base); //invalid
        ```
    - reinterpret_cast:
        - Converts between types by reinterpreting the underlying bit pattern.
        ```cpp
        int i = 18;
        float * p1 = reinterpret_cast<float *>(i); // static_cast will fail
        int * p2 = reinterpret_cast<int*>(p1);
        ```
