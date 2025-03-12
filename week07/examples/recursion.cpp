#include <iostream>
using namespace std;

void div2(double val);

int main()
{
    div2(1024.); // call the recursive function
    return 0;
}

void div2(double val)
{

    cout << "Entering val = " << val << endl;
    if (val > 1.0)
        //StackOverFlow
        //递归函数的调用过程中，会在栈中开辟内存空间，栈的内存空间是有限的，
        //当递归函数的调用次数过多时，会导致栈溢出
        div2( val / 2); // function calls itself
    else
        cout << "--------------------------" << endl;
    
    cout << "Leaving  val = " << val << endl;
    //相当于函数调用到val=1 即会执行else那段语句，然后跳转到cout 输出leaving val，输出完了之后，函数执行完，
    //执行到val=2那一层，div2（2/2）语句执行完，然后跳转到cout
}
