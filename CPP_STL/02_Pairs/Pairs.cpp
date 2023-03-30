#include<iostream>
#include<utility>   // swap() and make_pair(), not need for creating a pair
#include<algorithm> // sort()

using namespace std;

int main()
{
    pair <int, int> p1(10, -10);
    cout<<p1.first<<"("<<typeid(p1.first).name()<<")\t"<<p1.second<<"("<<typeid(p1.second).name()<<")\n";

    pair <float, string> p2(4.9, "dnsx");
    cout<<p2.first<<"("<<typeid(p2.first).name()<<")\t"<<p2.second<<"("<<typeid(p2.second).name()<<")\n";
    // Implicit type conversion, any decimal number is double by default but here, 4.9 is typecasted from double to float

    // Separate Declaration & Initialization 
    pair <int, char> p3;
    p3 = {44, 'f'};
    cout<<p3.first<<"\t"<<p3.second<<"\n";

    // Initialized to zero, by default
    pair <char, int> p4;
    cout<<p4.first<<"\t"<<p4.second<<"\n";  // ASCII 0 represents NULL

    // make-pair(), same as using {}, redundant nowadays
    pair <char, string> p5;
    p5 = make_pair('z', "GFG");


    // Comparing Pairs
    pair <int, int> p6(10, 4);
    pair <int, int> p7(-2, 20);

    cout << (p6 == p7) << "\n";     // if (p6.first == p7.first && p6.second == p7.second) True;    else False;
    cout << (p6 != p7) << "\n";     // if (p6.first != p7.first || p6.second != p7.second) True;    else False;
    cout << (p6 > p7) << "\n";      // if (p6.first > p7.first || (p6.first == p7.first && p6.second > p7.second)) True;    else False;
    cout << (p6 < p7) << "\n";      // if (p6.first < p7.first || (p6.first == p7.first && p6.second < p7.second)) True;    else False;
    
    
/*
=> SORT ONE ARRAY ACCORDING TO ANOTHER ARRAY [Easy  Accuracy: 65.86%  Submissions: 243  Points: 2]
    You are given two arrays a[] (integer) and b[] (char). The ith value of a[] corresponds to the ith value of b[]. Sort the array b[] with respect to a[].

        Example 1:-
            Input:  a[] = {3, 1, 2}
                    b[] = {'G', 'E', 'K'}
            Output: E K G
            Explanation: Here 3 corresponds to G, 1 corresponds to 'E', 2 corresponds to 'K'
        
        Example 2:
            Input:  a[] = {4, 1, 3, 2}
                    b[] = {'A', 'X', 'B', 'Y'}
            Output: X Y B A
            Explanation: ___
            Your Task:  ___

    Your task is to complete the function sortArray() which takes two array as input and sorts the second array with respect to the first array. The function prints the second array space separated. The new line is given by the driver's code.

    Note: Use pair

    Constraints:    1 <= n <= 1000
                    1 <= a[i] <= 1000
                    'A' <= b[i] <= 'Z'
                    Value of a[i]  are distinct.
*/

    int a[] = {4, 1, 3, 2};
    int b[] = {'A', 'X', 'B', 'Y'};
    int n = sizeof(a)/sizeof(a[0]);     // OR sizeof(b)/sizeof(b[0]);

    pair <int, char> p[n];
    for (int i = 0; i < n; i++)
        p[i] = {a[i], b[i]};
    
    sort(p, p+n);
    // sort() function (hybrid of quick, heap and insertion sort) will sort the array of pairs as per the first element in each pair as that's how '>' and '<' comparisons work in case of pairs and '=' comparison is irrelevant in the algorithm that sort() utilises.

    for(int i=0; i<n; i++)
        cout<<p[i].first<<" -> ";
    cout<<"\n";
    for(int i=0; i<n; i++)
        cout<<p[i].second<<" -> ";

    return 0;
}