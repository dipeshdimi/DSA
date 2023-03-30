#include<iostream>
#include<list>

using namespace std;

template <typename T>
void traversal(const list <T> &l)
{
    // for (const T &x:l)
    //     cout<<x<<" <-> ";
    // cout<<"\n\n";

    // *** this is still valid as we are going one element at a time instead of randomly jumping from element to element (l.begin()+i), which is also why something like l.begin()++ will still work in both of the scenarios referenced here :-
     for(auto it=l.begin(); it!=l.end(); it++)
        cout<<(*it)<<" -> ";
    cout<<"\n\n";
}


using namespace std;

int main()
{
/*
     Function    |  Description	                                     |   Time Complexity
    -------------|---------------------------------------------------|-------------------
    front()	     |   Returns element at front                        |   O(1)
    back()	     |   Returns element at end                          |   O(1)
    size()	     |   Returns size of the List                    	 |   O(1)
    begin()	     |   Returns iterator pointing to first element  	 |   O(1)
    end()	     |   Returns iterator pointing to last element   	 |   O(1)
    erase(itr)	 |   Erases element pointed by itr               	 |   O(1)
    push_front() |   Inserts element at front                    	 |   O(1)
    push_back()	 |   Inserts element at back                     	 |   O(1)
    pop_front()	 |   Removes element from front                  	 |   O(1)
    pop_back()	 |   Removes element from end                    	 |   O(1)
    remove()	 |   Removes all occurrences of a particular element |   O(N)
    reverse()	 |   Reverses the list                           	 |   O(N)
    unique()	 |   Removes the consecutively repeated element      |   O(N)
    sort()	     |   Sorts the linked list                           |   O(N*logN)
*/
// DECLARATION & INITIALIZATION
    /*1)*/   list <int> l1;
    /*2)*/   list <int> l2(5);
    /*3)*/   list <char> l3(5, 'f');
    /*4)*/   list <int> l4 = {3,6,4,8,0,-3};
    /*5)*/   list <int> l5 = {l4.begin(), l4.end()};
    /*6)*/   list <int> l6 = l4;
    /*7)*/   int arr[] = {3,0,9};
             list <int> l7 = {arr, arr+sizeof(arr)/sizeof(arr[0])};


// TRAVERSAL
    traversal <int> (l1);   // <datatype> is optional
    traversal(l2);
    traversal(l3);
    traversal(l4);
    traversal(l5);
    traversal(l6);
    traversal(l7);


// ITERATOR
    list <int> :: iterator sample_iterator1 = l2.begin();
                        // OR
    auto sample_iterator2 = l2.begin();


// LIST FUNCTIONS
    cout<<"l4 front element =  "<<l4.front()<<"\n\n";
    cout<<"l4 back element =  "<<l4.back()<<"\n\n";
    cout<<"l4 size =  "<<l4.back()<<"\n\n";

    l4.push_front(19);
    traversal(l4);

    l4.push_back(4);
    traversal(l4);

    l4.pop_front();
    traversal(l4);

    l4.pop_back();
    traversal(l4);

    // NOTE: Both front as well as back functionalities are available in case of list (doubly linked list) as it maintains both a head as well as tail pointer to traverse in both directions while only front functionalities are available in case of forward_list (singly linked list) as it only maintains head pointer to traverse in only forward direction.

    l4.erase(--l4.end());
    traversal(l4);
    l4.erase(++(++l4.begin()), --l4.end());
    traversal(l4);

    l4.insert(l4.begin(), 7);               // inserts 3 at position l4.begin()
    l4.insert(++l4.begin(), 2, 8);          // inserts two 8s at position ++l4.begin()
    l4.insert(--l4.end(), {6,-3,-3,0,1});   // inserts {6,-3,-3,0,1} at position --l4.end()
    traversal(l4);
    // NOTE: l.emplace(...), l.emplace_after(...), l.emplace_before(...) also exist while l.insert_after(...) and l.insert_before(...) don't.

    l4.remove(6);
    traversal(l4);

    l4.reverse();
    traversal(l4);

    l4.unique();        // removes consecutive duplicates leaving only one element in the end
    traversal(l4);

    l4.sort(greater<int>());
    traversal(l4);

    l5.sort();
    l7.sort();
    l7.merge(l5);
    traversal(l7);

    if(l5.empty())
        cout<<"l5 is empty\n\n";
    else
        cout<<"l5 is not empty\n\n";
    
    l6.clear();
    if(l6.empty())
        cout<<"l6 is empty\n\n";
    else
        cout<<"l6 is not empty\n\n";

    l6.assign({3,-2,9,0});
    l6.assign(4,'k');
    l6.assign(++(++(l7.begin())), --(--l7.end()));
    traversal(l6);



    return 0;
}