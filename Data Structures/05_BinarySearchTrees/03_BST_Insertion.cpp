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

node *insertIterative(node *root, int key)
{
    if(root == NULL)
        return new node(key);

    node *curr = root;
    node *parent = NULL;
    while(curr != NULL)
    {
        parent = curr;

        if(curr->data == key)
            return root;
        else if(curr->data > key)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if(parent->left == NULL)
        parent->left = new node(key);
    else if(parent->right == NULL)
        parent->right = new node(key);

    return root;
}

node *insertRecursive(node *root, int key)
{
    if(root == NULL)
        return new node(key);

    if(root->data > key)
        root->left = insertRecursive(root->left,key);
    else if(root->data < key)
        root->right = insertRecursive(root->right,key);
    
    return root;
}

void inorder(node*root)
{
    if(root != NULL)
    {
        inorder(root->left);
        cout<<root->data<<"  ";
        inorder(root->right);
    }
}

int main()
{
    node*root = new node(9);
    root->left = new node(4);
    root->right = new node(11);
    root->left->left = new node(2);
    root->left->right = new node(7);
    root->right->right = new node(15);
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

    root = insertIterative(root,-3);
    inorder(root);
    cout<<"\n";
    root = insertIterative(root,4);
    inorder(root);
    cout<<"\n";

    root = insertRecursive(root,0);
    inorder(root);
    cout<<"\n";
    root = insertRecursive(root,14);
    inorder(root);

    return 0;
}