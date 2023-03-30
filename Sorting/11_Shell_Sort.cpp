#include<iostream>

using namespace std;

void printArray(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        cout<<arr[i]<<"->";
    }
    cout<<"\n";
}

void Shell_Sort(int arr[], int n)
{
    // METHOD 1
    int key, j;
    // We start with gap=n/2 and then keep halving it until gap>=1 (there can also be other gap sequences to achieve better time complexity).
    // When gap==1, shell sort becomes insertion sort (insertion sort is a special case of shell sort when gap==1) and thus, sorting is always ensured at the end of shell sort's execution execution.
    // Since we have already shifted most of the smaller elements to the left side by the time gap becomes 1, long shifting operations are not usually performed which makes insertion sort in this case efficient (close to linear time).
    for (int gap = n/2; gap >=1; gap/=2)
    {
    // CODE BELOW SAME AS INSERTION SORT CODE< JUST REPLACING every occurrence of '1' WITH 'gap' HERE :-

        // Same as we initialise i with '1' (2nd element) in insertion sort as we consider the first element (0th element) to be sorted and then place remaining unsorted elements at its correct position in the sorted subarray, here, we initialise i with gap as we consider the first element (index=0) of the array to be sorted and next we place the upcoming elements each at length 'gap' (index=gap+1) at their correct positions in the sorted subarray.
        // We keep incrementing i by 1 up until i reaches the end of the array so that all the possible elements separated by length 'gap' are covered.
        for (int i = gap; i < n; i++)
        {
            key = arr[i];   // Element to be placed at correct position in sorted subarray

            // We keep initilise j at distance 'gap' from i and then keep decrementing it to be distance multiple of 'gap' from i until we cross the beginning of the array or find an element already at its correct position i.e., arr[j]>key (we won't need to check for (compare key with) elements that lie before the correct position element (arr[j]) as elements before arr[j] will all be less than or equal to it since we finding key's correct position in the sorted subarray).
            for (j = i-gap; j>=0 && arr[j]>key; j-=gap)
            // for (j = i; j>=gap && arr[j-gap] > key; j-=gap)
            {
                // We keep shifting jth element to (j+gap)th index in each execution
                // This shifting will keep onn happening until we find the correct position of key element or run out of the array i.e., -ve j (j+gap would be the index of the first element of gapped subarray and arr[j] will be the min element in the gapped subarray as no arr[j]<=key was found)
                // There will remain a different duplicate in each j-=gap loop execution.
                arr[j+gap] = arr[j];
                // arr[j] = arr[j-gap];
            }
            // j+gap will be the correct index for key element, so we place key at (j+gap)th index. This will remove the duplicate too, if any (there will be no duplicate in case j-=gap is not executed even once and in this case we will just be assigning the same element to itself i.e., arr[j+gap] == arr[i-gap+gap] == arr[i] == key)
            arr[j+gap] = key;
            // arr[j] = key;
        }
        
    }
    
}

int main()
{
    int arr[] = {3,5,-5,5,0,9,23,1,5,3,7,-4,5};
    int n = sizeof(arr)/sizeof(arr[0]);

    Shell_Sort(arr, n);
    printArray(arr, n);

/*
    => Shell sort is mainly a variation of Insertion Sort.
    => In insertion sort, we move elements only one position ahead. When an element has to be moved far ahead, many movements are involved. The idea of Shell Sort is to allow the exchange of far items.
    => Gap Sorted Array:-
        -> In Shell sort, we make the array gap-sorted for a large value of gap (usually n/2).
        -> Then, we keep reducing the value of gap until it becomes 1.
        -> An array is said to be gap-sorted if all sublists of every gap’th element are sorted.
    
    => STABILITY : Unstable sorting algorithm because this algorithm does not examine the elements lying in between the intervals.

    => IN-PLACE COMPARISON SORT

    => ADAPTIVE : Yes, faster execution in case of sorted/partially sorted array

    => SPACE COMPLEXITY : O(1)

    => TIME COMPLEXITY :-
        __________________________________________________
        |         LOOP             |  No. of Executions  |
        |__________________________|_____________________|
        | OUTER LOOP (gap-loop)    |      log₂n          |
        | MIDDLE LOOP (i-loop)     |      n-gap          |
        | INNER LOOP (j-loop)      |     <= n/gap        |
        --------------------------------------------------
        https://stackoverflow.com/a/12771634

        -> Best Case :  # Array is already sorted in best case and the inner loop (j-loop) is never executed
                        # No. of executions = log₂n*(n-gap)
                        # TIME COMPLEXITY : O(nlog₂n)
        
        -> Worst Case : # No. of executions for :-
                            * Inner loop : = n/gap  (in worst case)
                            * Inner + Middle loop : = (n-gap)*(n/gap) ~ n²/gap
                            * Inner + Middle + Outer :  = n²/(n/2) + n²/(n/4) + n²/(n/8) + ... n²/(1)   [log₂n times]
                                                        = 2n + 4n + 8n + ... n²                         [log₂n times]
                                                        = 2n(1+2+4+ ... + n/2)                          [log₂n times]
                                                        = 2n * [1(2⁽ˡᵒᵍ₂ⁿ⁾ - 1)/(2-1)]              
                                                        = 2n * (n-1)

                        # TIME COMPLEXITY : O(n²)

                        # ??? According to Poonen Theorem, worst case complexity for shell sort is Θ(Nlog N)2/(log log N)2) or Θ(Nlog N)2/log log N) or Θ(N(log N)2) or something in between. ???
        
        -> Average Case : ??? O(nlog₂n) ???
*/

    return 0;
}