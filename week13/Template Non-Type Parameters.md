# Template Non-Type Parameters

**To declare a template**

```cpp
template < parameter-list > declaration 
```

- The parameters can be
    - type template parameters
    - template template parameters
    - non-type template parameters
    [x] integral types
    [x] floating-point type
    [x] pointer types
    [x] lvalue reference types
    [x] ...

Such as:
```cpp
vector<int> vec1;
vector<int,16> vec2;
//16 means the size of the vector,called non-type parameter
```



If we want to create a static matrix (no dynamic memory allocation inside)

```cpp
/* ***
 * It means that the matrix is not a dynamic memory allocation,
 * so it set up on the compile time.
 * 
 * Because the matrix is not a dynamic memory allocation,
 * so we donot allocate the memory on the heap.
 * and the matrix is a ~static~ memory allocation,
 * so we donot need to ~destruct~ the ~matrix~.
 * 
* ***/
template<typename T, size_t rows, size_t cols>
class Mat
{
    T data[rows][cols];
  public:
    Mat(){}
    T getElement(size_t r, size_t c);
    bool setElement(size_t r, size_t c, T value);
};
/***
 * If you wanna use it, you have to instantiate it,
 * 
 * ***/
```
