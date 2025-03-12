# Hard Copy&Soft Copy & smart pointer
## Solution 1:Hard Copy
- Provide a user-define copy constructor and copy assignment operator.
    ```cpp
    Mystring::Mystring(const Mystring& str){
        this->buf_len=0
        this->characters=NULL;
        create(str.buf_len,str.characters);
    }
    ```
- `create()` release the current memory and allocate a new one.
- `this->characters` will not point to `str.characters`, but a new memory.
- It's a hard copy.
### Copy Assignment
- Provide a user-defined copy assignment.
    ```cpp
    Mystring&operator=(const Mystring& str){
        create(str.buf_len,str.characters);
        return *this;
    }
    ```
    if you wanna understand the example ,you could visit the [example2-mystring.hpp](./example2/mystring.hpp)
    we use the `create()` function to release the current memory and allocate a new one.

### Problems of Hard Copy
- Frequently allocate and free memory.
- Time consuming when the memory is big.

But ...
- if serval objects share the same memory, who should release it?

## CvMat struct

```cpp
typedef struct CvMat{
   int type;
   int setp;
   
   int * refcount;
   int hdr_refcount;

   union{
    uchar* ptr;
    short* s;
    int * i;
    float * fl;
    double * db;
   }data;
   //union is a data type that can hold different types of data.
   //it's like a switch statement.
   //阅后即焚
};
```


```cpp
class CV_EXPORTS Mat{
    public:
        //...
        int flag;

        int dims;

        int rows,cols;

        uchar* data;

        //! interaction with UMat
        UMatData* u;
        //we see the data and u allocated at the same time;
        //we could consider that : they're a pair.



        MatSize size;
        MatStep step;
};
```

### Solution in OpenCV
<img src="C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250312235915134.png" alt="image-20250312235915134" style="zoom:50%;" />
- The allocated memory can be used by multiple object.
- Mat::u->refcount is used to count the times the memory is referenced
- CV_XADD:macro for atomic add.





- Copy constructor of cv::Mat

<img src="C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250313000155410.png" alt="image-20250313000155410" style="zoom:50%;" />



<img src="C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250313000243864.png" alt="image-20250313000243864" style="zoom:50%;" />

## Smart pointers

### std::shared_ptr

- Smart pointers are used to make sure that an object can be deleted when 
it is no longer used. 
- Several shared pointers can share/point to the same object.
- The object is destroyed when no shared_ptr points to it.
    ```cpp
    std::shared_ptr<MyTime>mt1(new MyTime(10));
    std::shared_ptr<MyTime>mt2=mt1;

    auto mt1=std::make_shared<MyTime>(1,70);
    ```

### std::unique_ptr

- Different from shared_ptr,a std::unique_ptr will point to an object,and not allow others to point to.
- But an object pointed by a std::unique_ptr can be moved to another std::unique_ptr.
    ```cpp
    std::unique_ptr<MyTime> mt1(new MyTime(10));
    std::unique_ptr<MyTime> mt2 = std::make_unique<MyTime>(80); //c++17
    std::unique_ptr<MyTime> mt3 = std::move(mt1);
    ```
### How to understand Smart Pointers
- Let's look at their definitions.
    ```cpp
     template< class T > class shared_ptr;
    template<
    class T,
    class Deleter = std::default_delete
    <T>
    > class unique_ptr;
    ```
- mt1 and mt2 are two objects of type shared_ptr<>.
    - You can do a lot in the constructor and the destructor.
    ```cpp
    std::shared_ptr<MyTime>mt1(new MyTime(10));
    std::shared_ptr<MyTime> mt2=mt1;
    ```
    