#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **allocate_string_array(int array_length, int string_length)
{
    /* TODO: Allocate string array here */
    /* Food for thought: Why can we just return a char ** here while
       the local variable is deleted after the end of the function call? */
}

void free_string_array(char **all_names, int array_length)
{
    /* TODO: Free the string array here */
}

void sort_strings(char **strings, int array_length)
{
    /* TODO: Sort the strings here */
}

void main()
{
    char **all_names;
    FILE *fp;
    int counter = 0;

    all_names = allocate_string_array(100,20);
    fp = fopen("names.txt", "r");
    while (!feof(fp))
    {
        fgets(all_names[counter], 20, fp);
        counter++;
    }
    fclose(fp);
    sort_strings(all_names,counter);
    for (int i=0;i<counter;i++)
        printf("%s", all_names[i]);
    free_string_array(all_names, 100);
}
