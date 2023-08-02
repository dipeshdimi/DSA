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

void level_BFS(node *root)
{
    if(root == NULL)
        return;
    
    queue <node*> q;
    q.push(root);

    while(!q.empty())
    {
        if(q.front()->left != NULL)
            q.push(q.front()->left);
        if(q.front()->right != NULL)
            q.push(q.front()->right);
        
        cout<<q.front()->data<<"  ";
        q.pop();
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

    level_BFS(root);

    // TIME COMPLEXITY: Θ(n)
    // AUXILIARY SPACE: Θ(width of BT) or O(n)
            // [At any point, the maximum possible number of nodes in the queue would be the no. of nodes at the current tree level + 1]
    
    return 0;
}