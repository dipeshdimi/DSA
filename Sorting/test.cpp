#include <stdio.h>

void printArray(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void bubble(int arr[], int n)
{
    int temp;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
        
    }
    
}


void insertion(int A[], int n)
{
    int j, key;
    for (int i = 1; i < n; i++)
    {
        key = A[i];
        for (j=i-1; j>=0 && key < A[j]; j--)
        {
            A[j+1] = A[j];
        }
        A[j+1] = key;
    }
    
}


void selection(int A[], int n)
{
    int maxIndex, temp, j;
    for (int i = 0; i < n-1; i++)
    {
        maxIndex=0;
        for (j = 0; j < n-i-1; j++)     // n-i-1 since even if the last element in unsorted subarray is maximum, it won't need to be swapped.
        {
            if(A[j] > A[maxIndex])
                maxIndex = j;
                // printf("%d\t", A[maxIndex]);
        }
        printf("\n");
        temp = A[n-i-1];
        A[n-i-1] = A[maxIndex];
        A[maxIndex] = temp;
        // printArray(A, n);
    }
    
}



int main()
{
    int arr[] = {9, 4, 4, 8, 7, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    // bubble(arr, n);
    // printArray(arr, n);
    
    // insertion(arr, n);
    // printArray(arr, n);

    selection(arr, n);
    printArray(arr, n);

    // quickSort(arr, n);
    // printArray(arr, n);


    return 0;
}