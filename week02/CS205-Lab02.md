---
title: CS205 Lab02 data types and arithmetic operators in C/C++
published: 2025-04-22
updated: 2025-04-23
description: 'Welcome to my CS205 lecture notes!'
image: ''
tags: [ComputerScience,ProgramDesign,Cpp,Ubuntu,Linux ]
category: 'ComputerScience''English'
draft: false 
lang: en
---

> [!TIP]
>
> Welcome to my CS205 lecture notes! Because the lecture is not in English, I will try my best to translate it.
>
> And at the same time, the `PPT`,`lab-file` also use the English,I will write **the English notes but not all.**

>[!NOTE]
>
>If you have a passion to konw more about the course, you can click the link below to learn more about the course.
>Read the repo.
>
>::github{repo="MongxinChan/CPP"}

#  C++ provides two methods to control the output formats

## 1.1 Using member functions of ios class

1.1.1 **`cout.setf()`**: The setf() function has two prototypes,the first one is:

​	` cout.set(fmtflags);`

![image-20250422104606826](./images/ios_baseSetf.png)

![image-20250422104714487](./images/ios_baseSetf2.png)

The second one is:

​	`cout.set(fmtflags,fmtflags);`

![image-20250422104909301](./images/ios_baseSetf3.png)

1.1.2. **`cout.width(len)`**:set the field width

1.1.3.**` cout.fill(ch)`** :fill character to be used with justified field

1.1.4.**``cout.precision(p)`** :set the precision of floating-point numbers

```cpp
#include <iostream>
using namespace std;

int main()
{
    //cout.setf(ios_base::fixed, ios_base::floatfield);
    cout << 56.8 << endl;
    cout.width(12);
    cout.fill('+');
    cout << 456.77 << endl;

    cout.precision(2);
    cout << 123.356 << endl;
    cout.precision(5);
    cout << 3897.678485 << endl;

    return 0;
}
```

Output-result:

```tex
56.8
+++++456.77
1.2e+02
3897.7
```

> [!tip]
>
> we see the `significant digits`

Using the ios-class

```cpp
#include <iostream>
using namespace std;

int main()
{
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout << 56.8 << endl;
    
    cout.width(12);	//set 12 digits
    cout.fill('+');	//fill the '+' in the front of the number
    cout << 456.77 << endl;

    cout.precision(2);
    cout << 123.356 << endl;
    cout.precision(5);
    cout << 3897.678485 << endl;

    return 0;
}
```

Output-result:

```tex
56.800000 	//normally print the float style
++456.770000//the digits is 12 and fill "+" in not more than 12
123.36
3897.67848
```

> [!TIP]
>
> we see the  `precision of floating number`

C++ <u>**offers several manipulator**</u>s to invoke setf(),automatically supplying the right arguments.

![image-20250422221256284](./images/ios_baseSetf4.png)

![image-20250422221300145](./images/ios_baseSetf5.png)

## 1.2 Using iomanip manipulators

`#include <iomanip>`

1. setw(p)   2. setfill(ch)   3. setprecision(d)

```CPP
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout << 56.8 << setw(12) << setfill('#') << 456.77 << endl;

    cout << left;
    cout << setw(12) << setprecision(2) << 123.356 << endl;
    cout << setw(12) << setprecision(5) << 3897.6784385 << endl;

    cout << right;
    cout << setw(12) << setfill(' ') << 123.356 << endl;
    cout << setw(12) << setfill(' ') << 3897.6784385 << endl;

    cout.unsetf(ios_base::fixed);
    cout << 56.8 << setw(12) << setfill('$') << 456.77 << endl;

    return 0;
}
```

## 1.3 `printf()` vs `cout`

Which one do you prefer? 

```CPP
int a=1234;
float f=123.456;
char ch='a';
printf("%7d,%2d\n",a,a);
printf("%f,%8.1f,%.2f,%.2e",f,f,f,f);
printf("%3c\n",ch);
```


>[!TIP]
>
>在设定输出格式时，如果并不复杂可以用cout，否则用printf，由于cout和print并不是属于同一个输出流，如果混用会容易超时，所以一般只采用一种输入输出格式。
>
>printf()是C语言的标准输出函数，而cout是C++的标准输出函数。
>
# Debug C/C++ by using gdb in VScode

