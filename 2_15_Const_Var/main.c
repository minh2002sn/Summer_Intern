#include <stdio.h>

const int a = 10;

int main()
{
    const int b = 5;
    int *a_ptr = &a;
    int *b_ptr = &b;
    // a = 15;
    // b = 20;
    *a_ptr = 15;
    *b_ptr = 20;
}

