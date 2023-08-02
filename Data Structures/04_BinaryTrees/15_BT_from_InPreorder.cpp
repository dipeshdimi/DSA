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

node *inPre(int in[], int pre[], int in_start, int in_end, int *preIndex)
{
    // To make sure we do not divide the tree any further than an empty subtree.
    if(in_start > in_end)
        return NULL;

    // Creating root nodes as we traverse through the preorder array.
    // We needed a pointer since otherwise, the index of the preorder array traversed so far would get refreshed with each recursive call.
    node *root = new node(pre[(*preIndex)++]);

    // Index of the element which we just assigned root for the current subtree (left/right)
    int inMid; 
    for(int i=in_start; i<=in_end; i++)
    {
        if(in[i] == root->data)
        {
            inMid = i;
            break;
        }
    }

    // Left and right subtree
    root->left = inPre(in, pre, in_start, inMid-1, preIndex);
    root ->right = inPre(in, pre, inMid+1, in_end, preIndex);

    // Return the root of the current subtree and eventually, the root of the entire tree.
    return root;
}

unordered_map <int,int> hashing(int in[], int n)
{
    unordered_map <int,int> m;
    for(int i=0; i<n; i++)
            m[in[i]] = i;
    
    return m;
}

node *inPreHash(int in[], int pre[], int in_start, int in_end, int *preIndex, unordered_map <int,int> m)
{
    if(in_start > in_end)
        return NULL;
    
    node *root = new node(pre[(*preIndex)++]);

    int inMid = m[root->data];

    root->left = inPreHash(in, pre, in_start, inMid-1, preIndex, m);
    root->right = inPreHash(in, pre, inMid+1, in_end, preIndex, m);

    return root;
}

void post(node *root)
{
    if(root == NULL)
        return;
    
    post(root->left);
    post(root->right);
    cout<<root->data<<"  ";
}

int main()
{
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

    int in[] = {10,50,-10,20,-20,30,80,60,0,40,70};
    int pre[] = {-20,-10,10,50,20,0,30,60,80,40,70};

// The idea is to start forming the tree in the order of preorder array. One by one, we go through the preorder array, for each element, form a root node, find that value in the inorder array so that the elements left of it would comprise the left subtree and the elements right of it would comprise the right subtree. Then, we keep repeating this process for each left & right subtree obtained.
// The use of preorder and inorder array as described above is due to the sequence of nodes in them being, ROOT->LEFT->RIGHT & LEFT->ROOT->RIGHT respectively.
/*
    => TREE{10,50,-10,20,-20,30,80,60,0,40,70}: [in_start=0 to in_end=10]
        root = -20                                          [first preorder element]
        root->leftSubtree = {10,50,-10,20}                  [inorder elements left of root]
        root->leftSubtree = {30,80,60,0,40,70}              [inorder elements right of root]
        preOrder Remaining = {-10,10,50,20,0,30,60,80,40,70}

        => LEFT SUBTREE{10,50,-10,20}: [0 to 3]
            root = -10
            Left Subtree = {10,50}
            Right Subtree = {20}
            preOrder Remaining = {10,50,20,0,30,60,80,40,70}
        
            => LEFT SUBTREE{10,50}: [0 to 1]
                root = 10
                Left Subtree = NULL
                Right Subtree = {50}
                preOrder Remaining = {50,20,0,30,60,80,40,70}

                => LEFT SUBTREE{}: [0 to -1] => RESOLVED

                => RIGHT SUBTREE{50}: [1 to 1]
                    root = 50
                    Left Subtree = NULL
                    Right Subtree = NULL
                    preOrder Remaining = {20,0,30,60,80,40,70}

                    => LEFT SUBTREE{}: [1 to 0] => RESOLVED

                    => RIGHT SUBTREE{}: [2 to 1] => RESOLVED
            
            => RIGHT SUBTREE{20}: [3 to 3]
                root = 20
                Left Subtree = NULL;
                Right Subtree = NULL;
                preOrder Remaining = {0,30,60,80,40,70}

                => LEFT SUBTREE{}: [3 to 2] => RESOLVED

                => RIGHT SUBTREE{}: [4 to 3] => RESOLVED
        
        => RIGHT SUBTREE{30,80,60,0,40,70}: [5 to 10]
            root = 0
            Left Subtree = {30,80,60}
            Right Subtree = {40,70}
            preOrder Remaining = {30,60,80,40,70}

            => LEFT SUBTREE{30,80,60}: [5 to 7]
                root = 30
                Left Subtree = NULL
                Right Subtree = {80,60}
                preOrder Remaining = {60,80,40,70}
            
                => LEFT SUBTREE{}: [5 to 4] => RESOLVED

                => RIGHT SUBTREE{80,60}: [6 to 7]
                    root = 60
                    Left Subtree = {80}
                    Right Subtree = NULL
                    preOrder Remaining = {80,40,70}

                    => LEFT SUBTREE{80}: [6 to 6]
                        root = 80
                        Left Subtree = NULL
                        Right Subtree = NULL
                        preOrder Remaining = {40,70}
                    
                        => LEFT SUBTREE{}: [6 to 5] => RESOLVED
                        
                        => RIGHT SUBTREE{}: [7 to 6] => RESOLVED
                    
                    => RIGHT SUBTREE{}: [8 to 7] => RESOLVED
                
            => RIGHT SUBTREE{40,70}: [9 to 10]
                root = 40
                Left Subtree = NULL
                Right Subtree = {70}
                preOrder Remaining = {70}

                => LEFT SUBTREE{}: [9 to 8] => RESOLVED

                => RIGHT SUBTREE{70}
                    root = 70
                    Left Subtree = NULL
                    Right Subtree = NULL
                    preOrder Remaining = {}
                
                    => LEFT SUBTREE{}: [10 to 9] => RESOLVED

                    => RIGHT SUBTREE{}: [11 to 10] => RESOLVED
*/

    int preInd = 0;
    node *root = inPre(in, pre, 0, sizeof(pre)/sizeof(pre[0])-1, &preInd);
        // TIME COMPLEXITY: O(n²)
        // AUXILIARY SPACE: O(h)
    post(root);
    cout<<"\n";
    
    
    // USING HASHING
    preInd = 0;
    unordered_map <int,int> m = hashing(in, sizeof(in)/sizeof(in[0]));
    node *root_hash = inPreHash(in,pre, 0, sizeof(in)/sizeof(in[0])-1, &preInd, m);
        // TIME COMPLEXITY: O(n)
        // AUXILIARY SPACE: O(n)
    post(root_hash);


    // NOTE: To construct a binary tree, we either need inorder & preorder traversal or inorder & postorder traversal (we just start from the end of postorder traversal to get the desired result). It can't be done without inorder traversal.

    return 0;
}