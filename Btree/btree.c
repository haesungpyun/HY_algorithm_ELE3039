#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define degree 4
#define max_child 4
#define max_keys 3
#define True 1
#define False 0

#define len_command 2
#define max_num 30                  // max_num은 나올 수 있는 최대 값을 설정
#define num_commands 30             // command list의 길이 설정
                                    // 두 값을 바꾸어 다양한 수 가능

typedef struct node
{
    int key[max_keys + 1];               //3 keys + additional space for insert and split
    struct node* parent;
    struct node* child[max_child+1];       //4 child + additional space for insert and split
    int height;
} node;

////////////////////////////////////////////////////////////////////////////////////////////

// Function, Variable Declaration
node* create_node();
node* findloc(node* t_node, float target);
int* InSort(int* insort);
void insert(node* t_node, int target);
void split(node* t_node);
node** fill_tree_pointer(node** tree_p, node** sub_root);
void printTree(node* root, node* tree_p[]);
void update_height(node* t_node);
void delete(node* t_node, int target, int index);
void underflow(node* t_node);
void transfer(node* t_node, int tidx, node* s_node, int sidx);
void fusion(node* t_node, int tidx);
void redistribute(node* t_node);

node* root = NULL;
node* location = NULL;
node* tree_pointer[max_num]={NULL,};
FILE* fin = NULL;
FILE* fout = NULL; 

////////////////////////////////////////////////////////////////////////////////////////////

int *InSort(int insort[])
{
    int i = 0;
    int j = 0;
    int insert;

    for(i = 1; i <max_keys+1; i++)
    {
        insert = insort[i];
        for(j = i-1; j >= 0; j--)
        {
            if(insort[j]> insert)
            {
                insort[j+1] = insort[j];
            }
            else
            {break;}  
        }
        insort[j+1] = insert;
    }
    return insort;
}

int main()
{
    int i = 0;
    int target = 0;
    char command, space = '\0';

    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");

    root = create_node();
    root->height = 1;
    
    if (fin == NULL)
    {
        fprintf(fout, "%s", "input.txt File Open Error");
        return 0;
    }

    while (!feof(fin))
    {   // 명령어와 insert할 숫자(target)를 읽어옴
        fscanf(fin, "%c%d%c", &command, &target, &space);

        // insert operation
        if (command == 'i')    
        {
            // insert 명령어와 insert할 숫자(target)를 출력
            fprintf(fout, "i%d \n", target);

            // target이 tree안에 있다며 그 위치 반환, 없다면 있어야하는 위치 반환(leaf node)
            location = findloc(root, target); 
            
            // 위치에 target이 있을 때 error 문구 출력     
            for (i = 0; i < max_keys; i++)
            {
                if(location->key[i] == target)
                {   fprintf(fout, "%d %s\n",target, "already in the tree");
                    break;}
            }

            // target이 없다면 insert 진행
            if(i == max_keys)
            {
                // insert 
                insert(location, target);
                // insert 이후 각 노드의 높이 재조정
                update_height(root);
                // tree_pointer array에 node의 주소를 저장 
                tree_pointer[0] = root;
                fill_tree_pointer(tree_pointer, tree_pointer);
                // tree_pointer array에서 height 별로 노드 출력 
                printTree(root, tree_pointer);
            }
            fprintf(fout, "\n");
        }

        //delete operation
        else if (command == 'd')
        {
            // delete 명령어와 delete할 숫자(target)를 출력
            fprintf(fout,"d%d \n", target);
            
            // target이 tree안에 있다며 그 위치 반환, 없다면 있어야하는 위치 반환(leaf node)
            location = findloc(root, target); 
            
            // 위치에 target이 없을 때 error 문구 출력     
            for (i = 0; i < max_keys; i++)
            {
                if(location->key[i] == target){break;} 
            }
            if(i == max_keys){fprintf(fout, "%d %s\n",target, "not in the tree");}
            
            else if(i< max_keys)
            {
                //delete
                delete(location, target, i);
                // delete 이후 각 노드의 높이 재조정
                update_height(root);
                // tree_pointer array에 node의 주소를 저장 
                tree_pointer[0] = root;
                fill_tree_pointer(tree_pointer, tree_pointer);
                // tree_pointer array에서 height 별로 노드 출력 
                printTree(root, tree_pointer);
            }
            fprintf(fout, "\n");
        }

        //search operation
        else if (command == 's') 
        {   // search 명령어와 search할 숫자(target)를 출력
            fprintf(fout, "s%d \n", target);
            location = findloc(root, target);
            
            for (i = 0; i < max_keys; i++)
            {
                if(location->key[i] == target)
                {   
                    fprintf(fout, "%s\n","exist");
                    break;
                }
            }
            if(i == max_keys)
            {   
                fprintf(fout, "%s\n", "not exist"); 
            }
            fprintf(fout, "\n");
        }
    }
    fclose(fin);
}

