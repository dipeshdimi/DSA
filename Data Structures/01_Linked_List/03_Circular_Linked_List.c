#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node*next;
};

void traversal(struct node*head)
{
    struct node*traversal = head;
    do
    {
        printf("%d\n", traversal->data);
        traversal = traversal->next;
    } while (traversal != head);
}


// INSERTION IN A LINKED LIST
struct node* insert_beginning(struct node*head, int data)
{
    struct node* ptr = (struct node*)malloc(sizeof(struct node));
    struct node* head_initially = head;

    while(head->next != head_initially)
        head = head->next;
    
    ptr->data = data;
    head->next = ptr;
    ptr->next = head_initially;

    return ptr;   
}

void insert_between(struct node*head, int data, int index)
{
    struct node*ptr = (struct node*)malloc(sizeof(struct node));
    
    while (--index)
        head = head->next;
    
    ptr->data = data;
    ptr->next = head->next;
    head->next = ptr;
}

void insert_end(struct node*head, int data)
{
    struct node* HEAD = head;

    while(head->next != HEAD)
        head = head->next;
    
    struct node*ptr = (struct node*)malloc(sizeof(struct node));

    head->next = ptr;
    ptr->next = HEAD;
    ptr->data = data;
}

void insert_after_node(struct node* prev_node, int data)
{
    struct node*ptr = (struct node*)malloc(sizeof(struct node));
    ptr->next = prev_node->next;
    prev_node->next = ptr;
    ptr->data = data;
}

// DELETION
struct node* delete_beginning(struct node*head)
{
    struct node*head_initially = head;

    while(head->next != head_initially)
        head = head->next;
    
    head->next = head_initially->next;
    free(head_initially);
    return head->next;
}

struct node* delete_between(struct node*head, int index)
{
    while(--index)
        head = head->next;
    
    struct node*ptr = head->next;
    head->next = ptr->next;
    free(ptr);
}

struct node* delete_end(struct node*head)
{
    
}

struct node* delete_after_node(struct node* prev_node)
{
    
}

struct node* delete_node_data_given(struct node*head, int data)
{
    
}


int main()
{
    // CREATION OF A CIRCULAR LINKED LIST
    // Node Creation
    struct node*head = (struct node*)malloc(sizeof(struct node));
    struct node*second = (struct node*)malloc(sizeof(struct node));
    struct node*third = (struct node*)malloc(sizeof(struct node));
    struct node*fourth = (struct node*)malloc(sizeof(struct node));
    struct node*fifth = (struct node*)malloc(sizeof(struct node));

    // Linking Nodes
    head->data = -20;
    head->next = second;

    second->data = -10;
    second->next = third;

    third->data = 0;
    third->next = fourth;

    fourth->data = 10;
    fourth->next = fifth;

    fifth->data = 20;
    fifth->next = head;
    
    // NOTE : Any node can be considered the head in a circular linked list



    // // TRAVERSAL IN A CIRCULAR LINKED LIST
    // traversal(head);        // Any node can be passed here, it will be treated as head



    // INSERTION IN A CIRCULAR LINKED LIST
        // // Insertion in the Beginning
        // head = insert_beginning(head, -30);
        // traversal(head);

        // // Insertion in Between
        // insert_between(head, 5, 3);
        // traversal(head);

        // // Insertion in the end
        // insert_end(head, 30);
        // traversal(head);

        // // Insertion after a node
        // insert_after_node(second, -5);
        // traversal(head);



    // DELETION IN A SINGLY LINKED LIST
        // // Deletion in the Beginning
        // head = delete_beginning(head);
        // traversal(head);
        // traversal(second);
        /* Both head and second point to the same node in memory */

        // // Deletion in Between
        // delete_between(head, 2);
        // printf("%d\n", third->data);             // DANGLING POINTER
        // third = NULL;                            // DANGLING POINTER TURNED INTO NULL POINTER
        // traversal(head);

        // // Deletion in the End
        // delete_end(head);
        // printf("%d\n", fifth->data);             // DANGLING POINTER
        // fifth = NULL;                            // DANGLING POINTER TURNED INTO NULL POINTER
        // traversal(head);

        // // Deletion after a Node
        // delete_after_node(second);
        // printf("%d\n", third->data);             // DANGLING POINTER
        // third = NULL;                            // DANGLING POINTER TURNED INTO NULL POINTER
        // traversal(head);

        // // Deletion of a node holding a given value
        // traversal(delete_node_data_given(head, 20));
        // Abhi dekhenge dangling pointers k bare me is case me


// NOT DOING THESE LAST ONES, ALL THESE CAN BE DONE SIMILARLY


    return 0;
}