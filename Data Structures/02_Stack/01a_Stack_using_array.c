#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct stack
{
    int size;
    int top;
    int *arr;
};

bool isEmpty(struct stack *s)
{
    if(s->top == -1)
        return true;
    else
        return false;
    // Time Complexity : O(1)
}

bool isFull(struct  stack *s)
{
    if(s->top == s->size-1)
        return true;
    else
        return false;
    // Time Complexity : O(1)
}

void push(struct stack*s, int value)
{
    if(isFull(s))
    {
        printf("Stack Overflow!!!\n");
        return;
    }
    s->top++;
    s->arr[s->top] = value;
    // Time Complexity : O(1)
}

void pop(struct stack*s)
{
    if(isEmpty(s))
    {
        printf("Stack Underflow!!!\n");
        return;
    }
    int popped_value = s->arr[s->top];
    s->top--;
    printf("Popped value = %d\n", popped_value);
    // Time Complexity : O(1)
}

void peek(struct stack*s, int position)
{
    if(s->top-position+1 < 0)
    {
        printf("Invalid position of the element demanded.\n");
        return;
    }
    printf("Element at position %d from the top = %d\n", position, s->arr[s->top-position+1]);
    // Time Complexity : O(1)
}



int main()
{
/* STACK CREATION */

    // struct stack s;              // stack instance s is stored in stack memory
    // s.size = 50;
    // s.top = -1;
    // s.arr = (int*)malloc(s.size*sizeof(int));
    // /* To pass in functions, isEmpty(&s), to fill array, s.arr[i]=whatever and s.top++, will do the job.*/

    // struct stack s;              // stack instance s is stored in stack memory
    // struct stack *s_ptr = &s;    // Pointer s_ptr is stored in stack memory
    // s_ptr->size = 50;
    // s_ptr->top = -1;
    // s_ptr->arr = (int*)malloc(s_ptr->size*sizeof(int));
    /* To pass in functions, isEmpty(s_ptr) will do the job. */


    struct stack *s = (struct stack*)malloc(sizeof(struct stack));
    // Memory allocation in heap for an instance of struct stack, this pointer s itself is stored in stack memory but it points to a memory location in heap which stores an instance of struct stack (we haven't given a name to that instance here)
    s->size = 50;
    // Any fixed size for array (maximum no. of elements the array can store in this stack), we may not completely fill upto this size
    s->top = -1;
    // top is array index (upto the point array is filled), top = -1 implies empty stack (i.e., no element in array)
    s->arr = (int*)malloc(s->size*sizeof(int));
    // Memory allocation in heap for array (pointer to this array is still stored in stack only)



/* STACK OPERATIONS */

    // // Checking if stack is EMPTY or not and FULL or not
    // if(isEmpty(s))
    //     printf("Stack is empty.\n");
    // else
    //     printf("Stack is not empty.\n");
    // if(isFull(s))
    //     printf("Stack is full.\n");
    // else
    //     printf("Stack is not full.\n");

    // s->arr[0] = 138;
    // s->top++;

    // if(isEmpty(s))
    //     printf("Stack is empty.\n");
    // else
    //     printf("Stack is not empty.\n");
    // if(isFull(s))
    //     printf("Stack is full.\n");
    // else
    //     printf("Stack is not full.\n");


    // // PUSH and POP Operation
    // push(s, 4);         // arr[0] = 4
    // pop(s);             // Array empty
    // pop(s);             // Stack Underflow
    for (int i = 0; i < s->size; i++)
        push(s, rand());        // arr[i] = some random number
    
    // // Array full by now
    
    // push(s, rand());            // Stack Overflow
    
    // for (int i = 0; i < s->size; i++)
    // {
    //     printf("%d\n", s->arr[i]);
    // // Will print any value we have pushed into the stack as well as garbage values for array indices we haven't yet pushed a value into.
    // }
    // for (int i = 0; i <= s->top; i++)
    // {
    //     printf("%d\n", s->arr[i]);
    // // Will print array values upto the index, we have filled.
    // }
    

    // // PEEK Operation
    for (int pos = 1; pos <= s->top+1; pos++)
    {
        peek(s, pos);
        // pos is the position of the element from the top of the stack, it starts from 1 and goes upto top+1.
        // This loop will execute only for valid positions, thus, "Invalid position of the element demanded." will not be printed for peek() executions within this loop.
    }


    // // STACK_TOP and STACK_BOTTOM Operations
    if(s->top != -1)
    {
        printf("Top Element of the stack(array) = %d.\n", s->arr[s->top]);
        printf("Bottom Element of the stack(array) = %d.\n", s->arr[0]);
    }
    else
        printf("Stack Empty, NO TOP/BOTTOM");


    return 0;
}