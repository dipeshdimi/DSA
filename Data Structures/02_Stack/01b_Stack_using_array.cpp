#include<iostream>
#include<vector>

using namespace std;

struct stack_arr
{
    // Need to be declared here instead of inside the constructor so that these can be used in other functions defined inside of this structure as well
    int top;
    int Max_Size;
    int *arr;

    stack_arr(int inputSize)
    {
        Max_Size = inputSize;
        top = -1;
        arr = new int[Max_Size];
    }

    bool isEmpty()
    {
        if(top == -1)
            return true;
        else
            return false;
    }

    bool isFull()
    {
        if(top == Max_Size-1)
            return true;
        else
            return false;
    }

    void push(int value)
    {
        if(isFull())
        {
            cout<<"STACK OVERFLOW !!!";
            return;
        }
        top++;
        arr[top] = value;
    }

    void pop()
    {
        if(isEmpty())
        {
            cout<<"STACK UNDERFLOW !!!";
            return;
        }
        top--;
    }

    void peekTop()
    {
        if(isEmpty())
            cout<<"Stack is Emmpty.";
        else
            cout<<"Peek Top: "<<arr[top]<<"\n";
    }

    int Occupied_Size()
    {
        return top+1;
    }

    void display()
    {
        for (int i = top; i >= 0; i--)
            cout<<arr[i]<<"\t";
    }
};


struct stack_vector
{
    vector<int> v;

    void push(int value)
    {
        v.push_back(value);
    }

    int pop()
    {
        int res = v.back();
        v.pop_back();
        return res;
    }

    int size()
    {
        return v.size();
    }

    bool isEmpty()
    {
        return v.empty();
    }

    int peek()
    {
        return v.back();
    }

    void display()
    {
        for (int i = size()-1; i >= 0; i--)
            cout<<v[i]<<"\t";
    }
};

int main()
{
    // STACK : Linear data structure that follows either FILO or LIFO order in which the order is performed.

    stack_arr s(100);    // Constructor, structure instance stored in statically allocated stack memory, we don't need the dot operator (.) or arrow operator (->) to access top, size or *arr as in any of the functions as they are all defined inside the structure itself.
        /* Other ways to use the struct stack_arr datatype (Using struct in the following declarations is optional everywhere here) :-
            (1)(2) stack_arr s; (1)
                    [C, directly use structure instance (stored in statically allocated stack memory) with the help of dot(.) operator]
            stack_arr *s_ptr = &s; (2)
                    [C, use pointer to refer to the structure instance (stored in statically allocated stack memory) with the help of arrow(->) operator]
            (3) stack_arr s(100);
                stack_arr *s_ptr = &s;
                    [Constructor, use pointer to refer to the structure instance (stored in statically allocated stack memory) with the help of arrow(->) operator]
            (4) stack_arr *s = new stack_arr; (4)
                    [C, use pointer to refer to the memory allocated in the heap (equal to the size of the structure 'stack_arr') with the help of arrow(->) operator]
            (5) stack_arr *s = new stack_arr(100); (5)
                    [Constructor, use pointer to refer to the memory allocated in the heap (equal to the size of the structure 'stack_arr') with the help of arrow(->) operator]
        */

    // We access the functions defined inside the structure the same way we would access any other structure member. If we create a pointer pointing to s, we can also use arrow operator (->).
    cout<<"Empty?   -   "<<s.isEmpty()<<"\n";
    cout<<"Full?    -   "<<s.isFull()<<"\n";

    s.push(-30);
    s.push(-20);
    s.push(-10);
    s.push(0);
    s.push(10);
    s.push(20);
    s.push(30);

    s.pop();
    s.pop();

    s.peekTop();

    s.Occupied_Size();

    s.display();



    // Since we are using arrays here, we need to provide Max_Size beforehand and thus, there is no dynamic resizing. To attain dynamic we can either implement the stack data structure using linked list or using vector :-
    stack_vector s2;
    
    s2.push(-35);
    s2.push(-25);
    s2.push(20);
    s2.push(5);
    s2.push(-2);
    s2.push(-40);

    cout<<"\n\nPopped Element = "<<s2.pop()<<"\n";
    cout<<"Popped Element = "<<s2.pop()<<"\n";

    cout<<"Top Element = "<<s2.peek()<<"\n";

    cout<<"Empty?   -   "<<s2.isEmpty()<<"\n";

    cout<<"Occupied Size = "<<s2.size()<<"\n";

    s2.display();



    /*
    =>  AMORTIZED Time Complexity for Vector Implementation : O(1)   [For push/pop]
        WORST CASE Time Complexity for Vector Implementation : O(1)  [For other operations]
            {Amortized Analysis is used for algorithms where an occasional operation is very slow, but most of the other operations are faster}

    =>  WORST CASE Time Complexity for Array Implementation : O(1)   [For all operations]
    */
    
    return 0;
}