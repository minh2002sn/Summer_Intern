#include <stdio.h>

const int c = 10;

int main()
{
    int *ptr = &c;
    printf("[1] Code still correct here.\n");
    *ptr = 5;
}


    // void *a = (void *)main - 0x1000000000000000;
    // printf("[1] Code still correct here.\n");
    // printf("%d\n", *((int *)a));
    // printf("[2] Code still correct here.\n");
// }    