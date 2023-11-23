#include<iostream>
#include<vector>

using namespace std;

int lcsRec(string s1, string s2, int m, int n)
{
    // One of the string is empty => Nothing common
    if(m==0 || n==0)
        return 0;
    
    // Character match => Ignore that character from both strings after adding its count (+1), and just find the lcs for the rest fo the substrings
    if(s1[m-1] == s2[n-1])
        return 1 + lcsRec(s1,s2,m-1,n-1);
    // Two options now - ignore the character from s1 and find lcs for s2 & rest of s1 OR ignore the character from s2 and find the lcs for s1 and rest of s2. We do both, at each step and choose the max output.
    else
        return max(lcsRec(s1,s2,m-1,n), lcsRec(s1,s2,m,n-1));
    
    // TIME COMPLEXITY: 2ᵐᵃˣ⁽ᵐ,ⁿ⁾   [Max height of binary tree would be the length of the longer string]
}

int lcsMem(string s1, string s2, int m, int n, vector <vector<int>> &mem)
{
    if(mem[m][n] == -1)
    {
        if(m==0 || n==0)
            return 0;
        
        if(s1[m-1] == s2[n-1])
            mem[m][n] = 1 + lcsMem(s1,s2,m-1,n-1,mem);
        else
            mem[m][n] = max(lcsMem(s1,s2,m-1,n,mem), lcsMem(s1,s2,m,n-1,mem));
    }
    return mem[m][n];

    // TIME COMPLEXITY: O(mn)       [Since we are filling a matrix mem[m+1][n+1] and every entry will be filled exactly once unlike in the simple recursion case in which same corresponding entry values would be repeatedly calculated e.g. :-
    /*
        Here, (BYXJB,BAJP) is calculated twice in case of simple recursion.
                                        -> (BYXJB,BAJP) ...
                        -> (ABYXJB,BAJP)
                                        -> (ABYXJB,AJP) ...
        -> (ABYXJB,BAJP)
                                        -> (BYXJB,BAJP) ...
                        -> (BYXJB,TBAJP)
                                        -> (YXJB,TBAJP) ...
    */
    // BEST CASE: O(m) == O(n), when both strings are equal
}

int lcsTab(string s1, string s2, int m, int n, vector <vector<int>> &tab)
{
    for(int i=0; i<m+1; i++)
        tab[i][0] = 0;
    for(int j=0; j<n+1; j++)
        tab[0][j] = 0;
    
    for(int i=1; i<m+1; i++)
    {
        for(int j=1; j<n+1; j++)
        {
            if(s1[i-1] == s2[j-1])
                tab[i][j] = 1 + tab[i-1][j-1];
            else
                tab[i][j] = max(tab[i-1][j], tab[i][j-1]);
        }
    }
    return tab[m][n];

    // TIME COMPLEXITY: O(mn)
}

int main()
{
    // Longest Common Substring [LCS]: String of common characters in same order of occurence.
    // Ex: s1 = "ABYXJB", s2 = "TBAJP" => lcs = BJ

    string s1 = "ABYXJB", s2 = "TBAJP";
    // string s1 = "AGGTAB", s2 = "GXTXAYB";
    int m = s1.size(), n = s2.size();

    cout<<lcsRec(s1, s2, m, n)<<"\n";
    
    // Variable length arrays are not allowed by Standard C++. In C++ the length of the array needs to be a compile time constant. Some compilers do support VLA as a compiler extension, but using them makes your code non-portable across other compilers. The current C++ standard does not require that compilers support VLAs. However, compiler vendors are permitted to support VLAs as an extension. GCC >= 4.7, for example, does. That's why vectors're more appropriate be use whenever an array is variable length, and not int n; arr[n];.
    // When it comes to 2D arrays however, even VLAs as an extension would require at least the number of columns to be known at compile time, therefore, we cannot pass variable length 2D arrays to a function, since, what we would be passing would be a pointer to that 2D array, and the we would not be able to resolve n, to the size, whatever we define there, since n is known only within the scope of int main().
    // int mem[m][n];
    vector <vector <int>> mem (m+1, vector<int> (n+1,-1));
    cout<<lcsMem(s1, s2, m, n, mem)<<"\n";
    
    vector <vector<int>> tab (m+1, vector<int> (n+1,-1));
    cout<<lcsTab(s1, s2, s1.size(), s2.size(), tab)<<"\n";

    for(int i=0; i<=m; i++)
    {
        for(int j=0; j<=n; j++)
            cout<<mem[i][j]<<"  ";
        cout<<"\n";
    }
    cout<<"\n\n";
    for(int i=0; i<=m; i++)
    {
        for(int j=0; j<=n; j++)
            cout<<tab[i][j]<<"  ";
        cout<<"\n";
    }

    // VARIATIONS OF LCS
    /*
        1) Shortest Common SUPERsequence
        2) Longest Palindromic Subsequence
        3) Longest Repeating Subsequence
        4) SPACE OPTIMIZED DP Solution of LCS
        5) Printing LCS
        6) Minimum Insertions & Deletion to convert s1 into s2
        7) Difference Utility
    */

    return 0;
}