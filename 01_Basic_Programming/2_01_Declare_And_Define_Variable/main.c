#include <stdio.h>

// Declaration
extern int declared_var; // has data type, name

// Definition
int c; // has data type, name, address, memory.

// Definition and initialize
int d = 5; // has data type, name, address, memory and value in memory.

int main()
{
    int declared_var = 5; // define the declared variable
    printf("[%p]: %d\n", &declared_var, declared_var);
}

