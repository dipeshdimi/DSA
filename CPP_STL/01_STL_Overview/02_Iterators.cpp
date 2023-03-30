#include<iostream>
#include<vector>

using namespace std;

int main()
{
/*
    => An iterator is an object (like a pointer) that points to an element inside the container.
    => We can use iterators to move through the contents of the container (begin() and end() can be used for this purpose).
    => A pointer is an example of an iterator.
    => Random access iterators (iterators for containers which allow random access, e.g., vector) follow pointer arithmetic and can be treated as pointer. However, in case of containers like forward_list, the iterators don't follow pointer arithmetic (as forward_list allows traversal in only one direction, one element at a time) and thus can't be treated as pointers.
    => SYNTAX 1: container_type <data_type> :: iterator iterator_name = container_name.begin();
                 [container_type <data_type> :: iterator would be the type of the iterator of the container container_type]
       SYNTAX 2: auto iterator_name = container_name.begin();
                 [auto keyword specifies that the type of the variable that is being declared will be automatically deducted from its initializer]
*/
    vector <int> v = {23,-3,7,8,5};     // Vector is a dynamically sized array
    vector <int> :: iterator i = v.begin();
    // auto i = v.begin();              // auto would deduce vector<int>::iterator itself

    // Dereferencing Iterator (pointer arithmetic applicable here)
    cout<<*i<<"\t";
    i++;
    cout<<*i<<"\t";
    i = v.end();
    cout<<*i<<"\t";     // Garbage value
    i--;
    cout<<*i<<"\t";


/*
=> Important Operations in Iterators:
    -> next(): This function RETURNS the new iterator that the iterator would point after advancing the positions mentioned in its arguments.
    -> prev(): This function RETURNS the new iterator that the iterator would point after decrementing the positions mentioned in its arguments.
    -> advance(): This function is used to increment the iterator position until the specified number mentioned in its arguments is met. It simply MODIFIES the existing value of the iterator with the given value.
*/
    i =  v.begin();     // first element
    cout<<"\n\n"<<*i<<"\t";
    i = next(i, 3);     // fourth element, RETURNS
    cout<<*i<<"\t";
    i = next(i);        // fifth element, default position advancement = 1, RETURNS
    cout<<*i<<"\t";
    i = prev(i, 2);     // third element, RETURNS
    cout<<*i<<"\t";
    i = prev(i);        // second element, default position decrement = 1, RETURNS
    cout<<*i<<"\t";
    advance(i, 3);      // fifth element, requires two arguments, MODIFIES
    cout<<*i<<"\t";

/*
=> TYPES OF ITERATORS
    Based upon the functionality of the iterators, they can be classified into five major categories (Note: These iterators are only logical classification of iterators, there are no classes as such in cpp library) :-
        1) Input Iterators: They are the weakest of all the iterators and have very limited functionality. They can only be used in single-pass algorithms, i.e., those algorithms which process the container sequentially such that no element is accessed more than once. The does not allow to write anything in the iterators. For eg., read data from iterator, prefix and postfix operations (traversal ahead using i++ or ++i) on the iterator.

        2) Output Iterators: Just like input iterators, they are also very limited in their functionality and can only be used in the single-pass algorithm, but not for accessing elements, but for being assigned elements. These can be used only to write something on iterators but not read.

        3) Forward Iterator: They are higher in the hierarchy than input and output iterators and contain all the features present in these two iterators. But, as the name suggests, they also can only move in the forward direction and that too one step at a time.

        4) Bidirectional Iterators: They have all the features of forward iterators along with the fact that they overcome the drawback of forward iterators, as they can move in both the directions, that is why their name is bidirectional.

        5) Random-Access Iterators: They are the most powerful iterators. They are not limited to moving sequentially, as their name suggests, they can randomly access any element inside the container. They are the ones whose functionality is same as pointers.

    # Iterator_Types_VS_Properties.jpg
    _________________________________________________________________________________________________________
    |   Container Types	 |   Containers	                        |   Supporting Iterators                    |
    |--------------------|--------------------------------------|-------------------------------------------|
    |   Simple	         |   forward_list(singly linked list)   |   Forward (only in forward directions)    |
    |   Simple	         |   list	                            |   bidirectional                           |
    |   Simple	         |   vector	                            |   Random                                  |
    |   Associate	     |   set	                            |   Bidirectional                           |
    |   Associate	     |   map	                            |   Bidirectional                           |
    |   Associate	     |   Multimap	                        |   Bidirectional                           |
    |   Associate	     |   Multiset	                        |   Bidirectional                           |
    |   Associate	     |   unordered_set	                    |   Forward                                 |
    |   Associate	     |   unordered_map	                    |   Forward                                 |
    |   Adapters	     |   queue	                            |   Do not have iterators                   |
    |   Adapters	     |   stack	                            |   Do not have iterators                   |
    |   Adapters	     |   priority_queue	                    |   Do not have iterators                   |
    |____________________|______________________________________|___________________________________________|

    NOTE: For the next(), prev() or advance() functions :-
            -> If the iterator is a random access iterator, they are going to work in O(1) time as the increments or decrements can be done directly.
            -> If the iterator is a forward iterator, they are going to work in O(n) time as the increments would be done one by one. Here n can never be negative, as in forward iterators one cannot traverse back into location.
            -> If the iterator is a bidirectional iterator, n can both be negative and positive, to traverse back and forth.
*/

    return 0;
}