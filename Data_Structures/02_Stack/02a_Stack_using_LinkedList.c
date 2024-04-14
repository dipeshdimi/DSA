#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node
{
    int data;
    struct node*next;
};

bool isEmpty(struct node*top)
{
    if(top == NULL)
        return true;
    else
        return false;
}

bool isFull()
{
    struct node*ptr = (struct node*)malloc(sizeof(struct node));
    struct node*temp = ptr;
    free(ptr);
    if(temp == NULL)         // malloc unable to allocate any memory in heap as heap memory is already exhausted
        return true;
    else
        return false;

    // We have created the pointer temp so as to ensure the memory doesn't get wasted if the heap memory ain't full.
}

struct node* push(struct node*top, int data)
{
    struct node*ptr = (struct node*)malloc(sizeof(struct node));
    if(isFull())// You can also set a custom size of the stack and check for full accordingly
    {
        printf("No further element can be pushed into the stack as the heap memory is already full (Stack/Heap Overflow).\n");
        return top;
    }
    ptr->next = top;
    ptr->data = data;
    top = ptr;
    return top;
}

struct node* pop(struct node*top)
{
    if(isEmpty(top))
    {
        printf("No element can be popped as the stack is already empty (Stack Underflow).\n");
        return top;
    }
    struct node*ptr = top;
    top = top->next;
    printf("Popped Element : %d\n", ptr->data);
    free(ptr);
    return top;
}

void peek(struct node*top, int position)
{
    int temp_pos = position;
    while (--temp_pos)
    {
        top = top->next;
        if(top == NULL)
        {
            printf("Invalid position of the element demanded.\n");
            return;
        }
    }
    printf("Element at position %d from the top = %d\n", position, top->data);
}

void display(struct node*top)           // Display/Traversal, same thing
{
    if(top == NULL)
    {
        printf("No element present in the stack.\n");
        return;
    }

    while(top != NULL)
    {
        printf("%d -> ", top->data);
        top = top->next;
    }
}

int stackTop(struct node*top)
{
    return top->data;
}

int stackBottom(struct node*top)
{
    while(top->next != NULL)
        top = top->next;

    return top->data;
}





int main()
{
    struct node*top = NULL;
    // Here, top is the head of the linked list. We have decided to make top linked list's head instead of its tail as insertion (push) and deletion (pop) operations have O(1) time complexity from the beginning of the linked list.

    top = push(top, 30);
    top = push(top, 20);
    top = push(top, 10);
    top = push(top, 0);
    top = push(top, -10);
    top = push(top, -20);
    top = push(top, -30);

    display(top);

    top = pop(top);
    
    display(top);

    peek(top, 4);

    printf("Stack Bottom Element = %d\n", stackBottom(top));
    printf("Stack Top Element = %d\n", stackTop(top));

    top = pop(top);
    display(top);
    top = pop(top);
    display(top);
    top = pop(top);
    display(top);
    top = pop(top);
    display(top);
    top = pop(top);
    display(top);
    top = pop(top);
    display(top);
    top = pop(top);
    display(top);


    /* ALTERNATE METHODS :-
    1) Make top global. In this case, you will have to give some other name (other than top) to the formal argument though.
    2) Pass the address of top pointer, i.e., &top (address of address of topmost element of stack) in the function instead of the top pointer itself. This will allow permanent change to top pointer. In this case, formal argument should be of the form, **top and we will have to dereference it (as *top) for obtaining the address of top.
    These approaches are useful when you want to return something else from the function other than the top pointer, e.g., popped value in case of pop() function.

    DETAILED PROGRAM : https://www.codewithharry.com/videos/data-structures-and-algorithms-in-hindi-30
    */

    return 0;
}