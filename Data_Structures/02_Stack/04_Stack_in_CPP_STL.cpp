#include<iostream>
#include<stack>

using namespace std;

int main()
{
    stack<int> s;

    s.push(-29);
    s.push(34);
    s.push(0);
    s.push(-2);
    s.push(99);

    cout<<"Top = "<<s.top()<<"\n";

    cout<<"Size = "<<s.size()<<"\n";

    s.pop();
    s.pop();

    while(!s.empty())
    {
        cout<<s.top()<<"->";
        s.pop();
    }

    /*
                                        push()    -----
                                        pop()         |
        => TIME COMPLEXITIES    ->      top()         |--- O(1)
                                        size()        |
                                        empty()   -----

        => INTERNAL WORKING
            -> Stack can be implemented on any underlying containers that provide the following operations :-
                1) back()       [To access the last element]
                2) size()
                3) empty()
                4) push_back()
                5) pop_back()
            
            -> List, vector and dequeue, these three containers provide all of the above mentioned operations in O(1) time (which is why all the stack operations also have O(1) time complexity).

            -> By default, dequeue is used to implement stack.

            -> Since stack is implemented using other containers and works as an interface, it is also called container adaptor.

            -> Data structures like queue and priority queue are also container adaptors.
    */

    return 0;
}