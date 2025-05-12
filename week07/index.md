---
title: CS205 Lab 7 shared library, function and memory
published: 2025-05-07
updated: 2025-05-12
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


- Shared library
    - Build
    - Use
    - Makefile
    - CMakelists.txt

- Function and Memory
    - function address
    - maps, executable memory

- Practice 

# Shared library

![image-20250512164158201](./images/image-20250512164158201.png)

|                 | **advantages**                                               | **disadvantages**                                            |
| --------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Static Library  | 1. Make the executable has fewer  dependencies, has been packaged into the executable file.<br />2. The link is completed in the  compilation stage, and the code is loaded quickly during execution. | 1. Make the executable file  larger.  <br />2. Being a library dependent on  another library will result in redundant copies because it must be packaged  with the target file.  <br />3. Upgrade is not convenient and  easy. The entire executable needs to be replaced and recompiled. |
| Dynamic Library | 1.Dynamic library can achieve  resource sharing between processes, there can be only one library file.  <br />2. The upgrade procedure is  simple, do not need to recompile. | 1. Loading during runtime will  slow down the execution speed of code.  <br />2. Add program dependencies that  must be accompanied by an executable file. |

## 1.1 Building a shared library

- A **shared library** packs compiled code of functionality that the developer wants to **share** with other developers.

- Shared libraries in linux are **.so** files.

- Remember to use arguments **`-shared`** and **`-fPIC`** when building it.

- Now we should see **`libmymath.so`** in the directory

```bash
g++ -shared -fPIC -o libmymath.so mymath.cpp
```



![image-20250512164633161](./images/image-20250512164633161.png)

## 1.2 Using shared library

- Now we can use the `.so` shared library.

- Let’s compile `main`:

    ![image-20250512164824193](./images/image-20250512164824193.png)

    ```bash
    g++ -o main main.cpp -L. -lmymath
    ```

- **-L**: indicates the directory of libraries

- **-l**: indicates the library name, the compiler can give the `**lib**` prefix to the library name and follows with **.so** as extension name.

After the `main` has been compiled, try to run it:

![image-20250512165341032](./images/image-20250512165341032.png)

```bash
./main
```



> [!TIP]
>
> It failed because `main` now relys on `libmymath.so`. By default, libraries are located in **/usr/local/lib** or **/usr/lib** , but our `libmymath.so` is not in that directory. You must tell the terminal where to find `libmymath.so`.

## 1.3 **Shared library in** **makefile**

- Using **export** command to set environment variable **`LD_LIBRARY_PATH`**

- And then run `main` again

    ```bash
    export LD_LIBRARY_PATH=.$LD_LIBRARY_PATH
    echo $LD_LIBRARY_PATH
    #Check the LD_LIBRARY_PATH is suceessful
    ./main
    ```

    ![image-20250512165545929](./images/image-20250512165545929.png)

    ![image-20250512165614830](./images/image-20250512165614830.png)

- Another choice is to move your .so file to **/us/lib** folder by **mv** command

    ![image-20250512165634688](./images/image-20250512165634688.png)

![image-20250512170230855](./images/image-20250512170230855.png)

```bash
# makefile with dynamic library

.PHONY: libd testlibd clean

libd: libfunction.so
libfunction.so: mymath.cpp
	g++ -shared -fPIC -o libfunction.so mymath.cpp

testlibd: main
main: main.cpp libfunction.so
	g++ main.cpp -L. -lfunction -Wl,-rpath=. -o main

clean:
	rm -f *.o *.so main
```

result:

![image-20250512170222467](./images/image-20250512170222467.png)

![image-20250512171927625](./images/image-20250512171927625.png)

