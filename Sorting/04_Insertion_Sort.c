#include<stdio.h>

void insertion(int arr[], int n)
{
    int temp, key, j;
    // Loop for passes
    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        // Loop for each pass
        for (j = i-1; j >= 0 && arr[j] > key; j--)
        {
            arr[j+1] = arr[j];
        }
        arr[j+1] = key;
        // printArray(arr, n);
    }
}

void printArray(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d->", arr[i]);
    }
    printf("\n");
}

int main()
{
    /*
    => In Insertion Sort, the array is virtually split into a sorted and an unsorted part. Values from the unsorted part are picked and placed at the correct position in the sorted part. Basically, you keep shifting the elements in sorted subarray until you find the correct position for your 'key' and then place it there.
    
    => This sort works on the principle of inserting an element at a particular position in the sorted part of the array, hence the name Insertion Sort.

    => Used in practice for small arrays as part of hybrid algorithms (for e.g., Tim Sort = Merge + Insertion & Intro Sort = Quick + Heap + Insertion)

    => Example: (12, 54, 65, 7, 23, 9)
    {'|' represents the partition between sorted and unsorted subarrays}
        // -1   0    1   2   3   4   5  --> ARRAY INDICES

        //      12,| 54, 65, 07, 23, 09 --> i=1, key=54, j=0
        //      12,| 54, 65, 07, 23, 09 --> 1st pass (i=1) done

        //      12, 54,| 65, 07, 23, 09 --> i=2, key=65, j=1
        //      12, 54,| 65, 07, 23, 09 --> 2nd pass (i=2) done as key>arr[1] i.e., 65>54

        //      12, 54, 65,| 07, 23, 09 --> i=3, key=7, j=2
        //      12, 54, 65,| 65, 23, 09 --> i=3, key=7, j=1
        //      12, 54, 54,| 65, 23, 09 --> i=3, key=7, j=0
        //      12, 12, 54,| 65, 23, 09 --> i=3, key=7, j=-1
        //      07, 12, 54,| 65, 23, 09 --> i=3, key=7, j=-1--> 3rd pass (i=3) done

        // Fast forwarding and 4th and 5th pass will give:
        //      07, 12, 54, 65,| 23, 09 --> i=4, key=23, j=3
        //      07, 12, 23, 54,| 65, 09 --> After the 4th pass

        //      07, 12, 23, 54, 65,| 09 --> i=5, key=09, j=4
        //      07, 09, 12, 23, 54, 65| --> After the 5th pass

        <*> Sorted Array : (7, 9, 12 ,23, 54, 65)
        <*> Total no. of Passes = n-1 (no. of times outer loop executes)
        <*> Max no. of comparisons = 1  + 2 + 3 + ... + (n-1) = n*(n-1)/2
                                 {P(1) + P(2) + P(3) +...+ P(n-1)}, P represents pass
    
    => In Place Sorting : Yes       [Space Complexity = O(1)]

    => Stable Sorting Algorithm : Yes

    => Adaptivity : Yes, best case time complexity is O(n), when the array is already sorted.

    => Recursive/Iterative : Iterative

    => Time Complexity :
        -> Worst and Average Case Time Complexity: O(n^2), bcoz max no. of comparisons = n*(n-1)/2. [Worst case occurs when array is reverse sorted]
        -> Best Case Time Complexity: O(n), bcoz each element will be compared only once and that happens (n-1) times, which means total number of comparisons in this case will be (n-1), thus leading to a best case time complexity of O(n). [Best case occurs when array is already sorted]

    => Bubble -> Swapping
       Insertion -> Shifting
    
    */

    int arr[] = {12, 54, 65, 7, 23, 9};
    int n = sizeof(arr)/sizeof(arr[0]);

    insertion(arr, n);
    printArray(arr, n);


    return 0;
}