#include<iostream>
#include<string>
#include<stack>

using namespace std;

int precedence(char op)
{
    if(op == '^')
        return 3;
    else if(op == '/' || op == '*')
        return 2;
    else if(op == '+' || op == '-')
        return 1;
    else
        return 0;   // i.e., op == '('
}

string inf_post(string infix)
{
    int len = infix.length();
    string postfix;     // empty string of size zero, postfix[i] = 'Z'; won't work
    stack<char> st;

    for (int i = 0; i < len; i++)
    {
        if( (infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z') || (infix[i] >= '0' && infix[i] <= '9') )
        {
            postfix += infix[i];
            // postfix.push_back(infix[i]);     // SAME
        }
        else if(infix[i] == '(')
        {
            st.push(infix[i]);
        }
        else if(infix[i] == ')')
        {
            while(st.top() != '(')
            {
                if(st.empty())
                {
                    cout<<"WARNING: Unbalanced Parenthesis !";
                    break;
                }
                postfix += st.top();
                st.pop();
            }
            if(st.top() == '(')
                st.pop();
        }
        else        // Operator
        {
            while (!st.empty() && precedence(infix[i]) <= precedence(st.top()))
            {
                // In case of other operators (+, -, *, /), associativity is left to right and we are traversing the string from left to right, thus, the precedence of infix[i] (right) will always be less than the precedence of st.top() (left) for equal precedence operators => pop().
                // In the case of '^' operator though, associativity is right to left, while we are still traversing from left to right, thus, the precedence of infix[i] (right) will always be more than the precedence of st.top() (left) for equal precedence operators => push().
                // NOTE: Associativity comes into play only when the precedence functions returns equal values.
                if(infix[i] == '^' && st.top() == '^')
                    break;
                postfix += st.top();
                st.pop();
            }
            st.push(infix[i]);
        }
    }
    while(!st.empty())
    {
        postfix += st.top();
        st.pop();
    }
    
    return postfix;
}


int main()
{
/*
      OPERATOR  |  ASSOCIATIVITY
    ------------|-----------------      _
       ^ (exp)  |  Right to Left       /|\
        *,/     |  Left to Right      / | \  Precedence
        +,-     |  Left to Right        |
         (      |  Left to Right        |
        
        NOTE: When '(' is encountered, we just push it into the stack without bothering about the precedence of st.top(). However, when an operator is encountered, the precedence of '(' is taken into account.

    Ex: 1) 5^1^3 = 5^(1^3) = 5             [Associativity -> Right to Left]
            {Postfix -> a^b^c = (a^(b^c)) = (a^(bc^)) = abc^^}
            {Postfix -> a^b^c = (a^(b^c)) = (a^(^bc)) = ^a^bc}

        2) 5*1/3 = (5*1)/3 = 1.6666...     [Associativity -> Left to Right]
            {Postfix -> a*b/c = ((a*b)/c) = ((ab*)/c) = ab*c/}
            {Prefix -> a*b/c = ((a*b)/c) = ((*ab)/c) = /*abc}
*/

/*
    => WHY POSTFIX/PREFIX EXPRESSION?
        -> The compiler scans the expression either from left to right or from right to left.
        -> Consider the below expression:   a op1 b op2 c op3 d
           If op1 = +, op2 = * and op3 = +, the compiler first scans the expression to evaluate the expression b * c, then again scan the expression to add a to it. The result is then added to d after another scan.
        -> The repeated scanning makes it very in-efficient. It is better to convert the expression to postfix(or prefix) form before evaluation. The corresponding expression in postfix form is: abc*+d+. The postfix expressions can be evaluated easily using a stack.
*/

/*
    => INFIX TO POSTFIX CONVERSION Algorithm
        1) Create an empty stack, st.
        2) Scan the infix expression from left to right, repeating step 3 for each character.
        3) If the scanned character, x is :-
            i) Operand: Output it.
            ii) Left Parenthesis, '(' : Push x into the stack st.
            iii) Right Parenthesis, ')' : Keep popping and outputting the elements from the stack st until a left parenthesis is popped (don't output '(', just pop it out of the stack).
            iv) Operator : If st is empty, push x into the stack, else :-
                a) If x has higher precedence than st.top(), push x into st.
                b) If x has lower precedence than st.top(), pop st.top() and repeat step iv) with the new st.top() [i.e., keep popping st.top() until a higher/equal precedence character is found].
                c) If x and st.top() have equal precedence, use associativity.
        4) Pop and output all the remaining stack elements.
    
    => INFIX TO POSTFIX CONVERSION Examples
        1) Input: a+b*c
                x   |    st     |  Postfix
            --------|-----------|-----------
                    |           |
                a   |  |     |  |    a
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                +   |  |  +  |  |    a
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                b   |  |  +  |  |    ab
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                *   |  |  *  |  |    ab
                    |  |-----|  |
                    |  |  +  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                c   |  |  *  |  |    abc
                    |  |-----|  |
                    |  |  +  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
            Pop out |           |
           remaining|  |     |  |    abc*+
             stack  |  |_____|  |
            elements|           |

        2) Input: (a+b)*c
                x   |    st     |  Postfix
            --------|-----------|-----------
                    |           |
                (   |  |  (  |  |    
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                a   |  |  (  |  |    a
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                +   |  |  +  |  |    a
                    |  |-----|  |
                    |  |  (  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                b   |  |  +  |  |    ab
                    |  |-----|  |
                    |  |  (  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                )   |  |     |  |    ab+
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                *   |  |  *  |  |    ab+
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                c   |  |  *  |  |    ab+c
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
            Pop out |           |
           remaining|  |     |  |    ab+c*
             stack  |  |_____|  |
            elements|           |

        3) Input: a*b/c
                x   |    st     |  Postfix
            --------|-----------|-----------
                    |           |
                a   |  |     |  |    a
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                *   |  |  *  |  |    a
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                b   |  |  *  |  |    ab
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                /   |  |  /  |  |    ab*        => Associativity is left to right for *,/
                    |  |_____|  |               => * is on the left side in the given expression
                    |           |               => * has higher precedence here
            --------|-----------|-----------
                    |           |
                c   |  |  /  |  |    ab*c
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
            Pop out |           |
           remaining|  |     |  |    ab*c/
             stack  |  |_____|  |
            elements|           |

        4) Input: a+b/c-d*e
                x   |    st     |  Postfix
            --------|-----------|-----------
                    |           |
                a   |  |     |  |    a
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                +   |  |  +  |  |    a
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                b   |  |  +  |  |    ab
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                /   |  |  /  |  |    ab
                    |  |-----|  |
                    |  |  +  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                c   |  |  /  |  |    abc
                    |  |-----|  |
                    |  |  +  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                -   |  |  -  |  |    abc/+
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                d   |  |  -  |  |    abc/+d
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                *   |  |  *  |  |    abc/+d
                    |  |-----|  |
                    |  |  -  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                e   |  |  *  |  |    abc/+de
                    |  |-----|  |
                    |  |  -  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
            Pop out |           |
           remaining|  |     |  |    abc/+de*-
             stack  |  |_____|  |
            elements|           |
*/

/*
    => TIME COMPLEXITY
        ->  # 1 Operands: O(1)                      [Simply output the operand]
            # All Operands: O(n)                    [All the operands in the expression => Linear function of n, n is the upper cap as the no. of operands have to be less than n]

        ->  # 1 Left Parenthesis: O(1)              [Push is O(1) operation]
            # All Left Parenthesis: O(n)            [All the operands in the expression => Linear function of n, n is the upper cap as the no. of left parenthesis have to be less than n]

        ->  # 1 Right Parenthesis: O(n)             [Considering the no. of operators popped (i.e., no. of operators between the current pair of left-right parenthesis) to be a linear function of n, n is the upper cap as the no. of operators popped have to be less than n]
            # All Right Parenthesis: O(n)           [Considering the total no. of operators popped (i.e., the total no. of operators in the expression) to be a linear function of n, n is the upper cap as the total no. of operators in the expression have to be less than n]

        ->  # 1 Operator: O(1)                      [Push/Pop]
            # All Operators: O(n)                   [No. of operators < n]
        
        ----> For every character, we either push and pop it (two O(1) operations) or we output it (O(1) operation) or neither [')' is neither pushed/popped nor outputted, just used as an indicator to pop out other characters]. Since there are n characters, with each character being operated on with O(1) time, the time complexity of infix to postfix conversion is O(n).
    
    => SPACE COMPLEXITY : O(n)
                        ______________________________________________________________________________________
                        | # Stack length -> No. of operators/left parenthesis -> Linear function of n -> O(n) |
                        | # Output (Postfix Expression) -> n length -> O(n)                                   |
                        |_____________________________________________________________________________________|
*/

    string infix;
    cin>>infix;
    cout<<inf_post(infix);

    return 0;
}