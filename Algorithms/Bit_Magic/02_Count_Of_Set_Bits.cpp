#include<iostream>

using namespace std;

// lookupTable[i] represents the no. of set bits in i
int lookupTable[256];

void initialize()
{
    lookupTable[0] = 0;     // 0 has 0 set bits

    for(int i=0; i<256; i++)
        lookupTable[i] = lookupTable[i/2] + 1&i;
        /* 
            => i/2 is equivalent of i>>1 i.e., right shifting the bits once.
            => In case of even numbers, since the rightmost bit would be 0, the no. of set bits remain the same even after the shift, no. of set bits in i = no. of set in i/2.
            => In case of odd numbers, since the rightmost bit would be 1, the no. of set bits would be one less after the shift, no. of set bits in i = (no. of set bits in i/2) + 1.
            => Generalized result:  No. of set bits in i = (No. of set bits in i/2) + 1&i 
                    [1&i = 1 if odd and 0 if even]
        */
                        
}

int main()
{
    int n=9, count=0;

    // θ(total no. of bits in n)        [32, usually]
    while(n>0)
    {
        // if(n%2 == 1)
        //     count++;
        // n/=2;

        if(n&1)
            count++;
        n>>1;
    }

    // BRIAN KERNINGAM's ALGORITHM [θ(no. of set bits in n)]
    n=9, count=0;
    while(n>0)
    {
        n = n&(n-1);
        count++;
            // n&(n-1) turns the rightmost set bit into 0 since n-1 would be the same of n up until just before the rightmost set bit and then, rest of the bits would be flipped.
    }

    // LOOKUP TABLE METHOD [θ(1) after preprocessing, would be highly efficient when we wish to  calculate the no. of set bits in a large no. of integers]
    n=9, count=0;
    count += lookupTable[n & 0xff];
    n = n>>8;
    count += lookupTable[n & 0xff];
    n = n>>8;
    count += lookupTable[n & 0xff];
    n = n>>8;
    count += lookupTable[n & 0xff];
    n = n>>8;
        // 0xff is hexadecimal form of the number with 8 righmost bits as 1
        // Instead of evaluating the no. of set bits in one go, we divide our 32 bit number into 4 chunks of 8 bits each and calculate of each chunk separately.
        // With (n&0xff), we only leave 8 bits unchanged in the number, rest're turned into 0s and then our lookupTable answers the number of set bits in obtained the 8 bit sequence.
    


    return 0;
}