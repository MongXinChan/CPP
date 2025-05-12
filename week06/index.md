---
title: CS205 Lab6 static library, parameters
published: 2025-04-27
updated: 2025-04-28
description: '主要涉及静态库的编译，以及参数的传递'
image: ''
tags: [ComputerScience,ProgramDesign,Cpp,Ubuntu,Linux ]
category: 'ComputerScience-En'
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

> [!IMPORTANT]
>
> 由于本文篇幅过长，个人会添加适当的中文注解在里面。

**Introduction：**

Static library

- build
- use
- makefile
- CMake



Parameters of function

- pass by value
    - fundamental type
    - pointer
- pass by reference
- pass a huge structure vs pass its pointer



# Static library

**Static Linking and Static Libraries** (also known as an **archive**) is the result of the linker making copy of all used library functions to the executable file. Static Linking creates larger binary files, and need more space on disk and main memory. Examples of static libraries are, **.a** files in Linux and **.lib** files in Windows.

**Dynamic linking and Dynamic Libraries** Dynamic Linking doesn’t require the code to be copied, it is done by just placing name of the library in the binary file. The actual linking happens when the program is run, when both the binary file and the library are in memory. If multiple programs in the system link to the same dynamic link library, they all reference the library. Therefore, this library is shared by multiple programs and is called a "**shared library**" . Examples of Dynamic libraries are, **.so** in Linux and **`.dll`** in Windows.

<img src="D:\Manage\CPP\week06\images\image-20250506091745553.png" alt="image-20250506091745553" style="zoom:50%;" />

|                 | **advantages**                                               | **disadvantages**                                            |
| --------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Static Library  | 1. Make the executable has fewer  dependencies, has been packaged into the executable file.  <br />2. The link is completed in the  compilation stage, and the code is loaded quickly during execution. | 1. Make the executable file  **larger**.  <br />2. Being a library dependent on  another library will result in redundant copies because it must be **packaged  with the target file.**  <br />3. Upgrade is not convenient and  easy. The entire executable needs to be replaced and recompiled. |
| Dynamic Library | 1.Dynamic library can achieve  resource sharing between processes, there can be only one library file.  <br />2. The upgrade procedure is  simple, do not need to recompile. | 1. Loading during runtime will  slow down the execution speed of code. <br />2. Add program dependencies that  must be accompanied by an executable file. |

In this part,we focus on the static library.

## 1.1 build

