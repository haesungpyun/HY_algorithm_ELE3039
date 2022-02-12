# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int swapfunc(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}



int *InSort(int insort[])
{
    int i = 0;
    int j = 0;
    int insert;

    for(i = 1; i <40000; i++)
    {
        insert = insort[i];
        for(j = i-1; j >= 0; j--)
        {
            if(insort[j]> insert)
            {

                insort[j+1] = insort[j];
            }
            else
            {
                break;
            }  
        }
        insort[j+1] = insert;
    }
    return insort;
}


int main(void) 
{
    FILE *fin = NULL;
    FILE *fout = NULL;
    int fsorted ;
    int nums[40000] ={0,};
    int i;    

    fin = fopen("./input.txt", "r");
    if(fin == NULL)
    {
        printf("input.txt File Open Error");
        return 1;
    } 
    else
    {
        for(i = 0; i < 40000; i++)
        {
            fscanf(fin, "%d", &nums[i]);
            //printf("%d\n" , nums[i]);
        }
    }
    fclose(fin);

    clock_t start = clock();
    int *sorted = InSort(nums);
    clock_t end = clock();

    fout = fopen("insortoutput.txt", "w");
    for(i = 0; i<40000; i++)
    {
        fsorted = sorted[i];
        fprintf(fout, "%d ", fsorted);
    }
    fclose(fout);

    printf("Insertion sort Time: %0.4lf", (double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}
