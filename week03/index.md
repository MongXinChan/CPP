---
title: CS205 Lab03 Common Commands in Linux,  Makefile
published: 2025-04-23
updated: 2025-04-27
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

1. Commands in Linux

    - commands: directory, file .etc.

    - lists of commands, pipelines

2. Makefile

    - file: makefile/Makefile 

    - command: make, make clean

3. Practices

    - commands, makefile

    - branch, loop

# Commandas in Linux

Linux is a family of open-source Unix operating systems based on the *Linux Kernel*. 

There are some popular distributions  such as Ubuntu, Fedora, Debian, openSUSE, and Red Hat.

A Linux command is a program or utility that runs on the Command Line Interface – a console that interacts with the system via texts and processes.

Linux command’s general syntax looks like:

```tex
CommandName [option(s)] [parameter(s)]
```

- **CommandName** is the rule that you want to perform.
- **Option** or **flag** modifies a command’s operation. To invoke it, use hyphens (-) or double hyphens (--).
- **Parameter** or **argument** specifies any necessary information for the command.

## 1.1 Linux directory and file commands:

| **Command**                   | **Meaning**                                               |
| ----------------------------- | --------------------------------------------------------- |
| **pwd**                       | **P**rint the name of current/**w**orking  **d**irectory. |
| **cd** `<directory name>`     | **C**hange the current **d**irectory.                     |
| **ls**                        | **L**i**s**t  of  content of a directory.                 |
| **mkdir**  `<directory name>` | **M**a**k**e a  new **dir**ectory  under any directory.   |
| **rmdir**  `<directory name>` | **R**e**m**ove **dir**ectories without files.             |
| **cat** `<file name>`         | Display content of the file.                              |
| **rm** `<file name>`          | **R**e**m**ove  a file.                                   |
| **cp** `<source> <dest>`      | **C**o**p**y a  file or files to another                  |
| **mv** `<source><dest>`       | **M**o**v**e a  file or files to another directory        |

**cat/tail/head, less/more, nano/vim, file, whereis, echo**

[You can click here to visit the commands of Linux/Ubuntu](https://www.javatpoint.com/linux-commands)

### 1.1.1 Absolute path and relative path

A **path** is how you refer to files and directories. **<u>It gives the location of a file or directory</u>** in the Linux directory structure. It is composed of a **name** and **slash** syntax.

If the path starts with slash "/", the first slash denotes root. The rest of the slashes in the path are just separators.

> [!CAUTION]
>
> 用`\`虽然说在md格式下是可行的，但是还是不符合Astro框架下的文件引用，因为这件事我很多次博客部署失败...

![image-20250427213815128](./images/pathAbsoluteOrRelative.png)

The one is **`aboslute path`**,because it include `/root/` directory(In Linux it means start).

A **`relative path`** starts from the current directory.

> [!NOTE]
>
> **Two special relative paths:**
>
> **.** **( single dot) denotes the current directory in the path.**
>
> **..** **(two dots) denotes the parent directory, i.e., one level above.**

###  1.1.2 **pwd** command

Use the **pwd** command to display the current working directory you are in. 

Start Ubuntu, you will see:

![image-20250427220327969](./images/pwdCommands.png)

**$** or **#** is the prompt, you can type command now.

![image-20250427220141981](./images/pwdCommands2.png)

`/mnt/d/manage` means the current directory.

### **1.1.3 cd** command

To navigate through the Linux files and directories, use the **cd** command. 

![image-20250427220520360](./images/cdCommands2.png)

you can use the below command to open the directory:

```bash
cd /mnt/d
```

It means you use the `absolute path` to open the directory，**change the directory to the root directory of d drive**

![image-20250427220858396](./images/cdCommands3.png)

```bash
cd /root/
```

change the directory to the `root` directory，`root` means the adminitor files，the `home` means the ordinary users' files.

> [!TIP]
>
> root和home，前者为管理员用户的个人文件，后者为普通用户的个人文件，权限不同，由于这里用的是wsl连接，获得到的是最高级权限。



![image-20250427221937654](./images/cdCommands.png)

```bash
cd /
```

change the directory to the `root` directory.

![image-20250427221921303](./images/cdCommands4.png)

```bash
cd ~
```

change the directory to the `home` directory

You can see that : There's a `go` files in my home directory,because I have installed the `go` enviornment.

But actually you see that: There're so many folders in `root` directory.

**Here are some shortcuts to help you navigate:**

1. **cd ~[username]** goes to another user’s home directory.
2. **cd ..** moves one directory up.
3. **cd -** moves to your previous directory.
4. **cd** without an option will take you to the home folder. 

### 1.1.4 **ls** command

The **ls** command lists files and directories within a system. Running it without a flag or parameter will show the current working directory’s content.

And you see I used it in `cd` command.

![image-20250427221937654](./images/cdCommands.png)

You can see `ls`:

![image-20250427222434045](./images/lsCommandsDetails.png)

Here are some options you can use with the **ls** command:

1. **ls -R** lists all the files in the subdirectories.
2. **ls -a** shows hidden files in addition to the visible ones.
3. **ls -l (or** **ll)** shows detail information of subdirectory and files

### 1.1.5 **mkdir** command

Use the **`mkdir`** command to **create one or multiple directories at once**. 

![image-20250427222951510](./images/mkdir.png)

> [!NOTE]
>
> Aplogize to you, I use the original picture.

### 1.1.6 **rmdir** command

Use the **`rmdir`** command to permanently delete an **`empty directory`**.

![image-20250427223139078](./images/rmdirCommands.png)

### 1.1.7 **rm** command

The **`rm`** command is used to **`delete files within a directory`**. Make sure that the user performing this command has write permissions.

![image-20250427223209929](./images/rmCommands.png)

```bash
rm test.txt hello
```

Means that:Deleting `test.txt`,and `hello`,**DONOT** require you confirmation.

Here are some acceptable options you can add:

1. **-i** prompts system confirmation before deleting a file.
2. **-f** allows the system to remove without a confirmation.
3. **-r** deletes files and directories recursively.

### 1.1.8 **cp command and mv command**

The **`cp`** command is used to copy a file or directory.

![image-20250427223239394](./images/cpCommands.png)

```bash
cp main.cpp test
```

The **mv** command is used to move a file or a directory form one location to another location.

![image-20250427223256136](./images/cpCommands2.png)

![image-20250427223301731](./images/cpCommands3.png)

```bash
mv A B
```

means that:Moving A file into B fold

```bash
mv A B C
```

menas that: Moving A into B and Renaming its name:C;

### 1.1.9 **cat** command

Concatenate, or **`cat`**, is one of the most frequently used Linux commands. It lists, combines, and writes file content to the standard output. To run the cat command, type **cat** followed by the file name and its extension. 

![image-20250427224904763](./images/catCommands.png)

Here are other ways to use the cat command:

1. **cat > filename.txt** creates a new file.
2. **cat filename1.txt filename2.txt > filename3.txt** merges **filename1.txt** and **filename2.txt** and stores the output in **filename3.txt**.
3. **tac filename.txt** displays content in reverse order.

## 1.2 lists of commands, pipelines

### 1.2.1 lists of commands

1. An **AND list** has the form： command1 **`&&`** command2
    - **command2 is executed if, and only if, command1 returns an exit status of zero (success).**

2. An **OR list** has the form： command1 **`||`** command2

    - **command2 is executed if, and only if, command1 returns a non-zero exit status.**

3. **Command Sequence**:  command1 **`;`** command2
- **Commands separated by a ‘`;`’ are executed sequentially;**

> [!TIP]
>
> For the shell’s purposes, a command which **exits with a** **zero exit** **status has succeeded**. A non-zero exit status indicates failure.
>
> The exit status of the last command is available in the special parameter **$?**

![image-20250427225330993](./images/utiliseOfCommands.png)

### 1.2.2 pipelines

- A pipeline is a sequence of one or more commands separated by one of the control operators `|` or `|&`.
- The output of each command in the pipeline is connected via a pipe to the input of the next command. That is, each command reads the previous command’s output. This connection is performed before any redirections specified by command1.

![image-20250427225537908](./images/utiliseCommands2.png)

![image-20250427225542866](./images/utiliseCommands3.png)

### **TIPS: Shortcut keys**

1. **`Up`** and **down** arrow keys can list the commands you typed.
2. **`Tab`** key can complete the command. For a long command, you can type first few letters and press Tab key to complete the command or list alternate commands.

![image-20250427225604450](./images/shortcutKey1.png)

**`clear`** is a standard Unix computer operating system command that is used to clear the terminal screen.

![image-20250427225610366](./images/shortcutKey2.png)

# gcc & g++

**gcc** and **g++** are GNU C or C++ compilers respectively, which issued for preprocessing, 

compilation, assembly and linking of source code to generate an executable file. 

Type command **gcc** or **g++ --help**, you can get the common options of the gcc or g++. **g++** accepts

mostly the same options as **gcc**.

![image-20250427225829509](./images/gccAndG++.png)

**-c**  Compile or assemble the source files, but do not link. The ultimate output is in the form of an object file for each source file. The object file name for a source file is made by replacing the suffix **.c** with **.o**.

**-o** **<file>**  Place output in file *file*. This applies regardless to whatever sort of output is being produced, 

​         whether it be an executable file, an object file, an assembler file or preprocessed C code.

​          If **-o** is not specified, the default is to put an executable file in *a.out*.

**we use `gcc source_file.c -o program_name`   or   `gcc source_file.o -o program_name` to compile the c&cpp files.**

![image-20250427230010354](./images/processOfCompile.png)

**With one step to generate an executable target file:** 

**gcc** **file_name**  or **g++** **file_name**

This command is used to compile and create an executable file *a.out* (default target name).

```cpp
#include <iostream>
using namespace std;
int main()
{    
        cout << "Hello World!!!" << endl;   

        return 0;
}
```

![image-20250427230049814](./images/processOfCompile1.png)

## **2.1 compile multiple files**

You can compile the files one by one and then link them to an executable file.

Another choice is using one step to list all the .c(or .cpp) files after gcc(or g++) command and create an executable file named a.out.

```cpp
//area.h
#define PI 3.1415

double compute_area(double r);

```

```cpp
//area.c
#include "area.h"

double compute_area(double r)
{
    return PI * r * r;
}

```

```cpp
//main.c
#include <stdio.h>
#include "area.h"

int main()
{
    double r, area;

    printf("Please input a radius:");
    scanf("%lf", &r);

    area = compute_area(r);

    printf("The area of %lf is %.4lf\n", r, area);

    return 0;
}

```

![image-20250427230604864](./images/processOfCompile2.png)

# Makefile

What is a Makefile?

**Makefile** is a tool to simplify and organize compilation. **Makefile** **is a** **set of commands with variable names and targets .** You can compile your project(program) or only compile the update files in the project by using Makefile.

[If you wanna know more Makefile click here.](https://www.loners.site/posts/makefile/)

And if you wanna know the example you can [click here come to my github repo read this code.](https://github.com/MongXinChan/SUST-Cpp-course/tree/main/lab03/exa02)

Normally, you can compile these files by the following command:

![image-20250427234147274](./images/makefileSuccessful.png)

![image-20250427234400326](./images/makefileSuccessful2.png)

How about if there are hundreds of files to compile? If only one source file is modified, need we compile all the files? Makefile will help you.

The name of makefile must be either **makefile** or **Makefile** without extension.You can write makefile in any text editor. A rule of makefile including three elements: **targets**, **prerequisites** and **commands**. There are many rules in the  makefile.





A makefile consists of a set of rules. A rule including three elements: **target**,**prerequisites** and **commands**. 

![image-20250427234233492](./images/targetsPrerequisites.png)

1. The **target** is an object file, which is generated by a program. Typically, there is only one per rule.
2. The **prerequisites** are file names, separated by spaces, as input to create the target.
3. The **commands** are a series of steps that make carries out. These need to start with a **tab character**, not spaces.

![image-20250427234333806](./images/writeMakefile.png)

Type the command **make** in VScode

![image-20250427234527147](./images/writeMakefile1.png)

If you don’t install make in VScode, the information will display on the screen. 

![image-20250427234557353](./images/writeMakefile2.png)

## **3.1 Define Macros/Variables in the** **makefile**

To improve the efficiency of the **makefile**, we use variables.

![image-20250427235549000](./images/writeMakefile3.png)

start with <TAB> Write target, prerequisite and commands by variables using `$()`

![image-20250427235621941](./images/writeMakefile4.png)

> [!NOTE]
>
> Deletes all the .o files and executable file created previously before using make command. Otherwise, it’ll display: 
>
> ![image-20250427235639914](./images/writeMakefile5.png)

If only one source file is modified, we need not compile all the files. So, let's modify the makefile.

![image-20250427235839514](./images/writeMakefile6.png)

If main.cpp is modified, it is compiled by make.

![image-20250427235854370](./images/writeMakefile-7.png)

**All** the .cpp files are compiled to the .o files, so we can modify the makefile like this:

~~~makefile
# Using several ruls and several targes
CXX = g++
TARGET = testfiles
0BJ = main.o printinfo.o factorial.o

# options pass to the compilen
#-c generates the object file
# -Wall displays compiler warning
CFLAGS = -c -Wall

$(TARGET) : $(OBJ)
	$(CXX) -o $@ $(OBJ)

%.o : %.cpp
	$(CXX) $(CFLAGS) $^
~~~

**$@**: the target file

**$^**: all the prerequisites files

**$<**: the first prerequisite file

```makefile
%.o:%.cpp
```

or

```makefile
$(CXX) $(CFLAGES)$^
```

> [!TIP]
>
> 实际上，就是说Makefile的存在很好的消除了我们的命令行输入输出需求。正所谓前人栽树后人乘凉的道理，由于VSCode本身不存在已经配置好的环境，我们还需要自己手动写一份Makefile文件【当然也可以用ai作为助手当作辅佐工具】，如果实在是头疼配置问题，可以移步到下载VS(**V**isual **S**tudio)的下载，VSCode只是相当于一个轻文本编辑器，许多环境都是我们自行配置的，而VS相当于集成的IDE，只是所需内存更大。但是相对而言，VS的即装即用是很多学C/Cpp的新手首选。

## 3.2 `Phony` target

Using `phony` target to clean up compiled results automatically

~~~makefile
# Using several rules and several targets

CXX = g++
TARGET = testfiles
OBJ = main.o printinfo.o factorial.o

# options pass to the compiler
# -c generates the object file
# -Wall displays compiler warning
CFLAGS = -c -Wall

$(TARGET) : $(OBJ)
	$(CXX) -o $@ $(OBJ)

%.o : %.cpp
	$(CXX) $(CFLAGS) $^

.PHONY : clean
clean:
	rm -f *.o $(TARGET)
~~~

Because **clean** is a label not a target, the command **make clean** can execute the clean part. Only **make** command can not execute clean part.

<u>**Adding .PHONY to a target will prevent making from confusing the phony target with a file name.**</u>

> [!TIP]
>
> 这里实际上就是借用了PHONY来删除多余的编译文件

**Functions in** **makefile**

![image-20250428002819586](./images/writeMakefile-8.png)

~~~makefile
SRC=$(wildcard ./*.cpp)$
target:
	@echo $(SRC)$
~~~

![image-20250428002909488](./images/writeMakefile9-.png)

**patsubst**(pattern substitution): replace file  

$(**patsubst** original pattern, target pattern, file list)

![image-20250428003000540](./images/writeMakefile10.png)

```makefile
SRC = $(wildcard ./*.cpp)$
OBJ = $(pasubst %.cpp,%o,$(SRC))$
target:
	@echo $(SRC)
	@echo $(OBJ)
```

![image-20250428003131619](./images/writeMakefile7.png)

## 3.3 OBJS vs OBJ

~~~makefile
OBJS=$(patsubst %.cpp,%.o,$(SRC))$
~~~

Vs

~~~makefile
OBJ=main.o printinfo.o factorial.o
~~~

![image-20250428003303903](./images/writeMakefile8.png)

> [!TIP]
>
> 我们可以看到OBJS只需要**描述法**就可以使用了，比OBJ直接**列举法**要来得简单得多。但是利弊也是看情况，文件不多的情况下也可以酌情用OBJ。

## 3.4 **Use** **Options to Control Optimization**

**-O1**, the compiler tries to reduce code size and execution time, without performing any optimizations that take a great deal of compilation time.

**-O2**,Optimize even more. GCC performs nearly all supported optimizations that do not involve a space-speed tradeoff. As compared to -O1, this option increases both compilation time and the performance of the generated code.

**-O3**, Optimize yet more. O3 turns on all optimizations specified by -O2.

You can click here to learn more:

[Options from org](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)

[Optional details from csdn](https://blog.csdn.net/xinianbuxiu/article/details/51844994)

![image-20250428003448307](./images/writeMakefile9.png)

![image-20250428003457952](./images/writeMakefile11.png)

![image-20250428003508092](./images/writeMakefile12.png)

[GNU Make Manual](http://www.gnu.org/software/make/manual/make.html)

# Exercise 

## 4.1 **Exercises . commands and command list**

The existing directory structure is shown in the upper right image. There are different types of C/C++files in the `p1` directory while the directory structure under p2 is unknown.
 ![image-20250428095913754](./images/exercise1.png)

> [!IMPORTANT]
>
> Task. Use the command list to create subdirectories as needed and place files of different types into different subdirectories in the `p2` directory (as shown in the lower right image).Place the header file in `p2/inc`, and the cpp source file in `p2/src`, and create `p2/build`.

> [!NOTE]
>
> 1. when using commands, if there is already an `inc` subdirectories, do not create `inc` repeatly. If there is no `inc` subdirectories, create it;The same requirement also applies to `src` and `build`.
>
> 2. File copying work should only be performed after the destination subdirectories have been created.
>
> 3. Use as few command lists as possible to complete this exercise (options include `and list`, `or list`, `command sequence`, which can be combined as needed)

**My implements:**

![image-20250428234625985](./images/implements2.png)

or use this:

```bash
mkdir -p p2 &&
cd p2 &&
mkdir -p inc src build && \
cp -u ../lab/functions.h inc/ && \
cp -u ../lab/makefile inc/ && \
cp -u ../lab/factorial.cpp src/ && \
cp -u ../lab/main.cpp src/ && \
cp -u ../lab/printhello.cpp src/
```

![image-20250429005017531](./images/implements1.png)

## 4.2 **Exercises . Makefile and make**

create a makefile, run it by command `make` or `make clean` to complete following tasks:

1. compile your project(program) or only compile the update files in the project by running `make`based on makefile to generate the executable file `lab3_practice`.

    > [!NOTE]
    >
    > the object file *.o and the executable file `lab3_practice` should be in the directory `build`

2. remove all the files in the directory `build` by running `make clean` 

![image-20250428095927958](./images/exercise2.png)

3. edit the source file `lab3_practice.cpp` (change parameter `5` to another number), save it, then run `make` again, which object file would be updated in the process? 

## 4.3 **Exercises** . Run the following source code and explain the result.

You need to explain the reason to a SA to pass the test.

```cpp
#include <iostream>
using namespace std;

int main()
{
    for(size_t n = 2; n >= 0; n--)
        cout << "n = " << n << "  "; 

    return 0;
    
}

```

Using the `size_t`,and the `size_t`, and the range of the type like the `unsigned int` ， so you will konw the `n` will not be less than 0.

## 4.4 Exerices . Run the following source code and explain the result.

You need to explain the reason to a SA to pass the test.

```cpp
#include <iostream>
using namespace std;

int main()
{
    int n = 5;
    int sum;
    while(n >0){
        sum += n;
        cout << "n = " << n << "  ";
        cout << "sum = " << sum << "  ";
    }
    return 0;
}

```

Firstly,the code shows us a while-loop when `n`>0 its condition is true,but the `sum` donot initialize and `n` donot plus or mins to the while-loop is ALWAYS-TRUE.

```cpp
#include <iostream>
using namespace std;

int main()
{
    unsigned int n = 5;  
    int sum;
    while(n >0){
        sum += n;
        cout << "n = " << (n-=2) <<endl;
        cout << "sum = " << sum << "  ";
    }
    return 0;
}

```

Secondly,the code shows the n is the `unsigned int` type ,but the `sum` still donot initialize.Then the `n` still not plus or mins to the while-loop is ALWAYS-TRUE .

Thirdly, there're the same question in the two Codes,just like `sum` donot initialize and the `n` donot changes. So we should make the `n` mins,and initialize the `sum`. 

## 4.5 Exerices. Run the following source code and explain the result.

```cpp
#include <iostream>
using namespace std;

int main()
{
    int n,fa;

    do{
        fa *= n;
        n++;
    }while(n <= 10);

    cout << "fa = " << fa << endl;

    return 0;
}

```

Actually, there're the same problems in the `Exerices4.4`,donot initialize the participation elements of while-loop, it will effect on the while-loop cannot excute rightly.
