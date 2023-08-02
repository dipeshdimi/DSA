#include<iostream>
#include<unordered_map>

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

int precomputeHeightForEachNodeAsRoot(node *root, unordered_map <node*,int> *m)
{
    if(root == NULL)
        return 0;
    
    int lh = precomputeHeightForEachNodeAsRoot(root->left, m);
    int rh = precomputeHeightForEachNodeAsRoot(root->right, m);

    // We start filling bottom-up, like in the balanced tree problem.
    (*m)[root] = max(lh,rh) + 1;
    return max(lh,rh)+1;
}

int diameterMap(node *root, unordered_map <node*,int> m)
{
    // Diameter = 0, when the tree/subtree is empty.
    if(root == NULL)
        return 0;
    
    // Maximum length b/w two leaf nodes (diameter) when the node that is currently 'root' in the current recursive call (i.e., height of left subtree + height of right subtree + 1).
    int currNodeDiameter = m[root->left] + m[root->right] + 1;

    // Similarly, we calculate the diameter for the immediate left and right nodes.
    int leftNodeDiameter = diameterMap(root->left, m);
    int rightNodeDiameter = diameterMap(root->right, m);

    // We calculate the max in each recursive call. Thus, we get the maximum diameter among the nodes completely traversed so far, as we get this maximum from btm to top.
    return max(currNodeDiameter, max(leftNodeDiameter,rightNodeDiameter));
}

int diameter(node *root, int *dia)
{
    // Empty tree => Zero height
    if(root == NULL)
        return 0;
    
    // Left & right subtree height
    int lh = diameter(root->left, dia);
    int rh = diameter(root->right, dia);

    // Maximum among diameters (lh+rh+1, for each node)
    *dia = max(*dia, lh+rh+1);

    // Height corresponding to current root
    return max(lh,rh)+1;
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

    // Diameter of a tree refers to the max number of nodes b/w two leaf nodes, including the  two leaf nodes. For example, in the above tree, diameter is 8 (from n7 to n10).

    // METHOD I: A naive approach would be to calculate the height of a subtree each time it required [i.e., int currNodeDiameter = height(root->left) + height(root->right) + 1;].
        // TIME COMPLEXITY: O(n²)
        // AUXILIARY SPACE: O(h)

    
    // METHOD II: We preprocess the height of each subtree as store it in an unordered map for future reference.
    unordered_map <node*,int> m;
    precomputeHeightForEachNodeAsRoot(root, &m);
    cout<<diameterMap(root, m)<<"\n";
        // TIME COMPLEXITY: O(n)
        // AUXILIARY SPACE: O(n)
    

    // METHOD III: We simultaneously calculate the diameter corresponding to the current root node while evaluating the left and right subtree height for that node, and store the maximum among the diameters calculated as our answer.
    int dmtr = 0;
    diameter(root, &dmtr);
    cout<<dmtr;
        // TIME COMPLEXITY: O(n)
        // AUXILIARY SPACE: O(h)

    return 0;
}