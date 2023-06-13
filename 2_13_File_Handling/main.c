#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    FILE *pfile = fopen("output/output.txt", "r");
    char str[256];

    printf("Start\n");
    if(pfile == NULL)
    {
        printf("Create ""output"" folder\n");
        mkdir("output", S_IRWXU);
        pfile = fopen("output/output.txt", "w");
        if(pfile == NULL)
            return 1;
    }

    while(fgets(str, 50, pfile) != NULL)
    {
        printf("%s", str);
    }

    fputc('M', pfile);
    fputs("inh\n", pfile);
    fprintf(pfile, "%s %d\n", "ABC", 113);

    fclose(pfile);

    return 0;
}