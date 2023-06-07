#ifndef _SOMEONE_H
#define _SOMEONE_H

typedef enum
{
    ANXIN,
    ANTROM,
    CONGNHAN,
} type_t;

typedef void (*action_t)();

typedef struct
{
    // public
    type_t type;

    // private
    void *income;
    action_t action;
} someone_t;

void someone_init(someone_t *psomeone, type_t type);
void someone_print_income(someone_t *psomeone);

#endif
