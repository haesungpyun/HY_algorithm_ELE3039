# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>

int swapfunc(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void quick_sort(int A[], int start, int end);
int partition(int A[], int start, int end);

int partition(int A[], int start, int end)
{
    int pivot;
    int i;
    int j;

    pivot = A[end];
    i = start-1;

    for(j=start; j < end; j++)
    {
        if(A[j] <= pivot)
        {
            i = i+1;
            swapfunc(&A[i], &A[j]);
        }
    }
    swapfunc(&A[i+1], &A[end]);
    return i+1;
}

void quick_sort(int A[], int start, int end)
{
    int mid;

    if(start<end)
    {
        mid = partition(A, start, end);
        quick_sort(A, start, mid-1);
        quick_sort(A, mid+1, end);

    }
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
    quick_sort(nums, 0, 40000);
    clock_t end = clock();

    fout = fopen("quicksortoutput.txt", "w");
    for(i = 0; i < 40001; i++)
    {
        fsorted = nums[i];
        fprintf(fout, "%d ", fsorted);
    }
    fclose(fout);

    printf("Quick sort Time: %0.6lf", (double)(end-start)/CLOCKS_PER_SEC);
}