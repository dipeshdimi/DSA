#include<iostream>
using namespace std;

void printArray(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d->", arr[i]);
    }
    printf("\n");
}

int Heap_Sort(int arr[], int n)
{
    
}

int main()
{
    int arr[] = {3,5,-5,5,0,9,23,1,5,3,7,-4,5};
    // -5->-4->0->1->3->3->5->5->5->5->7->9->23->
    int n = sizeof(arr)/sizeof(arr[0]);

    Heap_Sort(arr, n);
    printArray(arr, n);


    return 0;
}