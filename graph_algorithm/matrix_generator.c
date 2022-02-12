#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

# define ver_num 5
# define max_weight 6

typedef struct vertex
{
    int name;
    int distance;
    struct vertex* adjcents[ver_num];
    struct vertex* pred;

}vertex;

typedef struct graph
{
    int weight[ver_num+1][ver_num+1];

}graph;

graph* create_graph()
{
    graph* G = NULL;
    G = (graph*)malloc(sizeof(graph));
    return G;

}
void mat_generator(graph* G)
{
    FILE* fout = NULL;
    srand(time(NULL));
    int i = 0;
    int j = 0;
    int random = 0;

    fout = fopen("matrix input ", "w");
    
    for (i = 1; i <= ver_num; i++)
    {
        for (j = 1; j <= ver_num; j++)
        {
            random =(rand() % (max_weight+1)) * pow(-1, rand());
            G->weight[i][j] = random;

            if(i==j)
            {
                G->weight[i][i] = 0;
            }
        }
    }
    
    fprintf(fout, "%d",ver_num);
    fprintf(fout, "\n");

    for (int i = 1; i <= ver_num; i++)
    {
        for (int j = 1; j <= ver_num; j++)
        {
            fprintf(fout, "%d      ", G->weight[i][j]);
        }
        fprintf(fout, "\n");
    }

}

int main()
{
    graph* G = NULL;
    G = create_graph();
    mat_generator(G);
}
