#include<stdio.h>
#include<stdlib.h>

void printArray(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d->", arr[i]);
    }
    printf("\n");
}


void Merge_1_Array(int arr[], int low, int mid, int high)
{
    int i = low;
    int j = mid+1;
    int k = 0;  // ***

    int M[high-low+1];

    // int *M = (int*)malloc(((high-low)+1)*sizeof(int));   // free(M) should be used at the end of the function in case of DMA.


    while(i<=mid && j<=high)
    {
        if(arr[i] <= arr[j])    // <= would make the algorithm remains stable as it would ensure arr[i] (which occurs first in the given array) is given order preference over arr[j] (which occurs later in the given array) in case arr[i] == arr[j].
        {
            M[k] = arr[i];
            i++;
            k++;
        }
        else
        {
            M[k] = arr[j];
            j++;
            k++;
        }
    }

    while(i<=mid)
    {
        M[k] = arr[i];
        k++;
        i++;
    }

    while(j<=high)
    {
        M[k] = arr[j];
        k++;
        j++;
    }

    for (i = low; i <= high; i++)
    {
        arr[i] = M[i-low];  // ***
    }

    // free(M);    // Dynamically allocated memory is not deallocated when the function terminates. The only way to deallocate dynamic memory is via free() function.

    // *** k=low and arr[i] = M[i] won't work as the allocated size of M[] is high-low+1, which would mean the index of array M will vary from 0 to high-low. In the case of k=low and arr[i]=M[i], however, we will be accessing M elements ranging from index low to high (even when the last element of M is at index high-low).
}


void Merge_2_Arrays(int arr[], int low, int mid, int high)
{
    int n1 = (mid+1)-low;
    int n2 = high-mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[low+i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid+1+i];
    
    int i=0;
    int j=0;
    int k=low;

    while (i<n1 && j<n2)
    {
        if(L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void Merge_Sort(int arr[], int low, int high)
{
    int mid;     // Dividing the array into two halves
    if(low < high)      // Minimum two elements
    {
        mid = low + (high-low)/2;   // same as (low+high)/2 but this will prevent overflow in case low and/or high  are very large (low+high exceeding the maximum int value).
        Merge_Sort(arr, low, mid);
        Merge_Sort(arr, mid+1, high);
        Merge_1_Array(arr, low, mid, high);
        // Merge_2_Arrays(arr, low, mid, high);
        // https://cdn.programiz.com/cdn/farfuture/PRTu8e23Uz212XPrrzN_uqXkVZVY_E0Ta8GZp61-zvw/mtime:1586425911/sites/tutorial2program/files/merge-sort-example_0.png
    }
}

int main()
{
    /*
    => In this algorithm, we divide the arrays into subarrays and subarrays into more subarrays until the size of each subarray becomes 1. Since arrays with a single element are always considered sorted, this is where we merge. Merging two sorted subarrays creates another sorted subarray. We continue merging until we get the required sorted array.


    => BASIC MERGING PROCEDURE :-
        ->  Let two sorted arrays be:   A[m] = {a1, a2, a3, ..., am}
                                        B[n] = {b1, b2, b3, ..., bn}
            Let the merged array be:    M[m+n] = {Element of A and B in sorted order}

        ->  Let i = 0 (first element in A)
            Let j = 0 (first element in B)
            Let k = 0 (first element in M)

        ->  Fill smaller elements first in the merged array.
            while(i!=m && j!=n)
                M[k] = min(A[i], B[j]);
                k++;
                A[i] < B[j] ? i++ : j++;

        ->  Once the above loop finishes, either array A or B or both get finished. And now you run two while loops for each array A and B, and insert all the remaining elements as they are in the array C. And you are done merging.
            while(i!=m)                         while(j!=n)
                M[k] = A[i];                        M[k] = A[j];
                i++;                                j++;
                k++;                                k++;


    => MERGE SORT
        1) Whenever you are asked to sort an array using the merge sort algorithm, first divide the array until the size of each subarray becomes 1.
        2) Now, since an array or subarray of size 1 is considered already sorted, we call our merge function, which merges these subarrays into bigger sorted subarrays.
        3) And finally, you end up with your array fully sorted.

        -> The situation used in the above merge procedure would quite not be our situation when sorting an array using the merge sort. We wouldn’t have two different arrays A and B, rather a single array having two sorted subarrays. Thus, the merging procedure will need to be modified in this case :-
                                                        _____
            # low = First index of first subarray           |
            # high = Last index of second subarray          |
            # mid = (low+high)/2                            |
            # low to mid : First Subarray                   |---- The merge procedure will be
            # mid+1 to high : Second Subarray               |         updated accordingly
            # i = low                                       |
            # j = mid+1                                     |
            # k = low                                   ____|

            
    => TIME COMPLEXITY
        -> T(n) = 2T(n/2) + Θ(n)   [T(n/2) for each Merge_Sort() call and Θ(n) for the Merge() call]
        -> Recurrence Tree (height of the tree will be ⌈log₂n⌉+1) / Master Theorem -> Θ(nlog₂n), O(nlog₂n) & Ω(nlog₂n) [same in average, worst and best cases]
        -> Note: ⌈ x ⌉ represents SIF/ceiling function.

    
    => AUXILIARY SPACE
        ->  O(n) 
            [We do not need to have the sum of the space allocated each time Merge() function is called, since every time a Merge() function terminates, the allocated space is also deallocated before the space is allocated in some other Merge() function call. We just need to mention the maximum space allocated at any given point during the execution of the algorithm, i.e., the spacea alloacted when the Merge() function is called the last time as it merges the two sorted halves of the given array to give our final sorted array.]


    => MERGE SORT vs QUICK SORT
        For Arrays -> Quick Sort outperforms Merge Sort
        For Linked Lists -> Merge Sort outperforms Quick Sort

    */
    // int arr[] = {10, 20, 30, 4, 12, 17, 22, 33};
    // merge(arr, 0, 2, 7);
    // printArray(arr, 8);

    int arr[] = {-3, 4, 0, 78, 23, -45, 20, -3, 0, 7};
    int n = sizeof(arr)/sizeof(arr[0]);

    Merge_Sort(arr, 0, n-1);
    printArray(arr, n);

    return 0;
}