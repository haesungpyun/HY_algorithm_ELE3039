#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

# define ver_num 5          // graph를 구성하는 vertex의 수를 입력한다.
# define max_weight 6       // random하게 graph를 구성하는 경우 weight의 최댓값을 정한다.
# define INF 9999999        // 연결돼 있지 않거나, 현재 path를 찾지 못한 경우 INF 값을 갖는다.


// graph를 adjacent matrix로 표현한다.
typedef struct graph
{
    int weight[ver_num][ver_num];
    
}graph;


// 함수 선언
graph* create_graph();
graph* initialize_mat(graph* G, int input);
void floyd(graph* G);


// 입력으로 주어질 수 있는 weight (명세 및 교과서 예제)
int weight1[5][5] = {{0,10,0,0,5},
                    {0,0,1,0,2},
                    {0,0,0,4,0},
                    {7,0,6,0,0},
                    {0,3,9,2,0}};

int weight2[5][5] = {{0,6,0,0,7},
                    {0,0,5,-4,8},
                    {0,-2,0,0,0},
                    {2,0,7,0,0},
                    {0,0,-3,9,0}};

int weight3[5][5] = {{0,3,8,0,-4},
                    {0,0,0,1,7},
                    {0,4,0,0,0},
                    {2,0,-5,0,0},
                    {0,0,0,6,0}};

// 기타 weighted, directed graph 예시
/*
{{0,   5,  0, 10},
{0,  0,  3,  0},
{0, 0, 0,   1},
{0, 0, 0, 0} };


{{0,3,INF, 4},
{-8,0,2,INF},
{5,INF,0,1},
{2,INF,INF,0}};

{{0,   5,  INF, 10},
{INF,  0,  3,  INF},
{INF, INF, 0,   1},
{INF, INF, INF, 0} };

{{0,   3,  INF, 5},
{2,  0,  INF,  4},
{INF, 1, 0,   INF},
{INF, INF, 2, 0} };

{{0,3,8,INF,-4},
{INF,0,INF,2,7},
{INF,4,0,INF,INF},
{2,INF,-5,0,INF},
{INF,INF,INF,6,0}};*/

int main()
{
    graph* G = NULL;
    G = create_graph();
    int input; 
    printf("#  Select Input\n1. No.1 input matrix\n2. No.2 input matrix \n3. No.3 input matrix \n4. read my_input.txt \n5. generate random input\n");
	printf("Your Input: ");

	scanf("%d", &input);
    if(input == 4)
    {
        printf("reading your my_input.txt files\n");
    }
    G = initialize_mat(G, input);
    floyd(G);
}


// graph를 생성하기 위해서 메모리를 할당한다.
graph* create_graph()
{
    graph* G = NULL;
    G = (graph*)malloc(sizeof(G));
    return G;
}

