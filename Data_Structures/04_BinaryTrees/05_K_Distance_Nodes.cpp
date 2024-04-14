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

void kDist(node *root, int k)
{
    if(root == NULL)
        return;
    
    if(k==0)
        cout<<root->data<<"  ";
    else
    {
        kDist(root->left, k-1);
        kDist(root->right, k-1);
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
              /        \
          -10(n1)       0(n2)
          /     \       /    \
        10(n3)  20(n4) 30(n5) 40(n6)
         \              \        \
         50(n7)        60(n8)    70(n9)
                      /
                    80(n10)
    */

    kDist(root, 3);

    // TIME COMPLEXITY: O(n)
    // AUXILIARY SPACE: O(h)    [Max no. of recursive calls in the stack at any time = (height of BT + 1)]
    
    return 0;
}