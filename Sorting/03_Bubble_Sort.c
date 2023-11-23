#include<stdio.h>

void bubble_unoptimised(int arr[], int n)
{
    int temp;
    for (int i = 0; i < n-1; i++)       // Number of passes
    {
        for (int j = 0; j < n-1-i; j++)     // Number of Comparisons
        {
            if(arr[j]>arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
        printf("Pass\n");
    }
}

void bubble_optimised(int arr[], int n)
{
    int temp, sorted;
    for (int i = 0; i < n-1; i++)       // Number of passes
    {
        sorted = 1;
        for (int j = 0; j < n-1-i; j++)     // Number of Comparisons
        {
            if(arr[j]>arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                sorted = 0;
            }
        }
        // printArray(arr, n);
        printf("Pass\n");
        if(sorted == 1)
            return;
    }
}

void bubble_recursion(int arr[], int n)
{
    int temp, sorted = 1;

    // Base case
    if(n == 1)
        return;
 
    // One pass of bubble sort - After this pass, the largest element in unsorted array is moved (or bubbled) to the end.
    for(int i=0; i<n-1; i++)        // Number of Comparisons
    {
        if(arr[i]>arr[i+1])
        {
            temp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = temp;
            sorted = 0;
        }
    }

    // If array is already sorted
    if(sorted == 1)
        return;
 
    // Largest element in unsorted array is fixed, recur for remaining array
    bubble_recursion(arr, n-1);       // Number of passes
    // Every time this function is called, n=n-1 due to which the loop above becomes of the form n-1-i, same as the number of times the inner loop executes in the iterative approach and this function, bubble_recursion() is called n-1 times until n=1, same as the number of times, the outer loop runs in the iterative approach.
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
    => Bubble Sort works by repeatedly swapping the adjacent elements if they are in wrong order.
    
    => The “bubble” sort is called so because the list elements with greater value than their surrounding elements “bubble” towards the end of the list. For example, after first pass, the largest element is bubbled towards the right most position.

    => Example: ( 7 9 2 11 4 )
        -> First Pass :- 
        ( 7 9 2 11 4 )      [No swap since 7<9]     |       Comparisons = n-1 = 5-1 = 4
        ( 7 2 9 11 4 )      [Swap since 9>2]        |       Maximum Possible Swaps = n-1 = 4
        ( 7 2 9 11 4 )      [No swap since 9<11]    |
        ( 7 2 9 4 11 )      [Swap since 11>4]       |

        -> Second Pass :- 
        ( 2 7 9 4 11 )      [Swap since 7>2]        |       Comparisons = n-2 = 5-2 = 3
        ( 2 7 9 4 11 )      [No swap since 7<9]     |       Maximum Possible Swaps = n-2 = 5-2 = 3
        ( 2 7 4 9 11 )      [Swap since 9>4]        |

        -> Third Pass :- 
        ( 2 7 4 9 11 )     [No swap since 2<7]      |       Comparisons = n-3 = 5-3 = 2
        ( 2 4 7 9 11 )     [Swap since 7>4]         |       Maximum Possible Swaps = n-3 = 5-3 = 2

        -> Fourth Pass :- 
        ( 2 4 7 9 11 )      [No swap since 2<4]     |       Comparisons = n-4 = 5-4 = 1
                                                            Maximum Possible Swaps = n-4 = 5-4 = 1

        <*> Sorted Array : (2 4 7 9 11)
        <*> No. of Passes = n-1 (no. of times outer loop executes)
    
    => In Place Sorting : Yes       [Auxiliary Space = O(1) (Iterative Approach)]

    => Stable Sorting Algorithm : Yes

    => Adaptivity : No, but can be optimised to become adaptive.

    => Recursive/Iterative : Both, their time complexity is same, space complexity of recursive approach is O(n) though (due to n function calls in stack) instead of O(1), as of the iterative approach.

    => Time Complexity :
        -> Worst and Average Case Time Complexity: O(n^2) [Worst case occurs when array is reverse sorted]
        -> Best Case Time Complexity: O(n) [Best case occurs when array is already sorted, talking about optimised approach]
    
    */

    int arr[] = {7, 9, 2, 11, 4};
    int n = sizeof(arr)/sizeof(arr[0]);
    // Array arr in main function is not the same as in another function. The array decays to a pointer when passed. So sizeof only works to find the length of the array if you apply it to the original array. Thus, the length of the array needs to be passed as a separate argument to the function. In another function declaration, int arr[] is same as int*arr and arr is a pointer, not an array. Therefore, sizeof(arr) = 4 (i.e., the size of pointer int*arr).
    
    bubble_unoptimised(arr, n);
    printArray(arr, n);

    // bubble_optimised(arr, n);
    // printArray(arr, n);

    // bubble_recursion(arr, n);
    // printArray(arr, n);

    return 0;
}