## 2.1 Install "gdb" (the debug tool of C/C++)

- using cmd "**which** **gdb**" to check whether gdb is installed or no

    1. if you wanna **update** package list,using it:

        ```bash
        sudo apt undate
        ```
    
        ![image-20250422222533620](./images/debuggingUsingGdb.png)
    
    2. if you wanna **insatll** gdb, using it:
    
        ~~~bash
        sudo apt install gdb
        ~~~
    
    3. üIf the installation directory of gdb is displayed after running command "**which** **gdb**" is executed, it means that gdb has been successfully installed.
    
        Like:
        ![image-20250422222422877](./images/debuggingUsingGdb2.png)
    

## 2.2 configure VSCode for using gdb to debug C/C++ code

- create and edit `".vscode"` folder and json files

    1. create a new folder named `".vscode"` in the directory of C/C++ codes

    2. create a new json file named `"launch.json"` in the ".vscode" folder which is created in step1

        - edit “launch.json” to set gdb for debugging the execute file which is created by “g++ -g" / “gcc -g”
        - tips: option “-g” used with gcc/g++ is to generate information for debugging while compiling the C/C++ source code.

        ~~~json
        {
            "version": "0.2.0",
            "configurations": [
                {
                    "name": "(gdb) Launch",
                    "type": "cppdbg",
                    "request": "launch",
                    "program": "${fileDirname}/${fileBasenameNoExtension}",
                    "args": [],
                    "stopAtEntry": false,
                    "cwd": "${workspaceFolder}",
                    "environment": [],
                    "externalConsole": false,
                    "MIMode": "gdb",
                    "setupCommands": [
                        {
                            "description": "Enable pretty-printing for gdb",
                            "text": "-enable-pretty-printing",
                            "ignoreFailures": true
                        },
                        {
                            "description": "Set Disassembly Flavor to Intel",
                            "text": "-gdb-set disassembly-flavor intel",
                            "ignoreFailures": true
                        }
                    ]
                }
            ]
        }
        ~~~


## 2.3 lunch gdb to debug in VS Code by "Run and Debug"

- Compile the source code with "-g" option to generate information for debug and generate the executable file

    ![image-20250427150150671](./images/optionToGenerate.png)

    and you just click here:![image-20250427150040865](./images/debug.png)

## 2.4 Set "BreakPoint" on source file, lunch gdb to run and debug

![image-20250427150322747](./images/setBreakPoint.png)

## 2.5 View the data stored in a variable by gdb(optional)

- During debugging, you can use GDB commands to view the data stored in variable(s).
    - step1. choose “DEBUG CONSOLE” window.
    - step2. run the command in command line in the  “DEBUG CONSOLE” window.
        - exec [gdb command] in vscode
    - step3. View the results after executing the command in the “DEBUG CONSOLE” window.

![image-20250427150452120](./images/viewTheDataStored.png)

## 2.6 Examine

Using the command x (for “examine”) to examine memory in any of several formats, independently of your program’s data types.

```cpp
#include<iostream>

using namespace std;
int main(){
    cout<<"sizeof(char:)"<<sizeof char<<" byte(s)"<<endl;
    char x=0xFF;
    char y='b';
    char z='B';
    return 0;
}
```

we could use the command to make x equals some variable:

```bash
-exec x /1xb &x
0x7fffffffd50d:	0xff
-exec x /1tb &x
0x7fffffffd50d:	11111111
-exec x /1ob &x
0x7fffffffd50d:	0377
-exec x /1db &x
0x7fffffffd50d:	-1
-exec x /1ub &x
0x7fffffffd50d:	255
```

![image-20250427152752336](./images/terminalX.png)

- x /nfu addr
    - n, the repeat count
    - f, the display format
    - u, the unit size 



# Data type conversions and calculations

## 3.1 data storage: integer vs float

```cpp
#include<iostream>
#include<iomanip>

using namespace std;

int main(){
    int x=1;
    float y=1;
    cout<<"sizeof x:"<<sizeof(x)<<" byte(s),"<<"sizeof y"<<sizeof(y)<<" bytes(s)\n";
    //如果把它应用于一个类型，必须要像上面所示的那样使用括号，但是如果对一个变量使用它，可以不要括号。
    return 0;
}
```

