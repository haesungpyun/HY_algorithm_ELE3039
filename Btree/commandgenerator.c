#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define len_command 2
#define max_num 100
#define num_commands 100


int main()
{
    FILE *fout = NULL;
    int random = 0;
    char command[] = " ids";
    int j;
    int i;

    srand(time(NULL));
    
    fout = fopen("input.txt", "w");

    for (i = 0; i < num_commands; i++)
    {   
        random = rand() % max_num + 1;
        j = rand() % 3 + 1;
        command[j];

        fprintf(fout, "%c%d ", command[j], random);
    }
}