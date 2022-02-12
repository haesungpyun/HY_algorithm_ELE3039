# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>


void Merge(int mergesort[], int start, int mid, int end);
void MergeSort(int mergesort[], int start, int end);

void Merge(int mergesort[], int start, int mid, int end)
{
    int i = start;
    int j = mid+1;
    int k = 0;
    int temp[end-start+1];

    while(i <= mid && j <= end)
    {
        if(mergesort[i] < mergesort[j])
        {
            temp[k] = mergesort[i]; i ++; k++;
        }
        else if (mergesort[i] == mergesort[j])
        {
            temp[k] = mergesort[i]; i ++; k++;
            temp[k] = mergesort[j]; j ++; k++;
        }
        else
        {
            temp[k] = mergesort[j]; j ++; k++;
        }
    }

    for(i; i<= mid; i++)
    {
        temp[k] = mergesort[i]; k ++;
    }
    for(j; j<= end; j++)
    {
        temp[k] = mergesort[j]; k ++;
    }
    for(int l = 0; l < end-start+1; l++)
    {
        mergesort[l+start] = temp[l];
    }
}

void MergeSort(int mergesort[], int start, int end)
{
    
    if (start < end)
    {   
        int mid = floor((start+end)/2);
        MergeSort(mergesort, start, mid);
        MergeSort(mergesort, mid+1, end);
        Merge(mergesort, start, mid, end);
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
    MergeSort(nums, 0, 39999);
    clock_t end = clock();

    fout = fopen("mergesortoutput.txt", "w");
    for(i = 0; i < 40000; i++)
    {
        fsorted = nums[i];
        fprintf(fout, "%d ", fsorted);
    }
    fclose(fout);

    printf("Merge sort Time: %0.6lf", (double)(end-start)/CLOCKS_PER_SEC);

}
