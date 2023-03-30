#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node*next;
};

void display(struct node *ptr)
{
    printf("\n");
    printf("Queue/Linked List Elements =>  ");
    while (ptr != NULL)
    {
        printf("%d->", ptr->data);
        ptr = ptr->next;
    }
    printf("\n\n");
}

void enqueue(struct node**fp, struct node**rp, int value)       // front_pointer, rear_pointer
{
    struct node*ptr = (struct node*)malloc(sizeof(struct node));

    if(ptr == NULL)
        printf("Queue/Heap Overflow");
    else
    {
        ptr->data = value;
        ptr->next = NULL;

        if(*fp == NULL)
            *rp = *fp = ptr;
        else
        {
            (*rp)->next = ptr;
            *rp = ptr;
        }   
    }
}

void dequeue(struct node**fp, struct node**rp)
{
    if(*fp == NULL)
    {
        printf("Queue Underflow.\n");
    }
    else if ((*fp)->next == NULL)
    {
        printf("Dequeued Value = %d\n", (*fp)->data);
        free(*fp);                                  // OR free(*rp), either will do
        *fp = *rp = NULL;
        /* This if statement is for the case in which there is just one element left in the deque */
    }
    else
    {
        struct node*ptr = *fp;
        *fp = (*fp)->next;
        printf("Dequeued Value = %d\n", ptr->data);
        free(ptr);
    }
}

int main()
{
    struct node*front = NULL;
    struct node*rear = NULL;

    enqueue(&front, &rear, -30);
    enqueue(&front, &rear, -20);
    // enqueue(&front, &rear, -10);
    // enqueue(&front, &rear, 0);
    // enqueue(&front, &rear, 10);
    // enqueue(&front, &rear, 20);
    // enqueue(&front, &rear, 30);
    
    display(front);

    dequeue(&front, &rear);
    dequeue(&front, &rear);
    dequeue(&front, &rear);

    display(front);

    return 0;
}