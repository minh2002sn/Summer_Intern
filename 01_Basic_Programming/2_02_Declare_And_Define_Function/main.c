#include <stdio.h>

// Declaration
// Has name, return type, parameter type, number of parameters
int func_1(int a);

// Definition
// Has name, body, return type, parameter type, number of parameters
int func_1(int a)
{
    return a;
}

int main()
{
    printf("%p\n", func_1);
}


