#include<iostream>
#include<math.h>

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

int countNaive(node *root)
{
    if(root == NULL)
        return 0;
    
    return 1+countNaive(root->left)+countNaive(root->right);
}

int countEfficient(node *root)
{
    // NOTE 1: There is no need for the base case if (root==NULL) return 0;, since that is also handled by pow(2,0)-1 = 0.
    // NOTE 2: We can't just use the regular height function here, coz it would give the same lh and rh value even when the last node is a left node (instead of a right node) in which case, the function would return ppow(2,lh+1)-1, even though the current subtree is not a complete binary tree [we are using lh+1 (could also be used since this statement is executed when lh==rh) since when calculating height(root->left) or height(root->right), root itself is not counted]. Besides, the  time complexity would become O(n*log₂n), which would be even worse than the naive method.

    // Here, lh & rh may not necessarily be the height of the left and right subtree (including the root) when the given tree is not complete, but our condition for using the pow(2,lh)-1 is for the tree to be complete which is possible only when lh and rh are indeed the same and represent the height of the tree. We calculate lh and rh just to check if the current tree is a complete binary tree or not.
    int lh=0, rh=0;

/* I. Θ(h) */
    // Just calculate by the lh & rh by going to the leftmost and rightmost nodes of the tree and counting the number of elements we had to pass through.
    node *temp = root;
    while(temp != NULL)
    {
        lh++;
        temp = temp->left;
    }

/* II. Θ(h) */
    temp = root;
    while(temp != NULL)
    {
        rh++;
        temp = temp->right;
    }

    // When a subtree is completely filled even at the last level.
    if(lh == rh)
        return pow(2,lh+1)-1;
    // When a subtree is not completely filled at the last level, we just revert back to the naive method.
    else
        return 1 + countEfficient(root->left) + countEfficient(root->right);
/* III. 
    => If pow(2,lh+1)-1 is returned, time complexity would be Θ(1).

    => In case lh!=rh, two function calls are going to be executed, i.e., countEfficient(root->left) & countEfficient(root->right). Now, there can be two cases :-

        1) Last node falls into the LEFT subtree: In this case, the RIGHT subtree would definitely be a complete binary tree, and thus, countEfficient(root->right) would be resolved in Θ(h)+Θ(h)+Θ(1) = Θ(h) complexity. The countEfficient(root->left) call, on the hand, may or may not be a complete binary tree, so it could take more than Θ(h) complexity to resolve.
        
        2) Last node falls into the RIGHT subtree: In this case, the LEFT subtree would definitely be a complete binary tree, and thus, countEfficient(root->left) would be resolved in Θ(h)+Θ(h)+Θ(1) = Θ(h) complexity. The countEfficient(root->right) call, may or may not be a complete binary tree, so it could take more than Θ(h) complexity to resolve.
        
    => Thus, in either case, at least one of the two calls would be resolved in Θ(h) time (both could be resolved too). 
    
    => Maximum number of nodes remaining once one of the two calls is resolved, an upper cap of 2n/3 elements would be left in the unresolved subtree.
        { Max unresolved nodes would be when the unresolved subtree has the last level completely filled except its rightmost element (if even the last element was filled, it would have also resolved as explained in the previous  point) i.e. :-
                             1
                           /   \
                          2     3
                         / \   / \
                        4   5 6   7
                       /\  / \
                      8  9 0 NULL
            Here, n = 1 + (2ʰ⁻²-1) + (2ʰ⁻¹-1-1)     [Root + Left Subtree + Right Subtree]
                  n = 2ʰ⁻²(1+2) - 2
                  n = 3*2ʰ⁻² - 2    ...(1)

                  Also, no. of unresolved nodes = n - (no. of resolved nodes + 1)       [+1 for root]
                                                = n - ((2ʰ⁻²-1) + 1)
                                                = n - 2ʰ⁻²
                                                = n - (n+2)/3   [From (1), 2ʰ⁻² = (n+2)/3]
                                                = (3n-n-2)/3
                                                = 2(n-1)/3
        That's why, upper cap of 2n/3. }
    
    =>  T(n) < T(2n/3) + Θ(h)        [Θ(h), three times]
        T(n) = T(2n/3) + Θ(log₂n)
        T(2n/3) = T(4n/9) + Θ(log₂(2n/3))
        T(4n/9) = T(8n/27) + Θ(log₂(4n/9)
        T(4n/9) = T(16n/81) + Θ(log₂(8n/27)
                                .
                                .
                                .
                              Θ(log₂1)
        [Worst case, we had to come down to the leaf node (would happen when a leaf node is unpaired i.e., no right leaf node), for which n=1]

    => Now, n, 2n/3, 4n/9, 8n/27, ... 1 is a GP with a=n & r = 2/3.
    Thus, to get to 1, number of steps = x (let). Then,
        -> n*(2/3)ˣ = 1
        -> (3/2)ˣ = n
        -> x = log₃⸝₂(n)
    
    => Thus, in worst case, we perform log₃⸝₂(n) steps, each with complexity Θ(log₂n).

    => Hence,   TIME COMPLEXITY = O(log₃⸝₂n * log₂n)
                AUXILIARY SPACE = O(log₃⸝₂n)    [Each step means a recursive call]
    */
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
    root->left->left->left = new node(50);
    root->left->left->right = new node(60);
    root->left->right->left = new node(70);
    /*
                    -20(n0)
                  /         \
            -10(n1)          0(n2)
            /     \         /     \
        10(n3)   20(n4)   30(n5)  40(n6)
        /   \      /
    50(n7) 60(n8) 70(n9)
    */

    // Works on any kind of binary tree.
    cout<<countNaive(root)<<"\n";
        // TIME COMPLEXITY: O(n)
        // AUXILIARY SPACE: O(h)
    
    // Works only on complete binary trees.
    cout<<countEfficient(root);
        // TIME COMPLEXITY: O(log₃⸝₂(n) * log₂(n))
        // AUXILIARY SPACE: O(log₃⸝₂(n))

    return 0;
}