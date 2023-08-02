#include<iostream>
#include<queue>

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

void leftViewRecursive(node *root, int curLvl, int *maxLvl)
{
    // Preorder traversal while maintaining a variable representing the current level in the tree we're traversing/to traverse, and a variable representing the max level upto which we've already traversed/printed the leftmost element.
    if(root == NULL)
        return;

    if(curLvl > *maxLvl)
    {
        cout<<root->data<<"  ";
        (*maxLvl)++;    // precedence(++) > precedence(* i.e., dereferencing operator)
    }

    leftViewRecursive(root->left, curLvl+1, maxLvl);
    leftViewRecursive(root->right, curLvl+1, maxLvl);
}

void leftViewIterative(node *root, int curLvl, int *maxLvl)
{
    if(root == NULL)
        return;

    queue <node*> q;
    q.push(root);

    while(!q.empty())
    {
        int cur_lvl_width = q.size();
        for(int i=0; i<cur_lvl_width; i++)
        {
            // Printing only the first element of each level
            if(i==0)
                cout<<q.front()->data<<"  ";
            
            if(q.front()->left != NULL)
                q.push(q.front()->left);
            if(q.front()->right != NULL)
                q.push(q.front()->right);
            
            q.pop();
        }
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

    int maxLvl = 0;
    leftViewRecursive(root, 1, &maxLvl);
    // Using Preorder Traversal
        // TIME COMPLEXITY: O(n)
        // AUXILIARY SPACE: O(h)

    cout<<"\n";

    leftViewIterative(root, 1, &maxLvl);
    // Using Level Order Traversal
        // TIME COMPLEXITY: Θ(n)
        // AUXILIARY SPACE: Θ(w)

    return 0;
}