```makefile
# 定义编译器
CXX = g++

# 定义编译选项
compile_flags := -g -O3 -w -fPIC

# 定义包含路径
include_path := ./include
I_options := $(include_path:%=-I%)

# 定义源文件目录和目标文件目录
SRC_DIR = src
OBJ_DIR = objs
LIB_DIR = lib

# 使用 wildcard 函数自动获取所有源文件
cpp_srcs := $(wildcard $(SRC_DIR)/*.cpp)
# 使用 patsubst 函数生成目标文件列表
cpp_objs := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(cpp_srcs))
# 过滤掉 main 目标文件，只编译库文件
so_objs := $(filter-out $(OBJ_DIR)/main.o, $(cpp_objs))

# 默认目标
all: compile dynamic

# 编译所有源文件
compile: $(cpp_objs)

# 创建目标文件
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(compile_flags) $(I_options)

# 创建动态库
dynamic: lib/libfunction.so

lib/libfunction.so : $(so_objs)
	@mkdir -p $(dir $@)
	$(CXX) -shared $^ -o $@

# 清理生成的文件
clean:
	rm -rf $(OBJ_DIR)/*.o $(LIB_DIR)/*.so

# 伪目标
.PHONY: all compile dynamic clean
```

The second part of the makefile links the dynamic library **libfunction.so** to the executable file **testdynamic** in the`objs` folder.

```makefile
# 创建动态库
library_path := ./lib

linking_libs := function

l_options := $(linking_libs:%=-l%)
L_options := $(library_path:%=-L%)
r_options := $(library_path:%=-Wl,-rpath=%)

# 可执行文件位于objs/下
objs/testdynamic : objs/main.o compile dynamic
    mkdir -p $(dir $@)
    g++ $< -o $@ $(l_options) $(L_options) $(r_options)

run : objs/testdynamic
    ./$<

clean :
    rm -rf lib objs

.PHONY : compile dynamic run clean
```



## 1.4 **Creating and linking a dynamic library by** **CMake**

We want to create a dynamic library by function.cpp and call the dynamic library in main.cpp. This time we write two CMakeLists.txt files, one in **CmakeDemo5** folder and another in **lib** folder.

![image-20250512172857556](./images/image-20250512172857556.png)

![image-20250512172906594](./images/image-20250512172906594.png)

