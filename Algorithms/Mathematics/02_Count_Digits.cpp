#include<iostream>
#include<cmath>

using namespace std;

int Count_Digit_Iterative(int n)
{
    int count = 0;
    while(n!=0)
    {
        n=n/10;
        count++;
    }
    return count;
}

int Count_Digit_Recursive(int n)
{
    if(n==0)
        return 0;
    else
        return Count_Digit_Recursive(n/10)+1;
}

int Count_Digit_Log(int n)
{
    return floor(log10(n)+1);
    // log10(1<=n<10) = [0,1)       =>  floor(log10(1<=n<10)) = 0       [No. of digits - 1]
    // log10(10<=n<100) = [1,2)     =>  floor(log10(10<=n<100)) = 1     [No. of digits - 1]
    // log10(100<=n<1000) = [2,3)   =>  floor(log10(100<=n<1000)) = 2   [No. of digits - 1]
    // ...
}


int main()
{
    int n = 393821;     // n>0
    cout<<Count_Digit_Iterative(n)<<"\t";
    cout<<Count_Digit_Recursive(n)<<"\t";
    cout<<Count_Digit_Log(n)<<"\t";

    return 0;
}