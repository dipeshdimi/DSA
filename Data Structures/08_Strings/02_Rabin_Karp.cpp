#include<iostream>

using namespace std;

// String Hash => s[0]*xᵐ⁻¹ + s[1]*xᵐ⁻² + ... + s[m-2]*x¹ + s[n-1]*x⁰
// Here, x is a constant, usually a prime close to the size of character set of the string. For example, if the string was made up of all lower case letters only, x=31 would be an appropriate value (prime close to 26). Similarly, if it was exclusively made up of the lower and upper case letters, x=53 would be an appropriate value.
// Here, we are assuming the string (pat or txt) to be made up of any of the 256 possible characters, so x=256.
const int x = 256;

// Modulo is chosen to be prime and large to avoid spurious hits (e.g., 1=13 would mean the resultant of the modulus operation can range from 0 to 12, so large q value would mean, there a would be large no. of possible hash values and thus, low collision rate).
const int q = 1000000007;

void RabinKarp(string txt, string pat)
{
    // @ -> value calclulated is equivalent to the modulus of the entire calculation even though it is done on steps bcoz of the property (a$b) % n = (a%n $ b%n) % n, where $ = {*,+,-}.

    int m = pat.size();
    int n = txt.size();

    int p=0, t=0;
    for(int i=0; i<m; i++)
    {
        p = (p*x + pat[i]) % q;     // @
        t = (t*x + txt[i]) % q;     // @
        // With every iteration, x is multiplied to the entire string and a new character is added with no 'x' part, thus, giving the hash function.
    }

    // calculating exp = xᵐ⁻¹
    int exp = 1;
    for(int i=1; i<m; i++)
        exp = (exp*x) % q;  // @

    bool flag;
    for(int i=0; i<=n-m; i++)
    {
        if(p == t)
        {
            flag=true;
            for(int j=0; j<m; j++)
            {
                if(pat[j] != txt[j+i])
                {
                    flag = false;
                    break;
                }
            }
            if(flag==true)
                cout<<i<<"  ";
        }

        // If we calculate t for i==n-m, we would have tried accessing txt[n], which is out of the array bounds.
        if(i < n-m)
        {
            t = (t*x - exp*x*txt[i] + txt[i+m]) % q;    // @
            // deleting the iᵗʰ character (trailing digit) and adding the (i+m)ᵗʰ character (leading digit), this is why it's called rolling hash.

            // The value of t can be negative. As we are taking modulo q in each step, the value of t can be between 0 to q-1. So, txt[i]*exp can be greater than the old value of t, making (t - txt[i]*exp) negative.
            if(t<0)
                t = t+q;
                // Since we're taking the modulo value of t, it won't matter if we q to t as (t+q)%q = t+0 = t. And by adding q to t, we'll definitely make t>0 as t ranges from 0 to q-1.
                // Ex: -3%11 = 3 = 8%11 and 8 = -3+11
        }
    }
}

int main()
{
    string text = "abdabcbabc";
    string pattern = "abc";

    RabinKarp(text, pattern);

    // Time Complexity: The average and best case running time of the Rabin-Karp algorithm is O(n+m), but its worst-case time is O(nm). Worst case of Rabin-Karp algorithm occurs when all characters of pattern and text are the same as the hash values of all the substrings of txt[] match with the hash value of pat[]. For example pat[] = "AAA" and txt[] = "AAAAAAA".

    return 0;
}