#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>


typedef struct node
{
    int key;
    struct node*left;
    struct node*right;
    struct node*parent;

}node;

node* create_node();
node* search(node* root, int t_num);
node* minimum(node* t_node);
node* maximum(node* t_node);
node* successor(node* t_node);
node* insert(node* root, int t_num);
node* delete(node* root, node* t_node);

node* root=NULL;

void main()
{   
    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 3);
    
    node* min = minimum(root);
    node* max = maximum(root);
    root = delete(root, search(root, 4));
    printf("%d", root->key);
}


node* create_node()
{
    node* new_node = NULL;
    new_node = (node*)malloc(sizeof(node));

    new_node->key= -1;
    new_node->left=NULL;
    new_node->right=NULL;
    new_node->parent=NULL;
    
    return new_node;
}

node* search(node* root, int t_num)
{
    if(root == NULL || t_num == root->key)
    {
        return root;
    }
    if(t_num < root->key)
    {
        return search(root->left, t_num);
    }
    else{return search(root->right, t_num);}
}

node* minimum(node* t_node)
{   
    if( t_node->left == NULL)
    {
        return  t_node;
    }
    while( t_node->left != NULL)
    {
         t_node =  t_node->left;
    }
    return  t_node;
}

node* maximum(node* t_node)
{
    if( t_node->right == NULL)
    {
        return  t_node;
    }
    while( t_node->right != NULL)
    {
         t_node =  t_node->right;
    }
    return  t_node;
}

node* successor(node* t_node)
{
    node* temp= t_node;
    node* p_node=NULL;
    if(temp->right != NULL)
    {
        return minimum(temp->right);
    }
    p_node = temp->parent;
    while((p_node != NULL) && (temp =p_node->right))
    {
        temp = p_node;
        p_node = p_node->parent;
    }
    return p_node;
}

node* insert(node* root, int t_num)
{
    node* p_node = NULL;
    node* temp = root;
    node* t_node = create_node();
    t_node->key = t_num;
    while(temp != NULL)
    {
        p_node = temp;
        if(t_node->key < temp->key)
        {
            temp = temp->left;
        }
        else{temp = temp->right;}
    }
    t_node->parent = p_node;
    if(p_node == NULL)
    {
        root = t_node;
    }
    else if(t_node->key < p_node->key)
    {
        p_node->left = t_node;
    }
    else{p_node->right = t_node;}
    return root;
}

node* delete(node* root, node* t_node)
{   
    node* temp=NULL;
    node* child=NULL;

    if(root == NULL){ return NULL;}
    if(t_node->left == NULL || t_node->right == NULL){temp=t_node;} //target has no child or 1 child
    else{temp = successor(t_node);}   //target has 2 child
    
    if(temp->left != NULL){child=temp->left;}  
    else{child=temp->right;}    

    if(child != NULL){child->parent=temp->parent;}
    
    if(temp->parent == NULL){root=child;}
    else if(temp==(temp->parent->left)){(temp->parent)->left=child;}
    else{temp->parent->right=child;}

    if(temp != t_node)
    {
        t_node->key = temp->key;
        free(temp);
    }
    else
    {
        free(temp);
        free(t_node);
    }

    return root;
}

