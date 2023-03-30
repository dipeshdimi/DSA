#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void No_Change(vector <int> v)      // Changes made to a copy of the vector, not the original one (pass by value)
{
    v.push_back(11);
    v.push_back(-37);
    v.push_back(49);
}

void Change1(vector <int> &v)       // Changes made to the original vector, as it is directly referenced here (pass by reference)
{
    v.push_back(11);
    v.push_back(-37);
    v.push_back(49);
}

vector<int> Change2(vector <int> &v)
{
    v.push_back(2);
    v.push_back(3);
    v.push_back(-9);

    return v;
}

void Eff_Traversal (const vector <int> &v)   // const optional, just to make sure the vector doesn't get changed during traversal, by mistake
{
    for(const int &x:v)       // Efficient as the vector elements are not copied to x in this case, instead we just refer to the vector element itself
        cout<<x<<"  ";
    cout<<"\n\n";
    // v.push_back(9999);   // This will give error as const is used
}

int main()
{
/*
    => Dynamically Sized Arrays
    => ADVANTAGES :-    1) Dynamic Size
                        2) Rich Library Functions
                        3) No need to pass size (vector_name.size(), sizes of the arrays passed through a function can't be calculated as what is passed is a pointer to the first element of the array (in both cases, *arr or arr[]) and thus sizeof(arr) would just give the memory occupied by the pointer pointing to the first element of the array)
                        4) Unlike the locally created arrays, even the locally created vectors can be returned from a function (dynamically created local arrays' pointers can still be returned though)
                        5) Default values (int vector initialised to 0, float to 0, string to "", bool to false, char to '0' i.e., NULL i.e., an empty vector)
                        6) Copying values (v1 = v2)
*/
// DECLARATION/INITIALIZATION
    /*1)*/ vector <int> v1;                         // Empty vector
    /*2)*/ vector <int> v2(10);                     // Vector of size=10, all elements initialiazed with 0
    /*3)*/ vector <int> v3 {-20, 5, -3, 10};        // Vector of size=4 holding the specified values
    /*3)*/ vector <int> v3again = {-20, 5, -3, 10}; // Vector of size=4 holding the specified values
    /*4)*/ vector <char> v4(5, 'z');                // Vector of size=5, all elements initialzed with 'z'
    /*5)*/ vector <int> v5(v3.begin()+1, v3.end()); // Copies vector v3 to v5
    /*6)*/ vector <int> v6 = v3;                    // Copies vector v3 to v6
    /*7)*/ int arr[] = {-29,2,9,0,-4};              // Copies array arr to v7
           vector <int> v7(arr, arr+sizeof(arr)/sizeof(arr[0]));


// VECTOR TRAVERSAL
    /* METHOD 1: */ for (int i = 0; i < v3.size(); i++)
                        cout<<v3[i]<<"  ";
                    cout<<endl<<endl;

    /* METHOD 2: */ for(int x:v5)
                        cout<<x<<"  ";
                    cout<<endl<<endl;

    /* METHOD 3: */ for(auto it=v6.begin(); it != v6.end(); it++ /* OR advance(it, 1) OR it=next(it) */)
                        cout<<*it<<"  ";
                    cout<<"\n\n";

    /* METHOD 4 (Reverse traversal): */ for(auto it=v7.rbegin(); it != v7.rend(); it++)
                                            cout<<*it<<"  ";
                                        cout<<"\n\n";


// VECTOR UPDATION
    /* METHOD 1: */ cout<<v2[0]<<"  ";
                    v2[0] = -1;
                    cout<<v2[0]<<"\n\n";
    
    /* METHOD 2: */ // DOESN'T UPDATE THE VECTOR
                        for(int x:v2)
                        {
                            cout<<x<<"  ";
                            x = 7;
                            cout<<x<<"\n";
                        }
                        for(int x:v2)
                            cout<<x<<"  ";
                        cout<<"\n\n";
                    // UPDATES THE VECTOR
                        for(int &x:v2)
                        {
                            cout<<x<<"  ";
                            x = 7;
                            cout<<x<<"\n";
                        }
                        for(int x:v2)
                            cout<<x<<"  ";
                        cout<<"\n\n";
                    // &x:v implies that the vector will be originally replaced and no copy will be made for temporary use (i.e. by reference) as in case of x:v.


// VECTOR FUNCTIONS
    // 1) vector_name.push_back(Element_to_be_pushed_at_the_back_of_the_vector);
        v1.push_back(9);
        v1.push_back(-2);
        v1.push_back(1);
        v1.push_back(-3);
        v1.push_back(5);
        v1.push_back(4);

    // 2) vector_name.size()
        for (int i = 0; i < v1.size(); i++)
        {
    // 3) vector_name.at(index)
            cout<<v1[i]<<" ";           // Does not perform array out of bound checking
            cout<<v1.at(i)<<"\n";       // Performs array out of bound checking
        }
        cout<<"\n";

    // 4) vector_name.pop_back()
        v1.pop_back();      // removes element from the back of the vector
        for(int x:v1)
            cout<<x<<"  ";
        cout<<"\n\n";

    // 5) vector_name.front()
        cout<<v1.front()<<"  ";
        v1.front() = 1;             // would work as front() returns the reference to the first element
        cout<<v1.front()<<"\n\n";

    // 5) vector_name.back()
        cout<<v1.back()<<"  ";
        v1.back() = -1;             // would work as front() returns the reference to the first element
        cout<<v1.back()<<"\n\n";
    
    // 6) vector_name.insert(it, Element_to_be_inserted)
    //          [for inserting a single element]
    //                     OR
    //    vector_name.insert(it, begin(), end())
    //          [for inserting an array/vector of elements, including element at begin() and not including element at end()]

    //  {it = Iterator to the position before which the element(s) is/are to be inserted i.e., at which the element(s) would be after insertion}
        v1.insert(v1.begin()+2, -50);
        for(int x:v1)
            cout<<x<<"  ";
        cout<<"\n\n";
        
        v1.insert(v1.begin()+3, v3.begin()+1, v3.end()-1);
        for(int x:v1)
            cout<<x<<"  ";
        cout<<"\n\n";

    // 7) vector_name.erase(Iterator_of_element_to_be_deleted);
    //                          OR
    //    vector_name.erase(range_begin_iterator, range_end_iterator)
    //          [To delete a range of element in the given vector, deletion not including range_end_iterator and including range_end_iterator]
        v1.erase(v1.end()-3);
        for(int x:v1)
            cout<<x<<"  ";
        cout<<"\n\n";

        v1.erase(v1.begin()+2, v1.begin()+4);
        for(int x:v1)
            cout<<x<<"  ";
        cout<<"\n\n";

    // 8) vector_name.resize(new_size)
    //              OR
    //    vector_name.resize(new_size, new_element(s)_value)
    //          [if new_element(s)_value is not specified, all the new elements will be initialized as the default value e.g., 0 in case of integers]
        v1.resize(7);
        for(int x:v1)
            cout<<x<<"  ";
        cout<<"\n\n";

        v1.resize(10, 5);
        for(int x:v1)
            cout<<x<<"  ";
        cout<<"\n\n";

        v1.resize(8);
        for(int x:v1)
            cout<<x<<"  ";
        cout<<"\n\n";

    // 9) vector_name.empty()
        if(v1.empty())
            cout<<"Empty\n\n";
        else
            cout<<"Not Empty\n\n";

    // 10) vector_name.clear()        [Deletes all the vector elements, empty vector remains, useful when we have to rewrite the vector after every test case]
        v1.clear();
        if(v1.empty())
            cout<<"Empty\n\n";
        else
            cout<<"Not Empty\n\n";
    

// TIME COMPLEXITIES OF VECTOR OPERATIONS
    /*
        1)  pop_back()  ->  O(1)
        2)  push_back() ->  O(1)
        3)  front()     ->  O(1)
        4)  back()      ->  O(1)
        5)  size()      ->  O(1)
        6)  empty()     ->  O(1)
        7)  begin()     ->  O(1)    [begin(), rbegin, crbegin(), cbegin()]
        8)  end()       ->  O(1)

        9)  insert()    ->  O(n)    [Elements need to be moved to make space for the new element]
        10) erase()     ->  O(n)    [Elements need to be moved to fill the space left behind by the removed element]
        11) resize()    ->  O(n)    [New elements may need to be added]
    */


// EFFICIENT TRAVERSAL OF A VECTOR
    Eff_Traversal(v3);


// PASSING VECTORS TO FUNCTIONS
    No_Change(v3);
    Eff_Traversal(v3);

    Change1(v3);
    Eff_Traversal(v3);

    v3 = Change2(v3);   // changed bcoz we assigned the returned vector to v3
    Eff_Traversal(v3);


// INTERNAL WORKING OF A VECTOR
    /*
        => Internally uses dynamically allocated arrays.
        => If currently allocated space gets full, do the following:
            1) Create a new layer space (new dynamically alloacted array) of greater size (double, triple, etc, varies, compiler dependent).
            2) Copy elements from old space to new space.
            3) Free old space (previous dynamically allocated array).
        => To check current capacity of any vector : vector_name.capacity();
    */
    /*
        => Time Complexity of inserting (n+1) new elements at the end when n is the capacity :-
            = O(1)+O(1)+ O(1)+ ....(first n elements)...... +O(1) + O(n)
                                                                    |---> (n+1)th element as previous dynamically allocated array is to be copied into the new one
            = O(n) + O(n) = 2*O(n)

        => Thus, average time complexity of inserting one new elements at the end = 2*O(n)/(n+1) = O(1)
    */
   cout<<v3.capacity()<<"\n";   // Currently stores 7 elements but has a capacity of storing 8 elements
   cout<<v1.capacity()<<"\n";   // Currently empty but has had the capacity of storing 14 elements which doesn't change even when all the vector elements are removed
   vector <char> v8;
   cout<<v8.capacity()<<"\n\n";   // Empty vector, never had any element stored, thus 0 capacity

   // vector_name.reverse()     [part of <algorithm> library]
        reverse(v3.begin()+4, v3.end()-2);
        for(int x:v3)
            cout<<x<<"  ";
        cout<<"\n\n";

    
    return 0;
}