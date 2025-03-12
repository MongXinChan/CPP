# An example with dynamic memory
This example shows how to use dynamic memory in a program.
The `Pointer` and `Memory` types are used to allocate and free memory, you do not konw that the environment of thr `C++`programing ,if you could not understand them how to work .
Not only remember allocated memory, you need to free it,but also you 
now I will show you an example with dynamic memory.
```cpp
class MyString{
    /***
    * we need to konw This code is super easy to mess up.
    * we use the char type,it may beyond the char array or
    * underflow, so we define the MyString type.
    ***/    
    int buf_len;
    char *characters;
public:
    MyString(int buf_len=64,const char*data =NULL){
        this->buf_len = 0;
        this->characters=NULL;
        create(buf_len,data);
        //notice the function-create is not a normal function,
        //means we use the allocated memory to create a string.
        //but the create function we use the static memory to create a string.
    }
    ~MyString(){
        delete[]this->characters;
        //at the end of the program, we need to free the memory.
        //we use the delete[] operator to free the memory.
        //The function serves to free the memory allocated , 
        // and decrease the mistake of memory leak. 
    }
    bool create(int buf_len,const char * data){

        //release();

        this->buf_len=buf_len;
        if(this->buf_len!=0){
            this->characters=new char[this->buf_len]{};
            if(data){
                strncpy(this->characters,data,this->buf_len);
            }
        }
        return true;
    }
    friend std::ostream & operator<<(std::ostream & os,const MyString& str){
        os<<"buf_len="<<str.buf_len;
        os<<",characters="<<static_cast<void>(str.characters);
        os<<" ["<<str.characters<<"]";
        return os;
    }
};
```
## Dynamic Memory in Objects
```cpp
MyString str1(10,"ShenZhen");
MyString str2=str1;
//the str2 will be the same as str1.
//but the str2 and str1 will use the same memory.
Mystring str3;
str3=str1;
//the str3 will be the same pointer as str1.

//so they will release the same memory thirce.
```
>[!tip]
> 当有指针作为数据成员时必须要自定义一个赋值构造函数和赋值运算符。
>这里已经没有内存释放了，因为str3释放了。
>eg：3个人都喜欢同一个女生，这个女生已经和第三个男的谈了的意思。

```cpp
    bool release(){
        this->buf_len = 0;
        if(this->characters!=NULL)
        {
            delete []this->characters;
            this->characters = NULL;
        }
        return 0;
    }
```