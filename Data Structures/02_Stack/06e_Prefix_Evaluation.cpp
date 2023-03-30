#include<iostream>
#include<string>
#include<stack>

using namespace std;

int preEval(string infix)
{
    stack <int> st;
    int op1, op2, len = infix.length();

    for (int i = len-1; i>=0; i--)
    {
        // No parenthesis in prefix/postfix expression => Not Operator ~ Operand
        if( !( infix[i]=='+' || infix[i]=='-' || infix[i]=='*' || infix[i]=='/' || infix[i]=='^' ) )
            st.push(infix[i] - '0');
        else
        {
            op1 = st.top();
            st.pop();
            op2 = st.top();
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
                    st.push(op1 ^ op2);
                    break;
            }
        }
    }
    return st.top();
}

int main()
{
    string infix;
    cin>>infix;
    cout<<"RESULT = "<<preEval(infix);
    return 0;
}