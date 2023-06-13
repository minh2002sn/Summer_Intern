#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "input.h"

/* Max number of people */
#define MAX_PEOPLE      255

/*
 * @brief   Receive number of people from user
 * @param   pointer to int variable that storing number of people
 */
void input_handle(int *p_num_people)
{
    /* Random number of people in range 0 - 255 */
    *p_num_people = rand() % MAX_PEOPLE;
}
