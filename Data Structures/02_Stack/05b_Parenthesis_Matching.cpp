#include<iostream>
#include<stack>
#include<string.h>   // Needed for strlen() function (only)

using namespace std;

bool balanced_parenthesis(string exp)
{
    stack<char> s;
    // STRING LENGTH
        // int exp_length = exp.length();
        // int exp_length = exp.size();
        // int exp_length = strlen(exp.c_str());   // The constructor of string [s_str()] will set it to the C-style string, which ends at the '\0'
        // while(exp){...}      {iterating while string is NOT NULL}

    for(int i=0; exp[i] != '\0'; i++)   // NULL terminated cpp? : https://stackoverflow.com/a/40717279
    {
        if (exp[i] == '[' || exp[i] == '{' || exp[i] == '(')
            s.push(exp[i]);
        
        if(exp[i] == ']' || exp[i] == '}' || exp[i] == ')')
        {
            if(s.empty())
                return false;

            if( !((s.top()=='(' && exp[i]==')') || (s.top()=='{' && exp[i]=='}') || (s.top()=='[' && exp[i]==']')))
                return false;
            
            s.pop();
        }
    }
    if(s.empty())
        return true;
    
    return false;
}

int main()
{
    string exp;
    cin>>exp;

    if(balanced_parenthesis(exp))
        cout<<"Balanced";
    else
        cout<<"Unbalanced";
    
    // NOTE: Since in this algorithm, we keep checking and removing the last added element and stack follows LIFO/FILO order, stack is the ideal data structure here. Any other data structure will complicate the procedure.
    return 0;
}