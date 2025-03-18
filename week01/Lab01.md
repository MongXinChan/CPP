# Lab 1
## Task 1 Install WSL

install wsl
```bash
wsl --install
```
In this task,I fail to install wsl.
So I do this :
```bash
wsl -l -o
wsl --install -d Ubuntu-20.04
```

![image-20250318003050449](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250318003050449.png)

That's my successful examples.

```BASH
DISM.exe /Online /Enable-Feature /FeatureName:VirtualMachinePlatform /All /NoRestart
```

![image-20250318003517641](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250318003517641.png)

use the `bash` to start the system:

```bash
wsl -l -v
wsl -d Ubuntu-24.04
```



the username and password is

```bash
I donnot update in the markdown = =
```

![image-20250318004410701](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250318004410701.png)

<img src="C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250318004520398.png" alt="image-20250318004520398" style="zoom:50%;" />

we see that the `Ubuntu-24.04` has been installed.

![image-20250318004758417](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250318004758417.png)

```bash
sudo apt update
sudo apt install g++ -y
```

we use the commond to check their version up

```bash
gcc --version
```

![image-20250318090019674](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250318090019674.png)

## Task 2 Use the WSL in visual studio code

Open the `vscode`(Downloaded)

<img src="C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250318091814709.png" alt="image-20250318091814709" style="zoom:50%;" />

We use the `Ctrl`+`Alt`+`O` to command the system, and wait for a while to install the server of WSL

If the connection is successful you will see:

![image-20250318095726482](C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250318095726482.png)

<img src="C:\Users\陈孟欣\AppData\Roaming\Typora\typora-user-images\image-20250318100004986.png" alt="image-20250318100004986" style="zoom:50%;" />

`/mnt/d/Code/Cplusplus/SUST Cpp course/` is a file path, typically used in a `Linux` system to indicate a directory within a mounted Windows file system. Here’s a breakdown of its components:

- **`/mnt/d`**: In Linux, `/mnt` is a mount point directory commonly used for mounting external storage devices or partitions. `/mnt/d` indicates that the D drive from a Windows system is mounted here.
