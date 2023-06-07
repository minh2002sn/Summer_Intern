#include <stdio.h>
#include <stdint.h>
#include "someone.h"

static uint32_t SALARY = 500000;

static void* INCOME[3] =
{
    "tuytam",
    "henxui",
    &SALARY
};

static void cadge();
static void stole();
static void work();

static action_t ACTION[3] =
{
    cadge,
    stole,
    work
};

void someone_init(someone_t *psomeone, type_t type)
{
    psomeone->type = type;
    psomeone->income = INCOME[type];
    psomeone->action = ACTION[type];
}

void someone_print_income(someone_t *psomeone)
{
    if(psomeone->type == CONGNHAN)
    {
        printf("%d", *(uint32_t *)INCOME[psomeone->type]);
    }
    else
    {
        printf("%s", (char *)INCOME[psomeone->type]);
    }
}

static void cadge()
{
    printf("lam on lam phuoc\n");
}

static void stole()
{
    printf("!!!\n");
}

static void work()
{
    printf("%d\n", *(uint32_t *)INCOME[2]);
}