////////////////////////////////////////////////////////////////////////////////////////////

// make a new node, with initial condition
node* create_node()
{
    node* new_node = NULL;
    new_node = (node*)malloc(sizeof(node));

    new_node->parent = NULL;

    for (int i = 0; i < max_child+1; i++)
    {
        new_node->child[i] = NULL;
    }
    for (int i = 0; i < max_keys+1; i++)
    {
        new_node->key[i] = __INT_MAX__;
    }
    new_node->height = 0;
    return new_node;
}

////////////////////////////////////////////////////////////////////////////////////////////

// find targets location
// exist return location node, not exist return node before null
node* findloc(node *t_node, float target)
{
    int i;
    int loc;
    
    // target in the t_node
    for (i = 0; i < max_keys; i++)
    {
        if (t_node->key[i] == target)
        {
            return t_node;
        }
    }
    // t_node의 key값과 target을 비교하여 가야할 path(child)를 정함
    // 다음 조사할 node가 정해졌다면(child) recursive하게 내려감
    if (t_node->key[0] > target)
    {   
        if (t_node->child[0] == NULL)
        {
            return t_node;
        }
        return findloc(t_node->child[0], target);
    }
    else if (t_node->key[1] > target)
    {
        if (t_node->child[1] == NULL)
        {
            return t_node;
        }
        return findloc(t_node->child[1], target);
    }
    else if (t_node->key[2] > target)
    {
        if (t_node->child[2] == NULL)
        {
            return t_node;
        }
        return findloc(t_node->child[2], target);
    }
    else if (t_node->key[2] < target)
    {
        if (t_node->child[3] == NULL)
        {
            return t_node;
        }
        return findloc(t_node->child[3], target);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

// return 1 if insert ended
void insert(node* t_node, int target)
{
    int j;

    // 1(null)-node => IM, IM, IM, (IM)
    if(t_node->key[0] == __INT_MAX__)
    {
        t_node->key[0] = target;
    }
    // 2-node => key[0] , INT_MAX, INT_MAX, (INT_MAX)
    else if(t_node->key[1] == __INT_MAX__)
    {   
        t_node->key[1] = target;
        InSort(t_node->key);
        return;
    }

    // 3-node => key[0], key[1], INT_MAX, (INT_MAX)
    else if(t_node->key[2] == __INT_MAX__)
    {
        t_node->key[2] = target;
        InSort(t_node->key);
        return;
    }

    // 4-node => key[0], key[1], key[2], (INT_MAX) ==> split
    else if(t_node->key[3] == __INT_MAX__)
    {
        t_node->key[3] = target;
        InSort(t_node->key);
        split(t_node);
        return;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

// split and fix up
void split(node* t_node)
{
    node* p_node = t_node->parent;
    node* new_node = create_node();
    int temp = t_node->key[2];
    
    // root -> create parent(new root);
    if(p_node == NULL)
    {
        p_node = create_node();
        p_node->child[0] = t_node;
        t_node->parent = p_node;
        p_node->height = root->height;
        root = p_node;
    }

    //new_node key
    new_node->key[0] = t_node->key[3]; 
    t_node->key[2] = __INT_MAX__;
    t_node->key[3] = __INT_MAX__;
    //new_node child
    new_node->child[0] = t_node->child[3];
    new_node->child[1] = t_node->child[4];
    t_node->child[3] = NULL;
    t_node->child[4] = NULL;

    //new_node parent
    if(new_node->child[0] != NULL)
    {
        new_node->child[0]->parent = new_node;
        new_node->child[1]->parent = new_node;
    }
    new_node->parent = p_node;

    // new_node height
    new_node->height = t_node->height;
    
    // p_node 1(null)-node->2-node => IM, IM, IM, (IM) -> t_key[2], IM, IM, (IM)
    if((p_node->key[0] == __INT_MAX__) && (p_node->child[1] == NULL))
    {   
        p_node->key[0] = temp;
        p_node->child[1] = new_node;
    }

    // p_node 2-node->3-node => key[0], IM, IM, (IM) -> t_key[2], key[0], IM, (IM)
    else if((p_node->key[1] == __INT_MAX__) && (p_node->key[0] > temp))
    {   
        p_node->key[1] = p_node->key[0];
        p_node->key[0] = temp;
        
        p_node->child[2] = p_node->child[1];
        p_node->child[1] = new_node;
    }

    // p_node 2-node->3-node => key[0], IM, IM, (IM) -> key[0], t_key[2], IM, (IM)
    else if((p_node->key[1] == __INT_MAX__) && (p_node->key[0] < temp))
    {   
        p_node->key[1] = temp;
        p_node->child[2] = new_node;
    }
    // p_node 3-node->4-node => key[0], key[1],IM, (IM) -> t_key[2], key[0], key[1], (IM)
    else if((p_node->key[2] == __INT_MAX__) && (p_node->key[0] > temp))
    {   
        p_node->key[2] = p_node->key[1];
        p_node->key[1] = p_node->key[0];
        p_node->key[0] = temp;
        
        p_node->child[3] = p_node->child[2];
        p_node->child[2] = p_node->child[1];
        p_node->child[1] = new_node;
    }
    // p_node 3-node->4-node => key[0], key[1],IM, (IM) -> key[0], t_key[2], key[1], (IM)
    else if((p_node->key[2] == __INT_MAX__) && (p_node->key[0] < temp) && (temp < p_node->key[1]))
    {   
        p_node->key[2] = p_node->key[1];
        p_node->key[1] = temp;
        
        p_node->child[3] = p_node->child[2];
        p_node->child[2] = new_node;
    }
    // p_node 3-node->4-node => key[0], key[1],IM, (IM) -> key[0], key[1], t_key[2], (IM)
    else if((p_node->key[2] == __INT_MAX__) && (p_node->key[1] < temp))
    {
        p_node->key[2] = temp;
        p_node->child[3] = new_node;
    }

    // p_node 4-node->5-node => key[0], key[1], key[2], (IM) -> t_key[2], key[0], key[1], key[2] => split p_node
    else if((p_node->key[2] != __INT_MAX__) && (p_node->key[0] > temp))
    {
        p_node->key[3] = p_node->key[2];
        p_node->key[2] = p_node->key[1];
        p_node->key[1] = p_node->key[0];
        p_node->key[0] = temp;

        p_node->child[4] = p_node->child[3];
        p_node->child[3] = p_node->child[2];
        p_node->child[2] = p_node->child[1];
        p_node->child[1] = new_node;

        split(p_node);
    }

    // p_node 4-node->5-node => key[0], key[1], key[2], (IM) -> key[0], t_key[2], key[1], key[2] => split p_node
    else if((p_node->key[2] != __INT_MAX__) && (p_node->key[0] < temp) && ( temp< p_node->key[1]))
    {
        p_node->key[3] = p_node->key[2];
        p_node->key[2] = p_node->key[1];
        p_node->key[1] = temp;

        p_node->child[4] = p_node->child[3];
        p_node->child[3] = p_node->child[2];
        p_node->child[2] = new_node;

        split(p_node);
    }

    // p_node 4-node->5-node => key[0], key[1], key[2], (IM) -> key[0], key[1], t_key[2], key[2] => split p_node
    else if((p_node->key[2] != __INT_MAX__) && (p_node->key[1] < temp) && ( temp< p_node->key[2]))
    {
        p_node->key[3] = p_node->key[2];
        p_node->key[2] = temp;

        p_node->child[4] = p_node->child[3];
        p_node->child[3] = new_node;
        split(p_node);
    }

    // p_node 4-node->5-node => key[0], key[1], key[2], (IM) -> key[0], key[1], key[2], t_key[2] => split p_node
    else if((p_node->key[2] != __INT_MAX__) && (p_node->key[2] < temp))
    {
        p_node->key[3] = temp;
        
        p_node->child[4] = new_node;
        split(p_node);
    }
    return;

}

////////////////////////////////////////////////////////////////////////////////////////////

// 모든 node를 각 레벨 별로 tree_pointer에 삽입하고 level이 같은 경우 왼쪽부터 
// tree_pointer 앞쪽에 할당
node** fill_tree_pointer(node** tree_p, node** sub_root)
{
    int i;

    if(*tree_p == root)
    {
        tree_p++;
    }
    if(*sub_root == NULL)
    {
        return tree_p;
    }
    else{
        // check if the i th child is NULL and put valid child into the pointer array
        for(i=0; i<4; i++)
        {
            if((*sub_root)->child[i] == NULL){break;}
            else{
                *(tree_p) = (*sub_root)->child[i];
                tree_p++;
            }
        }
        sub_root++;
        tree_p = fill_tree_pointer(tree_p, sub_root);
        return tree_p;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

// tree_pointer에 들어있는 node들을 모두 출력한다. 이때 height를 체크하여 
// 같은 height끼리만 출력 아니면 엔터
void printTree(node* root, node* tree_p[])
{
    int i;
    int j;
    
    for(i=0; i<max_num; i++)
    {
        if(tree_p[i] == NULL){return;}
        else
        {
            if(tree_p[i]->key[0] == __INT_MAX__){break;}
            else
            {
                fprintf(fout, "(%d", tree_p[i]->key[0]);

                if(tree_p[i]->key[1] != __INT_MAX__)
                {   
                    fprintf(fout, " %d", tree_p[i]->key[1]);
                    if(tree_p[i]->key[2] != __INT_MAX__)
                    {
                        fprintf(fout, " %d) ", tree_p[i]->key[2]);
                    }
                    else
                    {fprintf(fout, ") ");}
                }
                else
                {fprintf(fout, ") ");}
            }

            if(tree_p[i+1] == NULL || tree_p[i]->height != tree_p[i+1]->height)
            {fprintf(fout, "\n");}
        }   
    }
   
}

////////////////////////////////////////////////////////////////////////////////////////////

//tree 내부의 높이 재설정 root에서부터 시작하여 말단 노드까지 모두 높이 설정
//root를 1로 하고 leaf node를 가장 큰 높이 값으로 설정
void update_height(node* t_node)
{   
    int i;
    if(t_node == NULL)
    {return;}

    if(t_node->child[0] == NULL)
    {return;}

    else{
        for(i=0; i<max_child; i++)
        {
            if(t_node->child[i] == NULL)
            {break;}
            t_node->child[i]->height = t_node-> height + 1;
            update_height(t_node->child[i]);
        }
        return;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

void delete(node* t_node, int target, int index)
{   
    // t_node 이하 subtree에서 target의 predecessor의 위치 pre_node 찾음
    node* pre_node = findloc(t_node, target-0.001);
    node* p_node = pre_node->parent;
    node* temp;
    int tidx=0;
    int sidx=0;
    
    // t_node가 빈 경우 return
    if(t_node->key[index] == __INT_MAX__)
    {
        return;
    }    

    // t_node가 internal node라면 적절한 key(pre/suc)를 찾고 swap
    if(t_node->child[0] != NULL)
    {
        // pre가 4-node인 경우 가장 큰 key인 key[2]와 swap하고 target은 삭제
        if(pre_node->key[2] != __INT_MAX__)
        {
            t_node->key[index] = pre_node->key[2];
            pre_node->key[2] = __INT_MAX__;
            return;
        }
        // pre가 3-node인 경우 가장 큰 key인 key[1]과 swap하고 target은 삭제
        else if(pre_node->key[1] != __INT_MAX__)
        {
            t_node->key[index] = pre_node->key[1];
            pre_node->key[1] = __INT_MAX__;
            return;
        }
        
        // pre가 2-node인 경우 
        else
        {   
            // target 삭제 pre_node fix up
            t_node->key[index] = pre_node->key[0];
            pre_node->key[0] = __INT_MAX__;
        
            redistribute(pre_node);  
        }

    }
    else
    {
        // t_node가 2-node가 아닌 경우 target을 삭제하고 return
        if(t_node->key[1] != __INT_MAX__)
        {
            t_node->key[index] = __INT_MAX__;
            InSort(t_node->key);
            return;
        }

        else
        {   
            t_node->key[index] = __INT_MAX__;

            redistribute(t_node);
            
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

// tree 전체를 재정비하고 sibling의 수에 따라 경우 나눔
void redistribute(node* t_node)
{
    int i;
    int tidx;
    int sidx;
    node* p_node = t_node->parent;
    node* temp = create_node();

    if(p_node->parent == NULL)
    {   
        return;
    }

    for(tidx=0; tidx<max_child; tidx++ )
    {
        if(p_node->child[tidx] == t_node){break;}
    }

    // 3-nod, 4-node인 sibling 있는지 확인
    for(sidx=0; sidx<max_child; sidx++)
    {
        if(p_node->child[sidx] == NULL){sidx=__INT_MAX__; break;}
        if(p_node->child[sidx]->key[1] != __INT_MAX__)
        {break;}
    }

    // 3-node, 4-node sibling 존재 => transfer
    if(sidx < max_child)
    {
        transfer(p_node->child[tidx], tidx, p_node->child[sidx], sidx);
        return;
    }

    // 3/4-node sibling이 없고 p_node가 3/4-node인 경우 => fusion
    else if(p_node->key[1] != __INT_MAX__)
    {
        if(tidx > 0)
        {
            fusion(p_node->child[tidx], tidx);
        }
        else
        {
            fusion(p_node->child[tidx], tidx);
        }
        return;
    }

    // 3/4-node sibling이 없고 부모 노드의 key가 1개인 경우 => recursive underflow
    else
    {   
        if(tidx == 0)
        {
            p_node->child[0] = t_node->child[0];
            if(p_node->child[0] != NULL)
            {
                p_node->child[0]->parent = p_node;
                underflow(p_node->child[0]);
            }
        }
        else
        {
            p_node->child[1] = t_node->child[0];
            if(p_node->child[1] != NULL)
            {
                p_node->child[1]->parent = p_node;
                underflow(p_node->child[1]);
            }
        }
        
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

// 3/4-node sibling이 있는 경우
void transfer(node* t_node, int tidx, node* s_node, int sidx)
{   
    node* p_node = t_node->parent;
    int i=0;

    if(tidx < sidx)
    {
        // t_node가 s_node보다 앞쪽에 있는 경우 순차적으로 transfer
        for(i=tidx; i<sidx; i++)
        {
            p_node->child[i]->key[3] = p_node->key[i];
            p_node->key[i] = __INT_MAX__;
            InSort(p_node->child[i]->key);

            // 3/4-node인 sibling 있는 경우 
            if(p_node->child[sidx]->key[1] != __INT_MAX__)
            {    
                p_node->key[i] = p_node->child[i+1]->key[0];
                p_node->child[i+1]->key[0] = __INT_MAX__;
                InSort(p_node->child[i+1]->key);
            }
        }
        return;
    }
    else if(tidx > sidx)
    {
        for(i=tidx; i>sidx; i--)
        {
            p_node->child[i]->key[3] = p_node->key[i-1];
            p_node->key[i-1] = __INT_MAX__;
            InSort(p_node->child[i]->key);

            // 3/4-node sibling이 있는 경우
            if(p_node->child[sidx]->key[1] != __INT_MAX__)
            {    
                // 연속적으로 transfer할 때 가장 큰 값을 가져오기 위해서
                // 옆 sibling의 key가 3개인 경우
                if(p_node->child[i-1]->key[2] != __INT_MAX__)
                {    
                    p_node->key[i-1] = p_node->child[i-1]->key[2];
                    p_node->child[i-1]->key[2] = __INT_MAX__;
                    InSort(p_node->child[i-1]->key);
                }

                // 옆 sibling의 key가 2개인 경우
                else if(p_node->child[i-1]->key[1] != __INT_MAX__)
                {
                    p_node->key[i-1] = p_node->child[i-1]->key[1];
                    p_node->child[i-1]->key[1] = __INT_MAX__;
                    InSort(p_node->child[i-1]->key);
                }
                // 옆 sibling의 key가 1개인 경우
                else
                {
                    p_node->key[i-1] = p_node->child[i-1]->key[0];
                    p_node->child[i-1]->key[0] = __INT_MAX__;
                    InSort(p_node->child[i-1]->key);
                }
            }   
        }
        return;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

//부모가 3/4-node이고 sibling이 모두 2-node인 경우
// sibling끼리 합침
void fusion(node* t_node, int tidx)
{
    node* p_node = t_node->parent;

    // 0보다 큰 경우에는 바로 왼쪽 sibling이랑 결합
    if(tidx > 0)
    {
        p_node->child[tidx]->key[1] = p_node->key[tidx-1];
        p_node->key[tidx-1] = p_node->child[tidx-1]->key[0];
        p_node->child[tidx]->key[0] = p_node->key[tidx-1];
        p_node->key[tidx-1] = __INT_MAX__;
        InSort(p_node->key);

        p_node->child[tidx]->child[2] = p_node->child[tidx]->child[1];
        p_node->child[tidx]->child[1] = p_node->child[tidx]->child[0];
        if(p_node->child[tidx-1]->child[0] != NULL && p_node->child[tidx-1]->child[1] != NULL)
        {        
            p_node->child[tidx]->child[0]->key[0] = p_node->child[tidx-1]->child[0]->key[0];
            p_node->child[tidx]->child[0]->key[1] = p_node->child[tidx-1]->child[1]->key[0];
        }
        //p_node->child[tidx]->child[0] = p_node->child[tidx]->child[0];
        if(p_node->child[tidx]->child[0] != NULL)    
        {   
            p_node->child[tidx]->child[0]->parent =  p_node->child[tidx];
        }

        for(int i= tidx-1; i<max_child; i++)
        {
            p_node->child[i] = p_node->child[i+1];
        }
        p_node->child[4] = NULL;
        
    }
    // 0보다 큰 경우 오른쪽 sibling이랑 결합
    else
    {   
        p_node->child[0]->key[0] = p_node->key[0];
        p_node->key[0] = p_node->child[1]->key[0]; 
        p_node->child[0]->key[1] = p_node->key[0];
        p_node->key[0] = p_node->key[1];
        p_node->key[1] = p_node->key[2];
        p_node->key[2] = __INT_MAX__;

        if(p_node->child[0]->child[0] != NULL && p_node->child[0]->child[1] != NULL)
        {    
            p_node->child[0]->child[0]->key[1] = p_node->child[0]->child[1]->key[0];
            p_node->child[0]->child[1] = p_node->child[1]->child[0];
            p_node->child[0]->child[2] = p_node->child[1]->child[1];
            p_node->child[0]->child[1]->parent = p_node->child[0];   
            p_node->child[0]->child[2]->parent = p_node->child[0];
        }

        // t_node 제거
        for(int i=1; i<max_child; i++)
        {
            p_node->child[i] = p_node->child[i+1];
        }
        p_node->child[4] = NULL;
    }
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////

void underflow(node* t_node)
{
    node* p_node = t_node->parent;

    if(p_node == NULL)
    {
        root = t_node;
        return;
    }
    
    if(p_node->key[2] != __INT_MAX__)
    {
        split(p_node);

    }

}