#include <stdio.h>
#include "func.h"
#include "func2.h"

#define FUNCTION_ENABLE 0
#define WEAK_ENABLE     0

__attribute__((weak)) int a;
__attribute__((weak)) int b;

#if FUNCTION_ENABLE
#if WEAK_ENABLE
__attribute__((weak))
#endif
int func_mul(int a, int b)
{
    return 0;
}

#if WEAK_ENABLE
__attribute__((weak))
#endif
int func_sum(int a, int b)
{
    return 0;
}
#endif

int main(int argc, char **argv)
{
    printf("%d\n", func_mul(3, 3));
    printf("%d\n", func_sum(3, 3));
    printf("%X\n", a);

    return 0;
}