[You can click here to read the code](https://github.com/MongXinChan/SUST-Cpp-course/tree/main/lab06/lab)

![image-20250506092331495](D:\Manage\CPP\week06\images\image-20250506092331495.png)

- In previous class we do the following:
- This will compile the “main.cpp” and “mymath.cpp” into “main”
- And then run “main”

```bash
g++ *.cpp -o main -std=c++11
./main
```

![image-20250506092622918](D:\Manage\CPP\week06\images\image-20250506092622918.png)

- A static library is created by **.o** file.
- Remember to use “**ar**” command with arguments “**-cr**” when building it.
- Now we should see **“libmymath.a”** in the current directory

```bash
g++ -c mymath.cpp
ls
ar -cr libmymath.a mymath.o
ls
```

![image-20250506093008943](D:\Manage\CPP\week06\images\image-20250506093008943.png)

Result:

![image-20250506093153253](D:\Manage\CPP\week06\images\image-20250506093153253.png)



## 1.2 use

- Now we can use “.a” static library.
- Let’s compile “main” again:

```bash
g++ main.cpp library.a --std=c++11
# There are three equivalent method :
g++ main.cpp -L -lmymath --std=c++11
# or
g++ -c main.cpp -std=c++11
# or
g++ main.o -L. -lmymath
```



![image-20250506093300713](D:\Manage\CPP\week06\images\image-20250506093300713.png)

- **-L**: indicates the directory of libraries
- **-l**: indicates the library name, the compiler can give the “**lib**” prefix to the library name and follows with **.a** as extension name.

## 1.3 makefile

![image-20250506094421596](D:\Manage\CPP\week06\images\image-20250506094421596.png)

```Makefile
# Makefile with static library

.PHONY: liba testliba clean

# 定义编译器
CC = gcc

# 定义静态库文件名
LIBFUN = libfun.a

# 默认目标
all: testliba

# 编译静态库
liba: $(LIBFUN)
$(LIBFUN): max.o min.o
	ar cr $@ $^

# 编译 max.o
max.o: max.c fun.h
	$(CC) -c max.c

# 编译 min.o
min.o: min.c fun.h
	$(CC) -c min.c

# 编译并链接 main.out
testliba: main.out
main.out: main.o $(LIBFUN)
	$(CC) -o $@ main.o -L. -lfun

# 编译 main.o
main.o: main.c fun.h
	$(CC) -c main.c

# 清理生成的文件
clean:
	rm -f *.o *.a main.out
```



![image-20250506094222507](D:\Manage\CPP\week06\images\image-20250506094222507.png)

```makefile
# makefile with all the .c files created static library

OBJ = $(patsubst %.c, %.o, $(wildcard ./*.c))
TARGET = libmyfun.a
CC = gcc

$(TARGET): $(OBJ)
	ar -r $@ $^

%.o : %.c
	$(CC) -c $^ -o $@

clean:
	rm -f *.o $(TARGET)
```



![image-20250506094309180](D:\Manage\CPP\week06\images\image-20250506094309180.png)



~~~makefile
#link with static library in makefile

OBJS = $(patsubst %.c, %.o, $(wildcard ./*.c))
TARGET = main
CC = gcc

LDFLAG = -L./lib_a
LIB = -lmyfun

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAG) $(LIB)

%.o : %.c
	$(CC) -c $^ -o $@

clean:
	rm -f *.o $(TARGET)
~~~



![image-20250506094313930](D:\Manage\CPP\week06\images\image-20250506094313930.png)

```MAKEFILE
$(TARGET): $(OBJS)
	$(CC) $(LIB) $(LDFLAG)  %^ -o $@
```



![image-20250506094323170](D:\Manage\CPP\week06\images\image-20250506094323170.png)

```MAKEFILE
lib_srcs := $(filter-out src/main.c, $(wildcard src/*.c))
lib_objs := $(patsubst %.c, %.o, $(lib_srcs))

include_path := ./include

I_options := $(include_path:%=-I%)

lib/%.o : src/%.c
    mkdir -p $(dir $@)
    gcc -c $^ -o $@ $(I_options)

lib/libmath.a : $(lib_objs)
    mkdir -p $(dir $@)
    ar -rc $^ -o $@ $^

static_lib : lib/libmath.a

clean :
    rm -rf ./lib

.PHONY : clean static_lib
```



![image-20250506094329584](D:\Manage\CPP\week06\images\image-20250506094329584.png)

```MAKEFILE
#============= Linking static library ==============
library_path := ./lib
linking_libs := math

I_options := $(linking_libs:%=-I%)
L_options := $(library_path:%=-L%)

linking_flags := $(I_options) $(L_options)

objs/main.o : src/main.c
    mkdir -p $(dir $@)
    gcc -c $^ -o $@ $(I_options)

objs/test : objs/main.o
    mkdir -p $(dir $@)
    gcc $^ -o $@ $(linking_flags)

run : objs/test
    ./$<

clean :
    rm -rf ./lib ./objs

.PHONY : clean static_lib run
```



## 1.4 CMake

We want to create a static(or dynamic) library by function.cpp and call the static library in main.cpp. This time we write two CMakeLists.txt files, one in **CmakeDemo4** folder and another in **lib** folder.

![image-20250511184053491](D:\Manage\CPP\week06\images\image-20250511184053491.png)

```makefile
# Search the source files in the current directory
# and store them in the variable SRC
aux_source_directory(. LIB_SRC)

# Create a static library named MyFunction
add_library(MyFunction STATIC ${LIB_SRC})
```

![image-20250511184109711](D:\Manage\CPP\week06\images\image-20250511184109711.png)

```makefile
# CMake minimum version
cmake_minimum-required(VERSION 3.10)

# Project name
project(CMakeDemo4)

# Search the source files in the current directory
# and store them in the variable DIR_SRCS
aux_source_directory(. DIR_SRCS)

# add the directory of include
include_directories(lib)

# Specify the subdirectory of lib
add_subdirectory(lib)

# Specify the build target
add_executable(CMakeDemo4 ${DIR_SRCS})

# Link the library to the executable
target_link_libraries(CMakeDemo4 MyFunction)

```



# Parameters of function

```cpp
#include<stdio.h>
int add1(int a,int b){
    int sum = (a++)+(b++);
    return sum;
}
int add2(int *x,int *y){
    int sum = ((*x)++)+((*y)++);
    return sum;
}
int add3(int &c,int &d){
    int sum = (c++)+(d++);
    return sum;
}
int main(){
    int i=0,j=0;
    scanf("%d",&i);
    scanf("%d",&j);
    printf("i_address:%p,j_address:%p\n",&i,&j);
    int sum=add1(i,j);
    printf("%d+%d=%d\n",i,j,sum);
    sum=add3(i,j);
    printf("%d+%d=%d\n",i,j,sum);
    return 0;
}

```

Q1. How to compile the source code on the left hand, by using gcc or g++ ?

Q2. Is there any compiling error on the source code, if no, compile it, if yes, correct and compile. 

Q3. What’s the output of this piece of code while input data is 1 and 2?

我们发现，得到的答案是：

![image-20250511184449060](D:\Manage\CPP\week06\images\image-20250511184449060.png)

这是由于值传递和址传递而导致的。

[如果你想看值传递和址传递，可以点击跳跃到我之前写的博客，这里不再赘述。](https://www.loners.site/posts/cpp-pointer-and-reference/)

## 2.1 pass a huge structure vs pass its pointer

- using “**g++ -S -o**” to generate assembly code based on **x64**. (The CPU of the testing machine is based on x64)
- In x64, register “**rsp**” is stack pointer.

here passing the value of a huge struct needs more stack space (1040+8+1032) than passing the value of a pointer which points the buge struct(16+1040). 

![image-20250512162905258](D:\Manage\CPP\week06\images\image-20250512162905258.png)

- using “aarch64-linux-gnu-g++ -S -o” to generate assembly code based on **ARM64**.
- In ARM64, register “**sp**” is stack pointer

```bash
aarch64-linux-gnu-g++ -S -o fdemo3-arm64.s fdemo3.c
cat fdemo3-arm64.s | grep sub | grep sp
```

```bash
aarch64-linux-gnu-g++ -S -o fdemo3_ptr-arm64.s fdemo3_ptr.c
cat fdemo3_ptr-arm64.s | grep sub | grep sp
```

here passing the value of the huge struct needs more stack space (2096) than passing the value of a pointer which points the buge struct(1056). 

![image-20250512163137542](D:\Manage\CPP\week06\images\image-20250512163137542.png)

- using “riscv64-linux-gnu-gcc -S -o” to generate assembly code based on **RISC-V64.**
- In **RISC-V64**, register “**sp**” is stack pointer.

```bash
riscv64-linux-gnu-gcc -S -o fdemo3-risc-v64.s fdemo3.c
cat fdemo3-risc-v64.s | grep addi | grep sp,-
```

```bash
riscv64-linux-gnu-gcc -S -o fdemo3_ptr-risc-v64.s fdemo3_ptr.c
cat fdemo3_ptr-risc-v64.s | grep addi | grep sp,-
```

here passing the value of the huge struct needs more stack space (16+64+2032) than passing the value of a pointer which points the buge struct(32+1056). 

![image-20250512163344162](D:\Manage\CPP\week06\images\image-20250512163344162.png)



# Exercise

## 3.1 Exercise 1

```cpp
#include <iostream>
using namespace std;
int * create_array(int size)
{
    int arr[size];
    for(int i = 0; i < size; i++)
        arr[i] = i * 10;
    return arr;
}
int main()
{
    int len = 16;
    int *ptr = create_array(len);
    for(int i = 0; i < len; i++)
        cout << ptr[i] << " ";
    return 0;
}

```

What compilation warnings occur when you compile the program? Why?

What will happen if you ignore the warning and run the program?

Fix bugs of the program and run it correctly without memory leak.

## 3.2 Exercise 2

Define a function that swaps two values of integers. Write a test program to call the function and display the result.

```cpp
#include <iostream>
using namespace std;

void swap1(int a,int b){
    int t=a;
    a=b;
    b=t;
}

void swap2(int &a ,int &b){
    int t=a;
    a=b;
    b=t;
}

int main(){
    int a=1,b=2;
    swap1(a,b);
    pirntf("swap1:%d %d\n",a,b);
    swap2(a,b);
    printf("swap2:%d %d\n",a,b);
    return 0;
}
```

You are required to compile the function into a static library “libswap.a”, and then compile and run your program with this static library.

点击这里，查看实现。

## 3.3 Exercise 3

3-1. Run the demo code on page 21 and 22, answer the questions on these pages. 

> Q1. Is the value of variable “x” same with the address of “i”? how about the value of “b” and the address of “j” ?
>
> Q2. Do variables x and y still exist after returning from the “add2” to the “main” ?
>
> Q3. Which following piece(s) of add2 would cause segment falut, or both ? Why?
>
> ```cpp
> //option A
> int add2(int*x,int*y){
>     int sum= ((*x)++)+((*y)++);
>     return sum;
>     free(x);
>     free(y);
>     x=NULL;
>     y=NULL;
> }
> 
> //option B
> int add2(int*x,int*y){
>     int sum= ((*x)++)+((*y)++);
> 	free(x);
>     free(y);
>     x=NULL;
>     y=NULL;    
> 	return sum;
> }
> ```
>
> ![image-20250512160815003](D:\Manage\CPP\week06\images\image-20250512160815003.png)
>
> Q1. Is the address of variable “c” same with the address of “i”? how about the address of “b” and the address of “j” ?
>
> Q2. For the following code “add3_x”, is the space of “e” belongs to heap or stack?
>
>  What’s the problem of the following code? Fix it and make the return value is 4. 
>
> ![image-20250512160821780](D:\Manage\CPP\week06\images\image-20250512160821780.png)
>
> ```cpp
> int add3_x(int &c,int &d){
>     int sum= (c++)+(d++);
>     int *e= (int*)malloc(sizeof(int));
>     c=*e;
>     d=*e;
>     *e=1;
>     sum= (c++)+(d++);
>     return sum;
> }
> ```

1. x的地址与i相同是由于x为址引用，同样的，b与j地址相同为传址。由于sum=(x++)+(y++),sum得到的只能是x+y的数值。`++`滞后说明完成sum的赋值操作后x与y各自加一。

2. 第一个小问与上一问一样，但是`add2()`需要在变量前加上`&`，才能解引用`*`;属于栈，用完后再释放;

    在给定的代码中，变量 `e` 是一个指向 `int` 的指针，它通过 `malloc` 函数分配了内存。`malloc` 函数用于**动态分配堆内存**，因此 `e` 指向的内存空间属于堆（heap）

    ```cpp
    int add3_x(int &c, int &d) {
        c++; // 增加 c 的值
        d++; // 增加 d 的值
        int sum = c + d; // 将 c 和 d 的新值加到 sum 上
        return sum; // 返回 sum
    }
    ```



3-2. Change fdemo3_ptr.c on page 23 to pass the reference instead of pass the pointer, generate the assembly soure code on your PC and answer the question: Would passing the reference use more stack space than passing the pointer in this situation ?

```bash
g++ -S -o fdemo3-x64.s fdemo3.c
cat fdemo3-x64.s | grep sub
```

![image-20250512162229582](D:\Manage\CPP\week06\images\image-20250512162229582.png)

在这个例子中，`disp_struct` 函数接收一个 `Stu` 类型的结构体作为参数。当调用 `disp_struct(stum);` 时，`stum` 结构体的内容会被复制到函数内部的 `stud` 参数中。这种通过值传递的方式意味着函数内部对 `stud` 的修改不会影响到原始的 `stum` 结构体。

```bash
g++ -S -o fdemo3_ptr-x64.s fdemo3_ptr.c
cat fdemo3_ptr-x64.s | grep sub
```

![image-20250512162208724](D:\Manage\CPP\week06\images\image-20250512162208724.png)

在这个例子中，`disp_struct` 函数接收一个指向 `Stu` 类型结构体的指针作为参数。当调用 `disp_struct(&stum);` 时，传递的是 `stum` 结构体的地址。函数内部通过解引用操作符 `->` 来访问和修改结构体的成员。这种通过指针传递的方式意味着函数内部对 `stud` 的修改会直接影响到原始的 `stum` 结构体。

3-3. Compare the differences between pointers and references in C++, as well as the differences between references in C++and Python, make a summay.

**C++ 中指针和引用的差异：**

1. **定义和初始化**：
    - **指针**：可以定义后不初始化，也可以指向 `NULL` 或任意地址。指针可以被重新赋值以指向不同的对象。
    - **引用**：必须在定义时初始化，并且一旦初始化后，就不能改变引用的对象。
2. **内存地址**：
    - **指针**：存储的是它所指向对象的内存地址。
    - **引用**：实际上是对象的别名，不存储地址，它就是对象本身。
3. **空值**：
    - **指针**：可以是 `NULL` 或 `nullptr`，表示不指向任何对象。
    - **引用**：不能是空的，必须引用一个已经存在的对象。
4. **自增操作**：
    - **指针**：可以进行自增操作（`++`），这会改变指针所指向的内存地址。
    - **引用**：不能进行自增操作，因为它不是地址。
5. **数组和函数参数**：
    - **指针**：可以方便地用于数组和函数参数，以传递数组或对象的地址。
    - **引用**：在函数参数中使用引用可以避免对象的复制，提高效率。
6. **算术运算**：
    - **指针**：可以进行算术运算，如自增（`++`）和相减（`-`）。
    - **引用**：不支持算术运算。

**C++ 和 Python 中引用的差异：**

1. **语法和语义**：
    - **C++**：引用是类型安全的，必须明确指定引用的类型，且在定义时必须初始化。
    - **Python**：引用是通过对象的标识（id）来实现的，Python 中的变量实际上是对象的引用。Python 不需要指定类型，且变量可以重新赋值为任何类型的对象。
2. **内存管理**：
    - **C++**：引用本身不管理内存，但需要确保引用的对象在引用的生命周期内有效。
    - **Python**：内存管理由 Python 的垃圾回收机制自动处理。
3. **多态和继承**：
    - **C++**：引用可以用于多态，即基类引用可以指向派生类对象。
    - **Python**：由于 Python 是动态类型语言，变量可以自动适应多态的需求，不需要显式使用引用。
4. **函数参数**：
    - **C++**：引用可以用于函数参数，以避免对象的复制，提高效率。
    - **Python**：函数参数传递的是对象的引用（实际上是对象的副本），但由于 Python 的动态特性，这通常不是问题。
