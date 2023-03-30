#include<iostream>
#include<vector>

using namespace std;


bool prime_naive(int n)
{
    if(n==1)
        return false;
    
    for (int i = 2; i < n; i++)
    {
        if(n%i == 0)
            return false;
    }
    return true;
    
}


bool prime_root(int n)
{
    if(n==1)
        return false;
    
    /* => For any non-prime number n, it must have two factors, 1<(a,b)<n where a and b may or may not be equal (perfect square in case of both factors being equal).
       => Let a<=b. Then,   -> a*b = n
                            -> a*a <= n
                            -> a <= √n.
        => Thus, if a number is non-prime, we will reach its factor by the time we traverse till √n).
    */
    for (int i = 2; i*i <= n; i++)
    {
        if(n%i == 0)
            return false;
    }
    return true;
}


vector<int>AllPrimeFactors(int N) {
	    vector <int> v;
	    
	    for(int i=2; i*i<=N; i++)
	    {
	        if(N%i == 0)
	            v.push_back(i);
	        
	        while(N%i == 0 && N!=1)
	            N/=i;
	    }
	    if(N>1)
	        v.push_back(N);
	   /* 1) Find the first prime factor.
	      2) Divide the number with that first prime factor.
	      3) Find the first prime for the newly obtained no. and keep repeating the same process.
	      4) Once we reach √N, whatever will be left of N would either be 1 (in case of perfect squares, i.e., when both first and second factors are equal) or the second prime factor of the number whose first prime factor we found out in the last iteration.
	   */
	   /* Time Complexity :-
	          Worst case will be when N is prime and thus, will not undergo N=N/i due to which the for loop will run √N times.
	          Thus, Time Complxity will be O(√N)   [Worst Case]
	   */
	    return v;
	}


void AllDivisors(int n)
{
    /*
        => For any divisor i of n, there will be a corresponding divisor, n/i of n such that i*(n/i) = n.
        => We first find the first divisor which would lie in range (1,√n] and then the second divisor of the pair which would lie range [√n, n).
        => In case of perfect square, both i and n/i will be equal and thus should be printed only once.
    */

    cout<<"DIVISORS IN UNSORTED ORDER:  ";
    for(int i=1; i*i<=n; i++)
    {
        if(n%i == 0)
        {
            cout<<i<<"  ";

            if(i != n/i)
                cout<<n/i<<"  ";
        }
    }
    cout<<"\n";

    cout<<"DIVISORS IN SORTED ORDER:    ";
    int i;
    // Prints divisors in range [1, √n)
    for(i=1; i*i<n; i++)
    {
        if(n%i == 0)
            cout<<i<<"  ";
    }
    // Prints divisors in range [√n, n]
    for(    ; i*i>=1; i--)
    {
        if(n%i == 0)
            cout<<n/i<<"  ";
    }
    cout<<"\n";
}


vector <bool> Sieve_of_Eratosthenes_1(int n)
{
    // p is the vector that stores prime indices as true and composite ones as false.
    // We initialise this vector as true for every index.
    // We iterate through the vector and assign every non-prime index the value 'false'.
    // Indices 0 and 1 remain true throughout the algorithm but we start considering the candidates for prime no from 2, so they don't matter.
    vector <bool> p(n+1, true);
    /* We only need to iterate upto √n. This is because :-
        Let there be a number m beyond √n such that √n<m<n (we checked only upto √n, thus we have to make sure in case there is a number m > √n, it has already been crossed out as a multiple of its smaller factor), then it must have a smaller than √m factor (and one greater than √m factor), fₛₘₐₗₗₑᵣ < √m < √n. Since this fₛₘₐₗₗₑᵣ lies within √n, its multiple must already have benn crossed out from vector p. Thus, any non-prime no. m > √n would had already been crossed out (i.e., p[m] = false) by the time we traverse till √n and the non-crossed out no. (i.e., p[i] = true) would only be primes.
        https://math.stackexchange.com/questions/58799/why-in-sieve-of-erastothenes-of-n-number-you-need-to-check-and-cross-out-numbe
    */
    for(int i=2; i*i<=n; i++)
    {
        // Check if no. is primes
        if(p[i])
        {
            // We can also start with j=2*i as it would be the first multiple of i but that would be inefficient as we will be crossing out the same no. again and again (p[i]=false to p[i]= false). This is because any composite no. j < i*i would be of the form i*(i-1), i*(i-2), i*(i-3), ..., i.e., with a factor less than i (i-1, i-2, i-3, ...), thus, for a value of j<i*i, j would be a multiple of an already covered prime number (i in previous iterations). So, we need to start crossing out hte multiples of i starting from i*i only.
            // for(int j=2*i; j<=n; j+=i)
            for(int j=i*i; j<=n; j+=i)
                p[j] = false;
        }
    }
    return p;
}


void Sieve_of_Eratosthenes_2(int n)
{
    vector <bool> p(n+1, true);
    // Same thing, bs printing sath k sath kr rhe h, print krne k liye n tk chla diya, kuchh fark nhi pdega since √n k age wale primes ko already cross out kr diya gya h, agr √n k age koi prime hua to if(p[i]) true hokr print kr dega (inner for loop chlega nhi since agr i>√n h to j initialise > n se hoga jbki max j value n) aur composite hua to if(p[i]) condition false ho jaegi and outer for loop age bdh jaega
    for(int i=2; i<=n; i++)
    {
        if(p[i])
        {
            cout<<i<<"  ";
            for(int j=i*i; j<=n; j+=i)
                p[j] = false;
        }
    }
}



int main()
{
    int n;

    cin>>n;

    cout<<prime_naive(n)<<"\n";
    cout<<prime_root(n)<<"\n";

    vector<int> v = AllPrimeFactors(n);
    for(const auto &x:v)
        cout<<x<<"    ";
    cout<<endl;
    
    AllDivisors(n);

    vector<bool> p = Sieve_of_Eratosthenes_1(n);
    for(int i=2; i<=n; i++)
    {
        if(p[i])
            cout<<i<<"  ";
    }
    cout<<endl;

    Sieve_of_Eratosthenes_2(n);
    cout<<endl<<endl;

    // TIME COMPLEXITY OF SIEVE OF ERATOSTHENES : O(log(logn))  [for both functions]
    // Complex mathematical calculation
    // Very close to O(n)
    // Base of log doesn't matter here as https://math.stackexchange.com/a/1747690  [Base Independent]


    return 0;
}