#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

# define vertice 5

typedef struct table
{
    int mat[vertice][vertice];
    int split[vertice][vertice];
}table;


table* matrix_chain(int* p, int n, table* t )
{
    int i, j, k;
    int mat_num = n;
    int len;
    int min_cost;

    for(i=1; i <= mat_num; i++)
    {
        t->mat[i][i] = 0;
    }
    for(len=2; len<= mat_num; len++)
    {
        for(i=1; i<= mat_num-len+1; i++)
        {
            j = i+len-1;
            t->mat[i][j] = __INT_MAX__;
            for(k=i; k<= j-1; k++)
            {
                min_cost = t->mat[i][k] + t->mat[k+1][j] + p[i-1]*p[k]*p[j]; 
                if(min_cost < t->mat[i][j])
                {
                    t->mat[i][j] = min_cost;
                    t->split[i][j] = k;
                }
            }
        }
    }
    return t;
}

int main()
{

}