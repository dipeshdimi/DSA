#include<iostream>
#include<math.h>

using namespace std;

int main()
{
    string str = "abc";
    for(int counter=0; counter<pow(2,str.length()); counter++)
    {
        for(int i=0; i<str.size(); i++)
        {
            if(counter & (1<<i))    // print if we find a set bit in counter
                cout<<str[i];
        }
        cout<<"\n";
    }

    // COMPLEXITY: θ(2ⁿ*n)      [Can be done in O(n²) complexity without the bit operators]

    return 0;
}