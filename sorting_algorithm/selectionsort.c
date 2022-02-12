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
int *SelSort(int selsort[])
{
    int minindex = 0;
    int i = 0;
    int j = 0;
    

    for(i = 0; i <10000; i++)
    {
        minindex = i;
        for(j = i+1; j <10000; j++)
        {
            if(selsort[minindex] > selsort[j])
            {
                minindex = j;
            }
        }
        
        swapfunc(&selsort[minindex],&selsort[i]);
        
    }
    return selsort;
}*/


int *SelSort(int selsort[], int n, int k)
{
    int minindex = k;
    int j;

    if (k == n-1) return selsort;
    for(j = k+1; j <n; j++)
    {
        if(selsort[minindex] > selsort[j])
        {
            minindex = j;
        }
    }
    swapfunc(&selsort[minindex],&selsort[k]);
    *SelSort(selsort, n, k+1);
    
    return selsort;
}



int main(void) // 아직 파일 받아오는 것을 구현 못함
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
    int *sorted = SelSort(nums, 40000, 0);
    clock_t end = clock();

    fout = fopen("selsortoutput.txt", "w");
    for(i = 0; i<40000; i++)
    {
        fsorted = sorted[i];
        fprintf(fout, "%d ", fsorted);
    }
    fclose(fout);

    printf("Selection sort Time: %0.4lf", (double)(end-start)/CLOCKS_PER_SEC);

}


