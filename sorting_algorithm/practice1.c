# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>

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
    int temp;

    l = i+i;
    r = i+i+1;
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
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;

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
    int temp;

    build_max_heap(A, heap_size);

    for(i = n; i>1; i--)
    {   
        temp = A[1];
        A[1] = A[i];
        A[i] = temp;
        heap_size = heap_size -1;
        max_heapify(A, 1, heap_size);
    }
}


int main(void)
{
    int nums[10] ={10, 14, 2, 16, 7, 9, 12, 1, 4, 8};
    int i;

    for(i = floor(9/2); i>0; i--)
    {
        printf("%d", i);
        max_heapify(nums, i, 9);
        
    }
    printf("\n");
    for(i = 0; i< 10; i++)
    {
        printf( "%d ", nums[i]);
    }

}



