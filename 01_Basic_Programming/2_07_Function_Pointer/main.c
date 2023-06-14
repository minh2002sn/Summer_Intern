#include <stdio.h>

void print_int(int a)
{
    printf("int var = %d\n", a);
}

int main()
{
    void (*fptr)(int);  // Define function pointer 
    fptr = print_int;   // Store print_int address to function pointer
    fptr(10);           // Call function by using function pointer

    return 0;
}


