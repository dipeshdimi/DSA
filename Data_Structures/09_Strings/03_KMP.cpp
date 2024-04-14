#include<iostream>

using namespace std;

/*
    =>  LPS : Longest Perfect Prefix which is also a Suffix
        Ex  : "abacba"
                Prefix -> "", "a", "ab", "aba", "abac", "abacb", "abacba"
                Perfect Prefix -> "", "a", "ab", "aba", "abac", "abacb"     [i.e., should be equal to the entire string, similar to perfect subset]
                Suffix -> "", "a", "ba", "cba", "acba", "bacba", "abacba"
                Longest Perfect Prefix which is also a Suffix -> "a"
    
    => TIME COMPLEXITY
        -> All Character Same : Θ(m)
            [would only implement if(pat[len] == pat[i])]

        -> All Characters Distinct : Θ(m)
            [would only implement if(len == 0)]
        
        -> Both Same as well as Distinct Characters
            # Worst Case : O(2m)        [len = lps[len-1]; would also be executed]
            # m execution due to i++
            # Maximum m execution due to len = lps[len-1], at most len, each time

    => file:///C:/Users/dipes/Dropbox/My%20PC%20(LAPTOP-M3NBL2F7)/Downloads/[GeeksForGeeks]%20Placement%20100%20-%20Complete%20Interview%20Preparation/04.%20Data%20Structures%20(Advanced)/09.%20Strings/00.%20Theory.html
*/
void LPS(string pat, int lps[])
{
    // Pattern Length
    int m = pat.length();

    // len represents the length of the longest prefix suffix value for the previous index, i.e., i is the index of the current character we are checking if we could add to the longest prefix suffix and len is the index of the character we need to compare it to (pat[i] and pat[len]).
    // LPS array contains the length of the longest perfect prefix which is also a suffix i.e., lps[i] would represent the length of the longest perfect prefix which is also a suffix, in the string pat[0] to pat[i].
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while(i<m)
    {
        if(pat[len] == pat[i])
        {
            // Another match -> Longest prefix suffix increases by 1.
            // Here, pat[len] is the last character of the prefix and pat[i] is the last character of the suffix.
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if(len == 0)
            {
                // If even after using len=lps[len-1], once or several times, we find no match and len becomes len=0, it means there is no perfect prefix-suffix (except for the empty string) in the string pat[0] to pat[i].
                lps[i] = 0;
                i++;
            }
            else
            {
                // Since lps[] has been storing the values of len at each index, we fall back using lps[] and see if we can find a match with the current pat[i] somewhere in the matching part of the prefix. If we find a match of pat[i] and pat[len], we can update the values, len++, len[i] = len and i++ as we can be sure the prefix elements before len would match with the prefix elements before i (we have checked for it already).
                len = lps[len-1];
            }
        }
    }
}



/*
    => TIME COMPLEXITY  :   O(2n)
        [n for iterating through the text (i++) and n for sliding the patterns over the text]
*/
void KMP(string txt, string pat)
{
    int n = txt.length();
    int m = pat.length();

    // i iterates through the text while j iterates through the pattern
    int i=0, j=0;

    // Computing the LPS array
    int lps[m];
    LPS(pat, lps);

    // Till there are sufficient characters in the text to be compared with the characters in the pattern
    while((n-i) >= (m-j))
    {
        // If characters match, we iterate forward, and we would know, we have found a pattern match in the text, if the value of j reaches m, as j is the no. of consecutive pattern character matches in the text. Likewise, we would know, we have already iterated though the entire text if i reaches n.
        if(txt[i] == pat[j])
        {
            i++;
            j++;
        }

        // Pattern found in the text
        if(j==m)
        {
            // Position of the pattern in the text
            cout<<i-j<<"  ";

            // We know that lps[j-1] would store the length of the longest substring which would both be perfect prefix as well as suffix, which means that substring would appear two times in the string traversed so far (e.g., pat = ABDyxzABDxy, for string traversed so far (ABDyxzABD), ABD appears twice, once as perfect prefix and the other time as suffix). Thus, by going to lps[j-1] (previous time the ABD appears, if we assume ABDyxzABD is in the text but not xy) after jth character in pattern doesn't match with the ith character in th text, we are going back to the index in the string where the same substring (ABD, we know that the matched text ends with ABD, since the matched patterns ends with ABD, and it appears again in the beginning of the pattern too) appears again (i.e., index=3, i.e., pointing at y, since we already know ABD match and we would be comparing pat[j] and txt[i] in the next iteration). We keep going back to lps[j-1] and check if the pat[j]==txt[i] until j=0.
            j = lps[j-1];
        }
        // Mismatch after j matches (0 to j-1)
        // Gotta make sure i<n since the first if statement and this else if statement may both be executed and i might have reached n with i++ in the if statement
        else if(i<n && txt[i] != pat[j])
        {
            // We keep updating j until it reaches zero, in which case, we just have to move on to the next character in text (i++) and start over, with zero matches (j=0) and pattern search in text, starting with its next character (i++). 
            if(j!=0)
                j = lps[j-1];
            else
                i++;
        }
    }
    cout<<"\n";
}

int main()
{
    string txt = "AAAAABAAABA";
    string pat = "AAAA";

    KMP(txt, pat);

    txt = "ABABDABACDABABCABAB";
    pat = "ABABCABAB";
    KMP(txt, pat);

    // TIME COMPLEXITY OF KMP   ->      O(2n+2m) or O(n+m) or O(n)
    // AUXILIARY SPACE          ->      O(m)    [LPS Array]

    return 0;
}