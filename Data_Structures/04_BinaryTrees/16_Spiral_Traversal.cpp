#include<iostream>
#include<queue>
#include<stack>

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

void spiral_QS(node *root)
{
    queue <node*> q;
    stack <int> s;      // Just int is enough since we would just push integers into the stack and print them in the reverse order of their entrance (by popping).

    bool leftToRight = true;

    q.push(root);

    while(!q.empty())
    {
        int count = q.size();
        for(int i=0; i<count; i++)
        {
            // Everything is pushed into the queue, but only odd levels are printed. This makes sure all the odd levels are printed in the correct order and since even levels are stored in the reverse order in the queue, when we output them after passing through the stack, they are also printed in the desired order. If we try to directly push them into the stack w/o first passing them through the queue, we would get the wrong order.
            if(q.front()->left != NULL)
                q.push(q.front()->left);
            if(q.front()->right != NULL)
                q.push(q.front()->right);
            
            // If it's to be printed right to left, push it into the stack so that the left to right order of the queue gets reversed when we pop and print the elements from the stack.
            // If it's to be printed from left to right, just print them in the order of the queue popping.
            if(!leftToRight)
                s.push(q.front()->data);
            else
                cout<<q.front()->data<<"  ";
            
            q.pop();
        }

        // Empty the stack, we filled in the previous loop.
        // Note: The stack would be non-empty only in case of even levels anyway, thus, we don't need to check !leftToRight.
        while(!s.empty())
        {
            cout<<s.top()<<"  ";
            s.pop();
        }

        // Alternate the printing order with each iteration.
        leftToRight = !leftToRight;
    }
    cout<<"\n";
}

void spiral_SS(node *root)
{
    stack <node*> s1, s2;

    s1.push(root);

    while(!s1.empty() || !s2.empty())
    {
        while(!s1.empty())
        {
            if(s1.top()->left != NULL)
                s2.push(s1.top()->left);
            if(s1.top()->right != NULL)
                s2.push(s1.top()->right);
            
            cout<<s1.top()->data<<"  ";
            s1.pop();
        }
        while(!s2.empty())
        {
            if(s2.top()->right != NULL)
                s1.push(s2.top()->right);
            if(s2.top()->left != NULL)
                s1.push(s2.top()->left);
            
            cout<<s2.top()->data<<"  ";
            s2.pop();
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

    spiral_QS(root);    // -20 -> 0 -> -10 -> 10 -> 20 -> 30 -> 40 -> 70 -> 60 -> 50 -> 80
        // TIME COMPLEXITY: O(n)
        // AUXILIARY SPACE: O(w)

    // In the above method, each elements have to pass through a queue or a stack and a queue. We can optimize this solution a little by using two stacks such that any one element passes through a data structure only once.
    spiral_SS(root);
        // TIME COMPLEXITY: O(n)
        // AUXILIARY SPACE: O(w)

    return 0;
}