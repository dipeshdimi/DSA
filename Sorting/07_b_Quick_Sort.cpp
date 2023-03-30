#include<iostream>

using namespace std;

void printArray(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d->", arr[i]);
    }
    printf("\n\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Naive_Partitioning (int arr[], int low, int high, int pivot_index)
{                               //__
    // Time Complexity -> O(n)      |__ n = size of arr[]
    // Auxiliary Space -> O(n)    __|

    int temp[high-low+1];
    int temp_index=0, partition_index;

    for (int i = low; i <= high; i++)
    {
        if(i==pivot_index)
        {
            partition_index = i;
            continue;
        }

        if(arr[i]<=arr[pivot_index])
        {
            temp[temp_index] = arr[i];
            temp_index++;
        }
    }

    temp[temp_index] = arr[partition_index];
    partition_index = temp_index;       // pivot element placed at the index that comes after all the elements less than or equal to pivot element
    temp_index++;

    for (int i = low; i <= high; i++)
    {
        if(arr[i]>arr[pivot_index])
        {
            temp[temp_index] = arr[i];
            temp_index++;
        }
    }

    for (int i = low; i <= high; i++)
        arr[i] = temp[i-low];

    return partition_index;
}


int Lomuto_Partitioning(int arr[], int low, int high)
// int Lomuto_Partitioning(int arr[], int low, int high, int pivot_index)
{
    /*  [     <pivot     |     >=pivot     |     uniterated array elements     ]
       low              i i+1           j-1 j                                 high
    */

    // swap(&arr[high], &arr[pivot_index]);         // In case, pivot is not the last element
    int pivot = arr[high];                          // Assume last element to be the pivot
    int i = low-1;
    for (int j = low; j <= high-1; j++)
    {
        if(arr[j] < pivot)              // if you want the first occurence of an element equal to the pivot element to be considered the partition index (i.e., if you want the last element (pivot) to be swapped in such a way that the elements left to it are less than it and the elements right to it are greater than or equal to it)
        // if(arr[j] <= pivot)          // if you want the last occurence of an element equal to the pivot element to be considered the partition index (i.e., if you want the last element (pivot) to be swapped in such a way that the elements left to it are less than or equal to it and the elements right to it are greater than it)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return i+1;
        // partition index / index of the pivot element
        // will be the new index of the original last element since we do not run the loop for j==high
    
    // No swaps inside the for-loop in case of the smallest element present at the end (pivot).
    // All the elements iterated in the for-loop are swapped with themselves.
}


int Hoare_Partitioning(int arr[], int low, int high)
// int Hoare_Partitioning(int arr[], int low, int high, int pivot_index)
{
    int i=low-1;
    int j=high+1;

    // swap(&arr[pivot_index], &arr[low]);
    int pivot = arr[low];

    while(true)
    {
        do
        {
            i++;
        } while (arr[i] < pivot);

        do
        {
            j--;
        } while (arr[j] > pivot);

        // i++ loop which searches for elements >= pivot i.e., arr[low] comes to a halt at least once even when all the elements are less than arr[low]. Since all the elements are less than arr[low], the j-- loop will terminate (on its first execution itself) at the first element (pivot). Thus, i and j will have crossed [i==j(==low)] and the function will be terminated. We don't have to worry about i++ never finding the required element to terminate the loop (as reasoned above) or j-- loop never finding the requuired element to terminate the loop (as j will eventually find that element at arr[low])
        
        if(i>=j)
            return j;
        /*
            => In case i remains i == low throughout the execution of Hoare_Partitioning() function and j-- loop terminates at j == low for the first time, if we return partition_index = i and use Quick_Sort_Hoare(arr, low, low-1) and Quick_Sort_Hoare(arr, low, high), the first function (left subtree) will terminate just fine, however, the second function (right subtree) will get stuck in an infinite recursion as we input Quick_Sort_Hoare(arr, low, high) every time and get Quick_Sort_Hoare(arr, low, high) every time.

            => On the other hand, we won't face this issue of infinte recursion if we simply return partition_index = j since the Hoare_Partitioning() function won't ever terminate for j == high and i == high (never resulting in Quick_Sort_Hoare(arr, low, high) and Quick_Sort_Hoare(arr, high+1, high)). This is because before the execution of j-- loop, i++ loop would had already terminated at i == low (since pivot == arr[low]) and thus, even if j-- loop termiates at j == high, arr[i] and arr[j] would be swapped and j will decrease from high.
            
            ### BASICALLY, FIRST SWAPPING IS ALWAYS BETWEEN arr[low] AND arr[j] AS i++ LOOP ALWAYS TERMINATES AT i == low FIRST, i CAN MOVE UP TO high ONLY AFTER THIS SWAPPING AND j WON'T REMAIN AT j == high AFTER THE FIRST SWAPPING.

            => {arr[low][i][j], arr[low+1], arr[low+2], arr[low+3], ..., arr[high-2], arr[high-1], arr[high]}   ->  POSSIBLE
               {arr[low], arr[low+1], arr[low+2], arr[low+3], ..., arr[high-2], arr[high-1], arr[high][i][j]}   ->  IMPOSSIBLE

            => We could have returned i as partition_index if we were using arr[high] as the pivot. In this case, returning partion_index = j could had caused infinte recursion.
        */
        
        swap(&arr[i], &arr[j]);
        // i++ loop always terminates at i==low, the first time it is executed as (i==low => arr[i] == arr[low] == pivot).
        // Since we start with stopping i at the pivot element itself (loop terminated in case, arr[i] <= pivot) and then swapping it with arr[j], there will always be an element at or beyond j which would be equal to pivot, so we don't have to worry about the i++ loop not finding the required element within the given subarray to terminate the loop.
        // Since the elements left of i are always <= pivot and the i++ loop terminates for arr[i]>=pivot, as soon as j crosses i, the j-- loop will terminate at j==i in case arr[i] == pivot or at j==i-1 otherwise. Thus, we don't have to worry about the j-- loop not finding the required element within the given subarray to terminate the loop (Note: Termination is guaranteed at j==low only when while(true) loop runs for the first time, after that the pivot element at low is swapped).

        // CORNER CASES
            // PIVOT == arr[low] is the SMALLEST element
                // => i++ loop terminates at i==low, j-- loop terminates at j==low (only position where arr[j] <= pivot)
                // => i==j and function terminates.
                // => In case, there are multiples smallest elements (all equal to pivot), i and j can terminate at any position depending upon the given subarray.

            // PIVOT == arr[low] is the LARGEST element
                // => i==low, j==high -> Elements Swapped
                // => i++ loop terminates at i==high (only position where arr[i] >=pivot, as pivot element is swapped here)
                // => j==high-1 (all elements are <= pivot)
                // => j==i-1 -> Function Terminates
                // => In case, there are multiples largest elements (all equal to pivot), i and j can terminate at any position depending upon the given subarray.
            
            // ALL ELEMENTS EQUAL
                // (i) [5* 5$ 5! 5# 5^] (j), pivot == 5
                // [5*[i] 5$ 5! 5# 5^[j]] -> [5^ 5$[i] 5! 5#[j] 5*] -> [5^ 5# 5![i][j] 5$ 5*]   {UNSTABLE}
    }
}


void Quick_Sort_Lomuto(int arr[], int low, int high)
{
    if(low < high)
    {
        int partition_index = Lomuto_Partitioning(arr, low, high);      // ROOT

        Quick_Sort_Lomuto(arr, low, partition_index-1);                 // LEFT SUBTREE
        Quick_Sort_Lomuto(arr, partition_index+1, high);                // RIGHT SUBTREE
    }
}

void Quick_Sort_Hoare(int arr[], int low, int high)
{
    if(low < high)
    {
        int partition_index = Hoare_Partitioning(arr, low, high);       // ROOT

        Quick_Sort_Hoare(arr, low, partition_index);                    // LEFT SUBTREE
        Quick_Sort_Hoare(arr, partition_index+1, high);                 // RIGHT SUBTREE

    /*
        // partition_index = i and following function calls corresponding to it won't work as discussed above.

        Quick_Sort_Hoare(arr, low, partition_index-1);                  // LEFT SUBTREE
        Quick_Sort_Hoare(arr, partition_index, high);                   // RIGHT SUBTREE
    */
    }
}


int main()
{
/*
    => Divide and Conquer Algorithm

    => Despite worst case time complexity O(n²), it is considered faster because :-
        1) In-place (not considering the auxiliary space required for recursive call stack)
        2) Cache friendly
        3) Average case is O(nlogn)
        4) Tail Recursive (Unlike merge sort for which the non-recursive function Merge() is the last function call and not the recursive function Merge_Sort(), in the case of quick sort, the recursive function quick_sort() is the last function call and not the non-recursive function partition())

                                         ___ Naive Partition (Stable)
                                        /
    => Partition() is the key function /---- Hoare's Partition (Unstable: Equal elements are swapped)
                                       \
                                        \___ Lomuto Partition (Unstable: If there are multiple elements equal to pivot, we may change the pivot elements relative to them at the end when placing at its correct position)
*/

// // NAIVE PARTITIONING
    int arr_naive[] = {3,5,-5,5,0,9,23,1,5,3,7,-4,5};
    // -5->-4->0->1->3->3->5->5->5->5->7->9->23->
    int n_naive = sizeof(arr_naive)/sizeof(arr_naive[0]);

    // printf("%d\n", Naive_Partitioning(arr, 0, n_naive-1, 7));
    // printArray(arr, n);

    printf("%d\n", Naive_Partitioning(arr_naive, 0, n_naive-1, 3));
    printArray(arr_naive, n_naive);

    
// LOMUTO PARTITIONING
    int arr_lomuto[] = {3,5,-5,5,0,9,23,1,5,3,7,-4,5};
    // -5->-4->0->1->3->3->5->5->5->5->7->9->23->
    int n_lomuto = sizeof(arr_lomuto)/sizeof(arr_lomuto[0]);
    
    // printf("%d\n", Lomuto_Partitioning(arr_lomuto, 0, n_lomuto-1, 0));
    printf("%d\n", Lomuto_Partitioning(arr_lomuto, 0, n_lomuto-1));
    printArray(arr_lomuto, n_lomuto);


// HOARE'S PARTITIONING
    int arr_hoare[] = {3,5,-5,5,0,9,23,1,5,3,7,-4,5};
    // -5->-4->0->1->3->3->5->5->5->5->7->9->23->
    int n_hoare = sizeof(arr_hoare)/sizeof(arr_hoare[0]);
    
    // printf("%d\n", Hoare_Partitioning(arr_hoare, 0, n_hoare-1, 1));
    printf("%d\n", Hoare_Partitioning(arr_hoare, 0, n_hoare-1));
    printArray(arr_hoare, n_hoare);


// Quick Sort
    int arr_lomuto_quickSort[] = {3,5,-5,5,0,9,23,1,5,3,7,-4,5};
    int n_lomuto_quickSort = sizeof(arr_lomuto_quickSort)/sizeof(arr_lomuto_quickSort[0]);
    Quick_Sort_Lomuto(arr_lomuto_quickSort, 0, n_lomuto_quickSort-1);
    printArray(arr_lomuto_quickSort, n_lomuto_quickSort);
    
    
    int arr_hoare_quickSort[] = {3,5,-5,5,0,9,23,1,5,3,7,-4,5};
    int n_hoare_quickSort = sizeof(arr_hoare_quickSort)/sizeof(arr_hoare_quickSort[0]);
    Quick_Sort_Hoare(arr_hoare_quickSort, 0, n_hoare_quickSort-1);
    printArray(arr_hoare_quickSort, n_hoare_quickSort);


// LOMUTO_PARTITIONING() vs HOARE_PARTITIONING()
/*
    SIMILARITIES
        => Both linear time complexity algorithims.
        => Both causes Quick_Sort() to degrade to O(n^2) when the input array is already sorted.
        => Both are unstable.

    DIFFERENCES
        => Hoare more efficient than Lomuto (three times fewer swaps on average, and efficient partitions even when all values are equal).
        => Lomuto -> Generally, the last element is considered the pivot element.
           Hoare  -> Generally, the first element is considered the pivot element.

        => Lomuto -> It doesn’t fix the pivot element in the correct position.
           Hoare  -> It fixes the pivot element in the correct position.

        => Lomuto -> [  <pivot  | pivot(correct position) |   >=pivot]
                    // Continue placing pivots at their correct position in each upcoming left and right subtree {Quick_Sort_Lomuto(arr, low, partition_index-1) and Quick_Sort_Lomuto(arr, partition_index+1, high)}
        => Hoare -> [   <=pivot   |   >=pivot   ]
                    // If we sort the left and right subtrees individually, the array will get sorted {Quick_Sort_Hoare(arr, low, partition_index) and Quick_Sort_Hoare(arr, partition_index+1, high)}
*/


// ANALYSIS (HOARE'S PARTITION - same time and space complexities in case of Lomuto Partition)
/*
    => Since we traverse the array/subarray once and terminate the partition() function once i and j cross, the time complexity for such array traversal would be a function of size of array/subarray.
        T(n) = T(n1) + T(n2) + Θ(n)         {Θ(n) represents time complexity of type cn}
                                            {n1+n2 = n, partitioning array into two equal/unequal parts}

    => BEST CASE [When the partition() function always divides the array into two equal halves]
                          cn    ------------------------------->    cn
                        /    \
                    cn/2      cn/2  --------------------------->    cn
                    /    \    /    \
                cn/4   cn/4 cn/4  cn/4  ----------------------->    cn
                ......................
            ..............................
        ......................................
        Θ(1)  Θ(1)  Θ(1)  Θ(1) ...... Θ(1)  Θ(1)  ------------->    cn

        Recurrence Relation :   T(n) = 2T(n/2) + Θ(n)
        Time Complexity :   cn + cn + cn + ... cn + Θ(n)    {cn added log₂n times}
                          = cn*log₂n + Θ(n)
                          = Θ(n*log₂n) + Θ(n)
                          = Θ(n*log₂n)


    => WORST CASE (When the array is already sorted/reverse sorted {all elements equal is a special case of this})
            cn                                   ____
           /  \                                     |
        Θ(1)   c(n-1)                               |
               /    \                               |
            Θ(1)    c(n-2)                          |                             cn      ___
                    /    \                          |                           /    \      |
                 Θ(1)    c(n-3)                     |                       c(n-1)   Θ(1)   |
                        .........                   |-- Sorted              /    \          |__ Reverse
                            .........               |                   c(n-2)    Θ(1)      |   Sorted
                                .........           |                 ........              |
                                       \            |             ........                __|
                                       c(2)         |
                                      /    \        |
                                    Θ(1)   Θ(1)  ___|

        Recurrence Relation :   T(n) = T(n-1) + Θ(1)
        Time Complexity :   cn + c(n-1) + c(n-2) + ... {n-1 times as c(1) = Θ(1)} + Θ(n) {sum of all Θ(1), occurs n times}
                          = cn(n-1)/2 + Θ(n)
                          = Θ(n²) + Θ(n)
                          = Θ(n²)


    => AVERAGE CASE
                                cn      ------------------------------->    = cn
                            /        \
                    cn(1-x)            cnx  --------------------------->    = cn
                   /    \            /     \
        cn(1-x)(1-x)  cn(1-x)x  cnx(1-x)    cnxx  --------------------->    = cn
        ........................................  --------------------->    = cn
                      ..........................  --------------------->    < cn
                                            ....  --------------------->    < cn
        [One part of the tree will exhaust quicker than the other - if x>0.5, left subtree will exhaust first, else, right subtree (NOTE: 0<x<1)]

        Recurrence Relation :   T(n) = T(nx) + T(n(1-x)) + Θ(n)
        Time Complexity : To calculate an upperbound, assume the tree to be completely filled:-
                          = cn + cn + cn + ... cn + Θ(n)    {cn added logₓn times if x>0.5, log₁₋ₓn otherwise}
                          = cn*logₓn + Θ(n)  OR  cn*log₁₋ₓn + Θ(n)
                          = cn*(log₂n/log₂x) + Θ(n)  OR  cn*(log₂n/log₂(1-x)) + Θ(n)
                                [To convert base m to n, logₘ(x) = logₙ(x)/logₙ(a)]
                          = c₁*(n*log₂n) + Θ(n)  OR  c₂*(n*log₂n) + Θ(n)
                                [Replacing the constant terms with a single constant, c₁ = cn/log₂x and c₂ = cn/log₂(1-x)]
                          = Θ(n*log₂n) + Θ(n)
                          = Θ(n*log₂n)
*/


// AUXILIARY SPACE
/*
    => In-place (not considering the auxiliary space required for recursive call stack)
    => Max no. of recursive call stacks at any point of time = Depth of the recursion tree
                                                                __
                                                                |   n (Worst Case)
                                                                |   [Auxiliary Space in terms of no. of
                                                                |   recursive call stacks = Θ(n)]
                                                          =   --|
                                                                |   log₂n+1 (Best Case)
                                                                |   [Auxiliary Space in terms of no. of
                                                                |_  recursive call stacks = Θ(log₂n)]
*/


// CHOICE OF PIVOT & WORST CASE OF QUICK-SORT
/*
    => In both, Lomuto (last element selected as pivot) as well as Hoare's partitioning (first element selected as pivot), whenever a sorted/reverse sorted array is input, the worst case happens [Θ(nlog₂n)].
    => To prevent this pattern of input of quick sort fails, we generate a random pivot as follows :-
        -> Lomuto:  int pivot_index = low + rand()%(high-low+1);    // Random no. from low to high
                    swap(arr[high], arr[pivot_index]);
                    Lomuto_Partitioning();
        -> Hoare:   int pivot_index = low + rand()%(high-low+1);    // Random no. from low to high
                    swap(arr[low], arr[pivot_index]);
                    Hoare_Partitioning();
*/


    return 0;
}