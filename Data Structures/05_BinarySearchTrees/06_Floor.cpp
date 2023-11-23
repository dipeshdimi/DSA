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

node* floor(node *root, int key)
{
    // int res = INT_MIN;   /* We return INT_MIN in case no element is smaller than the key */
    node *res = NULL;       /* We return NULL in case no element is smaller than the key */
    while(root != NULL)
    {
        if(root->data > key)
            root = root->left;
        else if(root->data < key)
        {
            /* We don't need to do res = max(root->data, res) since every time we enter this else if statement, we enter the right subtree and all the elements in the right subtree are greater than than root element, so every time we pass this condition, we can be sure that the root this time (root->data) would be greater than the root the previous time (res). */
            
            // res = root->data;
            res = root;
            root = root->right;
        }
        else
        {
            // return root->data;
            return root;
        }
    }
    return res;
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
    root->left->right->left = new node(5);
    root->left->right->right = new node(8);
    root->right->right->left = new node(14);
    /*
         9
        / \
       4   11
      / \    \
     2   7    15
        / \   /
       5   8 14
    */

    // Find closest element to the given key, which is smaller than or equal to it.
    cout<<floor(root,6)->data<<"\n";
    cout<<floor(root,13)->data<<"\n";
    cout<<floor(root,7)->data<<"\n";
    cout<<floor(root,1)->data<<"\n";    // NULL

    // TIME COMPLEXITY: O(h)
    // AUXILIARY SPACE: O(1)
    
    return 0;
}