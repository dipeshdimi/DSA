#include<iostream>

using namespace std;

int main()
{
    // In an array, each number appears even number of times except one. Find the odd occuring number.
        int arr1[] = {1,4,2,1,4,4,2,2,2};
        int ans=arr1[0];
        for(int i=1; i<sizeof(arr1)/sizeof(arr1[0]); i++)
            ans = ans^arr1[i];
                // Since x^x=0 and x^(y^z)=(x^y)^z, all the even occuring elements would cancel each other out and just the odd occuring element would remain.
        cout<<ans<<"  ";


    // In an array of size (n-m), elements range from m to n and no element is repeated. Find the number that belongs to the range m to n, but doesn't appear in the array.
        int m=2, n=6;
        int arr2[n-m] = {2,5,6,4};
        ans = m^arr2[0];
        for(int i=1; i<n-m; i++)
            ans = ans^(m+i)^arr2[i];
                // Only the element in range m to n, and not present in the array would be left without an equal pair (since x^x=0 and x^(y^z)=(x^y)^z), thus the answer.
        ans ^= n;   // Array size = n-m, range size = n-m+1, so would need to add the i=n-m case manually.

        cout<<ans<<"\n";

    return 0;
}