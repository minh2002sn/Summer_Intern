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

int main();

void func_1(uint64_t param_1, uint64_t param_2)
{
    uint64_t local_var_1 = 1;
    uint64_t local_var_2 = 2;

    printf("___________ main() ___________\n");
    printf("Last PC value   [%p]: %p\n", &param_2 + 13, (void *)*(&param_2 + 13));
    printf("Last EBP value  [%p]: %p\n", &param_2 + 12, (void *)*(&param_2 + 12));
    printf("main_local_var  [%p]: %p\n", &param_2 + 11, (void *)*(&param_2 + 11));
    printf(">: Unknow :<    [%p]: %p\n\n", &param_2 + 10, (void *)*(&param_2 + 10));

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

void func_2(uint64_t param_1, uint64_t param_2)
{
    func_1(param_1, param_2);
}

void func(int a,int b)
{
    uint64_t loc = 0;
    char *sp = (char*)&loc;

    printf("main = %p\n", main);
    printf("return address = %p\n", *(void**)(sp + 24));
    printf("saved rbp = %p\n", *(void**)(sp + 16));
    printf("sp = %p\n", *(void**)(sp + 8));
    printf("loc = %ld\n", *(uint64_t*)(sp));
    printf("a = %d\n", *(int*)(sp - 4));
    printf("b = %d\n", *(int*)(sp - 8));
}

int main()
{
    uint64_t main_local_var = 0xFF;
    printf("main function address: %p\n\n", main);
    printf("func_1 function address: %p\n\n", func_1);
    printf("func_2 function address: %p\n\n", func_2);
    func_2(2, 3);
    // return 0;
}

#endif


