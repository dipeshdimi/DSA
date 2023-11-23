#include<iostream>

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

// node *prv=NULL;
node *treeDLL(node *root, node**prev)
{
    if(root == NULL)
        return root;    // returning NULL

    // head is returned (=NULL), i.e., this line terminates (treeDLL() function terminates), for the first time when root is the leftmost node of the binary tree, which would be the first node in the inorder traversal of the tree and thus the first node/head of the doubly linked list we'll form.
    node *head = treeDLL(root->left, prev);

    // The first (and only, since *prev would be changed from NULL after this if-else ladder) time this if statement executes would be when treeDLL() funtcion terminates for the first time. Since on its first termination, we know, root is the leftmost node of the tree, which we would want to be returned as the head of the doubly linked list, we would set head = NULL.
    if(*prev == NULL)
        head = root;
    else
    {
        // Here, left and right are equivalent to the PREV and NEXT pointers of a doubly linked list.
        (*prev)->right = root;
        root->left = *prev;
            // We don't need to set this for the head (leftmost tree node) of the tail element (rightmost tree node) of the DLL since for them, we write, head->PREV=NULL and tail->NEXT=NULL, which is automatically set as the left and right pointers of the tree point to NULL by default (set in the constructor).
    }

    // As we're going to call the child node of root, we set the previous node we processed as root itself.
    *prev = root;

    // We don't even store the value returned by the right node since it's of no use, unless we wish to return the tail of the DLL instead of its head.
    // Also, writing the prev pointer here is very important as otherwise, it will just take the value NULL, return the incorrect results, without showing any error.
    treeDLL(root->right, prev);

    // Once the head=treeDLL(root->left); line gives a result, head=root; line would be executed (only once throughout the entire execution) and head would already have the value we want to return. Since apart from these, there is no other line dealing with head, the same head value would keep returning up until it reaches the root node of the tree. By then, the left subtree would have been processed and right subtree would be left, but since whenever we call treeDLL(root->right), we don't store the value it returns, there would be no change in head. Thus, values returned by a right child don't matter and the left children just return the same value in a chain. Hence, we get our desired head pointer, which we return.
    // Even though there would be a chain of the first inorder element returned after the first time it terminates, the first termination would still return NULL from the if(root==NULL) statement. Note that only the leftmost elements return this value, not the entire subtree.
    /*
                    a
                /       \
               b         c
             /   \     /   \
            d     e   g     h
                 /
                f 
            
            Chain of return : d->b->a       [node *head = treeDLL(root->left, prev);]
            No other element would be part of this head returning chain. Even though f & g would return a head value to their parents, since their parents are right elements, that value won't carried further.
    */
    return head;
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

// Convert a given binary tree to a doubly linked list with the doubly linked list's nodes arranged in the order of the inorder traversal of the binary tree and return the head of the doubly linked list.

    // prevPtr is the pointer pointing to a pointer. This way, we can avoid defining a global variable 'node *prv'.
    node *prevPtr = NULL;
    node *head = treeDLL(root, &prevPtr);      // node *prev pointer is optional as we have given it a defualt value, NULL./

    while(head->right != NULL)
    {
        cout<<head->data<<"  ";
        head = head->right;
    }
    cout<<head->data<<"\n";

    while(head != NULL)
    {
        cout<<head->data<<"  ";
        head = head->left;
    }

    // NOTE: std::prev is an iterator defined in the #include<iterator> library, so using it a globally defined identifier by that name would give "refernce to 'prev' is ambiguous" error.

    // TIME COMPLEXITY: O(n)
    // AUXILIARY SPACE: O(h)

    return 0;
}