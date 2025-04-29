---
title: CS205 Lab04 CMake
published: 2025-04-27
updated: 2025-04-28
description: '本文强调所学Linux操作系统的指令，这些指令可以帮助我们快速熟悉Linux/Ubuntu操作系统。'
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

> [!IMPORTANT]
>
> 由于本文篇幅过长，个人会添加适当的中文注解在里面。

**Introduction:**

In this note, you will learn about that:

1. CMake

2. Inputs

    - Command-Line Arguments

    - Standard Input

3. Data storage 
    - array, string, struct, union

4. Exercises 

# **CMake**

## 1.1 What's the CMake?

**CMake** is an open-source, cross-platform family of tools designed to build, test and package software. **CMake** is used to control the software compilation process using simple platform and compiler independent configuration files, and generate native makefiles and workspaces that can be used in the compiler environment of your choice.



**CMake** needs **CMakeLists.txt** to run properly.

A CMakeLists.txt consists of **commands** , **comments** and **spaces**.

- The **commands** include command name, brackets and parameters , the parameters are separated by spaces. Commands are not case sensitive.
- **Comments** begins with ‘#’.



Steps for generating a makefile and compiling on Linux using CMake: 

**Step1**: Writes the CMake configuration file **CMakeLists.txt**.

**Step2**: Executes the command **cmake** **PATH** to generate the **Makefile**.(PATH is the directory where the CMakeLists.txt resides.)

**Step3**: Compiles using the **make** command.

## 1.2 A single source file in a project

The most basic project is an executable built from source code files. For simple projects, a three-line **CMakeLists.txt** file is all that is required.

![image-20250429234301761](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250429234301761.png)

In current directory, type **cmake** **.** to generate makefile. If cmake does not be installed, follow the instruction to install cmake.

![image-20250429234331489](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250429234331489.png)

![image-20250429234357317](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250429234357317.png)

![image-20250429234425456](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250429234425456.png)

## **1.3 Multi-source files in a project**

![image-20250429234449184](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250429234449184.png)

![image-20250429234510401](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250429234510401.png)



### **1.2.1 Multi-source files in a project-1**

If there are several files in directory, put each file into the **add_executable** command is not recommended. The better way is using**aux_source_directory** command.

![image-20250429234546928](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250429234546928.png)

### **1.2.2 Multi-source files in a project-2**

![image-20250429235623990](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250429235623990.png)

![image-20250429235647544](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250429235647544.png)

### **1.2.3 Multi-source files in a project in different directories**

**We write CMakeLists.txt in <u>CmakeDemo3 folder.</u>**

```TEX
./CmakeDemo3
│
├── src/
│   ├── main.cpp
│   └── function.cpp
│
└── include/
    └── function.h
```

![image-20250429235936870](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250429235936870.png)

![image-20250429235958222](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250429235958222.png)

# Inputs

## 2.1 Command-Line Arguments

- At the beginning of program execution, arguments are read.
- All the arguments here are treated as string.
- Suitable for scenarios involving scripts and tools, but lacks interactivity.

```cpp
#include <stdio.h>   // c_a_demo.c

int main(int argc, char*argv[]){
    if(argc ==1)
        printf("ONLY argv[0]:%s\n",argv[0]);
    else
        for(int i=0;i<argc;i++)
            printf("argv[%d]: %s\n",i, argv[i]);

    return 0;
}

```

![image-20250430000721904](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250430000721904.png)

## 2.2 Standard Input

- During program execution, read input data from standard input devices.
- Support different types of input data.
- Suitable for interacting with users.

```cpp
#include <stdio.h>

int main(int argc, char*argv[]){
    char uname[10]={""};
    char dname[10]={""};
    char cname[10]={""};
    printf("please input the name of University: ");
    scanf("%s", uname); 
    printf("please input the name of department: ");
    scanf("%s", dname);
    printf("please input the name of course: ");
    scanf("%s", cname);     
    printf("uname: %s, dname: %s, cname:%s\n",uname,dname,cname);  
    return 0;
}

```

