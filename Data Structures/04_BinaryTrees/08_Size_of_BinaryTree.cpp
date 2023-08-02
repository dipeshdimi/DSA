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

int sizeBT(node *root)
{
    if(root == NULL)
        return 0;
    
    return sizeBT(root->left) + sizeBT(root->right) + 1;
        // left subtree + right subtree + root
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

    cout<<sizeBT(root);
    // TIME COMPLEXITY: O(n)
    // AUXILIARY SPACE: O(h)

    // Iterative Solution: Count number of nodes using level order traversal problem [auxiliary space in that case would be O(w) instead of O(h)].

    return 0;
}