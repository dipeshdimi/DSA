#include<iostream>

using namespace std;

void printArray(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        cout<<arr[i]<<"->";
    }
    cout<<"\n";
}

void Counting_Sort_Stable(int arr[], int n, int exp)
{
    int b=10;
    int count[b];
        // b represents the base of the number sorted
        // Here, we are sorting decimal numbers (base 10)
        // For sorting binary numbers -> b=2, octal -> b=8, hexadecimal -> b=16,...

    for (int i = 0; i < b; i++)
        count[i] = 0;
    
    for (int i = 0; i < n; i++)
        count[(arr[i]/exp)%10]++;   // ***
    
    for (int i = 1; i < b; i++)
        count[i] = count[i] + count[i-1];
    
    int output[n];
    for (int i = n-1; i >= 0; i--)
    {
        output[count[(arr[i]/exp)%10] - 1] = arr[i];        //***
        count[(arr[i]/exp)%10]--;                           //***
    }
    
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
    
    /* *** Here we wish to sort the array based on a particular digit and not based on the whole number, thus, we replace the number with digit in the sorting algorithms (we are basically sorting these digits):-
        arr[i] -> Number (e.g., 319)
        arr[i]/exp -> Each subsequent exp rids the number of a digit (e.g., exp=1 => 319, exp=10 => 31, exp=100 => 3)
        (arr[i]/exp)%10 -> Each subsequent exp moves this from LSD to MSD (e.g., 9, 1, 3)
    */
}

void Radix_Sort(int arr[], int n)
{
    // We find max to find the number with max no. of digits
    int max = arr[0];
    for (int i = 0; i < n; i++)
    {
        if(arr[i] > max)
            max = arr[i];
    }
    
    for (int exp = 1; max/exp > 0; exp = exp*10)
        Counting_Sort_Stable(arr, n, exp);
    // exp = 10ᵏ [initialised with 10⁰ and updated as a multiple of 10]
    // max/exp > 0 -> No. of times it holds true = No. of digits => Sorting done for each digit from LSD to MSD
    // Counting_Sort(arr, n, 1)
    // Counting_Sort(arr, n, 10)
    // Counting_Sort(arr, n, 100)
    // Loop breaks for exp = 1000 as max/exp = 319/1000 = 0 (both int, thus truncation of 0.319 to integer 0).
}

int main()
{
    int arr[] = {319, 212, 6, 8, 100, 50};
    int n = sizeof(arr)/sizeof(arr[0]);
/*
    1) Rewrite numbers with leading zeroes.
        => {319, 212, 006, 008, 100, 050}

    2) Stable Count Sort w.r.t last digit (least significant digit)
        => {100, 050, 212, 006, 008, 319}
    
    3) Stable Count Sort w.r.t middle digit(s) sequentially
        => {100, 006, 008, 212, 319, 050}
    
    4) Stable Count Sort w.r.t first digit (most significant digit)
        => {006, 008, 050, 100, 212, 319}
    
    NOTE: Stable Sorting is pivotal here as in case, for two numbers, all the succeeding digits (e.g., MSD and middle digits) are equal, and we have arranged them in descending order according to the preceeding digits (e.g., LSD), that order will need to be maintained.
    Ex: ARRAY[] = {..., 0246, ..., 0249, ...}
        Stable Sorting w.r.t LSD -> {..., 0246, 0249, ...}
        Stable Sorting w.r.t Middle digits and MSD -> {..., 0246, 0249, ...}        [CORRECT]
        Unstable Sorting w.r.t Middle digits and MSD -> {..., 0249, 0246, ...}      [INCORRECT]
*/

    Radix_Sort(arr, n);
    printArray(arr, n);

/*
    =>  TIME COMPLEXITY
        -> Counting_Sort_Stable() : Θ(n+b)
        -> Radix_Sort() : Θ(n) + Θ(d*(n+b)) = Θ(d*(n+b))
            [Θ(n) for finding max & Θ(d*(n+b)) since the Counting_Sort_Stable() executes d no. of times (d is the number of digits = log𝔟(max))]
    
    => AUXILIARY SPACE
        -> Θ(n+b)       { output[n] & count[b] }
    
    => TIME vs SPACE TRADE-OFF
        -> Lower the base, the more the number of digits required for writing the number (e.g., 1010 [b=2] = 10[b=2]). Thus, 
            b ∝ 1/d
        -> Since d is a multiplication term unlike b in the time complexity expression Θ(d*(n+b)), d has more weightage in the time complexity expression than b. A change in d will affect the time complexity more than a change in b. Thus, if we decrease b, d will increase and overall, time complexity will increase.
        -> Since Auxiliary Space expression is Θ(n+b), it will decrease if we decrease b (more space required for count[b] array).
        -> Auxiliary Space ∝ b ∝ 1/d ∝ TIme Complexity
    
    => Used only for positive elements.

    => Non-Comparison based Sorting Algo.
*/

    return 0;
}