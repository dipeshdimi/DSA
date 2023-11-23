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

bool searchRecursive(node *root, int key)
{
    if(root == NULL)
        return false;
    
    if(root->data == key)
        return true;
    else if(root->data > key)
        return searchRecursive(root->left,key);
    else
        return searchRecursive(root->right,key);
}

bool searchIterative(node *root, int key)
{
    while(root != NULL)
    {
        if(root->data == key)
            return true;
        else if(root->data > key)
            root = root->left;
        else
            root = root->right;
    }

    return false;
}

int main()
{
    node*root = new node(9);
    root->left = new node(4);
    root->right = new node(11);
    root->left->left = new node(2);
    root->left->right = new node(7);
    root->right->right = new node(15);
    root->left->left->left = new node(1);
    root->left->left->right = new node(3);
    root->right->right->left = new node(14);
    /*
         9
        / \
       4   11
      / \    \
     2   7    15
    / \      /
   1   3    14
    */

    cout<<searchRecursive(root,3)<<"\n";        // True
    cout<<searchRecursive(root,22)<<"\n\n";     // False
    /*
        TIME COMPLEXITY: O(h)
        AUXILIARY SPACE: O(h)
    */

    cout<<searchIterative(root,15)<<"\n";        // True
    cout<<searchIterative(root,-4)<<"\n";       // False
    /*
        TIME COMPLEXITY: O(h)
        AUXILIARY SPACE: O(1)
    */

    // NOTE: Here, the height of a BST (h) can range from log₂n (in case of completely BST) to n (in case of completely unbalanced tree, i.e., skewed toward lefto or right). Only in the case of a self-balancing BST, can we pronounce its height to be log₂n.

    return 0;
}