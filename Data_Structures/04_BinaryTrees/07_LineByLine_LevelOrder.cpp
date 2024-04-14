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

void lineByLine_Level_Method1(node *root)
{
    // By the end of a level in the tree (i.e., by the time you pop the last node of a level), the next level would have been completely pushed to the queue. Thus, we start out by pushing root (start & end of first level) and a marker, NULL, which would represent the end of a level. Now, by the time we pop the root node, its both children (i.e., the entirety of level 2) would have been pushed into the queue. Thus, we again push NULL to signify the level's end. Similarly, we can place the marker (NULL) for the rest of the tree. Now, whenever we encounter a NULL pointer, we pop it out and add another NULL at the end of the queue signifying the next level's end, and we print the endlline character (\n) to start the next level afresh from a new line, as desired.

    queue <node*> q;
    q.push(root);
    q.push(NULL);       // NOTE: Memory address 0 signals that the pointer is not intended to point to an accessible memory location, that's why you get 0 as the result when you try to print a null pointer.

    while(!q.empty())
    {
        if(q.front()->left != NULL)
            q.push(q.front()->left);
        if(q.front()->right != NULL)
            q.push(q.front()->right);
        
        cout<<q.front()->data<<"  ";
        q.pop();

        if(q.front() == NULL)
        {
            cout<<"\n";
            q.pop();        // pop from the front
            q.push(NULL);   // push to the back

            // If there is just NULL pointer left in the queue (or we could write the operations in the order store front -> pop -> push children -> check if stored front is NULL)
            if(q.size() == 1)
                break;
        }
    }
    cout<<"\n\n";
}

void lineByLine_Level_Method2(node *root)
{
    queue<node*> q;
    q.push(root);

    // Each iteration while() : Each level of tree
    // Each iteration for() : Each element of tree
    // By the end of a level, the next level is already completely pushed, so we count how many queue elements are there at the end of each level (cur_lev_width) and print just those elements while continuing to fill the queue with further children.By the time we are done with the current level's width, the elements of the next level would have been pushed to the queue and so we recalculate the cur_lvl_width and keep repeating the same procedure.
    while(!q.empty())
    {
        int cur_lvl_width = q.size();     // We can't directly use q.size() in the for since it would calculated for each iteration and due to popping and pushing, it would keep changing.

        for(int i=0; i<cur_lvl_width; i++)
        {
            if(q.front()->left != NULL)
                q.push(q.front()->left);
            if(q.front()->right != NULL)
                q.push(q.front()->right);
            
            cout<<q.front()->data<<"  ";
            q.pop();
        }
        cout<<"\n";
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
    root->right->right->left = new node(70);
    root->right->left->right->left = new node(80);
    /*
               -20(n0)
              /        \
          -10(n1)       0(n2)
          /     \       /    \
        10(n3)  20(n4) 30(n5) 40(n6)
         \              \       / 
         50(n7)        60(n8)  70(n9)
                      /
                    80(n10)
    */

    lineByLine_Level_Method1(root);
    // TIME COMPLEXITY: Θ(n)
    // AUXILIARY SPACE: Θ(width of BT) or O(n)
            // [At any point, the maximum possible number of nodes in the queue would be the no. of nodes at the current tree level + 1]
    
    lineByLine_Level_Method2(root);
    // TIME COMPLEXITY: Θ(n)
    // AUXILIARY SPACE: Θ(width of BT) or O(n)
            // [At any point, the maximum possible number of nodes in the queue would be the no. of nodes at the current tree level + 1]

    return 0;
}