// 입력을 받아 graph의 초기 weight값을 정한다.
graph* initialize_mat(graph* G, int input)
{   
    FILE* fin = NULL;
    FILE* fout = NULL;

    srand(time(NULL));
    int vnum =ver_num;      // 입력마다 vertex의 수가 달라 vnum으로 받아준다.
    int i, j, random = 0;
    int sel[2]={0,};

    fin = fopen("my_input.txt", "r+");
    fout = fopen("input.txt", "w");
    
    // 입력이 1,2,3인 경우 처음 입력한 weight1, weight2, weight3을 G->weight에 입력한다. 
    if(input == 1)
    {
        vnum = 5;
        for(i=0; i<vnum; i++)
        {
            for(j=0; j<vnum; j++)
            {   
                G->weight[i][j] = weight1[i][j];
                
                // 위에 입력된 weight값은 현재 path를 찾지 못한 경우에 0을 할당하고 있으므로 이를 INF로 변경해준다.
                if(weight1[i][j]==0)
                {G->weight[i][j] = INF;}
                
                // 자기 자신의 경우 INF에 다시 0을 할당한다.
                if(i==j)
                {G->weight[i][j] = 0;}
            }
        }
    }
    else if(input == 2)
    {
        vnum=5;
        for(i=0; i<vnum; i++)
        {
            for(j=0; j<vnum; j++)
            {   
                G->weight[i][j] = weight2[i][j];
                
                // 위에 입력된 weight값은 현재 path를 찾지 못한 경우에 0을 할당하고 있으므로 이를 INF로 변경해준다.
                if(weight2[i][j]==0)
                {G->weight[i][j] = INF;}
                
                // 자기 자신의 경우 INF에 다시 0을 할당한다.
                if(i==j)
                {G->weight[i][j] = 0;}
            }
        }
    }
    else if(input == 3)
    {
        vnum=5;
        for(i=0; i<vnum; i++)
        {
            for(j=0; j<vnum; j++)
            {   
                G->weight[i][j] = weight3[i][j];
                
                // 위에 입력된 weight값은 현재 path를 찾지 못한 경우에 0을 할당하고 있으므로 이를 INF로 변경해준다.
                if(weight3[i][j]==0)
                {G->weight[i][j] = INF;}
                
                // 자기 자신의 경우 INF에 다시 0을 할당한다.
                if(i==j)
                {G->weight[i][j] = 0;}
            }
        }
    }
    // 입력이 4인 경우 임의의 txt 파일을 입력으로 받을 수 있다. 주어지는 my_input.txt 파일을 읽어 G->weight에 입력한다.
    else if(input==4)
    {
        if (fin == NULL)
        {
            printf("input.txt File Open Error");
            fclose(fin);
        }
        while (!feof(fin))
        {   // 주어진 txt 파일에서 vertex 수와 weight를 읽어와 입력한다.
            fscanf(fin, "%d    ", &vnum);
            for (int i = 0; i < vnum; i++)
            {
                for (int j = 0; j < vnum; j++)
                {
                    fscanf(fin, "%d    ", &G->weight[i][j]);
                    
                    if(G->weight[i][j]==0)
                    {G->weight[i][j] = INF;}
                    // 자기 자신의 경우 INF에 다시 0을 할당한다.
                    if(i==j)
                    {G->weight[i][j] = 0;}
                }
            }
        }
    }
    // 입력이 5인 경우 난수를 활용하여 weight matrix를 생성한다.
    else if(input == 5)
    {
        for (i = 0; i < vnum; i++)
        {
            for (j = 0; j < vnum; j++)
            {
                random =(rand() % (max_weight+1)) * pow(-1, rand());
                sel[0] = random;
                sel[1] = INF;
                G->weight[i][j] = sel[(rand()%2)];

                if(i==j)
                {
                    G->weight[i][i] = 0;
                }
            }
        }
    }

    fprintf(fout, "%d",vnum);
    fprintf(fout, "\n");

    // G->weight에 입력된 input과 vertex의 개수를 input.txt에 저장한다.
    for (int i = 0; i < vnum; i++)
    {
        for (int j = 0; j < vnum; j++)
        {   // G->weight에는 INF로 돼 있지만 명세에 따라 출력은 0으로 해야 하므로 바꾸어 출력한다. 
            if(G->weight[i][j] != INF)
            {
                fprintf(fout, "%d            ", G->weight[i][j]);    
            }
            else {fprintf(fout, "%d            ", 0);}
        }
        fprintf(fout, "\n");
    }
    fclose(fin);
    fclose(fout);

    return G;
}