![image-20250430000917782](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250430000917782.png)

### 2.2.1 C style：scanf, gets vs fgets

**scanf**

1.  **%d** **----int**
2.  **%f** **----float**
3. **%c** **-----char**
4.  <u>**%s** **-----string**</u>(There's no &)

![image-20250430001038441](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250430001038441.png)



![image-20250430001047519](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250430001047519.png)

```cpp
#include <stdio.h>

int main(){
    int prj_id=0;
    float prj_sc=0.0f;
    char valid=0;
    printf("please input 'project id' in decimal int: ");
    scanf("%d", &prj_id); 
    printf("please input the score : ");
    scanf("%f", &prj_sc);
    printf("please input the score is valid or not(Y/N): ");
    while (getchar() != '\n');
    scanf("%c", &valid);     
    printf("project id: %d, score: %.1f, %s\n",
               prj_id, prj_sc, (valid=='y'||valid=='Y')?"VALID":"NOT VALIDE" );  
    return 0;
}

```



![image-20250430001337789](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250430001337789.png)

> [!TIP]
>
> When using scanf ("% d") or scanf ("% f") to read values, scanf skips leading whitespace characters (spaces, line breaks, etc.), but does not consume line breaks in the input stream (i.e., those generated by pressing enter).

---

**gets**

![image-20250430001553558](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250430001553558.png)

![image-20250430001634283](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250430001634283.png)

### 2.2.2 C++ style: cin, cin.gets vs cin.getline, getline()

**cin**

- The **cin** is to use `whitespace--spaces`,`tabs`, and `newlines` to **separate** a string.

>[!CAUTION]
>
>注意此时要使用g++编译，否则会出现如下的报错
>
>![image-20250430003028773](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250430003028773.png)
>
>这是由于gcc编译器中并未引入**namespace**导致的。


Result:

![image-20250430002919249](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250430002919249.png)

**cin.get( )**

- Input a single character:

    - **istream& get(char&);**

    - **int get(void);**

- Input a string:
    - **istream& get(char\*,int);**



**cin.getline( )** 

- Input a string:
    - **istream& getline(char\*,int);**

![image-20250430003552680](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250430003552680.png)

**cin.get( ) vs cin.getline( )**

**getline()** and **get()** both read an entire input line—that is, up until a newline character. 

However, **getline()** **<u>discard</u>** the newline character, whereas get() leave it in the input queue.

## 2.3 others inputs source

Besides reading data from standard input (typically the keyboard), C++ programs can also obtain input from the following sources:

- **Files:** Data can be read from files using file stream classes such as `ifstream`. This allows programs to process data stored in various file formats.

- **Network:** Input can be received from remote servers or clients through network sockets. This involves network programming, which can use libraries like `Boost.Asio` or other networking libraries to handle TCP/IP communication.

- **GUI (Graphical User Interface):** User input can be gathered through GUI elements such as text boxes, buttons, and sliders. This typically involves using GUI frameworks like `Qt`, `GTK`, or `WxWidgets` to create and manage the graphical interface.

- **Database:** Data can be retrieved from databases using database connections and queries. This often requires database-specific libraries or connectors, such as `ODBC`, `MySQL Connector`, or `SQLite`, to interact with the database server.

- **Sensors:** Input can be acquired from physical sensors through hardware interfaces. This may involve using specific hardware drivers or APIs provided by the sensor manufacturer to communicate with and retrieve data from the sensors.

Each of these input methods may require additional setup and configuration, as well as the inclusion of appropriate libraries or frameworks in your C++ project to handle the input operations effectively.

# Storage

## 3.1.Data storage on construction type

### 3.1.1 array:

- One dimensional array and two-dimensional array

## 3.1.2 string:

- char array vs string

## 3.1.3 struct:

- align

### 3.1.4 union:

- share