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

void preorder(struct node*root)
{
    if(root != NULL)
    {
        printf("%d  ", root->data);

        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node*root)
{
    if(root != NULL)
    {
        postorder(root->left);
        postorder(root->right);

        printf("%d ", root->data);
    }
}

void inorder(struct node*root)
{
    if(root != NULL)
    {
        inorder(root->left);

        printf("%d ", root->data);

        inorder(root->right);
    }
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

/* TRAVERSAL */
    // Unlike linear data structures (Array, Linked List, Queues, Stacks, etc) which can only be traversed from front to back or back to front in linear fashion, trees can be traversed in different ways. Following are the generally used ways for traversing trees :-
    /* 1) Depth First Traversals :  (a) Postorder (Left, Right, Root) : [[50, 10], [20], -10], [[[80, 60], 30], [70, 40], 0], -20
                                                                        => 50, 10, 20, -10, 80, 60, 30, 70, 40, 0, -20

                                    (b) Preorder (Root, Left, Right) : -20, [-10, [10, 50], [20]], [0, [30, [60, 80]], [40, 70]]
                                                                        => -20, -10, 10, 50, 20, 0, 30, 60, 80, 40, 70

                                    (c) Inorder (Left, Root, Right) : [[10, 50], -10, [20]], -20, [[30, [80, 60]], 0, [40, 70]]
                                                                      => 10, 50, -10, 20, -20, 30, 80, 60, 0, 40, 70

       2) Breadth First or Level Order Traversal : --- {Not talking about this here}   */

       preorder(root_n0);
       printf("\n");
       postorder(root_n0);
       printf("\n");
       inorder(root_n0);
       printf("\n");

    /* TRAVERSAL TRICK -> Pre, Post, Inorder Traversal Trick.png */


    return 0;
}