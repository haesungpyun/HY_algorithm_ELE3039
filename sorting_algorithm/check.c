# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main(void) // 아직 파일 받아오는 것을 구현 못함
{
    FILE *fin = NULL;
    FILE *fout = NULL;
    int fsorted ;
    int snums[40000] ={0,};
    int bnums[40000] ={0,};
    int inums[40000] ={0,};
    int mnums[40000] ={0,};
    int seqmnums[40000] ={0,};
    int hnums[40000] ={0,};
    int qnums[40000] ={0,};
    int randqnums[40000] ={0,};
    int i;
    int j;
    int k;
    
    

    fin = fopen("selsortoutput.txt", "r");
    if(fin == NULL)
    {
        printf("input.txt File Open Error");
        printf("%d", fin);
        return 1;
    } 
    else
    {
        for(i = 0; i < 40000; i++)
        {
            fscanf(fin, "%d", &snums[i]);
            //printf("%d\n" , nums[i]);
        }
    }
    fclose(fin);

    fin = fopen("bubsortoutput.txt", "r");
    if(fin == NULL)
    {
        printf("input.txt File Open Error");
        printf("%d", fin);
        return 1;
    } 
    else
    {
        for(i = 0; i < 40000; i++)
        {
            fscanf(fin, "%d", &bnums[i]);
            //printf("%d\n" , nums[i]);
        }
    }
    fclose(fin);

    fin = fopen("insortoutput.txt", "r");
    if(fin == NULL)
    {
        printf("input.txt File Open Error");
        printf("%d", fin);
        return 1;
    } 
    else
    {
        for(i = 0; i < 40000; i++)
        {
            fscanf(fin, "%d", &inums[i]);
            //printf("%d\n" , nums[i]);
        }
    }
    fclose(fin);

    fin = fopen("mergesortoutput.txt", "r");
    if(fin == NULL)
    {
        printf("input.txt File Open Error");
        printf("%d", fin);
        return 1;
    } 
    else
    {
        for(i = 0; i < 40000; i++)
        {
            fscanf(fin, "%d", &mnums[i]);
            //printf("%d\n" , nums[i]);
        }
    }
    fclose(fin);

    fin = fopen("sequentialmergesortoutput.txt", "r");
    if(fin == NULL)
    {
        printf("input.txt File Open Error");
        printf("%d", fin);
        return 1;
    } 
    else
    {
        for(i = 0; i < 40000; i++)
        {
            fscanf(fin, "%d", &seqmnums[i]);
            //printf("%d\n" , nums[i]);
        }
    }
    fclose(fin);


    fin = fopen("heapsortoutput.txt", "r");
    if(fin == NULL)
    {
        printf("input.txt File Open Error");
        printf("%d", fin);
        return 1;
    } 
    else
    {
        for(i = 0; i < 40000; i++)
        {
            fscanf(fin, "%d", &hnums[i]);
            //printf("%d\n" , nums[i]);
        }
    }
    fclose(fin);



    fin = fopen("quicksortoutput.txt", "r");
    if(fin == NULL)
    {
        printf("input.txt File Open Error");
        printf("%d", fin);
        return 1;
    } 
    else
    {
        for(i = 0; i < 40000; i++)
        {
            fscanf(fin, "%d", &qnums[i]);
            //printf("%d\n" , nums[i]);
        }
    }
    fclose(fin);


    fin = fopen("randquicksortoutput.txt", "r");
    if(fin == NULL)
    {
        printf("input.txt File Open Error");
        printf("%d", fin);
        return 1;
    } 
    else
    {
        for(i = 0; i < 40000; i++)
        {
            fscanf(fin, "%d", &randqnums[i]);
            //printf("%d\n" , nums[i]);
        }
    }
    fclose(fin);


// check start
    for(i = 0; i<40000; i++)
    {
        if((snums[i] == inums[i]) && (snums[i] == bnums[i]) 
        && (bnums[i] == inums[i]) && (snums[i]== mnums[i])
        && (snums[i]== seqmnums[i]) && (snums[i]== hnums[i])
        && (snums[i]== qnums[i]))
        {
            continue;
        }
        else
        {
            printf("different Error at %d , sel = %d, bub = %d, in= %d, merge = %d", i, snums[i], bnums[i], inums[i], mnums[i]);
            printf("different Error at %d , seqm = %d,heap = %d, quick = %d, randquick = %d \n", i, seqmnums[i], hnums[i], qnums[i], randqnums[i]);
            break;
        }
    }    
    printf("sel, bub, in, merge, seqmerge, heap, quick, randquick \n");
    for(i = 0; i<40000; i++)
    {    if ((snums[i]== randqnums[i]))
        {
            continue;
        }
        else
        {
            printf("different Error at %d, quick: %d ", i ,randqnums[i]);
            break;
        }
    }
    
   printf("End");

}   