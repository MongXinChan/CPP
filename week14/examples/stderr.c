#include <stdio.h>

void div2(int n)
{
    if( n % 2 != 0)
    {
        fprintf(stderr, "Error: The input must be an even number. Here it's %d\n", n);
    }
    else
    {
        int result = n / 2;
        fprintf(stdout, "Info: The result is %d\n", result);
    }
    return;
}

int main()
{
    for(int n = -5; n <= 5; n++)
        div2(n);
    return 0;
}

/**** 
 * 
 * recommendation:
 * 1. use fprintf(stderr, "Error: ...\n", ...) to output error message
 * 2. use fprintf(stdout, "Info: ...\n", ...) to output info message
 * 
 * It is a good practice to separate error message from info message.
 * 
 * If you wanna learn more about fprintf, 
 * you can refer to the link below:
 * https://www.bilibili.com/video/BV1Vf4y1P7pq?p=62&vd_source=ea3c25b2fb27b611411c3ed78cb9f61f
 * time : 13:04
 * 
 * ****/