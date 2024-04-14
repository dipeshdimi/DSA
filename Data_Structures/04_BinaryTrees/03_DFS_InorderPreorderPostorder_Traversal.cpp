#include<iostream>

using namespace std;

struct node{
    int data;
    node* left, *right;

    node(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};

void preorder(node*root)
{
    if(root != NULL)
    {
        cout<<root->data;
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(node*root)
{
    if(root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        cout<<root->data;
    }
}

void inorder(node*root)
{
    if(root != NULL)
    {
        inorder(root->left);
        cout<<root->data;
        inorder(root->right);
    }
}


int main()
{
    node*root = new node(-20);
    root->left = new node(-10);
    root->right = new node(0);
    root->left->left = new node(10);
    root->left->right = new node(20);
    root->right->left = new node(30);
    root->right->right = new node(40);
    root->left->left->right = new node(50);
    root->right->left->right = new node(60);
    root->right->right->right = new node(70);
    root->right->left->right->left = new node(80);

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

    /* TRAVERSAL */
    // Unlike linear data structures (Array, Linked List, Queues, Stacks, etc) which can only be traversed from front to back or back to front in linear fashion, trees can be traversed in different ways. Following are the generally used ways for traversing trees :-
    /* 1) Depth First Traversals :  (a) Postorder (Left, Right, Root) : [[50, 10], [20], -10], [[[80, 60], 30], [70, 40], 0], -20
                                                                        => 50, 10, 20, -10, 80, 60, 30, 70, 40, 0, -20

                                    (b) Preorder (Root, Left, Right) : -20, [-10, [10, 50], [20]], [0, [30, [60, 80]], [40, 70]]
                                                                        => -20, -10, 10, 50, 20, 0, 30, 60, 80, 40, 70

                                    (c) Inorder (Left, Root, Right) : [[10, 50], -10, [20]], -20, [[30, [80, 60]], 0, [40, 70]]
                                                                      => 10, 50, -10, 20, -20, 30, 80, 60, 0, 40, 70

       2) Breadth First or Level Order Traversal : --- {Not talking about this here}   */

       preorder(root);
       cout<<"\n";
       postorder(root);
       cout<<"\n";
       inorder(root);
       cout<<"\n";

    /* TRAVERSAL TRICK -> Pre, Post, Inorder Traversal Trick.png */

    // TIME COMPLEXITY: O(n)
    // AUXILIARY SPACE: O(h)    [Max no. of recursive calls in the stack at any time = (height of BT + 1)]


    return 0;
}
  