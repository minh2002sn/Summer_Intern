#include <stdio.h>

void func_1(int *ptr)
{
    *ptr = 5;
}

int main()
{
    int var = 10;
    func_1(&var);
    printf("Print from main function: a = %d\n", var);
}

/*
int main()
{

    int var = 20;   // variable definition
    int *ptr;       // pointer definition
    ptr = &var;     // store variable's address to pointer variable
    *ptr = 15;      // change variable value by using pointer

}
*/