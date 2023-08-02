#include<iostream>

using namespace std;

bool powerOf2(int n)
{
    return (n!=0) & !(n&(n-1));
        // For a number to be a power of 2, there should be exactly one set bit since the only powers of 2 are 1, 2, 4, 8, 16, 32, ..., i.e., the values that the different bits hold.
        // If n=0, then return false.
        // If n!=0, but n&(n-1) can't make the number 0 in just one attempt, then that means there're more than 1 set bits.
        // Thus, return true only when n!=0 and n&(n-1)==0.
}

int main()
{
    // For numbers >= 0
    cout<< powerOf2(17);
    cout<< powerOf2(34);
    cout<< powerOf2(10);
    cout<< powerOf2(8);
    cout<< powerOf2(1);     // 1 is also power of 2 [2⁰=1]
    cout<< powerOf2(64);

    return 0;
}