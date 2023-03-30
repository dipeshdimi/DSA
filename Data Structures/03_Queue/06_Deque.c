#include<stdio.h>
#include<stdlib.h>

struct arr
{
    int size;
    int front;
    int rear;
    int*arr;
};

struct node
{
    int data;
    struct node*prev;
    struct node*next;
};

void enqueue_arr_front(struct arr*q_arr, int value)
{
    if((q_arr->rear+1)%q_arr->size == q_arr->front)
    {
        printf("Queue Overflow : No more elements can be inserted.\n");
    }
    else if(q_arr->front == -1)
    {
        q_arr->front = 0;
        q_arr->rear = 0;
        q_arr->arr[q_arr->front] = value;
    }
    else if(q_arr->front == 0)
    {
        q_arr->front = q_arr->size-1;
        q_arr->arr[q_arr->front] = value;
    }
    else
    {
        q_arr->front--;
        q_arr->arr[q_arr->front] = value;
    }
}

void enqueue_arr_rear(struct arr*q_arr, int value)
{
    if(q_arr->front == (q_arr->rear+1)%q_arr->size)
    {
        printf("Queue Overflow : No more elements can be inserted.\n");
    }
    else if(q_arr->front == -1)
    {
        q_arr->front = 0;
        q_arr->rear = 0;
        q_arr->arr[q_arr->rear] = value;
    }
    else
    {
        q_arr->rear++;
        q_arr->arr[q_arr->rear] = value;
    }
}

void dequeue_arr_front(struct arr*q_arr)
{
    if(q_arr->front == -1)      // OR if(q_arr->rear == -1), either will work
    {
        printf("Queue Underflow : Queue is  already Empty.\n");
    }
    else if(q_arr->front == q_arr->rear)
    {
        printf("Dequeued Value = %d\n", q_arr->arr[q_arr->front]);
        q_arr->front = -1;
        q_arr->rear = -1;
    }
    else
    {
        printf("Dequeued Value = %d\n", q_arr->arr[q_arr->front]);
        q_arr->front = (q_arr->front+1)%q_arr->size;
    }
}

void dequeue_arr_rear(struct arr*q_arr)
{
    if(q_arr->front == -1)      // OR if(q_arr->rear == -1), either will work
    {
        printf("Queue Underflow : Queue is  already Empty.\n");
    }
    else if(q_arr->front == q_arr->rear)
    {
        printf("Dequeued Value = %d\n", q_arr->arr[q_arr->rear]);
        q_arr->front = -1;
        q_arr->rear = -1;
    }
    else if(q_arr->rear == 0)
    {
        printf("Dequeued Value = %d\n", q_arr->arr[q_arr->rear]);
        q_arr->rear = q_arr->size-1;
    }
    else
    {
        printf("Dequeued Value = %d\n", q_arr->arr[q_arr->rear]);
        q_arr->rear--;
    }
}

void display_arr(struct arr*q_arr)
{
    if(q_arr->front == -1)
    {
        printf("Nothing to display, deque is empty.\n");
        return;
    }

    int i=q_arr->front;
    do
    {
        printf("%d->", q_arr->arr[i]);
        i = (i+1)%q_arr->size;
    }while(i != (q_arr->rear+1)%q_arr->size);

    // do while loop for the case when queue is full as i is initialised with q_arr->front and in case a full queue, (q_arr->rear+1) will be equal to q_arr->front. In case the queue is empty, function will terminate even before entering into the loop, thus, printing no garbage value in that case either.

    printf("\n");
}



void enqueue_ll_front(struct node**front, struct node**rear, int value)
{
    struct node*ptr = (struct node*)malloc(sizeof(struct node));

    if(ptr == NULL)
    {
        printf("Queue/Heap Overflow.\n");
    }
    else
    {
        ptr->next = *front;
        ptr->prev = NULL;
        ptr->data = value;

        if(*front == NULL)      // OR *rear == NULL, either will do
        {
            *front = *rear = ptr;
        }
        else
        {
            (*front)->prev = ptr;
            *front = ptr;
        }
    }
}

void enqueue_ll_rear(struct node**front, struct node**rear, int value)
{
    struct node*ptr = (struct node*)malloc(sizeof(struct node));

    if(ptr == NULL)
    {
        printf("Heap/Queue Overflwo.\n");
    }
    else
    {
        ptr->data = value;
        ptr->next = NULL;
        ptr->prev = *rear;

        if(*front == NULL)      // OR *rear == NULL, either will do
        {
            *rear = *front = ptr;
        }
        else
        {
            (*rear)->next = ptr;
            *rear = ptr;
        }
    }
}