[More detail click here](https://github.com/MongXinChan/SUST-Cpp-course/blob/main/lab07/shared%20library-02/Makefile)

# Function and Memory

![image-20250512172952553](./images/image-20250512172952553.png)

## 2.1 function address

![image-20250512173007833](./images/image-20250512173007833.png)

Here is the five memory type. We could run the code to understand it.

```cpp
#include <iostream>
int add(int a, int b) {
    return a + b;
}

int main(){
    int x=0, y=0,z=0;
    int (*func_ptr)(int, int) = add;
    printf("address of data:x:%p,y_address:%p\n",&x,&y);
    printf("address of func\"main\":%p\n",main);
    printf("address of func\"printf\":%p\n",printf);
    x=add(1,2);
    printf("address of func\"add\":%p\n",add);
    y=add(10,20);
    printf("address of func\"add\":%p\n",add);
    z=func_ptr(100,200);
    printf("address of func_ptr:%p\n",func_ptr);
    return 0;
}
```

![image-20250512173425966](./images/image-20250512173425966.png)

## 2.2 maps, executable memory

Q. What the specific memory usage during the execution of the “p3_demo1” program ?

![image-20250512173632047](./images/image-20250512173632047.png)

```bash
gcc -shared -fPIC -o libmymath.so mymath.c
gcc -o p2_demo1 p2_demo1.c -L. -lmymath
./p2_demo1
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
./p2_demo1
```

![image-20250512174539920](./images/image-20250512174539920.png)

[You can click here to visit the more detail of the code.](https://github.com/MongXinChan/SUST-Cpp-course/tree/main/lab07)

> [!TIP]
>
> 1. Use “pgrep” tool to view the process number of the currently running process that matches the specified name
> 2. Use “cat” to find current usage of memory by the process according to the “maps” of the process. 
>
> **The “perms” field is a set of permissions: r = read, w = write, x = execute, s = shared, p = private (copy on write)**
>
> [MORE](https://man7.org/linux/man-pages/man5/proc_pid_maps.5.html)

![image-20250512174632993](./images/image-20250512174632993.png)

# Exercise

## 3.1 Exercise 1

Overload a function **bool** **vabs(int \* p, int n)** which can compute the absolute value for every element of an array, the array can be int, float and double.

```cpp
#ifndef VABS_H
#define VABS_H

#include <cstddef> // for size_t

bool vabs(int* p, size_t n);
bool vabs(float* p, size_t n);
bool vabs(double* p, size_t n);

#endif // VABS_H
```

 Should be int or size_t? what's the difference? Remember to check whether the pointer is valid.



Create a shared library “libvabs.so” with 3 overloaded vabs() functions in it, and then compile and run your program with this shared library. Test the address of each  overloaded vabs() functions.



Create a static library “libvabs.a” with 3 overloaded vabs() functions in it, and then compile and run your program with this static library.Test the address of each  overloaded vabs() functions.



Conclude the difference between static library and shared library according to your experimental results.



[Click here to visit the implements.](https://github.com/MongXinChan/SUST-Cpp-course/tree/main/lab07/Exe01)

## 3.2 Exercise 2

Write a program that uses a function template called **Compare** to compare the relationship between the values of the two arguments and return 1 when the first argument is greater than the second one; return -1 when the first argument is smaller than the second one, return 0 when the both values are equal. Test the program using integer, character and floating-point number arguments and print the result of the comparation.

If there is a structure as follows, how to define an explicit specialization of the template function **Compare** and print the result of the comparation?

```CPP
struct stuinfo{
   string name;
    int age;
};
```

![image-20250512185044382](./images/image-20250512185044382.png)

```cpp
#include <iostream> // Or other necessary includes like <string> or <cstdio>
#include <string>   // Needed if stuinfo::name is std::string

// --- STEP 1: Define the struct stuinfo ---
// The full definition must come BEFORE the function that uses its members.
struct stuinfo {
    int age;          // Example member
    std::string name; // Example member (use std::string or char* as appropriate)
    // Any other members...
};

// --- STEP 2: (Optional) Define the generic template if you have one ---
// If you only have the specialization, you might not need this.
template<typename T>
int Compare(const T& a, const T& b) {
    // Default comparison logic for other types (if any)
    std::cout << "Using generic Compare template" << std::endl;
    if (a < b) return -1;
    if (b < a) return 1;
    return 0;
}


// --- STEP 3: Define the TEMPLATE SPECIALIZATION for stuinfo ---
// Make sure the struct definition above is already seen by the compiler.
// Use template<> to indicate specialization.
template<>
int Compare<stuinfo>(const stuinfo& a, const stuinfo& b) {
    // Now the compiler knows stuinfo has members 'age' and 'name'.
    if (a.age > b.age) {
        return 1;
    } else if (a.age < b.age) {
        return -1;
    } else {
        // Ages are equal, compare by name
        if (a.name > b.name) {
            return 1;
        } else if (a.name < b.name) {
            return -1;
        } else {
            return 0; // Both age and name are equal
        }
    }
}


// --- STEP 4: Your main function or other code using Compare ---
int main() {
    stuinfo s1 = { 20, "Charlie" };
    stuinfo s2 = { 22, "Bob" };
    stuinfo s3 = { 20, "Alice" };

    // These calls will use the specialized Compare<stuinfo> function
    int result1 = Compare(s1, s2); // Calls Compare<stuinfo>
    int result2 = Compare(s1, s3); // Calls Compare<stuinfo>

    std::cout << "Compare(s1, s2): " << result1 << std::endl; // Expected: -1 (s1.age < s2.age)
    std::cout << "Compare(s1, s3): " << result2 << std::endl; // Expected: -1 (s1.age == s3.age, s1.name < s3.name)

    // Example of calling the generic template (if defined)
    // int x = 10, y = 5;
    // std::cout << "Compare(x, y): " << Compare(x, y) << std::endl;

    return 0;
}
```

```bash
g++ -std=c++11 Exe02.cpp -o Exe02
./Exe02
```

