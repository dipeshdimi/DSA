#include<iostream>
#include<vector>

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

// Pass by reference for vectors: Accept vector as an address.
bool findPath(node *root, vector <node*> &path, node *descendant)
{
    // NULL root => Implies descendant not found
    if(root == NULL)
        return false;

    // We push the current root to the path, and then we check if our desired descendant is among any of its descendants (i.e., left/right subtree), in which case, root would lie in the path to the descendant or is the root itself, in which case, root would be the last node in the path. If not, we'll pop this.
    path.push_back(root);

    // We found the descendant => The path vector is filled from the root to the descendant => Just return true.
    if(root == descendant)
        return true;

    // If the root is not the descendant, we look into the left and right subtree and if we find it in either of them, we return true.
    if(findPath(root->left, path, descendant) || findPath(root->right, path, descendant))
        return true;
    
    // We have checked for the node among the root, root's left subtree and it's right subtree, so, it's safe to conclude, that the current root doesn't lie in the path of the descendant. Thus, we pop it.
    // First pop happens when we reach the leftmost leaf node's left NULL pointer.
    path.pop_back();

    // Return false for the current root & complete the rest of the calls.
    return false;
}

node *LCA_On(node *root, node *desc1, node *desc2)
{
    // Paths from the root to the descendants
    vector <node*> path1;
    vector <node*> path2;

    // If we can't find a path from the root node to either of the descendants, then we just return NULL since the the descendant(s) doesn't/don't exist in the tree and thus, would have no common ancestor.
    if(!findPath(root, path1, desc1) || !findPath(root, path2, desc2))
        return NULL;
    
    // In the paths from the root to the descendants, we return the last common node since that would be the LOWEST common ancestor.
    for(int i=0; i<path1.size()-1 && i<path2.size()-1; i++)
    {
        if(path1[i+1] != path2[i+1])
            return path1[i];
    }
    
    // Return NULL when desc1 == desc2, i.e., same node.
    return NULL;
}

node *LCA_Oh(node *root, node* desc1, node *desc2)
{
    /* Four possible cases :-

        I. Current Root is one of the descendants => Just return the current root since one of the descendant (== current root) is the ancestor of the other descendant and if we go any lower in the tree, we would lose one of the descendant. Thus, the current root is the LOWEST common ancestor.

        II. One descendant is in the left subtree and the other, in the right subtree of the current root => This would be possible only when the current root itself is the lowest common ancestor (if it was not the lowest, both would either be in the same subtree or in neither), so, just return the current root.

        III. Both descendants present in the same subtree of the current root (either, both descendants in left subtree or both in right subtree) => Return whatever the one subtree which contains both the descendants would return on passing through the LCA_Oh() function.

        IV. Neither descendant in either of the subtrees of the current root => Return NULL as this means we need to revert back and go through previous function calls (for previous root, higher up in the tree).
    */

    // On reaching the leaf nodes (happens when we don't find the descendants)
    if(root == NULL)
        return NULL;

    // CASE I
    if(root == desc1 || root == desc2)
        return root;    // In case, only one of the descendant is present, this function just returns that descendant as the answer, instead of returning NULL, which is why it doesn't work when one of the descendant is not present.
    
    node *LCA_left = LCA_Oh(root->left, desc1, desc2);
    node *LCA_right = LCA_Oh(root->right, desc1, desc2);

    // CASE II (Both return non-null values => return root encountered in both cases => Descendants in both subtrees)
    if(LCA_left != NULL && LCA_right != NULL)
        return root;
    
    // We know, since we did not return in the previous if statement itself, that at least one of LCA_left and LCA_right is NULL. Here, we are appling the condition, LCA_left!=NULL, which means LCA_right has to be NULL. So, this condition is, no descendant is present in one of the subtree and and both are present in the the other subtree i.e., CASE III. Thus, we return the output of the subtree containing both the descendants.
    if(LCA_left != NULL)
        return LCA_left;
    // Possible cases left: (LCA_left == NULL && LCA_right != NULL) || (LCA_left == NULL && LCA_right == NULL) i.e., CASE III OR CASE IV.
    // In CASE III, we return the output of the subtree containing both the descendants i.e., LCA_right.
    // In CASE IV, we return NULL(==LCA_right).
    else
        return LCA_right;
}


int main()
{
    node*root = new node(-20);
    root->left = new node(-10);
    root->right = new node(7);
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
          -10(n1)       7(n2)
          /     \       /    \
        10(n3)  20(n4) 30(n5) 40(n6)
         \              \        \
         50(n7)        60(n8)    70(n9)
                      /
                    80(n10)
    */

    node *desc1 = root->right->left->right->left;
    node *desc2 = root->right->right;

    // This can also  be used to find distance b/w two nodes [dist(lca to desc1) + dist(lca to desc2) + 1]
    cout<<LCA_On(root, desc1, desc2)->data<<"\n";  // 80 & 40
        // TIME COMPLEXITY: O(n)
        // AUXILIARY SPACE: O(n)

    // Works only when it is guaranteed that either both the descendants are present in the tree or neither are present. This is because we return as soon as we find one of the descendant assuming that the other descendant must be descended from the first descendant itself since it was guaranteed that the other descendant would be present, which is the basis for CASE I.
    cout<<LCA_Oh(root, desc1, desc2)->data;
        // TIME COMPLEXITY: O(n)
        // AUXILIARY SPACE: O(h)


    return 0;
}