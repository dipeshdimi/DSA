#include<iostream>
#include<algorithm>

using namespace std;

int main()
{
/*
                 |--> Containers [Implement data structures, take data-type (char, int, etc) as argument]
                 |      -> Simple: pair, vector, list, forward_list
    STL in CPP --|      -> Container Adapters: stack, queue, priority_queue
                 |      -> Associative: set, map, unordered_set, unordered_map
                 |
                 |--> Algorithms
                        # Use iterators, usually, begin() {points at the position of the first element} and end() {points at the position after the last element}
                        # Ex: binary_search(begin(), end(), key), sort(begin(), end()) [for ascending order], find, reverse, etc.
*/
    int arr[] = {2,6,0,-4};
    int n = sizeof(arr)/sizeof(arr[0]);
    sort(arr, arr+n);
    for (int i = 0; i < n; i++)
        cout<<arr[i]<<"->";
    cout<<"\n";

    if(binary_search(arr, arr+n, 0))
        cout<<"Found";
    else
        cout<<"Not found";

    return 0;
}