#include<iostream>

using namespace std;

struct node
{
    int data;
    struct node*next;
};

void Bucket_LL(int arr[], int n, int k)
{
    
}

void Bucket_Vector(int arr[], int n, int k)
{
    int min = arr[0], max = arr[0];
    for (int i = 0; i < n; i++)
    {
        if(arr[i] > max)
            max = arr[i];
        else if (arr[i] < min)
            min = arr[i];        
    }

    int range = max-min;
    int common_difference = range/k;
    int bucket_index;

    for (int i = 0; i < n; i++)
    {
        bucket_index = (arr[i]-min)/common_difference;
        
    }
}

int main()
{
    int arr_LL[] = {3,5,-5,5,0,9,23,1,5,3,7,-4,5};
    int n_LL = sizeof(arr_LL)/sizeof(arr_LL[0]);
    
    int arr_vector[] = {3,5,-5,5,0,9,23,1,5,3,7,-4,5};
    int n_vector = sizeof(arr_vector)/sizeof(arr_vector[0]);

    /*
        => Uniform distribution of integers 0 to max (max<=2147483647)
            ->  bucket_index = (k*arr[i])/(max+1);
                bucket[bucket_index] = arr[i];

            ->  min assumed to be zero

            ->  Buckets: [0 - _], [_ - _], ..., [_ - max]
        

        => Uniform distribution of integers min to max (min>=0 and max<=2147483647)
            ->  range = max-min;
                [range is the difference between the max possible element of the last bucket (also the max element of the given array) and the minimum possible element of the first bucket (also the max element of the given array)]
            
            ->  common_diff = range/k
                    [k = no. of buckets]
                    [common difference is the size of each bucket]
            
            ->  bucket_index = (arr[i]-min)/common_diff;
                bucket[bucket_index] = arr[i];

        
        => Uniform distribution of floating point numbers in range [0, 1.0)
            ->  bucket_index = n*arr[i];
                bucket[bucket_index] = arr[i];
        

        => Won't work for negative elements as bucket_index would be -ve for -ve arr[i] and bucket[bi] can't have -ve indices.
    */

    return 0;
}