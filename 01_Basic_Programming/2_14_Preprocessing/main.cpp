/* Macro */
#define PRINT_CHAR(x)   printf("%c\n", #@ x)
#define MAKE_CHAR(x)    #@ x

/* main function */
int main()
{
    // PRINT_CHAR(M);
    printf("%c\n", MAKE_CHAR(a));
}