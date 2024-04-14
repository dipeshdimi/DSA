#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

struct stack_arr
{
    int top;
    int size;
    char*arr;
};

struct node
{
    char data;
    struct node*next;
};


bool single_arr(char exp[])
{
    struct stack_arr *sin_arr = (struct stack_arr*)malloc(sizeof(struct stack_arr));
    sin_arr->top = -1;
    sin_arr->size = strlen(exp);        // Because '(' characters in sin_arr will be from the entered expression only, which means the max number of times '(' can occur in the stack array will be the size of the expression itself (that too, only in the case of the entire expression consisting of '(' only).
    sin_arr->arr = (char*)malloc(sizeof(char)*sin_arr->size);

    for (int i = 0; i < sin_arr->size; i++)
    {
        if (exp[i] == '(')
        {
            // push function
            sin_arr->top++;
            sin_arr->arr[sin_arr->top] = '(';
        }
        else if(exp[i] == ')')
        {
            if(sin_arr->top == -1)      // isEmpty function
                return false;
            
            // pop function
            sin_arr->top--;
        }
    }
    if(sin_arr->top == -1)      // isEmpty function
        return true;
    else
        return false;
}


bool single_ll(char exp[])
{
    struct node*sin_ll_top = NULL;
    
    for (int i = 0; exp[i] != '\0'; i++)        // i < strlen(exp) 'll also do, but using this function will increase the time complexity (even if we store it in a variable so that we won't have to calculate it for every iteration), making the algo less efficient. In previous case, we either ways needed size to allocate memory for the array.
    {
        if(exp[i] == '(')
        {
            // push function
            struct node*push = (struct node*)malloc(sizeof(struct node));
            push->next = sin_ll_top;
            push->data = '(';
            sin_ll_top = push;
        }
        else if(exp[i] == ')')
        {
            if(sin_ll_top == NULL)
                return false;
            
            // pop function
            struct node*pop = sin_ll_top;
            sin_ll_top = sin_ll_top->next;
            free(pop);
        }
    }
    if(sin_ll_top == NULL)
        return true;
    else
        return false;
}


bool multi_arr(char exp[])
{
    struct stack_arr *mul_arr = (struct stack_arr*)malloc(sizeof(struct stack_arr));
    mul_arr->size = strlen(exp);
    mul_arr->top = -1;
    mul_arr->arr = (char*)malloc(sizeof(char)*mul_arr->size);
    for (int i = 0; i < mul_arr->size; i++)
    {
        if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
        {
            mul_arr->top++;
            mul_arr->arr[mul_arr->top] = exp[i];
        }
        else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']')
        {
            if (mul_arr->top == -1)
                return false;
            
            if ( !((exp[i]==')' && mul_arr->arr[mul_arr->top] == '(') || (exp[i]=='}' && mul_arr->arr[mul_arr->top] == '{') || (exp[i]==']' && mul_arr->arr[mul_arr->top] == '[')) )
                return false;
            
            // pop function
            mul_arr->top--;
        }
    }
    if(mul_arr->top == -1)
        return true;
    else
        return false;
}


bool multi_ll(char exp[])
{
    struct node*mul_ll_top = NULL;
    
    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (exp[i]=='(' || exp[i]=='{' || exp[i]=='[')
        {
            struct node*push = (struct node*)malloc(sizeof(struct node));
            push->next = mul_ll_top;
            push->data = exp[i];
            mul_ll_top = push;
        }
        else if(exp[i]==')' || exp[i]=='}' || exp[i]==']')
        {
            if(mul_ll_top == NULL)
                return false;
            
            if( !((exp[i]==')' && mul_ll_top->data == '(') || (exp[i]=='}' && mul_ll_top->data == '{') || (exp[i]==']' && mul_ll_top->data == '[')) )
                return false;
            
            // pop function
            struct node*pop = mul_ll_top;
            mul_ll_top = mul_ll_top->next;
            free(pop);
        }
    }
    if(mul_ll_top == NULL)
        return true;
    else
        return false;
}



/*
    Balanced Examples : [{()}]
                        [({})]
                        [{()()()[{}]}]
                        (){}[]
                        {[({[()]})]}
    
    Unbalanced Examples : [({)}]
                          ][
                          ()()(
                          }{}
                          ({)}
*/
int main()
{
    char exp[100];          // Maximum size of the expression entered decided beforehand

    printf("Enter the expression : ");
    // gets(exp);
    /*
        => gets() allows user to enter space-separated strings
        => The gets() function is risky to use since it doesn't perform any array bound checking and keep reading the characters until the new line (enter) is encountered. It suffers from buffer overflow, which can be avoided by using fgets(). The fgets() makes sure that not more than the maximum limit of characters are read.
    */
    fgets(exp, 100, stdin);
    /*
        => It reads a line from the specified stream and stores it into the string pointed to by exp and stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.

        => SYNTAX : char *fgets(char *str, int n, FILE *stream)

                str : Pointer to an array of chars where the string read is copied
                n : Maximum number of characters to be copied into str (including the terminating null-character)
                *stream : Pointer to a FILE object that identifies an input stream
                          [stdin (stdin is an input stream where data is sent to and read by a program) can be used as argument to read from the standard input]

                returns : the function returns str
        
        => FILES vs STREAMS
            -> Files are just sequences of bytes, while Streams are just facilitators(helpers).
            -> A stream is an interface(an easy "face" to work with something that has many subtleties irrelevant to us, just like we don't need to know how a TV remote works!) for triggering input/output flow of data, from/to anything that can be a source/destination to that input/output data, hiding the low-level implementation details of the numerous methodologies that OSs devise in order to interact with the variously designed hardware, on behalf of the programmers(i.e., We -as programmers- are not really interested in re-programming the way an operating system interacts with various hardware every time we create new software).
    */


/* SINGLE PARANTHESIS MATCHING */
    // Single Paranthesis Matching using Array
    if(single_arr(exp))
        printf("Given expression is balanced.\n");
    else
        printf("Given expression is unbalanced.\n");


    // Single Paranthesis Matching using Linked List
    if(single_ll(exp))
        printf("Given expression is balanced.\n");
    else
        printf("Given expression is unbalanced.\n");


    
/* MULTIPLE PARANTHESIS MATCHING */
    // Multiple Paranthesis Matching using Array
    if(multi_arr(exp))
        printf("Given expression is balanced.\n");
    else
        printf("Given expression is unbalanced.\n");


    // Multiple Paranthesis Matching using Linked List
    if(multi_ll(exp))
        printf("Given expression is balanced.\n");
    else
        printf("Given expression is unbalanced.\n");


    return 0;
}