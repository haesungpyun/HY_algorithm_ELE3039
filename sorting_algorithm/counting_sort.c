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

# define length 40000
# define max_num 60000

int *counting_sort(int nums[])
{
    int i = 0;
    int j = 0;
    int sorted_arr[length]={0,};
    int idx_arr[max_num]={0,};

    for(j=1; j<length; j++)
    {
        idx_arr[nums[j]] = idx_arr[nums[j]]+1;
    } 
    for(i=1; i<max_num; i++)
    {
        idx_arr[i] = idx_arr[i]+idx_arr[i-1];
    }
    for(j=length-1; j>=1; j--)
    {
        sorted_arr[idx_arr[nums[j]]] = nums[j];
        idx_arr[nums[j]] = idx_arr[nums[j]]-1;
    }
    for(i=0; i<length; i++)
    {
        nums[i] = sorted_arr[i];
    }

    return nums;
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
        }
    }
    fclose(fin);

    clock_t start = clock();
    int *sorted = counting_sort(nums);
    clock_t end = clock();

    fout = fopen("counting_sortoutput.txt", "w");
    for(i = 0; i<40000; i++)
    {
        fsorted = sorted[i];
        fprintf(fout, "%d ", fsorted);
    }
    fclose(fout);

    printf("Counting sort Time: %0.4lf", (double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}
