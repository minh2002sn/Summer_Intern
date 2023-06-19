#include <stdio.h>
#include "func.h"

int main(int argc, char **argv)
{
    printf("%d\n", func_cal(3, 4));
    // if(argc >= 3)
    // {
    //     printf("%d\n", func_cal(argv[1][0] - '0', argv[2][0] - '0'));
    // }
    return 0;
}