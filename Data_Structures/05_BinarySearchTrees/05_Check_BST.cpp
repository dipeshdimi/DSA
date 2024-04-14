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

// Here, the min/max values are updated with each recursive call and thus, we do not need to use a pointer.
bool rangeHelper(node *root, int min, int max)
{
    if(root == NULL)
        return true;
    
    // Keep a range (depending upon the parent's value and whether current node is its left child or right) in which a node's value can be while the tree still being a BST.
    return (root->data > min) && (root->data < max) && rangeHelper(root->left, min, root->data) && rangeHelper(root->right, root->data, max);
}

// Here, prev would be updated only after all the left function calls are made for a node, and thus, when a call terminates and control returns to a previous function call, prev's value there would still be the old one. Thus, we need to use a pointer.
bool inorderHelper(node *root, int *prev)
{
    // The basic idea is, if the given tree is a BST, its inorder traversal should give a sorted sequence of numbers.

    // Base Case
    if(root == NULL)
        return true;
    
    // We traverse as per the order of inorder traversal i.e., left->root->right :-

    // Return false if the left subtree's inorder traversal doesn't result in a sorted sequence
    if(!inorderHelper(root->left,prev))
        return false;

    // Checking if the sequence is sorted (we initialized prev as INT_MIN, so that the first node checked i.e., the leftmost node passes the test and then other nodes would be judged based on this leftmost node since the lefmost node would be the smallest node in a BST)
    if(root->data <= *prev)
        return false;
    
    // After checking, we update current node as prev
    *prev = root->data;

    // If we have reached here, it means, the current left subtree and the current root follow the sorted inorder traversal sequence. Now, if the right subtree also follows that sequence, we can conclude that the given tree is indeed a BST, otherwise not.
    return inorderHelper(root->right,prev);
}

bool bst_range(node *root)
{
    // To avoid the use of global variable or extra arguments.
    return rangeHelper(root,INT_MIN,INT_MAX);
}

bool bst_inorder(node *root)
{
    // To avoid the use of global variable or extra arguments.
    int prev = INT_MIN;
    return inorderHelper(root,&prev);
}

int main()
{
    node*root = new node(9);
    root->left = new node(4);
    root->right = new node(11);
    root->left->left = new node(2);
    root->left->right = new node(7);
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

    cout<<bst_range(root)<<"\n";
    root->left->right->data = 10;   // 7(<9) to 10(>9)
    cout<<bst_range(root)<<"\n";
    root->left->right->data = 7;   // Back to being a BST

    cout<<bst_inorder(root)<<"\n";
    root->left->right->data = 10;   // 7(<9) to 10(>9)
    cout<<bst_inorder(root)<<"\n";
    root->left->right->data = 7;   // Back to being a BST
    
    /*
        TIME COMPLEXITY: O(n)
        AUXILIARY SPACE: O(h)   [h can range from log₂n to n]

        This problem can be solved with O(n) & O(1) complexity using Morris traversal.
    */

    /* NOTE: Simply checking if left and right children, and betting on a tree being a BST if its subtrees are BSTs would not work since for each node, we have to make sure all its descendants are smaller (if part of left subtree) or greater (if part of right subtree) than the current root. */

    return 0;
}