#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define len_command 2
#define num 1000000
#define num_commands 1000000

int* getcommand()
{
    FILE* fin = NULL;
    static int com_list[2*num_commands] = {0,};
    int i=0;
    int target=0;
    char command,space = '\0';
    


    fin = fopen("commandgenerator.txt", "r");

    if(fin == NULL)
    {
        printf("input.txt File Open Error");
        return NULL;
    } 
    else
    {
        for(i = 0; i < 3; i++)
        {   
            fscanf(fin, "%c%d%c", &command,&target,&space);
            com_list[2*i] = (int) command;
            com_list[2*i+1] = target;    
        }
    }
    fclose(fin);

    
    return com_list;
}

int main()
{
    int* commands = NULL;
    commands = getcommand();
    char cc = 'a';
    int j;

    for(int i = 0; i < 3 ; i++)               // command 확인, target 확인 후 tree에 함수 적용
        {
            if (commands[2*i]== 'i')
            {
                cc = commands[2*i];
                j = commands[2*i+1];
                printf("%c%d ", cc, j);
            }
            else if(commands[2*i]== 's')
            {
                cc = commands[2*i];
                j = commands[2*i+1];
                printf("%c%d ", cc, j);
            }
            else
            {
                 cc = commands[2*i];
                j = commands[2*i+1];
                printf("%c%d ", cc, j);
            }
        } 
}

