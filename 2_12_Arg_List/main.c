#include <stdio.h>
#include <stdarg.h>

float avg(int num, ...)
{
    int sum = 0;
    va_list ap;
    va_start(ap, num);
    for(int i = 0; i < num; i++)
    {
        sum += va_arg(ap, int);
    }
    va_end(ap);
    return sum / num;
}

int main()
{
    printf("Average of 3, 4, 5 = %f\n", avg(3, 3, 4, 5));
    printf("Average of 7, 8, 9, 10, 11 = %f\n", avg(5, 7, 8, 9, 10, 11));
}



