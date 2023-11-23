/*
    => DYNAMIC PROGRAMMING (DP)
        -> Optimization over plain recursion.
        -> The idea is to reuse the solutions of overlapping subproblems.
        -> Two ways to implement DP :-
            (i) Memoization (Top Down Approach)
            (ii) Tabulation (Bottom Up Approach)
*/

/*
    => MEMOIZATION (TOP DOWN APPROACH)
        -> The memoized program for a problem is similar to the recursive version with a small modification that it looks into a lookup table before computing solutions. Whenever we need the solution to a subproblem, we first look into the lookup table. If the precomputed value is there then we return that value, otherwise, we calculate the value and put the result in the lookup table so that it can be reused later.

        -> We initialize a lookup table with all initial values as NIL, i.e., a value that the parameter would never take.

        -> Dimensions of lookup table = No. of problem parameters 
            [e.g., if there is just one parameter, we just need a list, or if there are two parameters, we would need to store the result of each subproblem in a matrix i.e., each subproblem is a specific version of our original problem, here, specific version implying a particular value(s) of parameter(s)]

        -> Size of lookup table in a particular dimension = Range of the parameter value corresponding to that dimension

        -> Ex: In fibonacci numbers program, we calculate f(n)=f(n-1)+f(n-2), in each step. As we go further down though, we can notice that we're solving the same subproblem multiple times as f(n-1)=f(n-2)+f(n-3), i.e., calculating f(n-2) twice in just these two steps. To avoid this, we could store each value we calculate in an array and just refer to that array for already solved subproblems.

        ->                    f(5)                                      f(5)
                            /      \                                   /    \
                        f(4)         f(3)                            f(4)   f(3)
                       /    \        /   \                          /    \
                    f(3)   f(2)     f(2)  f(1)    ----->           f(3)   f(2)
                   / \     /  \      / \                          /  \
               f(2) f(1) f(1) f(0) f(1) f(0)                   f(2)   f(1)
               /  \                                            /  \
            f(1)  f(0)                                      f(1)  f(0)
                [Exponential Complexity]                        [Linear Complexity]
*/

/*
    => TABULTION [BOTTOM UP APPROACH]
        -> The tabulated program for a given problem builds a table in bottom up fashion and returns the last entry from table. For example, for the same Fibonacci number, we first calculate fib(0) then fib(1) then fib(2) then fib(3) and so on.
        -> Ease of Implementation   :   Memoization
                Optimality          :   Tabulation      [Coz no recursion]
*/

#include<iostream>

using namespace std;

const int n=5;
int mem[n+1] = {-1,-1,-1,-1,-1,-1};    // Initializing with -1 bcoz the parameter (n) can only be in the range [0,n].

int fibMem(int n)
{
    if(mem[n]==-1)
    {
        if(n==0 || n==1)
            mem[n] = n;
        else
            mem[n] = fibMem(n-1) + fibMem(n-2);
    }
    return mem[n];
}

int fibTab(int n)
{
    int tab[n+1];
    tab[0]=0, tab[1]=1;
    for(int i=2; i<=n; i++)
        tab[i] = tab[i-1]+tab[i-2];     // We just need to make sure, each time we calculate this, tab[i-1] and tab[i-2] are already known.
    
    return tab[n];
}

int main()
{
    // fib(0)=0, fib(1)=1, f(n)=?
    cout<<fibMem(n)<<"\n";
    cout<<fibTab(n)<<"\n";
    return 0;
}

