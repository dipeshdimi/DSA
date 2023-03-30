#include <stdio.h>
#include<stdlib.h>      // For malloc, calloc, realloc, free

struct node
{
    int data;
    struct node*next;
};


// TRAVERSAL IN A LINKED LIST
void traversal(struct node *traversal)
{
    while(traversal != NULL)
    {
        printf("%d->", traversal->data);
        traversal = traversal->next;
    }
    printf("\n");
}


// INSERTION IN A LINKED LIST
struct node *insert_beginning(struct node*head, int data)
{
    struct node* ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next = head;
    return ptr;
}

void insert_between(struct node*head, int data, int index)
{
    struct node*ptr = (struct node*)malloc(sizeof(struct node));

    while(--index)
        head = head->next;      
    
    ptr->next = head->next;
    head->next = ptr;
    ptr->data = data;

    /* NOTE : The value of actual argument head is not affected by changing the formal argument head. This is because :-
    1) These are two different pointers with same/different names (head, here, in both cases) pointing to the same address in memory. Hence, using either of the pointer, we can modify whatever is stored at the memory location these pointers point to, but the pointers themselves still remain independent of each other.
    2) The actual argument doesn't even exist in the scope of this function.
    3) Even if actual argument head did exist in the scope of the functin, it would had gotten overshadowed by the formal argument head due to which all the changes happen to this formal argument which gets destroyed as soon as the function terminates. It is like a local variable overshadowing a global variable despite same names. */
}

struct node *insert_end(struct node*head, int data)
{
    struct node*ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next = NULL;

    if(head == NULL)
        return ptr;

    struct node *curr = head;
    while((curr->next) != NULL)
        curr = curr->next;

    curr->next = ptr;

    return head;
}

void insert_after_node(struct node* prev_node, int data)
{
    struct node*ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next = prev_node->next;
    prev_node->next = ptr;
}


// DELETION
struct node *delete_beginning(struct node*head)
{
    if(head == NULL)
        return NULL;
    
    struct node *ptr = head->next;
    free(head);
    return ptr;
}

void delete_between(struct node*head, int index)
{
    while(--index)
        head = head->next;
    
    struct node *ptr = head->next;
    head->next = ptr->next;
    free(ptr);
}

struct node *delete_end(struct node*head)
{
    if(head == NULL)
        return NULL;

    if(head->next == NULL)
    {
        free(head);
        return NULL;
    }
    
    struct node *curr = head;
    while(curr->next->next != NULL)
        curr = curr->next;

    free(curr->next);
    curr->next = NULL;

    return head;
}

void delete_after_node(struct node* prev_node)
{
    struct node*ptr = prev_node->next;
    prev_node->next = ptr->next;
    free(ptr);
}

struct node* delete_node_data_given(struct node*head, int data)
{
    struct node*ptr_head = head;
    struct node*ptr_delete = head;

    if(head->data == data)
    {
        head = head->next;
        free(ptr_delete);
        return head;
    }

    while (head->next->data != data  && head->next->next != NULL)
        head = head->next;
    
    if(head->next->data == data)
    {
        ptr_delete = head->next;
        head->next = ptr_delete->next;
        free(ptr_delete);
    }
    return ptr_head;
}



int main()
{
    // CREATION OF A SINGLY LINKED LIST
        // Node Creation
        struct node*head = (struct node*)malloc(sizeof(struct node));
        struct node*second = (struct node*)malloc(sizeof(struct node));
        struct node*third = (struct node*)malloc(sizeof(struct node));
        struct node*fourth = (struct node*)malloc(sizeof(struct node));

        // Linking Nodes
        head->data = 10;
        // printf("Head Node Data= ");
        // scanf("%d", &(head->data));
        head->next = second;

        second->data = 20;
        // printf("Second Node Data = ");
        // scanf("%d", &(second->data));
        second->next = third;

        third->data = 30;
        // printf("Third Node Data = ");
        // scanf("%d", &(third->data));
        third->next = fourth;

        fourth->data = 40;
        // printf("Fourth Node Data = ");
        // scanf("%d", &(fourth->data));
        fourth->next = NULL;

        // printf("%d\n", head->data);      // -> accesses struct member via pointer to struct instance (node, here)
        // printf("%d\n", (*head).data);    // . accesses struct member via struct instance
        // printf("%d\n", second->data);
        // printf("%d\n", third->data);
        // printf("%d\n", fourth->data);


    // // TRAVERSAL IN A SINGLY LINKED LIST
    //     traversal(head);


    // INSERTION IN A SINGLY LINKED LIST
        // // Insertion in the Beginning
        // head = insert_beginning(head, 0);
        // traversal(head);

        // // Insertion in Between
        // insert_between(head, -10, 2);
        // traversal(head);

        // // Insertion in the End
        // head = insert_end(head, 50);
        // traversal(head);

        // // Insertion after a Node
        // insert_after_node(third, -20);
        // traversal(head);


    // DELETION IN A SINGLY LINKED LIST
        // // Deletion in the Beginning
        // head = delete_beginning(head);
        // traversal(head);
        // traversal(second);
        /* Here, both head and second point to the same node in memory*/

        // // Deletion in Between
        // delete_between(head, 2);
        // printf("%d\n", third->data);             // DANGLING POINTER
        // third = NULL;                            // DANGLING POINTER TURNED INTO NULL POINTER
        // traversal(head);

        // // Deletion in the End
        // head = delete_end(head);
        // printf("%d\n", fourth->data);            // DANGLING POINTER
        // fourth = NULL;                           // DANGLING POINTER TURNED INTO NULL POINTER
        // traversal(head);

        // // Deletion after a Node
        // delete_after_node(second);
        // printf("%d\n", third->data);             // DANGLING POINTER
        // third = NULL;                            // DANGLING POINTER TURNED INTO NULL POINTER
        // traversal(head);

        // // Deletion of a node holding a given value
        // traversal(delete_node_data_given(head, 20));


    return 0;
}