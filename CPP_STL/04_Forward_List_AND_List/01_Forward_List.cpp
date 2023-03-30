#include<iostream>
#include<forward_list>
#include<forward_list>

using namespace std;

template <typename T>
void traversal(const forward_list <T> &f)
{
    for (const T &x:f)
        cout<<x<<" -> ";
    cout<<"\n\n";

    // *** this is still valid as we are going one element at a time instead of randomly jumping from element to element (f.begin()+i), which is also why something like f.begin()++ will still work in both of the scenarios referenced here :-
    //  for(auto it=f.begin(); it<f.end(); it++)
    //     cout<<(*it);
    // cout<<"\n\n";
}

int main()
{
/*
    => Implements Singly Linked List
    => Can't be traversed backwards
    => Constant time insertion and removal of elements
    => Preferred in chaining in hashing, adjacency list representation of a graph, etc.
    => Initialzed with deafualt values same as vectors
*/
// DECLARATION & INITIALIZATION
    forward_list <int> f;
    /*1)*/ forward_list <int> f1;                       // Empty forward_list
    /*2)*/ forward_list <int> f2(10);                   // forward_list of size=10, all elements initialiazed with 0
    /*3)*/ forward_list <int> f3 {-20, 5, -3, 10, 5};      // forward_list of size=3 holding the specified values
    /*4)*/ forward_list <char> f4(5, 'z');              // forward_list of size=5, all elements initialzed with 'z'
    /*5)*/ forward_list <int> f5(f3.begin(), f3.end()); // Copies forward_list f3 to f5, can't use something like f3.begin()+2 here (***don't know why, maybe bcoz there is no random access?)
    /*6)*/ forward_list <int> f6 = f3;                  // Copies forward_list f3 to f6
    /*7)*/ int arr[] = {-29,2,9,0,-4};                  // Copies array arr to f7
           forward_list <int> f7(arr, arr+sizeof(arr)/sizeof(arr[0]));



// TRAVERSAL
    traversal <int> (f1);   // <datatype> is optional
    traversal(f2);
    traversal(f3);
    traversal(f4);
    traversal(f5);
    traversal(f6);
    traversal(f7);



// ITERATOR
    forward_list <int> :: iterator sample_iterator1 = f2.begin();
                        // OR
    auto sample_iterator2 = f2.begin();



// FORWARD_LIST FUNCTIONS           ____
    /*1)*/ f3.push_front(4);    //      |
           f3.push_front(16);   //      |--- Can push/pop only one element at a time
    /*2)*/ f3.pop_front();      //  ____|
    traversal(f3);


    /*3) assign() : This function is used to assign values to forward list (can't modify, will just rewrite the entire forward list */
        f3.assign({5,6,-2,0});  // 4 -> -20 -> 5 -> -3 -> 10    to    5 -> 6 -> -2 -> 0
        traversal(f3);

        f3.assign(f6.begin(), f6.end());
            // Can't use something like f3.begin()+2 here (***don't know why, maybe bcoz there is no random access?)
            // Same as f3 = f6;
        traversal(f3);

        f4.assign(7, 'h');  // forward_list_name.assign(No_of_reps, Element_to_be_filled_repeatedly)
        traversal(f4);


    /*4) remove(): This function removes all the elements from the forward list that is mentioned in its argument */
        f6.remove(5);       // Removes both instance of 5 in f6
        traversal(f6);


    /*5) insert_after():-
        -> Can insert one or multiple elements at the position just beyond the iterator passed as the argument
        -> Copies or moves the elements into the container by calling copy constructor or move constructor
        -> Returns the position of the inserted element (position of the first element in case of multiple insertions) */
        auto it = f3.insert_after(f3.begin(), -22);
        traversal(f3);
        it = f3.insert_after(it, {4,5,0});
        traversal(f3);


    /*6) emplace_after():-
        -> Can insert just one element at the position just beyond the iterator passed as the argument.
        -> Elements are constructed in-place, i.e. no copy or move operations are performed, thus more efficent with its usage being desirable if copying your class is a non trivial operation
        -> Returns the position of the inserted element */
        it = f3.emplace_after(f3.begin(), -22);
        traversal(f3);


    /*7) erase_after(): This function is used to erase a single or a range of elements from a particular position in the forward_list and return the position of the deleted element */
        it = f3.erase_after(it);
        traversal(f3);

        it = f3.erase_after(it, f3.end());
        traversal(f3);

    
    /*8) empty(): This function returns a boolean value indicating whether the forward_list is empty, i.e. whether its size is 0 or not.
        -> Syntax: forwardlistname.empty()
        -> Parameters: No parameters are passed
        -> Result/Return Value: True, if the list is empty else false
        if(f3.empty())
            cout<<"Empty\n\n";
        else
            cout<<"Not Empty\n\n";


    /*9) clear(): This function is used to remove all the elements of the forward list container, thus making its size 0.
        -> Syntax: forwardlistname.clear()
        -> Parameters: No parameters are passed
        -> Result: Removes all forward list elements
        -> Return Value: No return value */
        f3.clear();
        if(f3.empty())
            cout<<"Empty\n\n";
        else
            cout<<"Not Empty\n\n";

    
    /*10) reverse(): This is an inbuilt function in CPP STL which reverses the order of the elements present in the forward_list.
        -> Syntax: forwardlist_name.reverse()
        -> Parameter: No parameters are passed
        -> Result: Reverses the forward list
        -> Return Value: No return value */
        traversal(f7);
        f7.reverse();
        traversal(f7);

    
    /*11) sort(): This function is used to sort the elements of the container by changing their positions.
        -> Syntax: forwardlistname.sort()
        -> Parameter: No parameters are passed
        -> Result: Sorts the forward list in ascending order
        -> Return Value: No return value
        -> NOTE: This #include<forward_list> sort function is different from the sort function included in the #include<algorithm> library which accepts input as sort(container.begin(), container.end(), myComp) */
        f6.sort();
        traversal(f6);
        f7.sort();
        traversal(f7);


    /*12) merge():-
        -> Merges two sorted forward_lists into one (merges the second list into the first, thus emptying the second list). It's basically the merge function in merge sort.
        -> The merge() function can be used in two ways :-
            # Merge two forward lists that are sorted in ascending order into one.
            # Merge two forward lists into one using a comparison function.
        -> Syntax:  forwardlist_name1.merge(forward_list &forwardlist_name2)
                                        OR
                    forwardlist_name1.merge(forward_list &forwardlist_name2, greater<int>())
                                        OR
                    forwardlist_name1.merge(forward_list &forwardlist_name2, myComp)
        -> Parameters: The function accepts two parameters which are specified as below:
            # forwardlist_name2 – Another forward list of the same type which is to be merged
            # myComp – A comparison function which should return true or false.
        -> Return Value: No return value
        -> NOTE: There is another variation of merge() function where it can take a parameter to determine the order of sorting the forward_list. */
        f7.merge(f6);
        traversal(f7);
        if(f6.empty())
            cout<<"f6: Empty";
        else
            cout<<"f6: Not Empty";



// TIME COMPLEXITIES OF FORWARD LIST FUNCTIONS
    /*
        1) insert_after():  1 element -> O(1) & M elements -> O(m)

        2) erase_after():   1 element -> O(1) & M elements -> O(m)

        3) push_front():    O(1)

        4) pop_front():     O(1)

        5) reverse():       O(n)

        6) sort():          O(nlogn)

        7) remove():        O(n)

        8) assign():        1 element -> O(1) & M elements -> O(m)
    */


    return 0;
}