// Dynamic Node Representation / Linked Representation of BT

#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* left;
    struct node* right;
};

struct node* create_node(int data)
{
    struct node*ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->left = NULL;
    ptr->right = NULL;
    return ptr;
}


int main()
{
/* IMPLEMENTATION */
    // Creating Nodes
    struct node*root_n0 = create_node(-20);
    struct node*n1 = create_node(-10);
    struct node*n2 = create_node(0);
    struct node*n3 = create_node(10);
    struct node*n4 = create_node(20);
    struct node*n5 = create_node(30);
    struct node*n6 = create_node(40);
    struct node*n7 = create_node(50);
    struct node*n8 = create_node(60);
    struct node*n9 = create_node(70);
    struct node*n10 = create_node(80);

    // Connecting Nodes
    root_n0->left = n1;
    root_n0->right = n2;
    n1->left = n3;
    n1->right = n4;
    n2->left = n5;
    n2->right = n6;
    n3->right = n7;
    n5->right = n8;
    n6->right = n9;
    n8->left = n10;
    /*
         -20(n0)
        /       \
    -10(n1)       0(n2)
    /     \       /    \
  10(n3)  20(n4) 30(n5) 40(n6)
   \              \        \
   50(n7)        60(n8)    70(n9)
                /
               80(n10)
    */
    // All other left/right members of these nodes point to the NULL pointer (set at the time of creation using create_node function).

    return 0;
}