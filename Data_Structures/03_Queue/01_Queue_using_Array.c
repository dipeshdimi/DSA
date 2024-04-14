#include<stdio.h>
#include<stdlib.h>

struct queue
{
    int size;
    int front;
    int rear;
    int *arr;
};

void enqueue(struct queue*q, int value)
{
    if(q->rear == q->size-1)
        printf("Queue Overflow.\n");
    else
    {
        q->rear++;
        q->arr[q->rear] = value;
    }
}

void dequeue(struct queue*q)
{
    if(q->front == q->rear)
        printf("Queue Underflow.\n");
    else
    {
        // Dequeued indices in the beginning of the array remain unused, which is why circular array implementation is preferred
        q->front++;
        printf("Dequeued Value = %d", q->arr[q->front]);
    }
}

void display(struct queue*q)
{
    for (int i = q->front; i < q->rear; i++)
        printf("arr[%d] = %d\n", i, q->arr[i+1]);
}

int main()
{
/*
    => Stack: 1) Stack/pile of books 
              2) LIFO/FILO
              3) Deletion and Insertion, both from the front/head (like in the case of a stack of books)
    => Queue: 1) Queue/line to buy railway tickets
              2) FIFO/LILO
              3) Deletion from front and Insertion from rear (like in a queue to buy railway tickets)
*/
    struct queue*q = (struct queue*)malloc(sizeof(struct queue));
    q->size = 100;
    q->front = -1;
    q->rear = -1;
    q->arr = (int*)malloc(q->size*sizeof(int));

    enqueue(q, -30);
    enqueue(q, -20);
    enqueue(q, -10);
    enqueue(q, 0);
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    dequeue(q);
    dequeue(q);

    display(q);

    return 0;
}