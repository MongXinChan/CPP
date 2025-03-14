# Improve your source code
> Why we need to improve our source code?
>
> - Easy to read
> - Easy to maintain
> - Easy to debug
> - Easy to extend
> - Easy to reuse
> - Easy to test
> - Easy to ...
Yep,improving the source code can help us to complete the above goals,We can debugging better than if we not, but how to improve it?

we can see the [project3](../projects/2021Fall/project3.md), It use the `c` language to implement the `c++` language, and we will understand what the difference between them.

- The project only use `c` language for implementing the matrices times.
    - Firstly, Design a `struct` for matrices.

## Suggestions to your project 3
- Use `size_t` for mat.cols and mat.rows
    - the `size_t` means the range of the type is [0,2^32-1]
    - the matrices can't be beyond 2g * 4(because there're `float` type).
- Use memcpy() to copy data. Element assignment has a lower efficiency.
    - although we use double for loop to copy data, but the time complexity is $O(n^2)$
    - so we use the `memcpy()` to copy data, the time complexity is $O(n)$
- Use 1D array (float*) nor 2D array (float**) for matrix data.
    - the probability of leaking memory is heighter, if we use 1D array.
    - because we use 1D array, we need to use the `malloc()` to allocate memory **frequently**.
    - and the memory is not continuous, so we need to use the `memcpy()` to copy data.
- Redundant computation in loops
    - Staring at the code and considering that what's the best way to implement the function?Does I think it's easy to understand?
- **Do parameter checking in functions**: null pointers, dimension matching in  matrix operations, etc.
    - To many problmes derive from the `statement`.
- Do not bind the create matrix function with file I/O.
    - If we use the path, we usually not use the absolute path.
- File name: 1.c, 2.c, 3.h
    - we could not understand the code if we not use the same series of file name.
    - And we use the **little words to name the file**.
- Good implementation VS good homework
    - Not only just implement the function, but also think about the time complexity.

## head file
The `head file` only contains the function name and the parameter list.Do not include the function body.(or we called implements)
And we use that:
```h
#ifndef _MATRIX_H
#define _MATRIX_H
...
#endif
```
as the head of the head file.
It's a way to avoid the multiple inclusion of the head file.
```c
typedef struct Matrix_{
    ...
}Matrix;
```
Because in `c` language, if we use the struct , we need to spell `struct Matrix_`,not like the class in `c++` :just use the `Matrix`, so we use the **key words `typedef` to define the struct**.
```c
Matrix * createMat(size_t rows, size_t cols);
bool releaseMat(Matrix * p);
bool add(const Matrix * input1, const Matrix * input2, Matrix *output);
```

now let's see the [matrix](./examples/matrix/matrix.c),we use so many line to slove the pointer problem.(line 8 ~ line 32).
There're some tips in the code.
Such as:
- Check the pointer after we allocate the memory.
- A function just do one thing, it means that we do not finish multiple things in one function.