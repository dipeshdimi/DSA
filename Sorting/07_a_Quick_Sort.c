#include<stdio.h>

void printArray(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d->", arr[i]);
    }
    printf("\n");
}

int partition(int *arr, int low, int high)
{
    int pivot = arr[low];       // We can also use just arr[low] throughout this algorithm instead of pivot, pivot is only for our convenience/understanding
    int i = low+1;
    int j = high;
    int temp;

    // do-while so that in case, there are just 2 elements in the array/subarray, in which case, i and j will be equal,the loop does execute once (in case of just one element, the quick_sort() function and consequently this partition() function won't even execute as the condition is high>low, in case of 1 element, high = low = 0).
    do
    {
        // look for an element which is greater than pivot and stop i there (by terminating the loop)
        // i<=high to ensure we do not access any element outside the input array/subarray
        while(arr[i] <= pivot && i<=high)
        {
            i++;
        }
        
        // look for an element which is less than or equal to pivot and stop j there (by terminating the loop)
        // breaking the loop for arr[j] == pivot too is necessary (for instance in 9th call, 3rd line + i feel something more should be written here as the reason) to ensure we do not access an element beyond the input array/subarray, j can go up the zeroth element i.e., the pivot, not beyond that. Thus, either we can have the condition arr[j] > pivot OR arr[j] >= pivot && j>low.
        // j>low to ensure we do not access any element outside the input array/subarray (since pivot is meant to be the first element, there is no point really 🤔)
        while (arr[j] > pivot 
                // && j>low
                )
        {
            j--;
        }

        // Swapping takes place only if i<j coz once i>=j (more specifically, j=i (possible only when i==high) or j=i-1, only these two cases are possible, as in case of j=i-2 or further would imply the same element to be both less than as well as greater than the pivot), we have have already found the index where pivot element is to be placed, i.e., j. Also, if j=i or j=i-1, arr[i] is meant to be greater than the pivot element and arr[j] is meant to be less than or equal to the pivot element, thus the order is already correct.
        if(i<j)
        {
            // Swapping arr[i] and arr[j] so that, by the end of this function, we find that partition_index and place the pivot element there. Swapping these anomalous arr[i] and arr[j] values, will ensure that, by the end of this function, the elements present on the left side of the pivot would be less than or equal to it and the ones on the right side would be greater than it.
            temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
        
    } while(i < j);

    // Swap arr[low] and arr[j], here we must use arr[low] and not pivot as changing the value of pivot will have no effect on the array we intend to sort.
    // Here, we swap the pivot with jth element and not ith element since pivot is the leftmost element, which means the element we swap it with cannot be greater than the pivot (arr[i] is greater than the pivot except possibly in the case i==high).
    temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;

    return j;
}

void quick_sort(int arr[], int low, int high)
{
    if(high > low)
    {
        int partition_index = partition(arr, low, high);

        // printArray(arr, 11);
        quick_sort(arr, low, partition_index-1);    // sort left subarray
        quick_sort(arr, partition_index+1, high);   // sort right subarray
    }
}


int main()
{
    /*

        => Like Merge Sort, QuickSort is a Divide and Conquer algorithm. It picks an element as pivot and partitions the given array around the picked pivot. There are many different versions of quickSort that pick pivot in different ways. 
            -> Always pick first element as pivot (implemented below).
            -> Always pick last element as pivot.
            -> Pick a random element as pivot.
            -> Pick median as pivot.
        The key process in quickSort is partition(). Target of partitioning is, given an array and an element x of array as pivot, put x at its correct position in sorted array and put all smaller elements (smaller than x) before x, and put all greater elements (greater than x) after x. All this should be done in linear time.


        => The name "Quick Sort" comes from the fact that, quick sort is capable of sorting a list of data elements significantly faster (twice or thrice faster) than any of the common sorting algorithms.


        => EXAMPLE : Input Array = {3(p),7(i),2,9,0,-6,-6,56,34,89,23(j)}

            *** I quick_sort() Function Call ***
            -> {3(p),7[i],2,9,0,-6,-6,56,34,89,23(j)}
            -> {3(p),7[i],2,9,0,-6,-6,56,34,89(j),23}
            -> {3(p),7[i],2,9,0,-6,-6,56,34(j),89,23}
            -> {3(p),7[i],2,9,0,-6,-6,56(j),34,89,23}
            -> {3(p),7[i],2,9,0,-6,-6[j],56,34,89,23}
            -> {3(p),-6(i),2,9,0,-6,7(j),56,34,89,23}
            -> {3(p),-6,2(i),9,0,-6,7(j),56,34,89,23}
            -> {3(p),-6,2,9[i],0,-6,7(j),56,34,89,23}
            -> {3(p),-6,2,9[i],0,-6[j],7,56,34,89,23}
            -> {3(p),-6,2,-6(i),0,9(j),7,56,34,89,23}
            -> {3(p),-6,2,-6,0(i),9(j),7,56,34,89,23}
            -> {3(p),-6,2,-6,0,9[i](j),7,56,34,89,23}
            -> {3(p),-6,2,-6,0[j],9[i],7,56,34,89,23}
            -> {0(p),-6,2,-6,3{partition_index=j},9[i],7,56,34,89,23}

            *** II quick_sort() Function Call ***
            -> {0(p),-6(i),2,-6(j)} {3}[sorted] {9,7,56,34,89,23}
            -> {0(p),-6,2[i],-6(j)} {3}[sorted] {9,7,56,34,89,23}
            -> {0(p),-6,2[i],-6[j]} {3}[sorted] {9,7,56,34,89,23}
            -> {0(p),-6,-6(i),2(j)} {3}[sorted] {9,7,56,34,89,23}
            -> {0(p),-6,-6,2[i](j)} {3}[sorted] {9,7,56,34,89,23}
            -> {0(p),-6,-6[j],2[i]} {3}[sorted] {9,7,56,34,89,23}
            -> {-6(p),-6,0{partition_index=j},2[i]} {3}[sorted] {9,7,56,34,89,23}

            *** III quick_sort() Function Call ***
            -> {-6(p),-6(i)(j)} {0}[sorted] {2} {3}[sorted] {9,7,56,34,89,23}
            -> {-6(p),-6[i](j)} {0}[sorted] {2} {3}[sorted] {9,7,56,34,89,23}
            -> {-6(p),-6[i][j]} {0}[sorted] {2} {3}[sorted] {9,7,56,34,89,23}
            -> {-6(p),-6[i][j]} {0}[sorted] {2} {3}[sorted] {9,7,56,34,89,23}
            -> {-6(p),-6[i]{partition_index=j}} {0}[sorted] {2} {3}[sorted] {9,7,56,34,89,23}

            *** IV quick_sort() Function Call ***
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2} {3}[sorted] {9,7,56,34,89,23}

            *** V quick_sort() Function Call ***
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {9,7,56,34,89,23}

            *** VI quick_sort() Function Call ***
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {9(p),7(i),56,34,89,23(j)}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {9(p),7,56[i],34,89,23(j)}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {9(p),7,56[i],34,89(j),23}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {9(p),7,56[i],34(j),89,23}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {9(p),7,56[i](j),34,89,23}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {9(p),7[j],56[i],34,89,23}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7(p),9{partition_index=j},56[i],34,89,23}

            *** VII quick_sort() Function Call ***
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7}[sorted] {9}[sorted] {56(p),34(i),89,23(j)}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7}[sorted] {9}[sorted] {56(p),34,89[i],23(j)}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7}[sorted] {9}[sorted] {56(p),34,89[i],23[j]}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7}[sorted] {9}[sorted] {56(p),34,23(i),89(j)}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7}[sorted] {9}[sorted] {56(p),34,23,89[i](j)}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7}[sorted] {9}[sorted] {56(p),34,23[j],89[i]}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7}[sorted] {9}[sorted] {23(p),34,56[partition_index=j],89[i]}

            *** VIII quick_sort() Function Call ***
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7}[sorted] {9}[sorted] {23(p),34(i)(j)} {56}[sorted] {89}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7}[sorted] {9}[sorted] {23(p),34[i](j)} {56}[sorted] {89}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7}[sorted] {9}[sorted] {23(p)[j],34[i]} {56}[sorted] {89}
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7}[sorted] {9}[sorted] {23(p)[partition_index=j],34[i]} {56}[sorted] {89}

            *** IX quick_sort() Function Call ***
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7}[sorted] {9}[sorted] {23}sorted] {34}[sorted] {56}[sorted] {89}

            *** X quick_sort() Function Call ***
            -> {-6}[sorted] {-6}[sorted] {0}[sorted] {2}[sorted] {3}[sorted] {7}[sorted] {9}[sorted] {23}sorted] {34}[sorted] {56}[sorted] {89}[sorted]
        

        => TIME COMPLEXITY :-
            -> PARTITIONING ALGORITHM: We traverse the array/subarray once making the comparisons until i and j cross every time partition() function is called. Thus, the number of comparisons is going to be some linear function of n, f(n) = k₁*n + k₂.

            -> WORST CASE:  # Worst case will be when the array is already sorted/reverse sorted.
                            # For a sorted array, partioning will need to be done (n-1) times.
                            # Ex: 2(p) 4[i] 7 17 20 21 25(j) -----> 2(p)[j] 4[i] 7 17 20 21 25
                                  2[s] 4(p) 7[i] 17 20 21 25(j) -----> 2[s] 4(p)[j] 7[i] 17 20 21 25
                                  2[s] 4[s] 7(p) 17[i] 20 21 25(j) -----> 2[s] 4[s] 7(p)[j] 17[i] 20 21 25
                                  2[s] 4[s] 7[s] 17(p) 20[i] 21 25(j) -----> 2[s] 4[s] 7[s] 17(p)[j] 20[i] 21 25
                                  2[s] 4[s] 7[s] 17[s] 20(p) 21[i] 25(j) -----> 2[s] 4[s] 7[s] 17[s] 20(p)[j] 21[i] 25
                                  2[s] 4[s] 7[s] 17[s] 20[s] 21(p) 25[i](j) -----> 2[s] 4[s] 7[s] 17[s] 20[s] 21(p)[j] 25[i]
                                  2[s] 4[s] 7[s] 17[s] 20[s] 21(p) 25[i](j) -----> 2[s] 4[s] 7[s] 17[s] 20[s] 21(p)[j] 25[i]
                                  ~ Since low == high, the algo terminates for 25 : 2[s] 4[s] 7[s] 17[s] 20[s] 21[s] 25
                                  ~ Thus, number of partioning calls = n-1 for a sorted array.
                                  * p -> pivot, s -> sorted.
                                
                            # Thus, Time Complexity = (n-1)*(k₁*n+k₂) = O(n²).

            -> BEST CASE:   # Best case will be when the pivot always comes out to be the middle element.
                            # Partioning will need to be done log₂n times in this case.]                               ___
                            # Ex1: 7 elements                   Ex2:        16 elements             2⁰ * T(n)             |
                                  /          \                             /           \                                  |
                                 3            3                           7             8           2¹ * T(n/2¹)          |        T(x) represents
                               /   \        /   \                       /   \         /   \                               |--- partitioning time for an
                              1     1      1     1                     3     3       3     4        2² * T(n/2²)          |       array of length x
                                                                      / \   / \     / \   / \                             |
                                                                     1   1 1   1   1   1 1   2       T(2)              ___|
                                                                                             |                            
                                                                                             1

                            # Thus, Time Complexity ~ (1)*(k₁*n+k₂) + (2)*(k₁*(n/2)+k₂) + (4)*(k₁*(n/4)+k₂) + ... (until n/2 = 1 => k = log₂n times)
                                                    ~ (k₁n + k₁n + k₁n + ... k₁n) {log₂n times}  +  k₂*(1+2+4+...+n) {log₂n times}
                                                    ~ k₁n * log₂n  +  k₂ * 1(2ˡᵒᵍ₂ⁿ - 1)/(2-1)
                                                    ~ k₁n * log₂n  +  k₂ * (n-1)/(1)
                                                    ~ k₁(n*log₂n)  +  k₂*(n) - k₂
                                                    ~ O(n*log₂n)

            -> AVERAGE CASE: O(n*log₂n)


        => ADAPTIVE :-
            NOT ADAPTIVE (worst case is when array is already sorted).


        => STABILITY :-
            NOT STABLE (bcoz arr[j] is swapped when arr[j] == pivot).

        
        => IN PLACE/OUT OF PLACE ALGORITHM :-
            In place as it takes no auxiliary space.


    */

    // int arr[] = {3, 5, 2, 13, 12, 3, 2, 13, 45};
    int arr[] = {3,7,2,9,0,-6,-6,56,34,89,23};
    int n = sizeof(arr)/sizeof(arr[0]);

    quick_sort(arr, 0, n-1);
    printArray(arr, n);

    return 0;
}