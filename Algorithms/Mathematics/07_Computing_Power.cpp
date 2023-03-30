#include<iostream>

using namespace std;

int Computing_Power_Recursive(int x, int N)
{
    if(N==1)
        return x;   // Base case when x¹ is to be returned
    else if(N%2==0)
        return Computing_Power_Recursive(x, N/2) * Computing_Power_Recursive(x, N/2);   // Since xᴺ = xᴺ/² * xᴺ/²
    else
        return Computing_Power_Recursive(x, N-1) * x;     // Turn odd power into even
    
    // TIME COMPLEXITY: O(Height of binary tree) = O(log₂N)
    // We could've used if(N==0) return 1; in place of if(N==1) return x; if we wanted to include the calculation for power 0.
    // (a+b) % n = (a%n + b%n) % n      [True for - and * too, but not for /]
    // a^b = (a^2)^(b/2)
    // a^b = a*a^(b-1)
}

int Computing_Power_Iterative(int x, int N)
{
    while(N!=1)
    {
        
    }
}


int main()
{
    int x, N;
    cout<<"Base = ";
    cin>>x;
    cout<<"Power = ";
    cin>>N;
    cout<<"x^N (Recursive Approach) = "<<Computing_Power_Recursive(x, N)<<"\n";
    cout<<"x^N (Iterative Approach) = "<<Computing_Power_Iterative(x, N)<<"\n";

    return 0;
}