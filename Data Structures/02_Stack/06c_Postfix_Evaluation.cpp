#include<iostream>
#include<string>
#include<stack>
#include<typeinfo>
#include<math.h>

using namespace std;

int postEval(string infix)
{
    int op1, op2, len = infix.length();
    stack <int> st;

    for(int i=0; i<len; i++)
    {
        if( !( infix[i]=='+' || infix[i]=='-' || infix[i]=='*' || infix[i]=='/' || infix[i]=='^' ) )
        {
            // No parenthesis in prefix/postfix expression => Not Operator ~ Operand
            st.push(infix[i]-'0');      // Since infix[i] is a character ('0' to '9'), the ASCII values of infix[i] and '0' (=48) need to be subtracted, to turn it into its corresponding integer for evaluation purpose.

            // NOTE: Typecasting a char just gives its ASCII value :-
            cout<<infix[i]<<"("<<typeid(infix[i]).name()<<")"<<"  ";
            cout<<int(infix[i])<<"("<<typeid(int(infix[i])).name()<<")"<<"  \n";
        }
        else
        {
            op2 = st.top();
            st.pop();
            op1 = st.top();
            st.pop();

            switch(infix[i])
            {
                case '+':
                    st.push(op1 + op2);
                    break;
                case '-':
                    st.push(op1 - op2);
                    break;
                case '*':
                    st.push(op1 * op2);
                    break;
                case '/':
                    st.push(op1 / op2);
                    break;
                case '^':
                    st.push(pow(op1, op2));
                    break;
            }
        }
    }
    cout<<"RESULT = ";
    return st.top();
}

int main()
{
    string infix;
    cin>>infix;
/*
    1) Create a stack to store operands (or values).
    2) Scan the given expression left to right and do following for every scanned element.
        a) If the element is a number(operand), push it into the stack.
        2) If the element is an operator, pop the last two operands for the operator from the stack, evaluate the operator and push the result back to the stack.
    3) When the expression is ended, the number in the stack is the final answer.
*/
    cout<<postEval(infix);
    
    return 0;
}