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

/*
int *BubSort(int bubsort[])
{
    int i = 0;
    int j = 0;

    for(i = 9999; i >0; i--)
    {
        for(j = 0; j < i; j++)
        {
            if(bubsort[j] > bubsort[j+1])
            {
                swapfunc(&bubsort[j],&bubsort[j+1]);
            }
        }
        
    }
    return bubsort;
}
*/

int *BubSort(int bubsort[], int n, int i)
{
    int j ;
    if (i == n-1) return bubsort;
    for(j = n-1; j > i; j--)
    {
        if(bubsort[j] < bubsort[j-1])
        {
            swapfunc(&bubsort[j],&bubsort[j-1]);
        }
    }
    *BubSort(bubsort, n, i+1);
    return bubsort;
}


int main(void) 
{
    FILE *fin = NULL;
    FILE *fout = NULL;
    int fsorted ;
    int nums[40000] ={0,};
    int i;
    
    

    fin = fopen("input.txt", "r");
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
    int *sorted = BubSort(nums, 40000, 0);
    clock_t end = clock();

    fout = fopen("bubsortoutput.txt", "w");
    for(i = 0; i < 40000; i++)
    {
        fsorted = sorted[i];
        fprintf(fout, "%d ", fsorted);
    }
    fclose(fout);

    printf("Bubble sort Time: %0.4lf", (double)(end-start)/CLOCKS_PER_SEC);

}
