#include <stdio.h>
#include <string.h>

struct PERSON_t
{
    char name[20];
    unsigned int age;
} per_1;

int main()
{
    struct PERSON_t per_2 = {"An", 18};
    struct PERSON_t per_3 = 
    {
        .age = 10,
        .name = "Na"
    };
    per_1.age = 20;
    strcpy(per_1.name, "Beo");
    return 0;
}
