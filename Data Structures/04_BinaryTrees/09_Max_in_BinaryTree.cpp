#include<iostream>
#include<climits>

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

int maxBT(node *root)
{
    if(root == NULL)
        return INT_MIN;
    
    return max(root->data, max(maxBT(root->left), maxBT(root->right)));
    // Any kind of traversal would work, preorder/inorder/postorder [O(h) auxiliary space] or level order [O(w) auxiliary space] traversal.
}

int main()
{
    node*root = new node(-20);
    root->left = new node(25);
    root->right = new node(0);
    root->left->left = new node(10);
    root->left->right = new node(20);
    root->right->left = new node(130);
    root->right->right = new node(-40);
    root->left->left->right = new node(50);
    root->right->left->right = new node(60);
    root->right->right->right = new node(10);
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

    cout<<maxBT(root);
    // TIME COMPLEXITY: O(n)
    // AUXILIARY SPACE: O(h)

    // Iterative Solution (level order traversal): TC [O(n)] & AS [O(w)]

    return 0;
}