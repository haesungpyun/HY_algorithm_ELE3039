# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>


void Merge(int mergesort[], int p, int q, int r);
void MergeSort(int mergesort[], int p, int r);

void Merge(int mergesort[], int start, int mid, int end)
{
    int i = start;
    int j = mid+1;
    int k = start;
    int temp[40000];

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
    for(int l = start; l <= end; l++)
    {
        mergesort[l] = temp[l];
    }
}


void MergeSort(int mergesort[], int p, int r)
{
    int level = 0;
    int height = 0;
    int iteration = 0;
    int i = 0; 
    int start = 0;
    int mid = 0;
    int end = 0;
    int jump = 0;
    
    height = ceil(log2(r+1));

    for(level = 0; level<height; level++)
    {   
        jump = pow(2, level+1);

        start = 0;
        end = (jump-1);
        mid = floor((start+end)/2);

        iteration = ceil((r+1)/jump);
    
        for(i = 0; i < iteration; i++)
        {
            Merge(mergesort, start, mid, end);
            if ((start + jump > r)){break;}
            if((start + jump < r) && (end + jump > r))
            {   
                mid = end;
                end = r;
                Merge(mergesort, start, mid, end);
                break;
            }
            
            start = start + jump;
            end = end + jump;
            mid = floor((start+end)/2);
        }
        
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

    fout = fopen("sequentialmergesortoutput.txt", "w");
    for(i = 0; i < 40000; i++)
    {
        fsorted = nums[i];
        fprintf(fout, "%d ", fsorted);
    }
    fclose(fout);

    printf("Sequential merge sort Time: %0.6lf", (double)(end-start)/CLOCKS_PER_SEC);

}
