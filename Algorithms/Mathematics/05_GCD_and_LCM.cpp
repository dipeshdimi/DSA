#include<iostream>

using namespace std;

int GCD_Naive(int a, int b)
{
    int GCD = min(a,b);
    while(GCD > 0)
    {
        if(a%GCD==0 && b%GCD==0)
            return GCD;
        else
            GCD--;
    }
    return GCD;
}

int GCD_Euclid(int a, int b)
{
    if(a==0 || b==0)
        return max(a,b);
    else
        return GCD_Euclid(b, a%b);
        // (b,a%b) and not (a%b,b) to ensure for every recursive call, the first element remains greater than the second one. This is bcoz, if the first element is smaller than the second one, we will get stuck in an infinte recursion. In case of a>b when this function is called in main(), inputs for the first recursive call would (b,a%b) [b > a%b] and even in case of a<b when this function is called in main(), inputs for the first recursive call would be (b,a%b) [b>a%b]. If we had used (a%b,b) instead, in case of a>b, our input parameters will become first<second remain that way and in case a<b, our input parameters will remain as it is throughout i.e., first<second.

        /* Euclid's Theorem: gcd(a,b) = gcd(b,r)    [r = remainder(a/b) = a%b]
           Proof:   a = bq+r    ...(1)
                    {NOTE: x|y => x divides y}
                    Let d be any common divisor of (a,b). Then,
                        d|a and d|b => d|a and d|bq => d|(a-bq) => d|r  (from (1))

                    Let e be any common divisor of (b,r). Then,
                        e|b and e|r => e|bq and e|r => e|(bq+r) => e|a  (from (1))
                    
                    Thus, any common divisor of a and b must also be a common divisor of r and any common divisor of b and r must also be a common divisor of a. Hence, the set of common divisors of a & b must always be the same as the set of common divisors and b and r. And among these common divisors, there will a GCD (shared by both (a,b) as well as (b,r)), i.e., gcd(a,b) = gcd(b,r).
        */
}

int LCM(int a, int b)
{
    return (a*b)/GCD_Euclid(a,b);
}


int main()
{
    int a, b;
    cin>>a>>b;

    /* NOTE: Finding GCD of two numbers and b is like finding the largest square that can fill the entire region :-
           | 1 | 2 | 3 | 4 |...| a |
        ___|___|___|___|___|___|___|
         1 |   |   |   |   |   |   |
        ___|___|___|___|___|___|___|
         2 |   |   |   |   |   |   |
        ___|___|___|___|___|___|___|
         3 |   |   |   |   |   |   |
        ___|___|___|___|___|___|___|
         . |   |   |   |   |   |   |
        ___|___|___|___|___|___|___|
         . |   |   |   |   |   |   |
        ___|___|___|___|___|___|___|
         . |   |   |   |   |   |   |
        ___|___|___|___|___|___|___|
         b |   |   |   |   |   |   |
        ___|___|___|___|___|___|___|
*/

    cout<<GCD_Naive(a,b)<<"\n";
    // O(min(a,b))

    cout<<GCD_Euclid(a,b)<<"\n";
    // ~ O(log(min(a,b)))   [Approximation of a complex mathematical problem]

    cout<<LCM(a,b)<<"\n";
    // Same as GCD

    return 0;
}