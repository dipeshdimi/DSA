#include<iostream>
#include<string>
#include<stack>
#include<algorithm>

using namespace std;

int prec(char op)
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

string inf_pre(string infix)
{
	int len = infix.length();
	string prefix;
	stack <char> st;

    for (int i = len-1; i>=0; i--)
	{
		if( (infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z') || (infix[i] >= '0' && infix[i] <= '9') )
		{
			prefix += infix[i];
		}
		else if(infix[i] == ')')
		{
			st.push(infix[i]);
		}
		else if(infix[i] == '(')
		{
			while (st.top() != ')')
			{
				if(st.empty())
				{
					cout<<"WARNING: Unbalanced Parenthesis !";
					break;
				}
				prefix += st.top();
				st.pop();
			}
			if(st.top() == '(')
                st.pop();
		}
		else		// OPERATORS
		{
			while ( !(st.empty()) && prec(infix[i]) <= prec(st.top()))
			{
				if( ((infix[i]=='+' || infix[i]=='-') && (st.top()=='+' || st.top()=='-')) || ((infix[i]=='*' || infix[i]=='/') && (st.top()=='*' || st.top()=='/')) )
                {cout<<"ncsdujzndcundf\n\n";
					break;}
				
				prefix += st.top();
				st.pop();
			}
			st.push(infix[i]);
		}
	}

	while (!st.empty())
	{
		prefix += st.top();
		st.pop();
	}
	
	reverse(prefix.begin(), prefix.end());		// #include<algorithm>
	return prefix;
}

int main()
{

/*
    => INFIX TO PREFIX CONVERSION Algorithm
        1) Create an empty stack, st.
        2) Scan the infix expression from RIGHT TO LEFT, repeating step 3 for each character.
        3) If the scanned character, x is :-
            i) Operand: Output it.
            ii) RIGHT Parenthesis, ')' : Push x into the stack st.
            iii) LEFT Parenthesis, '(' : Keep popping and outputting the elements from the stack st until a RIGHT parenthesis is popped (don't output ')', just pop it out of the stack).
            iv) Operator : If st is empty, push x into the stack, else :-
                a) If x has higher precedence than st.top(), push x into st.
                b) If x has lower precedence than st.top(), pop st.top() and repeat step iv) with the new st.top() [i.e., keep popping st.top() until a higher/equal precedence character is found].
                c) If x and st.top() have equal precedence, use associativity.
        4) Pop and output all the remaining stack elements.
        5) REVERSE THE OUTPUT STRING.
    
    => INFIX TO POSTFIX CONVERSION Examples
        1) Input: a+b*c
                x   |    st     |  Prefix
            --------|-----------|-----------
                    |           |
                c   |  |     |  |    c
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                *   |  |  *  |  |    c
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                b   |  |  *  |  |    cb
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                +   |  |  +  |  |    cb*
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                a   |  |  +  |  |    cb*a
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
            Pop out |           |
           remaining|  |     |  |    cb*a+
             stack  |  |_____|  |
            elements|           |
            --------|-----------|-----------
                    |           |
             REVERSE|  |     |  |    +a*bc
                    |  |_____|  |
                    |           |

        2) Input: (a+b)*c
                x   |    st     |  Prefix
            --------|-----------|-----------
                    |           |
                c   |  |     |  |    c
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                *   |  |  *  |  |    c
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                )   |  |  )  |  |    c
                    |  |-----|  |
                    |  |  *  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                b   |  |  )  |  |    cb
                    |  |-----|  |
                    |  |  *  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                +   |  |  +  |  |    cb
                    |  |-----|  |
                    |  |  )  |  |
                    |  |-----|  |
                    |  |  *  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                a   |  |  +  |  |    cba
                    |  |-----|  |
                    |  |  )  |  |
                    |  |-----|  |
                    |  |  *  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                (   |  |  *  |  |    cba+
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
            Pop out |           |
           remaining|  |     |  |    cba+*
             stack  |  |_____|  |
            elements|           |
            --------|-----------|-----------
                    |           |
             REVERSE|  |     |  |    *+abc
                    |  |_____|  |
                    |           |

        3) Input: a^b^c (OR a^¹b^²c)
                x   |    st     |  Prefix
            --------|-----------|-----------
                    |           |
                c   |  |     |  |    c
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
               ^²   |  |  ^² |  |    c
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                b   |  |  ^² |  |    cb
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
               ^¹   |  |  ^¹ |  |    cb^²       => Associativity is right to left for ^
                    |  |_____|  |               => ^² is on the right side in the given expression
                    |           |               => ^² has higher precedence here
            --------|-----------|-----------
                    |           |
                a   |  |  ^¹ |  |    cb^²a
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
            Pop out |           |
           remaining|  |     |  |    cb^²a^¹
             stack  |  |_____|  |
            elements|           |
            --------|-----------|-----------
                    |           |
             REVERSE|  |     |  |    ^¹a^²bc OR ^a^bc
                    |  |_____|  |
                    |           |

        4) Input: a+b/c-d*e
                x   |    st     |  Prefix
            --------|-----------|-----------
                    |           |
                e   |  |     |  |    e
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                *   |  |  *  |  |    e
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                d   |  |  *  |  |    ed
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                -   |  |  -  |  |    ed*
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                c   |  |  -  |  |    ed*c
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                /   |  |  /  |  |    ed*c
                    |  |-----|  |
                    |  |  -  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                b   |  |  /  |  |    ed*cb
                    |  |-----|  |
                    |  |  -  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                +   |  |  +  |  |    ed*cb/
                    |  |-----|  |
                    |  |  -  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
                    |           |
                a   |  |  +  |  |    ed*cb/a
                    |  |-----|  |
                    |  |  -  |  |
                    |  |_____|  |
                    |           |
            --------|-----------|-----------
            Pop out |           |
           remaining|  |     |  |    ed*cb/a+-
             stack  |  |_____|  |
            elements|           |
            --------|-----------|-----------
                    |           |
             REVERSE|  |     |  |    +-a/bc*de
                    |  |_____|  |
                    |           |
*/

/*
    => TIME COMPLEXITY
        # For every character, we either push and pop it (two O(1) operations) or we output it (O(1) operation) or neither [')' is neither pushed/popped nor outputted, just used as an indicator to pop out other characters].
        # Since there are n characters, with each character being operated on with O(1) time, the time complexity for obtaining the reverse of the required prefix expression is O(n).
        # Then, to arrive at the final result, we will need to reverse the obtained string which will take O(n) time.
        # Thus, Overall Time Complexity -> O(n).
    
    => SPACE COMPLEXITY : O(n)
                        ______________________________________________________________________________________
                        | # Stack length -> No. of operators/left parenthesis -> Linear function of n -> O(n) |
                        | # Output (Prefix Expression) -> n length -> O(n)                                   |
                        |_____________________________________________________________________________________|
*/
    string infix;
    cin>>infix;
    cout<<inf_pre(infix);

    return 0;
}