void dequeue_ll_front(struct node**front, struct node**rear)
{
    if(*front == NULL)
    {
        printf("Queue Underflow.\n");
    }
    else if((*front)->next == NULL)          // OR (*rear)->prev == NULL, either will do
    {
        printf("Dequeued Value = %d\n", (*front)->data);
        free(*front);                       // OR free(*rear), either will do
        *front = *rear = NULL;
        /* This if statement is for the case in which there is just one element left in the deque */
    }
    else
    {
        struct node*ptr = *front;
        printf("Dequeued Value = %d\n", ptr->data);
        *front = (*front)->next;
        (*front)->prev = NULL;
        free(ptr);
    }
}

void dequeue_ll_rear(struct node**front, struct node**rear)
{
    if(*front == NULL)
    {
        printf("Queue Underflow.\n");
    }
    else if((*rear)->prev == NULL)          // OR (*front)->next == NULL, either will do
    {
        printf("Dequeued Value2 = %d\n", (*rear)->data);    // OR (*front)->data, either will do
        free(*rear);                       // OR free(*front), either will do
        *front = *rear = NULL;
        /* This if statement is for the case in which there is just one element left in the deque */
    }
    else
    {
        struct node*ptr = *rear;
        printf("Dequeued Value = %d\n", ptr->data);
        *rear = (*rear)->prev;
        (*rear)->next = NULL;
        free(ptr);
    }
}

void display_ll(struct node*front)
{
    if(front == NULL)
    {
        printf("Nothing to display, deque is empty.");
    }
    else
    {
        while(front != NULL)
        {
            printf("%d->", front->data);
            front = front->next;
        }
    }
    printf("\n");
}

int main()
{
    /* 
    1) Deque (Double Ended Queue) is a linear data structure in which the insertion and deletion operations are performed from both ends.
    2) Deque can be used both as stack and queue as it allows the insertion and deletion operations on both ends (Follows both LIFO/FILO as well as FIFO/LILO).
    3)  => In an input-restricted queue, insertion is possible on only a single end (rear end) while deletion is applicable from both the ends.
        => In an output-restricted queue, deletion can only be from one end (front end), whereas the insertion is possible from both ends.
    4) Deque can be implemented using two data structures, i.e., circular array (to make sure there is wastage of space, time complexity remains O(1) for all operations and all the operations are possible as long the allocated memory is not completely filled), and doubly linked list (bcoz we cannot delete from the rear in O(1) time in case of a singly/circular linked list). 
    */


// Circular Array
    struct arr *q_arr = (struct arr*)malloc(sizeof(struct arr));
    q_arr->size = 10;
    q_arr->front = q_arr->rear = -1;
    q_arr->arr =(int*)malloc(sizeof(int)*q_arr->size);
    
    display_arr(q_arr);
    enqueue_arr_front(q_arr, -40);
    enqueue_arr_front(q_arr, -30);
    // enqueue_arr_front(q_arr, -20);
    // enqueue_arr_front(q_arr, -10);
    // enqueue_arr_rear(q_arr, 0);
    // enqueue_arr_rear(q_arr, 10);
    // enqueue_arr_rear(q_arr, 20);
    // enqueue_arr_rear(q_arr, 30);
    // enqueue_arr_front(q_arr, 40);
    // enqueue_arr_front(q_arr, 50);

    display_arr(q_arr);

    dequeue_arr_front(q_arr);
    dequeue_arr_rear(q_arr);
    dequeue_arr_rear(q_arr);

    display_arr(q_arr);


// Doubly Linked List
    struct node*q_ll_front = NULL;
    struct node*q_ll_rear = NULL;

    enqueue_ll_front(&q_ll_front, &q_ll_rear, -30);
    enqueue_ll_rear(&q_ll_front, &q_ll_rear, -10);
    enqueue_ll_front(&q_ll_front, &q_ll_rear, -20);
    enqueue_ll_rear(&q_ll_front, &q_ll_rear, 0);

    display_ll(q_ll_front);

    dequeue_ll_front(&q_ll_front, &q_ll_rear);
    display_ll(q_ll_front);

    dequeue_ll_rear(&q_ll_front, &q_ll_rear);
    dequeue_ll_rear(&q_ll_front, &q_ll_rear);

    display_ll(q_ll_front);
    

    return 0;
}