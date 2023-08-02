#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node*left, *right;
};


struct node* createNode(int data)
{
    struct node*ptr = (struct node*)malloc(sizeof(struct node));

    ptr->data = data;
    ptr->left = NULL;
    ptr->right = NULL;

    return ptr;
}

int main()
{
/*
    # DEFINITION
        BST is the type of binary tree in which :-
        1) Data stored by each left child node is smaller than the data stored by its respective parent node.
        1) Data stored by each right child node is greater than the data stored by its respective parent node.

    # PROPERTIES
        1) Each subtree of a BST is a BST too.
        2) There can't be any duplicates in a BST.
        3) Inorder traversal of a BST gives an ascending sorted array.

    # Example
            9
           / \
          4   11
         / \    \
        2   7    15
           / \   /
          5   8 14

        INORDER TRAVERSAL -> 2, 4, 5, 7, 8, 9, 11, 14, 15
*/

    struct node*root_n0 = createNode(9);
    struct node*n1 = createNode(4);
    struct node*n2 = createNode(11);
    struct node*n3 = createNode(2);
    struct node*n4 = createNode(7);
    struct node*n5 = createNode(15);
    struct node*n6 = createNode(5);
    struct node*n7 = createNode(8);
    struct node*n8 = createNode(14);

    root_n0->left = n1;
    root_n0->right = n2;

    n1->left = n3;
    n1->right = n4;
    n2->right = n5;

    n4->left = n6;
    n4->right = n7;
    n5->left = n8;


    return 0;
}