#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *prev;
    struct node *next;
};

void traversal(struct node *head)
{
    struct node *tail;

    printf("In Forward Order :- \n");
    while(head != NULL)
    {
        printf("%d\n", head->data);
        tail = head;
        head = head->next;
    }
    
    printf("\nIn Reverse Order :- \n");
    while(tail != NULL)
    {
        printf("%d\n", tail->data);
        tail = tail->prev;
    }
}

int main()
{
    struct node *node1 = (struct node*)malloc(sizeof(struct node));
    struct node *node2 = (struct node*)malloc(sizeof(struct node));
    struct node *node3 = (struct node*)malloc(sizeof(struct node));
    struct node *node4 = (struct node*)malloc(sizeof(struct node));
    struct node *node5 = (struct node*)malloc(sizeof(struct node));

    node1->data = -20;
    node1->prev = NULL;
    node1->next = node2;

    node2->data = -10;
    node2->prev = node1;
    node2->next = node3;

    node3->data = 0;
    node3->prev = node2;
    node3->next = node4;

    node4->data = 10;
    node4->prev = node3;
    node4->next = node5;

    node5->data = 20;
    node5->prev = node4;
    node5->next = NULL;

    traversal(node1);

    return 0;
}