#include<stdio.h>

void printArray(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d->", arr[i]);
    }
    printf("\n");
}

void selection (int arr[], int n)
{
    int minIndex, temp;
    for (int i = 0; i < n-1; i++)
    {
        minIndex = i;
        for (int j = i+1; j < n; j++)   // i+1 since even if the first element in the unsorted subarray is minimum, it won't need to be swapped.
        {
            if(arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
    
}

int main()
{
    /*

    => The selection sort algorithm sorts an array by repeatedly finding the minimum element (considering ascending order) from unsorted part and putting it at the beginning. The algorithm maintains two subarrays in a given array :-
        1) The subarray which is already sorted. 
        2) Remaining subarray which is unsorted.
    In every iteration of selection sort, the minimum element (considering ascending order) from the unsorted subarray is   picked and moved to the sorted subarray.

    => This algorithm is called selection sort because it repeatedly selects the next-smallest element and swaps it into place.

    => Does less memory writes compared to quick sort, merge sort, insertion sort, etc. The optimal algorithm for memory writes is, however, cycle sort.

    => Basic idea for Heap Sort.

    => <*> Total no. of Passes = n-1 (no. of times outer loop executes)
       <*> Total no. of comparisons = (n-1) + (n-2) + ... + 2 + 1 = n*(n-1)/2
                                    {P(1) + P(2) +...+ P(n-2) + P(n-1)}, P represents pass
       <*> Max no. of swaps = n-1
       [MIN NO. OF SWAPS is the advantage of this sorting algo, can be useful when memory write is a costly operation]

    => In Place Sorting : Yes       [Space Complexity = O(1)]

    => Stable Sorting Algorithm : No [(1 9 3* 3`) -> (1 3` 3* 9)]

    => Adaptivity : No

    => Recursive/Iterative : Iterative

    => Time Complexity :
        -> Worst-case performance : О(n^2) comparisons, О(n) swaps
        -> Best-case performance : О(n^2) comparisons, O(1) swaps
        -> Average performance : О(n^2) comparisons, О(n) swaps

    */

    int arr[] = {45,56,3,76,9,0,3};
    int n = sizeof(arr)/sizeof(arr[0]);

    selection(arr, n);
    printArray(arr, n);

    return 0;
}