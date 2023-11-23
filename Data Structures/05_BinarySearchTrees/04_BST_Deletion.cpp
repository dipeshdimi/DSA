#include<iostream>

using namespace std;

struct node
{
    int data;
    node *left, *right;

    node(int value){
        data = value;
        left = NULL;
        right = NULL;
    }
};

// Works only when the inorder predecessor is not an ancestor, but that is of concern here since that happens only when at least one of the child node is NULL, in which case this function wouldn't have even been called as the previous two conditions handle that case [if(root->left == NULL) ands else if(root->right==NULL)].
node *inorderPredecessor(node* root){
    root = root->left;
    while (root->right!=NULL)
        root = root->right;
    
    return root;
}
node *inorderSuccessor(node* root){
    root = root->right;
    while (root->left!=NULL)
        root = root->left;
    
    return root;
}

node *deleteNode(struct node *root, int value)
{
    // Nothing to delete
    if (root == NULL)
        return NULL;

    // Searching for the node to be deleted
    if (value < root->data)
        root-> left = deleteNode(root->left,value);
    else if (value > root->data)
        root-> right = deleteNode(root->right,value);
    // Deletion strategy when the node is found (i.e., when value == root->data)
    else{
        // If the left subtree of the current node (i.e., the node to be deleted) is empty, we can just return current node's right child as the replacement node without tweaking anything since there is no left subtree and the right subtree is already a BST.
        // The return statement would return the deleted node's parent the replacement node and it will be set as its new child via root->left = deleteNode(root->left,value); or root->right = deleteNode(root->right,value);.
        // In case both, both the left as well as the right subtree are empty i.e., the current node (node to be deleted) is a leaf node, the following handles that too since we just delete the node and the return value is NULL, which becomes the deleted node's parent's new child after the (leaf) current node is deleted.
        if(root->left == NULL)
        {
            node *temp = root->right;
            delete(root);
            return temp;
        }
        // Similarly, if the right subtree is empty...
        else if(root->right == NULL)
        {
            node *temp = root->left;
            delete(root);
            return temp;
        }
        else
        {
            // We can't directly delete the root here since its children need to repositioned i.e., one of its descendant has to take its place so that we don't break the tree. Now, since we need to make sure that the tree remains a BST, we would have to replace the deleted node with the value closest to either (smaller closest or greater closest, either would work). This way, if we choose to replace the deleted node with the smaller closest node, the elements in the left subtree still remain smaller than the replaced element since deleted root's closest smaller value would be greater than all other values smaller than it, i.e., values in its left subtree and since the replaced element belongs to the left subtree, it would anyway be smaller than the right subtree elements. Similar would be the case if we replace the deleted node with the closest greater value.
            // Now, in order to find the closest smaller or the closest greater value, we can just obtain the value left to deleted node or the value right to the deleted node in the list of sorted tree nodes, respectively i.e., inorder predecessor or inorder successor.

        /* Replacement with Predecessor */
            // Deleted node's replacement (inorder successor would've also worked)
            node *iPre = inorderPredecessor(root);

            // Current root stores the value of its inorder predecessor now (the original predecessor node also exists as of now)
            root->data = iPre->data;

            // We look for the predecessor node in  the left subtree of the current root (left since we're looking for the predecessor) and delete it via one of the above two if/elseif statements since the closest inorder predecessor would have at least one NULL child. The new root's (predecessor value) left child is then updated as the result of this function call.
            root->left = deleteNode(root->left, iPre->data);

        // /* Replacement with Successor */
        //     node *iSuc = inorderSuccessor(root);
        //     root->data = iSuc->data;
        //     root->right = deleteNode(root->right, iSuc->data);
        }
    }

    // Returning the current root for all the call terminations without deletion
    return root;
}

void inorder(node*root)
{
    if(root != NULL)
    {
        inorder(root->left);
        cout<<root->data<<"  ";
        inorder(root->right);
    }
}

int main()
{
    node *root = new node(50);
    root->left = new node(40);
    root->right = new node(70);
    root->left->left = new node(20);
    root->right->left = new node(60);
    root->right->right = new node(80);
    root->left->left->left = new node(10);
    root->left->left->right = new node(30);
    /*
                    n1(50)
                    /    \
                n2(40)    n3(70)
                /         /    \
            n4(20)    n5(60)   n6(80)
            /   \
        n7(10)  n8(30)
    */

    inorder(root);
    cout<<"\n";
    deleteNode(root, 40);
    inorder(root);

    return 0;
}