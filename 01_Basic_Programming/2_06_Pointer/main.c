#include <stdio.h>

int a = 0xFF;
int b = 0xEE;
const int c = 0xAA;
int main()
{
    // char *p_c = NULL;
    char *p_c = "Minh";
    printf("%p\n", &a);
    printf("%p\n", p_c);
}


// void func_1(int *ptr)
// {
//     *ptr = 5;
// }

// int main()
// {
//     int var = 10;
//     func_1(&var);
//     printf("Print from main function: a = %d\n", var);
// }


// int main()
// {

//     int var = 20;   // variable definition
//     int *ptr;       // pointer definition
//     ptr = &var;     // store variable's address to pointer variable
//     *ptr = 15;      // change variable value by using pointer

// }
