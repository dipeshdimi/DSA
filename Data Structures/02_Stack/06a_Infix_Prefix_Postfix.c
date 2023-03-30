#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack_arr
{
    int top;
    int size;
    char *arr;
};

struct stack_ll
{
    char data;
    struct stack_ll*next;
};

int precedence(char ch)
{
    if(ch == '*' || ch == '/')
        return 2;
    else if(ch == '+' || ch == '-')
        return 1;
}

char* arr(char infix[])
{
    struct stack_arr *s = (struct stack_arr*)malloc(sizeof(struct stack_arr));
    s->size = strlen(infix);    // Since this is the maximum number of operators that can be pushed into the stack (in case the entire expression consists of operators only and these operators are arranged in their increasing order of precedence in the input expression)
    s->top = -1;
    s->arr = (char*)malloc(s->size*sizeof(char));
    char*postfix = (char*)malloc((s->size+1)*sizeof(char));      // +1 for '\0'
    int i=0, j =0;      // i to traverse infix[], j to traverse postfix[]

    while(infix[i] != '\0')
    {
        // The moment you encounter an operand, concatenate it to the postfix expression string and move forward (i++, j++)
        if(!(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/'))
        {
            postfix[j] = infix[i];
            i++;
            j++;
        }
        else    // The moment you encounter an operator...
        {
            // Empty Stack => Just push the operator (nothing to compare precedence to)
            if(s->top == -1 || precedence(infix[i]) > precedence(s->arr[s->top]))
            {
                // push the current operator (infix[i]) into the stack if its precedence is greater than the precedence of the topmost element (operator) in stack
                s->top++;
                s->arr[s->top] = infix[i];
                i++;
            }
            else
            {
                // Keep popping the elements (operators) from the stack until the precedence of the topmost stack element is less than the current operator's (infix[i]'s) precedence (this else statement will keep on implementing until then as there is no updation in i here)
                postfix[j] = s->arr[s->top];
                s->top--;
                j++;
            }
        }
    }

    // If you reach the end of input expression, pop every element from the stack, and concatenate them as well
    while(s->top != -1)
    {
        postfix[j] = s->arr[s->top];
        s->top--;
        j++;
    }
    postfix[j] = '\0';  // Terminate the postfix[] character array

    return postfix;
}


char* ll(char infix[])
{
    struct stack_ll*top = NULL;
    char*postfix = (char*)malloc(sizeof(char)*(strlen(infix)+1));
    int i=0, j=0;
    while (infix[i] != '\0')
    {
        if((infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/'))
        {
            // Empty Stack => Just push the operator (nothing to compare precedence to)
            if(top == NULL || precedence(infix[i]) > precedence(top->data))
            {
                // push
                struct stack_ll*push = (struct stack_ll*)malloc(sizeof(struct stack_ll));
                push->next = top;
                push->data = infix[i];
                top = push;
                i++;
            }
            else
            {
                // pop
                struct stack_ll *pop = top;
                top = top->next;
                postfix[j] = pop->data;
                j++;
                free(pop);
                pop = NULL;
            }
        }
        else
        {
            postfix[j] = infix[i];
            j++;
            i++;
        }
    }
    
    while(top != NULL)
    {
        postfix[j] = top->data;
        j++;
        top = top->next;
    }
    postfix[j] = '\0';

    return postfix;
}



int main()
{
/*
    =>  INFIX : <operand> <operator> <operand>
        Ex : a+b

    =>  PREFIX : <operator> <operand> <operand>
        Ex : +ab

    =>  POSTFIX : <operand> <operand> <operator>
        Ex : ab+


    =>  WHY POSTFIX/PREFIX
        -> When we evaluate a mathematical expression, we have a rule in mind, named BODMAS***, where we have operators’ precedence in this order; brackets, of, division, multiplication, addition, subtraction. But what would you do when you get to evaluate a 1000 character long-expression, or even longer one? You will try to automate the process. But there is one issue. Computers don’t follow BODMAS; rather, they have their own operator precedence. And this is where we need these postfix and prefix notations.
        -> In programming, we use postfix notations more often, likewise, following the precedence order of machines.
        -> To evaluate postfix expressions, the computer just needs to loop through the expression once and as soon as it finds an operator, it needs to perform the operation on the last two operands encountered thus generating the output operand. 
        -> Ex: I = a*(b+c)*d
                Since computers go left to right while evaluating an expression, we’ll convert this infix expression to its postfix form :-
               P = abc+*d*
                # STEP 1 - First operator found, '+', last two operands b and c, thus, computer adds b and c, we get (b+c) as the output operand here.
                # STEP 2 - Next operator '*', last two operands, a and (b+c), thus, computer multiplies a and (b+c), we get a*(b+c) as the output operand here.
                # STEP 3 - Next operator '*', last two operands, a*(b+c) and d, thus, computer multiplies a*(b+c) and d, we get a*(b+c)*d as the output operand here.

    *** 1) O in BODMAS stands for ‘Of’. It is replaced by the multiplication symbol. It is nothing but ‘prioritized multiplication’. Normally, multiplication comes after division in BODMAS but if it is Of, then it will come before division.
            Ex: 24 ÷ 4(8÷4) = 3     [24 ÷ 4×(8÷4) = 12]

        2) O in BODMAS stands for 'Order', i.e., exponential powers should be calculated before divison and the rest the operations that follow it.
            Ex: 3 x (2 + 4) + 5^2   [Brackets first (2 + 4 = 6), then the Orders (52 = 25), then any Division or Multiplication (3 x 6 (the answer to the brackets) = 18), and finally any Addition or Subtraction (18 + 25 = 43)]


    => INFIX TO PREFIX/POSTFIX CONVERSION
        -> I = x-y*z to Prefix
            # STEP 1: Parenthesize the infix expression following the operator precedence and associativity before converting it into a prefix expression.  [(x-(y*z))]
            # STEP 2: Reach out to the innermost parentheses and convert them into prefix form.    [(x-(*yz))]
            # STEP 3: Similarly, keep converting one by one, from the innermost to the outer parentheses.  [-x*yz]
        
        -> I = x-y*z to Postfix
            # STEP 1: Parenthesize the infix expression following the operator precedence and associativity before converting it into a postfix expression.  [(x-(y*z))]
            # STEP 2: Reach out to the innermost parentheses and convert them into postfix form.    [(x-(yz*))]
            # STEP 3: Similarly, keep converting one by one, from the innermost to the outer parentheses.  [xyz*-]

        -> EXAMPLES
            1)  I = p-q-r/a
                Parenthesizing : ((p-q)-(r/a))
                Prefix : ((p-q)-[/ra])      Postfix : ((p-q)-[ra/])
                Prefix : ([-pq]-[/ra])      Postfix : ([pq-]-[ra/])
                Prefix : --pq/ra            Postfix : pq-ra/-

            2)  I = (m-n)*(p+q)
                Parenthesizing : ((m-n)*(p+q))  [We can't change this into ((m-(n*p))+q) to suite the operator precedence order and associativity since it's already partly paranthesized]
                Prefix : ([-mn]*[+pq])      Postfix : ([mn-]*[pq+])
                Prefix : *-mn+pq            Postfix : mn-pq+*

    Clip 1 : https://www.youtube.com/watch?v=422Q_yx2yA8&list=PLu0W_9lII9ahIappRPN0MCAgtOu3lQjQi&index=35
*/
    char infix[100];
    printf("Enter the Infix Expression (without parentheses) : ");
    gets(infix);

    printf("%s\n", arr(infix));
    printf("%s\n", ll(infix));

    return 0;
}