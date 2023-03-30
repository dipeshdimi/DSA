#include<stdio.h>

void printArray(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d->", arr[i]);
    }
    printf("\n");
}

// UNSTABLE COUNT SORT
// Cannot be used as a general purpose algorithm for sorting objects with multiple members e.g., sorting an array of students by marks (???Cannot assign index to an array of objects???)
    void count_Sort_Unstable(int arr[], int n)
    {
        // Finding the max element in the given array arr[]
            int max = arr[0];
            for (int i = 1; i < n; i++)
            {
                if(arr[i]>max)
                    max = arr[i];
            }
            // printf("%d\n", max);

        // Declaring & initialsing count[] with 0 (count[] array stores the number of times an element occurs (frequency of occurence of an element) in arr[])
            int count[max+1];
            for (int i = 0; i < max+1; i++)
                count[i] = 0;
                // OR
            // int *count = (int*)calloc(max+1, sizeof(int));      // Since calloc initialises all the elements with zero
            
        // Storing the frequency of each arr[] element in count[] with arr[] being corresponding to count[]'s index.
            for (int i = 0; i < n; i++)
                count[arr[i]]++;
            // printArray(count, max+1);

        // Now traverse through the count array, and look for the nonzero elements. The moment you find an index with some value other than zero, fill in the sorted array the index of the non-zero element until it becomes zero by decrementing it by 1 every time you fill it in the resultant array. And then move further. This way, you create a sorted array.
            int j=0;
            for (int i = 0; i < max+1; i++)
            {
                while(count[i] != 0)
                {
                    arr[j] = i;
                    j++;
                    count[i]--;
                }
            }
    // TIME COMPLEXITY -> O(n+max)
    // Auxiliary Space -> O(max)        {count[max+1]}
    // STABILITY -> Unstable
    // ADAPTIVE -> Don't think so
    // IN PLACE/OUT OF PLACE -> Out of Place Sorting Algorithm
    // Count Sort can be used only when all the elements are non-negative since array indices cannot be negative due to which it would be impossible to store the frequencyof negative elements in count[] array.
    }


// STABLE COUNT SORT (Generalizes the algorithm to operate on objects that may differ but compare as equal)
// General Purpose Algorithm
    void count_Sort_Stable(int arr[], int n)
    {
        int max=arr[0];
        for (int i = 0; i < n; i++)
        {
            if(arr[i]>max)
                max = arr[i];
        }

        int count[max+1];
        for (int i = 0; i < max+1; i++)
            count[i] = 0;
        
        for (int i = 0; i < n; i++)
            count[arr[i]]++;
        
        for (int i = 1; i < max+1; i++)
            count[i] = count[i] + count[i-1];
            // => Frequency to Cumulative Frequency
            // => count[i] will represent the number of elements <= i
            // => count[i] will represent the correct position (count[i]-1 will represent the index) of element i in the sorted array (applicable only for the elements present in the given array, for all other i which are not an element in the given aray, count[i] will just remain 0 {Note: Min element in arr[] (first occuring min element in case of multiple min elements), let arr[min], will also have count[i] = count[arr[min]] = 0})
            // => If an elements occurs multiple times, count[i] will represent the rightmost position of the stretch in which those equal elements would lie in the sorted array.
        
        int output[n];
        for (int i=n-1; i>=0; i--)
            // Since count[i] represents the rightmost position of the stretch of an element and since we are placing elements in the output array starting with the rightmost position of the stretch (output[count[arr[i]] - 1] = arr[i];     count[arr[i]]--;), if we start placing elements from the end of the array, the output will be stable.
            // if we use i++ loop, the algo will be reverse stable
        {
            output[count[arr[i]] - 1] = arr[i];
                // arr[i] -> Element to be placed
                // count[arr[i]] -> Correct position of the element in the sorted array
                // count[arr[i]] - 1 -> Correct index of the element in the sorted array
                // output[count[arr[i]] - 1] = arr[i] -> Placing element to be placed (arr[i]) at its correct index in the ouutput array
            count[arr[i]]--;
                // Reducing count[arr[i]] by 1 so that the next time its equal element is encountered, it is placed just next to the previous one (left adjacent of the previous one's sorted index)
        }

        for (int i = 0; i < n; i++)
            arr[i] = output[i];
    
    // TIME COMPLEXITY -> O(n+max)
    // Auxiliary Space -> O(n+max)      {output[n] and count[max+1]}
    // STABILITY -> Stable
    // ADAPTIVE -> Don't think so
    // IN PLACE/OUT OF PLACE -> Out of Place Sorting Algorithm
    // Count Sort can be used only when all the elements are non-negative since array indices cannot be negative due to which it would be impossible to store the frequencyof negative elements in count[] array.
    }


// Stable Counting Sort which takes NEGATIVE numbers as well
// The problem with the previous counting sort was that we could not sort the elements if we have negative numbers in it because there are no negative array indices. So what we do is, we find the minimum element and we will store the count of that minimum element at zero index.
    void count_Sort_Stable_Negative(int arr[], int n)
    {
        int max=arr[0], min=arr[0];
        for (int i = 0; i < n; i++)
        {
            if(arr[i] > max)
                max = arr[i];
            else if (arr[i] < min)
                min = arr[i];
        }

        int count[max-min+1];   // If a negative element is the minimum element, max-min > max
        for (int i = 0; i < max-min+1; i++)
            count[i] = 0;
        
        for (int i = 0; i < n; i++)
            count[arr[i] - min]++;      // Count of minimum element at zero index
        
        for (int i = 1; i < max-min+1; i++)
            count[i] = count[i] + count[i-1];

        int output[n];
        for (int i = n-1; i >= 0; i--)
        {
            output[count[arr[i]-min] - 1] = arr[i];     // Count of minimum element at zero index
            count[arr[i] - min]--;      // Count of that minimum element at zero index
        }

        for (int i = 0; i < n; i++)
            arr[i] = output[i];
    }


int main()
{
    int arr_unstable[] = {3, 5, 0, 22, 9, 17, 7, 0, 1, 5, 5, 22, 3, 2};
    int n_unstable = sizeof(arr_unstable)/sizeof(arr_unstable[0]);
    count_Sort_Unstable(arr_unstable, n_unstable);
    printArray(arr_unstable, n_unstable);

    int arr_stable[] = {3, 5, 0, 22, 9, 17, 7, 0, 1, 5, 5, 22, 3, 2};
    int n_stable = sizeof(arr_stable)/sizeof(arr_stable[0]);
    count_Sort_Stable(arr_stable, n_stable);
    printArray(arr_stable, n_stable);

    int arr_stable_negative[] = {3, -5, 0, -22, 9, 17, -7, 0, 1, 5, 5, -22, 3, -2};
    int n_stable_negative = sizeof(arr_stable_negative)/sizeof(arr_stable_negative[0]);
    count_Sort_Stable_Negative(arr_stable_negative, n_stable_negative);
    printArray(arr_stable_negative, n_stable_negative);

/*
    => Efficient only if the range of input data is not significantly greater than the number of objects to be sorted.
    => Not a Comparison-based Sorting Algo.
    => Often used as a sub-routine to another sorting algorithm like radix sort. 
    => ???Counting sort uses partial hashing to count the occurrence of the data object in O(1)???
*/

    return 0;
}

/*
    NOTE 1: for(int i = 0; a[i]; i++) -> Loop keeps executing until a null element is found
    NOTE 2: memset(arr, 0, sizeof(arr)); -> All elements of arr[] are zero
            memset(arr, -1, sizeof(arr)); -> All elements of arr[] are -1
            [https://www.geeksforgeeks.org/memset-in-cpp/]
*/