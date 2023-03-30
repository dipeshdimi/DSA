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
    if((q->rear+1)%q->size == q->front)
        printf("Queue Overflow.\n");
    else
    {
        q->rear = (q->rear+1)%q->size;
        q->arr[q->rear] = value;
        // First element arr[1] and not arr[0]
    }
}

void dequeue(struct queue*q)
{
    if(q->front == q->rear)
        printf("Queue Underflow.\n");
    else
    {
        // Dequeued indices in the beginning of the array are reused, which is why circular array implementation is preferred
        q->front = (q->front+1)%q->size;
        // By increasing q->front to q->front+1, we are allowing arr[q->front] to store a value as q->front represents the index just before array begins. For example, if initially, front = x, arr[x] was not storing any particular value. Once we increment front=0 to front=1, arr[0] is allowed to store any value and we do not store value in arr[1].
        printf("Dequeued Value = %d\n", q->arr[q->front]);
    }
}

void display(struct queue*q)
{
    int i=q->front+1;
    while (i != (q->rear+1)%q->size)
    {
        printf("arr[%d] = %d\n", i, q->arr[i]);
        i = (i+1)%q->size;
    }
    printf("\n");
}

int main()
{
    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    q->size = 10;
    q->front = 0;
    q->rear = 0;
    q->arr = (int*)malloc(q->size*sizeof(int));

    enqueue(q, -40);
    enqueue(q, -30);
    enqueue(q, -20);
    enqueue(q, -10);
    enqueue(q, 0);
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);
    // enqueue(q, 50);     // Queue Overflow

    display(q);

    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);

    display(q);

    enqueue(q, 60);
    enqueue(q, 70);

    display(q);

    return 0;
}