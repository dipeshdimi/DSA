#include<iostream>
#include<queue>

using namespace std;

int main()
{
    // NOTE: In STL, front refers to the first element, not the index before the first element.
    queue <int> q;

    q.push(-20);
    q.push(-10);
    q.push(0);
    q.push(10);
    q.push(20);

    cout<<"Queue Size = "<<q.size()<<"\n";

    while(!q.empty())
    {
        cout<<"Front = "<<q.front()<<"\t&\tBack = "<<q.back()<<"\n";
        q.pop();
    }

    return 0;

    /*
                                        push()    -----
                                        pop()         |
        => TIME COMPLEXITIES    ->      front()       |--- O(1)
                                        back()        |
                                        size()        |
                                        empty()   -----

        => INTERNAL WORKING
            -> Stack can be implemented on any underlying containers that provide the following operations :-
                1) empty()
                2) size()
                3) front()
                4) back()
                5) push_back()
                6) pop_front()
            
            -> List and Dequeue, these two containers provide all of the above mentioned operations in O(1) time (which is why all the queue operations also have O(1) time complexity).

            -> By default, dequeue is used to implement queue.

            -> Since queue is implemented using other containers and works as an interface, it is also called container adaptor.

            -> Data structures like stack and priority queue are also container adaptors.
    */

}