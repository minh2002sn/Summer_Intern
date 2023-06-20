#include <stdio.h>
#include <stdint.h>

#if 0
uint8_t print_count;

void get_stack_frame(uint64_t param_1, uint64_t param_2)
{
    uint64_t local_var_1 = 1;
    uint64_t local_var_2 = 2;
    // printf("Parameter      [%p]: %ld\n", &param, param);
    // printf("Return address [%p]: 0x%lX\n", &param + 1, *(&param + 1));
    // printf("Base pointer   [%p]: 0x%lX\n", &param + 2, *(&param + 2));
    // printf("Local variable [%p]: %ld\n", &param + 3, *(&param + 3));
    // printf("local_var      [%p]: %ld\n", &local_var, local_var);

    for(int i = -30; i <= 0; i++)
    {
        if(i == 0) printf("-> ");
        printf("[%p]: 0x%lX\n", &param_2 - i, *(&param_2 - i));
    }
    printf("========================================\n");

    if(print_count < 2)
    {
        printf("print_count = %d\n", print_count);
        print_count++;
        get_stack_frame(10, 11);
        // uint64_t return_value = get_stack_frame(11);
    }

    // return local_var_1;
}

int main()
{
    get_stack_frame(9, 10);
    // uint64_t return_value = get_stack_frame(10);
    // printf("return_value's address: %p\n", &return_value);
    printf("print_count's address %p\n", &print_count);
}

#else

#define MAIN_ARG 1

int main();

void func_1(uint64_t param_1, uint64_t param_2)
{
    uint64_t local_var_1 = 1;
    uint64_t local_var_2 = 2;
#if MAIN_ARG
    // for(int i = 0; i < 7; i++)
    // {
    //     printf("                [%p]: %p\n", &param_2 + 22 - i, (void *)*(&param_2 + 22 - i));
    // }

    printf("                [%p]: %p\n", &param_2 + 22, (void *)*(&param_2 + 22));
    printf("                [%p]: %p\n", &param_2 + 21, (void *)*(&param_2 + 21));
    printf("                [%p]: %p\n", &param_2 + 20, (void *)*(&param_2 + 20));
    printf("                [%p]: %p\n", &param_2 + 19, (void *)*(&param_2 + 19));
    printf("                [%p]: %p\n", &param_2 + 18, (void *)*(&param_2 + 18));
    printf("                [%p]: %p\n", &param_2 + 17, (void *)*(&param_2 + 17));
    printf("                [%p]: %p\n", &param_2 + 16, (void *)*(&param_2 + 16));

    printf("___________ main() ___________\n");
    printf("Last PC value   [%p]: %p\n", &param_2 + 15, (void *)*(&param_2 + 15));
    printf("Last EBP value  [%p]: %p\n", &param_2 + 14, (void *)*(&param_2 + 14));
    printf("main_local_var  [%p]: %p\n", &param_2 + 13, (void *)*(&param_2 + 13));
    printf(">: Unknown :<   [%p]: %p\n", &param_2 + 12, (void *)*(&param_2 + 12));
    printf("argc            [%p]: %p\n", &param_2 + 11, (void *)*(&param_2 + 11));
    printf("argv            [%p]: %p\n\n", &param_2 + 10, (void *)*(&param_2 + 10));

#else
    
    printf("___________ main() ___________\n");
    printf("Last PC value   [%p]: %p\n", &param_2 + 13, (void *)*(&param_2 + 13));
    printf("Last EBP value  [%p]: %p\n", &param_2 + 12, (void *)*(&param_2 + 12));
    printf("main_local_var  [%p]: %p\n", &param_2 + 11, (void *)*(&param_2 + 11));
    printf(">: Unknown :<   [%p]: %p\n\n", &param_2 + 10, (void *)*(&param_2 + 10));

#endif

    printf("__________ func_2() __________\n");
    printf("Last PC value   [%p]: %p\n", &param_2 + 9, (void *)*(&param_2 + 9));
    printf("Last EBP value  [%p]: %p\n", &param_2 + 8, (void *)*(&param_2 + 8));
    printf("param_1         [%p]: %ld\n", &param_2 + 7, *(&param_2 + 7));
    printf("param_2         [%p]: %ld\n\n", &param_2 + 6, *(&param_2 + 6));

    printf("__________ func_1() __________\n");
    printf("Last PC value   [%p]: %p\n", &param_2 + 5, (void *)*(&param_2 + 5));
    printf("Last EBP value  [%p]: %p\n", &param_2 + 4, (void *)*(&param_2 + 4));
    printf("local_var_2     [%p]: %ld\n", &param_2 + 3, *(&param_2 + 3));
    printf("local_var_1     [%p]: %ld\n", &param_2 + 2, *(&param_2 + 2));
    printf("param_1         [%p]: %ld\n", &param_2 + 1, *(&param_2 + 1));
    printf("param_2         [%p]: %ld\n\n", &param_2 + 0, *(&param_2 + 0));
}

// void func_2()
void func_2(uint64_t param_1, uint64_t param_2)
{
    func_1(2, 3);
}
#if MAIN_ARG
int main(uint64_t argc, char **argv)
{
    uint64_t main_local_var = 0xFF;
    printf("argc address: %p\n", &argc);
#else
int main()
{
    uint64_t main_local_var = 0xFF;
#endif
    printf("main function address: %p\n", main);
    printf("func_1 function address: %p\n", func_1);
    printf("func_2 function address: %p\n\n", func_2);
    func_2(2, 3);
    // return 0;
}

#endif


