# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>
void Merge(int mergesort[], int p, int q, int r);

void Merge(int mergesort[], int p, int q, int r)
{
    int i = p;
    int j = q+1;
    int k = p;
    int temp[10000];

    while(i <= q && j <= r){
        if(mergesort[i] < mergesort[j]){
            temp[k] = mergesort[i]; i ++; k++;}
        
        else if (mergesort[i] == mergesort[j]){
            temp[k] = mergesort[i]; i ++; k++;
            temp[k] = mergesort[j]; j ++; k++;}
        
        else{temp[k] = mergesort[j]; j ++; k++;}}

    for(i; i<= q; i++) {temp[k] = mergesort[i]; k ++;}
    for(j; j<= r; j++) {temp[k] = mergesort[j]; k ++;}
    for(int l = p; l <= r; l++) {mergesort[l] = temp[l];}
}

/*
int main()
{
    int r = 8;
    int p = 0;
    int level = 0;
    int height = 0;
    int iteration = 0;
    int length = r-p + 1 ;
    int i = 0; 
    int mergesort[9] = {5,2,1,6,11,8,12,4,0};
    int onemore = 0;
    int start = 0;
    int mid = 0;
    int end = 0;
    int jump = 0;
    
    
    
    height = floor(log2(length));
    printf("height: %d\n", height);

    for(level = 0; level<height; level++)
    {
        onemore = 1;
        start = 0;
        end = (pow(2, level+1)-1);
        mid = floor((start+end)/2);

        iteration = ceil((length)/pow(2,level+1));

        printf("level: %d \n", level);
        printf("iteration: %d \n", iteration);
    
        for(i = 0; i < iteration; i++)
        {
            printf("i : %d \n", i);
            

            for(int j = 0; j < length; j++ ) //mergesort 내용물 확인
            {
                printf("%d ",  mergesort[j]);
            }
            printf("\n");

            printf("merge start, mid, end: %d, %d, %d \n", start, mid, end);
            Merge(mergesort, start, mid, end);

            for(int j = 0; j < length; j++ ) //mergesort 내용물 확인
            {
                printf("%d ",  mergesort[j]);
            }
            printf("\n");

            start = start + pow(2, level+1);
            end = end + pow(2, level+1);
            mid = floor((start+end)/2);

            if ((start > length-1) && (onemore == 0))
            {
                break;
            }
            if((start < length -1) && (end > length-1) && (onemore == 1 ))
            {   
                printf("end over range so one more iteration and break \n");
                start = start - pow(2, level+1);
                mid = end-pow(2, level+1);
                end = length -1;
                Merge(mergesort, start, mid, end);
                break;
                
            }
            printf("next merge start, mid, end: %d, %d, %d \n", start, mid, end);

           
            printf("\n");
        }
        printf("\n");
    }
}
*/
int main()
{
    int r = 8;
    int p = 0;
    int level = 0;
    int height = 0;
    int iteration = 0;
    int length = r-p + 1 ;
    int i = 0; 
    int mergesort[9] = {5,12,1,6,11,8,4,2,0};
    int start = 0;
    int mid = 0;
    int end = 0;
    int jump = 0;
    
    
    
    height = floor(log2(length));
    printf("height: %d\n", height);

    for(level = 0; level<height; level++)
    {
        jump = pow(2, level+1);

        start = 0;
        end = (jump-1);
        mid = floor((start+end)/2);

        iteration = ceil((length)/jump);

        printf("level: %d \n", level);
        printf("jump: %d \n", jump);
        printf("iteration: %d \n", iteration);
    
        for(i = 0; i < iteration; i++)
        {
            printf("i : %d \n", i);
            

            for(int j = 0; j < length; j++ ) //mergesort 내용물 확인
            {
                printf("%d ",  mergesort[j]);
            }
            printf("\n");

            printf("merge start, mid, end: %d, %d, %d \n", start, mid, end);
            Merge(mergesort, start, mid, end);

            for(int j = 0; j < length; j++ ) //mergesort 내용물 확인
            {
                printf("%d ",  mergesort[j]);
            }
            printf("\n");
            
            printf("merge start+jump, end+jump, r: %d, %d, %d \n", start+jump, end + jump, length-1);

            

            if ((start + jump > length-1))
            {
                break;
            }
            if((start + jump < length) && (end + jump> length-1))
            {   
                printf("end over range so one more iteration and break \n");
                mid = end;
                end = length -1;
                printf("break merge start, mid, end: %d, %d, %d \n", start, mid, end);
                Merge(mergesort, start, mid, end);

                for(int j = 0; j < length; j++ ) //mergesort 내용물 확인
                {
                    printf("%d ",  mergesort[j]);
                }
                printf("\n");
                break;
                
            }

            
            start = start + jump;
            end = end + jump;
            mid = floor((start+end)/2);

            printf("next merge start, mid, end: %d, %d, %d \n", start, mid, end);

            printf("\n");
        }
        printf("\n");
    }
}

/*
int main()
{
    int r = 8;
    int p = 0;
    int level = 0;
    int height = 0;
    int iteration = 0;
    int length = r-p + 1 ;
    int i = 0; 
    int mergesort[9] = {5,12,1,6,11,8,2,4,0};
    int onemore = 0;
    int start = 0;
    int mid = 0;
    int end = 0;
    int jump = 0;
    
    height = ceil(log2(r+1));

    for(level = 0; level<height; level++)
    {   
        jump = pow(2, level+1);
        onemore = 1;

        start = 0;
        end = (jump-1);
        mid = floor((start+end)/2);

        iteration = ceil((r+1)/jump);
    
        for(i = 0; i < iteration; i++)
        {
            if((start + jump < r) && (end + jump > r) && (onemore == 1))
            {   
                mid = end;
                end = r;
                Merge(mergesort, start, mid, end);
                onemore =0;
                break;
            }
            if ((start + jump > r) && (onemore == 0)){break;}
            
            Merge(mergesort, start, mid, end);
            start = start + jump;
            end = end + jump;
            mid = floor((start+end)/2);
        }
        
    }
    for(i = 0; i<9; i++)
    {
        printf("%d ", mergesort[i]);
    }
}
*/