void floyd(graph* G)
{   
    int i, j, k, l, m= 0;
    // 최종적으로 출력된 distance matrix와 predecessor matirx를 선언한다. 계산에 사용된 temp matrix를 선언한다. 
    int distance[ver_num][ver_num], temp[ver_num][ver_num] = {0,};
    int predecessor[ver_num][ver_num] ={0,};

    // fout, fout2를 사용하여 중간 계산 과정을 출력한다.
    // foutd, foutp를 사용하여 최종 계산 결과를 출력한다.
    FILE* fout = NULL;
    FILE* fout2 = NULL;
    FILE* foutd = NULL;
    FILE* foutp = NULL;

    fout = fopen("test_distance.txt", "w");
    fout2 = fopen("test_predecessor.txt", "w");
    
    foutd = fopen("floyd_warshall_distance.txt", "w");
    foutp = fopen("floyd_warshall_predecessor.txt", "w");
    
    // G->weight에 입력된 값을 distance와 temp matrix에 저장한다. 
    for(i=0; i<ver_num; i++)
    {
        for(j=0; j<ver_num; j++)
        {   
            distance[i][j] = G->weight[i][j];
            
            // G->weihgt이 현재 연결돼 있지 않은 path에 대해 0으로 표기할 수 있으므로
            // INF로 바꾸어 저장한다.
            if(G->weight[i][j]==0)
            {distance[i][j] = INF;}
            if(i==j)
            {distance[i][j] = 0;}
            
            temp[i][j] = distance[i][j];
            
            // 초기 weight에서 path가 있는 경우 predecessor을 입력해준다. 
            if(distance[i][j] != INF && distance[i][j] != 0)
            {predecessor[i][j] = i;}
            else{predecessor[i][j] = -1;}

        }
    }

    // 계산 과정 확인용 output txt 파일에 vertex 수 기록
    fprintf(fout, "%d",ver_num);
    fprintf(fout, "\n");

    fprintf(fout2, "%d",ver_num);
    fprintf(fout2, "\n");

    // 각 vertex를 순차적으로 순회하면서 해당 vertex를 경유하는 path와 경유하지 않는 path의
    // weight의 합을 비교한다. 더 작은 값을 갖는 path를 저장한다. 
    // 이때 같은 k에서의 결과가 순차적으로 저장되므로 뒤에 계산되는 weight에 영향을 주지 않기 위해
    // distacne matrix는 크기 바교만 하고, temp matrix로 실제 weight를 계산한다.
    // 그 후 distance에 temp를 복사한다.
    for(k=0; k<ver_num; k++)
    {

        // fout, fout2는 로그를 저장하는 파일로 설정하여 최종 결과 이전까지의 계산 결과를 출력했다.
        // 그래서 이 출력 코드는 k의 루프 안에서 돌게 된다. 
        fprintf(fout, "\n");
        fprintf(fout, "%d",k);
        fprintf(fout, "\n");

        fprintf(fout2, "\n");
        fprintf(fout2, "%d",k);
        fprintf(fout2, "\n");

        for (int i = 0; i < ver_num; i++)
        {
            for (int j = 0; j < ver_num; j++)
            {
                if(distance[i][j] != INF)
                {fprintf(fout, "%d              ", distance[i][j]);}
                else
                {fprintf(fout, "%s              ", "I");}
                if(predecessor[i][j] != -1)
                {fprintf(fout2, "%d              ", predecessor[i][j]);}
                else
                {fprintf(fout2, "%s              ", "N");}
            }
            fprintf(fout, "\n");
            fprintf(fout2, "\n");
        }
        fprintf(fout, "\n\n");
        fprintf(fout2, "\n\n");

        // l 번째 vertex를 경유점으로 지정한다. l은 0부터 k까지 반복된다. k 번째 matrix는 k와 그 전까지의 vertex를 경유점을 
        // 모두 고려한 결과이기 때문에 이와 같이 시행한다.
        // 또 distance에 바로 값을 저장하게 되면 같은 k 번째 matrix를 계산할 때에 앞서 계산된 결과를 사용할 수 있으므로
        // 경유점을 2번 사용하는 결과가 생길 수 있다. temp matrix를 사용하여 이것을 해결한다.
        // 교과서에 따르면 INF에 대한 사칙 연산의 결과를 모두 INF로 고려하였다. 코드 상에서는 INF인 경우를 제외하는 것으로
        // 교과서와 같은 결과를 낼 수 있었다. if문을 통해서 이를 해결할 수 있다.
        for(i=0; i<ver_num; i++)
        {
            for(j=0; j<ver_num; j++)
            {   
                if(distance[i][j] > (distance[i][k] + distance[k][j]))
                {
                    if((distance[i][k] != INF && distance[k][j] != INF))
                    {
                        fprintf(fout, "(%d, %d, %d)-(%d, %d, %d)  ", i, k, j, distance[i][j], distance[i][k], distance[k][j]);
                        fprintf(fout2, "(%d, %d, %d)-(%d, %d, %d)  ", i, k, j, distance[i][j], distance[i][k], distance[k][j]);
                        temp[i][j] = (distance[i][k] + distance[k][j]);
                        predecessor[i][j] = predecessor[k][j];
                    } 
                }
                distance[i][j] = temp[i][j];
                // random matrix을 생성할 경우 negative cycle이 있을 수 있기 때문에 
                // 아래와 같이 코드를 구성하였다. 
                if(distance[i][j] > (distance[i][k] + distance[k][j]))
                {
                    if((distance[i][k] != INF && distance[k][j] != INF))
                    {
                        fprintf(fout, "%s (%d, %d, %d)-(%d, %d, %d)  ","negative cycle at", i, k, j, distance[i][j], distance[i][k], distance[k][j]);
                        fprintf(fout2, "%s (%d, %d, %d)-(%d, %d, %d)  ","negative cycle at", i, k, j, distance[i][j], distance[i][k], distance[k][j]);
                        fprintf(fout, "%s", "end");
                        fprintf(fout2, "%s", "end");
                        fclose(fout);
                        fclose(fout2);
                    } 
                }
                
            }
        }    
    }

    // fout, fout2는 로그를 저장하는 파일로 설정하여 최종 결과 이전까지의 계산 결과를 출력했다.
    // 이 경우는 가장 마지막 vertex 개수 번째의 결과를 fout, fout2에 출력한다.
    fprintf(fout, "\n");
    fprintf(fout, "%d",ver_num);
    fprintf(fout, "\n");

    fprintf(fout2, "\n");
    fprintf(fout2, "%d",ver_num);
    fprintf(fout2, "\n");

    for (int i = 0; i < ver_num; i++)
    {
        for (int j = 0; j < ver_num; j++)
        {
            if(distance[i][j] != INF)
            {fprintf(fout, "%d              ", distance[i][j]);}
            else
            {fprintf(fout, "%s              ", "I");}
            if(predecessor[i][j] != -1)
            {fprintf(fout2, "%d              ", predecessor[i][j]);}
            else
            {fprintf(fout2, "%s              ", "N");}
        }
        fprintf(fout, "\n");
        fprintf(fout2, "\n");
    }
    fprintf(fout, "\n");
    fprintf(fout2, "\n");    
    
    // 최종 경과를 foutd, foutp에 출력한다. 각 distance와 predecessor에 대한 정보를 갖고 있다.
    // 그 결과를 최종 파일에 저정하였다.
    for (int i = 0; i < ver_num; i++)
    {
        for (int j = 0; j < ver_num; j++)
        {
            if(distance[i][j] != INF)
            {fprintf(foutd, "%d              ", distance[i][j]);}
            else
            {fprintf(foutd, "%s              ", "0");}
            if(predecessor[i][j] != -1)
            {fprintf(foutp, "%d              ", predecessor[i][j]);}
            else
            {fprintf(foutp, "%s              ", "N");}
        }
        fprintf(foutd, "\n");
        fprintf(foutp, "\n");
    }
    fprintf(foutd, "\n");
    fprintf(foutp, "\n");
    fclose(fout);
    fclose(fout2);
}


/*
int main()
{
    graph* G = NULL;
    G = create_graph();
    int input; 
    printf("#  Select Input\n1. No.1 input matrix\n2. No.2 input matrix \n3. No.3 input matrix \n4. read my_input.txt \n5. generate random input\n");
	printf("Your Input: ");

	scanf("%d", &input);
    if(input == 4)
    {
        printf("reading your my_input.txt files\n");
    }
    G = initialize_mat(G, input);
    floyd(G);
}
*/