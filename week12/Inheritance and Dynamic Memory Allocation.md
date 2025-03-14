# Inheritance and Dynamic Memory Allocation

## Question

- If a `base` class uses `dynamic` memory allocation, and redefines a copy constructor and assignment operator

Case 1: If no `dynamic` memory allocation in the `derived` class, no special operations are needed

Case 2: if `dynamic` memory is allocated in the `derived` class, you should redefine a copy constructor and an assignment operator.

```cpp

class MyMap: pubic MyString
{
    char * keyname;
  public:
    MyMap(const char * key, const char * value)
    {
    ...
    }
    MyMap(const MyMap & mm): MyString(mm.buf_len, mm.characters)
    {
    //allocate memory for keyname
    //and hard copy from mm to *this
    }
    MyMap & operator=(const MyMap &mm)
    {
       MyString::operator=(mm);
       //allocate memory for keyname
       //and hard copy from mm to *this
       return *this;
    }
};

```