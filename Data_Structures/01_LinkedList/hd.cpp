#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main()
{
    int n = 5;
    // cin>>n;

    // int arr[] = {1,4,2,6,9};
    // int arr[] = {5,4,3,2,1};
    int arr[] = {1,2,3,4,5};
    // for(int i=0; i<n; i++)
    //     cin>>arr[i];
    
    int res=n;
    int sum=0;
    int i=1;
    while(i<n)
    {

        if(arr[i] < arr[i-1])
        {
            int j=i;
            while(sum < arr[j-1])
            {
                sum += arr[i];
                i++;
                j++;
                res--;
            }
        }
        else
            i++;
    }

    cout<<res;

    return 0;
}