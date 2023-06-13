#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "output.h"
#include "someone.h"

/* Max number of people */
#define MAX_PEOPLE          255

/* direction from bin folder */
#define OUTPUT_FOLDER_DIR   "./output/"

/*
 * @brief   write type and action to output/output.txt file
 * @param   num_people  number of people
 * @return  if success, return 0; otherwise, return 1
 */
int output_handle(uint8_t num_people)
{
    /* Check parameter num_people */
    if(num_people > MAX_PEOPLE)
        num_people = MAX_PEOPLE;

    /* Initialization */
    someone_t h_someone[num_people];

    /* Open output.txt file */
    FILE *p_h_output_file = fopen(OUTPUT_FOLDER_DIR "output.txt", "w");
    
    /* Create output folder if it did not exit */
    if(p_h_output_file == NULL)
    {
        mkdir(OUTPUT_FOLDER_DIR, S_IRWXU);
        p_h_output_file = fopen(OUTPUT_FOLDER_DIR "output.txt", "w");
        if(p_h_output_file == NULL)
            return 1;
    }

    /* Print output.txt file */
    fprintf(p_h_output_file, "No.\tType\tAction\n");
    for(int i = 0; i < num_people; i++)
    {
        /* Random type for every people */
        someone_init(h_someone + i, rand() % 3);
        fprintf(p_h_output_file, "%d\t%d\t", i, (h_someone +i)->type);
        (h_someone + i)->action(p_h_output_file);
    }

    fclose(p_h_output_file);

    return 0;
}
