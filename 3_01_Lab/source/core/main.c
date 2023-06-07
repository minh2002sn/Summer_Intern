#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "someone.h"

#define MAX_PEOPLE  256

int main()
{
    srand(time(NULL));
    someone_t someone[MAX_PEOPLE];
    
    printf("No\t\tIncome\t\tAction\n");
    for(int i = 0; i < MAX_PEOPLE; i++)
    {
        someone_init(someone + i, rand() % 3);
        printf("%d\t\t", i);
        someone_print_income(someone + i);
        printf("\t\t");
        (someone + i)->action();
    }

    
}