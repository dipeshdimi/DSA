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

bool childrenSum(node *root)
{
    if(root == NULL || (root->left == NULL && root->right == NULL))
        return true;
    
    int sum = 0;
    if(root->left != NULL)
        sum += root->left->data;
    if(root->right != NULL)
        sum += root->right->data;
    
    return (root->data == sum) && childrenSum(root->left) && childrenSum(root->right);


    // int l = (root->left != NULL) ? root->left->data : 0;
    // int r = (root->right != NULL) ? root->right->data : 0;

    // // return (root->data == l+r) && childrenSum(root->left) && childrenSum(root->right);
    // //          OR :-
    // if(root->data == l+r)
    // {
    //     childrenSum(root->left);
    //     childrenSum(root->right);
    // }
    // else 
    //     return false;
    
    // return true;
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

    node*root2 = new node(50);
    root2->left = new node(70);
    root2->right = new node(-20);
    root2->left->left = new node(85);
    root2->left->right = new node(-15);
    root2->right->left = new node(4);
    root2->right->right = new node(-24);
    root2->left->left->right = new node(85);
    root2->right->left->right = new node(4);
    root2->right->right->right = new node(-24);
    root2->right->left->right->left = new node(4);
    /*
                50(n0)
              /        \
           70(n1)      -20(n2)
          /     \       /    \
        85(n3) -15(n4) 4(n5) -24(n6)
         \              \        \
         85(n7)         4(n8)    -24(n9)
                       /
                     4(n10)
    */

    // Children Sum Property: Sum of the children should be equal to the parent (if there is just one child, then it should be equal to the parent).

    cout<<childrenSum(root)<<"\n";
    cout<<childrenSum(root2)<<"\n";
        // TIME COMPLEXITY: O(n)
        // AUXILIARY SPACE: O(h)

    return 0;
}