#include <iostream>

#define NDEBUG
/*** 
 * The NDEBUG is a macro that is used to control the behavior of the assert macro.
 * It must be defined before the inclusion of the <cassert> header file.
 * 
 * ****/

#include <cassert>

int main(int argc, char ** argv)
{
    //argv的第0个参数是应用程序名称，从第1个开始才是传递的参数
    assert( argc == 2);
    std::cout << "This is an assert example." << std::endl;
    return 0;
}


/****
 * 
 * while(0)是一个常见的技巧，常常与do { ... } while(0)结构一起使用。
 * 这种结构用于定义只执行一次的循环。while(0)保证了循环体内的代码只会执行一次，
 * 因为条件0是始终为假的。
 * 
* ***/