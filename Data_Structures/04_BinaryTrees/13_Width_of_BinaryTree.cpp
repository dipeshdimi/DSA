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

int countLeafNodes(node *root)
{
    if(root == NULL)
        return 0;
    
    if(root->left == NULL && root->right == NULL)
        return 1;
    
    // We're simply adding to the result, every time, 1 is returned by the function (i.e., every time a leaf node is encountered)
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int maxWidth(node *root)
{
    // Max nodes level using level order traversal.
    // We can also do this with the help of preorder/inorder/postorder traversal by maintaining a count[] array such that count[lvl] represents the number of nodes in level lvl (https://www.geeksforgeeks.org/maximum-width-of-a-binary-tree/).

    if(root == NULL)
        return 0;
    
    queue <node*> q;
    q.push(root);

    int wmax=1;

    while(!q.empty())
    {
        int count = q.size();

        wmax = max(wmax, count);
        
        // Iterates through an entire level.
        while(count--)
        {
            if(q.front()->left != NULL)
                q.push(q.front()->left);
            if(q.front()->right != NULL)
                q.push(q.front()->right);

            q.pop();
        }
    }

    return wmax;
}

int main()
{
    node *root = new node(-20);
    root->left = new node(-10);
    root->right = new node(0);
    root->left->left = new node(10);
    root->left->right = new node(20);
    root->right->left = new node(30);
    root->right->right = new node(40);
    root->left->left->right = new node(50);
    root->right->left->right = new node(60);
    root->right->right->left = new node(999999);
    root->right->right->right = new node(70);
    root->right->left->right->left = new node(80);
    /*
               -20(n0)
              /        \
          -10(n1)        0(n2)
          /     \       /     \
        10(n3)  20(n4) 30(n5)  40(n6)
         \              \      /     \
         50(n7)        60(n8) 65(n8½) 70(n9)
                      /
                    80(n10)
    */

    // Width = Max Width (whichever level has it) = 
    // Max Width doesn't need to be equal to the number of leaf nodes. For example, for the tree defined above, number of leaf nodes = 5 & max width = 4 (at 3rd and 4th level).
    cout<<countLeafNodes(root)<<"\n";
    // TIME COMPLEXITY: O(n)
    //     [Θ(n + no. of nodes with no/one child), to be precise]
    // AUXILIARY SPACE: O(h)
    //     [Θ(h+1), to be precise]

    cout<<maxWidth(root)<<"\n";
    // TIME COMPLEXITY: Θ(n)
    // AUXILIARY SPACE: Θ(w)

    return 0;
}