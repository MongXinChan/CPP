---
title: CS205 Lab
published: 2025-04-27
updated: 2025-04-28
description: ''
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

<img src="C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250506091745553.png" alt="image-20250506091745553" style="zoom:50%;" />

|                 | **advantages**                                               | **disadvantages**                                            |
| --------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Static Library  | 1. Make the executable has fewer  dependencies, has been packaged into the executable file.  <br />2. The link is completed in the  compilation stage, and the code is loaded quickly during execution. | 1. Make the executable file  **larger**.  <br />2. Being a library dependent on  another library will result in redundant copies because it must be **packaged  with the target file.**  <br />3. Upgrade is not convenient and  easy. The entire executable needs to be replaced and recompiled. |
| Dynamic Library | 1.Dynamic library can achieve  resource sharing between processes, there can be only one library file.  <br />2. The upgrade procedure is  simple, do not need to recompile. | 1. Loading during runtime will  slow down the execution speed of code. <br />2. Add program dependencies that  must be accompanied by an executable file. |

In this part,we focus on the static library.

## 1.1 build

[You can click here to read the code](https://github.com/MongXinChan/SUST-Cpp-course/tree/main/lab06/lab)

![image-20250506092331495](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250506092331495.png)

- In previous class we do the following:
- This will compile the “main.cpp” and “mymath.cpp” into “main”
- And then run “main”

```bash
g++ *.cpp -o main -std=c++11
./main
```

![image-20250506092622918](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250506092622918.png)

- A static library is created by **.o** file.
- Remember to use “**ar**” command with arguments “**-cr**” when building it.
- Now we should see **“libmymath.a”** in the current directory

```bash
g++ -c mymath.cpp
ls
ar -cr libmymath.a mymath.o
ls
```

![image-20250506093008943](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250506093008943.png)

Result:

![image-20250506093153253](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250506093153253.png)



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



![image-20250506093300713](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250506093300713.png)

- **-L**: indicates the directory of libraries
- **-l**: indicates the library name, the compiler can give the “**lib**” prefix to the library name and follows with **.a** as extension name.

## 1.3 makefile

![image-20250506094421596](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250506094421596.png)

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



![image-20250506094222507](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250506094222507.png)

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



![image-20250506094309180](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250506094309180.png)



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



![image-20250506094313930](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250506094313930.png)

```MAKEFILE

```



![image-20250506094323170](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250506094323170.png)

```MAKEFILE

```



![image-20250506094329584](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250506094329584.png)

```MAKEFILE

```



## 1.4 CMake



# Parameters of function

## 2.1 pass by value

### 2.1.1 fundamental type

### 2.1.2 pointer

## 2.2 pass by reference

## 2.3 pass a huge structure vs pass its pointer

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



You are required to compile the function into a static library “libswap.a”, and then compile and run your program with this static library.

## 3.3 Exercise 3

3-1. Run the demo code on page 21 and 22, answer the questions on these pages. 

3-2. Change fdemo3_ptr.c on page 23 to pass the reference instead of pass the pointer, generate the assembly soure code on your PC and answer the question: Would passing the reference use more stack space than passing the pointer in this situation ?

3-3. Compare the differences between pointers and references in C++, as well as the differences between references in C++and Python, make a summay.
