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

void max_heapify(int A[], int i, int heap_size);
void build_max_heap(int A[], int heap_size);
void heap_sort(int A[], int n);

void max_heapify(int A[], int i, int heap_size)
{
    int l;
    int r;
    int largest;
    l = 2*i;
    r = 2*i+1;
    largest = i;
    
    if((l<= heap_size) && (A[l]>A[largest]))
    {
        largest = l;
    }
    
    if((r<= heap_size) && (A[r]>A[largest]))
    {
        largest = r;
    }
    if(largest != i)   
    {
        swapfunc(&A[i], &A[largest]);
        max_heapify(A, largest, heap_size);
    }    
    
}

void build_max_heap(int A[], int heap_size)
{
    int i;
    for(i = floor(heap_size/2); i>0; i--)
    {
        max_heapify(A, i, heap_size);
    }
}

void heap_sort(int A[], int n)
{
    int i;
    int heap_size;
    heap_size = n-1;

    build_max_heap(A, heap_size);

    for(i = n-1; i>1; i--)
    {
        swapfunc(&A[1], &A[i]);
        heap_size = heap_size-1;
        max_heapify(A, 1, heap_size);
    }
}


int main(void)
{
    FILE *fin = NULL;
    FILE *fout = NULL;
    int fsorted ;
    int nums[40001] ={40000,};
    int i;
    
    

    fin = fopen("input.txt", "r");
    if(fin == NULL)
    {
        printf("input.txt File Open Error");
        return 1;
    } 
    else
    {
        for(i = 1; i < 40001; i++)
        {
            fscanf(fin, "%d", &nums[i]);
            //printf("%d\n" , nums[i]);
        }
    }
    fclose(fin);

    clock_t start = clock();
    heap_sort(nums, 40001);
    clock_t end = clock();

    fout = fopen("heapsortoutput.txt", "w");
    for(i = 1; i < 40001; i++)
    {
        fsorted = nums[i];
        fprintf(fout, "%d ", fsorted);
    }
    fclose(fout);

    printf("Heap sort Time: %0.6lf", (double)(end-start)/CLOCKS_PER_SEC);
}