#include<iostream>

using namespace std;

int factorial_iterative(int n)
{
    int fact = n;
    for(int i=1; i<n-1; i++)
    {
        fact = fact*(n-i);
    }
    return fact;
}

int factorial_recursive(int n)
{
    if(n==1)
        return 1;
    else
        return n*factorial_recursive(n-1);
    
    // T(n) = T(n-1) + θ(1) = θ(n)
}

int trailingZeroes(int N)
{
    int count = 0;
    while(N>=5)
    {
        count = count + N/5;
        N = N/5;                // Basically n/5 + n/25 + n/125 + ...
    }
    // OR   for(int i=5; i<=N; i*=5)
    //          count = count + N/i;
    return count;
}


int main()
{
    int n;
    cin>>n;

    cout<<factorial_iterative(n)<<"\n";
    cout<<factorial_recursive(n)<<"\n";
    

    // TRAILING ZEROES IN FACTORIAL in O(log₅n) time
    cin>>n;
    cout<<trailingZeroes(n);

    return 0;
}