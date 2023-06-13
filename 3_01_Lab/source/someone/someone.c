#include <stdio.h>
#include <stdint.h>
#include "someone.h"

/* Salary of CONGNHAN type people */
static const uint32_t G_SALARY = 500000;

/* Pointer array of people */
static const void *G_P_INCOME[3] =
{
    "tuytam",
    "henxui",
    &G_SALARY
};

/* Declaration of action fuctions of people */
static void cadge(FILE *p_h_file);
static void stole(FILE *p_h_file);
static void work(FILE *p_h_file);

/* Function pointer array, pointing to action functions */
static action_t G_ACTION[3] =
{
    cadge,
    stole,
    work
};

/*
 * @brief   Initializes private elements of someone_t object according to its type
 * @param   p_h_someone pointer to someone_t structure.
 * @param   type        type of person
 */
void someone_init(someone_t *p_h_someone, type_t type)
{
    p_h_someone->type = type;
    p_h_someone->income = G_P_INCOME[type];
    p_h_someone->action = G_ACTION[type];
}

/*
 * @brief   print income of people to terminal
 * @param   pointer to someone_t structure
 */
void someone_print_income(someone_t *p_h_someone)
{
    if(p_h_someone->type == CONGNHAN)
    {
        printf("%d", *(uint32_t *)G_P_INCOME[p_h_someone->type]);
    }
    else
    {
        printf("%s", (char *)G_P_INCOME[p_h_someone->type]);
    }
}

/*
 * @brief   action of ANXIN type people
 * @param   pointer to FILE structure
 */
static void cadge(FILE *p_h_file)
{
    if(p_h_file == NULL)
        printf("lam on lam phuoc\n");
    else
        fprintf(p_h_file, "lam on lam phuoc\n");
}

/*
 * @brief   action of ANTROM type people
 * @param   pointer to FILE structure
 */
static void stole(FILE *p_h_file)
{
    if(p_h_file == NULL)
        printf("!!!\n");
    else
        fprintf(p_h_file, "!!!\n");
}

/*
 * @brief   action of CONGNHAN type people
 * @param   pointer to FILE structure
 */
static void work(FILE *p_h_file)
{
    if(p_h_file == NULL)
        printf("%d\n", *(uint32_t *)G_P_INCOME[2]);
    else
        fprintf(p_h_file, "%d\n", *(uint32_t *)G_P_INCOME[2]);
}