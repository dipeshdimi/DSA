#include<iostream>

using namespace std;

int main()
{
    // In an array, each number appears even number of times except two. Find the two odd occuring numbers.
        /* Find twoOddXor of the two odd appearing elements. */
            int arr[] = {1,4,2,4,1,4,4,2,2,5};
            int twoOddXor=arr[0];
            for(int i=1; i<sizeof(arr)/sizeof(arr[0]); i++)
                twoOddXor = twoOddXor^arr[i];
        
        /* Find the rightmost set bit (any other set bit would also work) */
            // int pos=1;
            // while(twoOddXor&1 != 1)   // Assuming twoOddXor!=0, which is guaranteed here since the two odd occuring elements're unique
            // {
            //     twoOddXor = twoOddXor>>1;
            //     pos++;
            // }
            
            int setBit = twoOddXor & ~(twoOddXor-1);
                // Here, setBit is the number with just one bit set i.e., the first set bit (from right) in twoOddXor. Any set bit of twoOddXor would work for our purpose, first set bit from right is just convenient, could use any other set bit too.
                // Ex:     twoOddXor   =   8^32 = 000...00100 ^ 000...10000 
                //                      =   000...10100 = 40
                //        twoOddXor-1   =   000...10011
                //      ~(twoOddXor-1)  =   111...01100
                //          setBit      =   000...00100
                // Now, all the bits on the righ of the first set bit would be zero for both x and ~(x-1) and all the bits on the left of the first set bit would be opposite of each other in x and ~(x-1), thus x & ~(x-1) would have all bits as 0 except the bit at the position of the first set bit in x, which would be 1.


        /* The given array can now be classified into two categories - one with bit at position pos (from right) set and another in which it is not set. In other words, one in which setBit and arr[i] have a common bit and another one in which they don't. This way, we know that one of the odd occuring element would be in the first category and the other in the second category. We calculate the combined XOR of elements in these two categories separately and the result would be our answer as our problem has reduced to two separate one odd occuring problems. */
            // int res1=0, res2=0;
            // for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
            // {
            //     if(arr[i]>>(pos-1) & 1)     // Category I
            //         res1 = res1^arr[i];
            //     else                        // Category II
            //         res2 = res2^arr[i];
            // }
            
            int res1=0, res2=0;
            for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
            {
                if(arr[i] & setBit)     // Category I
                    res1 = res1^arr[i];
                else                    // Category II
                    res2 = res2^arr[i];
            }

        cout<<res1<<"  "<<res2<<"\n";
    
    return 0;
}