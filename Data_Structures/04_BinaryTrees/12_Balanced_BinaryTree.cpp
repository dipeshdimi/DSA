#include<iostream>

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

// This function returns -1 if the tree is not balanced, otherwise, it returns the height of the tree/subtree.
int balanced(node *root)
{
    if(root == NULL)
        return 0;       // No node => Tree/subtree's height = 0
    
    // The first time this function would get resolved out of the recursion would be for the leftmost leaf node. When, for the leftmost leaf node, balanced(root->leaf) is called, 0 would be returned and thus, lh = 0 (height of left subtree of the leaf node is 0). Thus, we start calculating height of the left subtrees starting from the bottom to the top [lh(last) -> lh(second last) -> ..., each getting increased by +1 as we return function calls from bottom to top].
    int lh = balanced(root->left);
    if(lh == -1)
        return -1;
        // Left subtree height (lh) would be evaluated as -1 only when it is found that the tree is unbalanced. In that case, we don't need to check any further subtrees and can safely return -1 meaning unbalanced as the answer.
        // (Note: One 'return -1' would start a chain of 'return -1's that would continue until we revert back to our original tree and the function terminates with no as the answer).
    
    // Similarly, here, the recursion resolution here would be from the rightmost leaf node (bottom) to top.
    int rh = balanced(root->right);
    if(rh == -1)
        return -1;
    
    // A tree is defined as unbalanced if the height difference b/w the left and right subtree at any level, is more than 1. Thus, we return -1 in this case
    if(std::abs(lh-rh) > 1)
        return -1;
    else
        return std::max(lh, rh) + 1;
        // The usual height expression, except this time, we're going from btm to top.
}

int main()
{
    node *unbal = new node(8);
    unbal->left = new node(12);
    unbal->right = new node(15);
    unbal->left->left = new node(13);
    unbal->left->right = new node(14);
    unbal->right->right = new node(16);
    unbal->right->right->right = new node(17);
    /*
           8
          / \
         12  15
        /  \   \
       13  14   16
                 \
                  17
    */

    node *bal = new node(8);
    bal->left = new node(12);
    bal->right = new node(15);
    bal->left->left = new node(3);
    bal->left->right = new node(4);
    bal->right->left = new node(1);
    bal->right->right = new node(-9);
    bal->right->right->right = new node(-17);
    /*
            8
          /   \
         12    15
         /\    /\
        3  4  1 -9
                  \
                  -17
    */

    int h1 = balanced(unbal);
    int h2 = balanced(bal);
    // TIME COMPLEXITY: O(n)
    // AUXILIARY SPACE: O(h)

    if(h1 == -1)
        std::cout<<"Not balanced\n";
    else
        std::cout<<"Balanced, with height = "<<h1<<"\n";

    if(h2 == -1)
        std::cout<<"Not balanced\n";
    else
        std::cout<<"Balanced, with height = "<<h2<<"\n";
    
    return 0;
}