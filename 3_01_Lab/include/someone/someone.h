/*
 * @file    someone.h
 * @brief   Header file of someone module
 */
#ifndef SOMEONE_H
#define SOMEONE_H

#include <sys/stat.h>

/*
 * @brief   type_t enumeration definition
 */
typedef enum
{
    ANXIN,
    ANTROM,
    CONGNHAN,
} type_t;

/*
 * @brief   action_t function pointer definition
 */
typedef void (*action_t)(FILE *);

/*
 * @brief   someone_t structure definition
 */
typedef struct
{
    // Public
    type_t type;

    // Private
    const void *income;
    action_t action;
} someone_t;

void someone_init(someone_t *p_h_someone, type_t type);
void someone_print_income(someone_t *p_h_someone);

#endif /* SOMEONE_H */
