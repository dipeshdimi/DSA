#include<iostream>

using namespace std;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int value)
    {
        data = value;
        left = NULL;
        right = NULL;
    }
};

// void deleteNode(Node *root, int value)
// {
//     if(root == NULL)
//         return;
    
//     if(root->left == NULL && root->right == NULL)
//     {
//         free(root);
//         return;
//     }


// }


struct Node *inOrderPredecessor(struct Node* root){
    root = root->left;
    while (root->right!=NULL)
    {
        root = root->right;
    }
    return root;
}

struct Node *deleteNode(struct Node *root, int value){

    struct Node* iPre;
    if (root == NULL){
        return NULL;
    }
    if (root->left==NULL&&root->right==NULL){
        free(root);
        return NULL;
    }

    //searching for the Node to be deleted
    if (value < root->data){
        root-> left = deleteNode(root->left,value);
    }
    else if (value > root->data){
        root-> right = deleteNode(root->right,value);
    }
    //deletion strategy when the Node is found
    else{
        iPre = inOrderPredecessor(root);
        root->data = iPre->data;
        root->left = deleteNode(root->left, iPre->data);
    }
    return root;
}


int main()
{
    Node *root_n1 = new Node(50);
    Node *n2 = new Node(40);
    Node *n3 = new Node(70);
    Node *n4 = new Node(20);
    Node *n5 = new Node(60);
    Node *n6 = new Node(80);
    Node *n7 = new Node(10);
    Node *n8 = new Node(30);

    root_n1->left = n2;
    root_n1->right = n3;
    n2->left = n4;
    n3->left = n5;
    n3->right = n6;
    n4->left = n7;
    n4->right = n8;

    /*
                    n1(50)
                    /    \
                n2(40)    n3(70)
                /         /    \
            n4(20)    n5(60)   n6(80)
            /   \
        n7(10)  n8(30)
    */
    
    deleteNode(n7, 100);
    deleteNode(root_n1, 100);
    cout<<root_n1->data<<"\t"<<n2->data<<"\t"<<n3->data<<"\t"<<n4->data<<"\t"<<n5->data<<"\t"<<n6->data<<"\t"<<n7->data<<"\t"<<n8->data<<"\t";

    return 0;
}