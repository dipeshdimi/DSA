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
    # BST is the type of binary tree in which :-
        1. The left subtree of a node contains only nodes with keys lesser than the node’s key.
        2. The right subtree of a node contains only nodes with keys greater than the node’s key (e.g., 15's left child should be less than 15, but greater than any of its other ancestors i.e., >9 & >11).
        3. The left and right subtree each must also be a binary search tree.
        Ex: [7's right child should be >7, >4 & <9], [15's right child should be <15,>11,>9], etc.

    # PROPERTIES
        1) Each subtree of a BST is a BST too.
        2) There can't be any duplicates in a BST.
        3) Inorder traversal of a BST gives an ascending sorted array.
        4) Most of the operations in a BST are O(log₂n), which is why we like to keep the height of a BST (h=log₂n) to a minimum. This is where the concept of self-balancing BSTs comes in.

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