![image-20250427155034241](./images/theImplementsDetails.png)

![image-20250427155045494](./images/theTerminationOfSize.png)

## 3.2 Signed vs Unsigned

- Integer promotions of Implicit conversions

```cpp
#include <stdio.h>

int main(){
    char x=0xff;
    unsigned char y=0xff;
    printf("x: 0x%x, %d , %u\n",x,x,x);
    printf("y: 0x%x, %d , %u\n",y,y,y);

    printf("x>>2: 0x%x, %d , %u\n",x>>2,x>>2,x>>2);
    printf("y>>2: 0x%x, %d , %u\n",y>>2,y>>2,y>>2);
    return 0;
}
```

![image-20250427155317317](./images/differentUnsignedAndSigned.png)

#  Exerices

## 4.1 Compile and run the following program

Whta's the result?

```cpp
#include <stdio.h> 
int main()
{
    signed char a = 127;
    unsigned char b = 0x7f; 
    char c = 0x7f;

    a=a<<1;
    b=b<<1;
    c=c<<1;            printf("a=%x\nb=%x\nc=%x\n",a,b,c);
    printf("a=%d\nb=%d\nc=%d\n",a,b,c);
    a=a>>1;
    b=b>>1;
    c=c>>1;
printf("a=%x\nb=%x\nc=%x\n",a,b,c);
    printf("a=%d\nb=%d\nc=%d\n",a,b,c);

    return 0;
}
```

**You need to explain the reason to a SA to pass the test.**

## 4.2 Write a program to calculate integer multiplication: 56789 * 23456789

then print the result. Verify the result using a calculator.

If the result is wrong, what could be the reason? 

How to get the correct result for this exercise?

**It's my implement of mutiplication:** using the `long long int`,because there're 32 bit in `int` type,and the range of the `int` type is $-2^{31}$ ~ $2^{31}-1$. And there're 64 bit in`long long int`,the MAX value around $9*10^{18}$

## 4.3 Run the following source code and explain the result.

Then using the method learnt in lecture2 to make the output of the code same as following picture .

```cpp
#include <iostream>  //file name: lab3_p4_3.cpp
using namespace std;

int main() 
{
    cout << fixed;
    float f1 = 1.0f;
    cout<<"f1 = "<<f1<<endl;

    float a = 0.1f;
    float f2 = a+a+a+a+a+a+a+a+a+a;
    cout<<"f2 = "<<f2<<endl;
    
    if(f1 == f2)  //TIPS: Modify the code here
        cout << "f1 == f2" << endl;
    else
        cout << "f1 != f2" << endl;

    return 0;
}

```

> [!NOTE]
>
> **DO NOT** use `if (f1=f2)` instead of `if(f1==f2)`.

**It's my answer:**When with the float and double type,It's a matter of accuracy, **which means that computers can also deceive humans**.

## 4.4 Complete the following source code to print the variables as the following picture and explain the result.

Why the value of a and b are not equal? Explain the division operation with different types.

You need to explain the reason to a SA to pass the test.

```cpp
#include <iostream>
using namespace std;

int main()
{
    int a, b;
    double c, d,f,g;
    char h;

    a = 19.99 + 21.99;
    b = (int)19.99 + 21.99;
    c = 23 / 3;
    d = 23 / 3.0;
    f = 23 / 3.0e4;
    g = 23 / 3.0e5;
    h = 'b' - 32;

    //complete code here
    return 0;   
}

```

**My answer:**

When you use `(int)x`,it means the x will be explicit conversed to `int` type,and the `19.99` will be the `19`. Different the precision of division will effect on the result.

## 4.5 What is the output of the code as follows? What is the meaning of **auto** when defines a variable in C++?

You need to explain the reason to a SA to pass the test.

```cpp
#include <iostream> 

int main()
{
    auto a = 10;
    a = 20.5;
    a += 10.5;
    std::cout << a << std::endl;

    auto b=10.0;
    b = 20.5;
    b +=a;
    std::cout << b << std::endl;

    return 0;
    
}

```

**My answer**:

Because the `auto` type means **automatic recognize the type**,and the `a` is recognized the `int`,but the `b` is recogfnized the `float`,and the different  type operation between `float` and `int` output the `float+`
