#include<iostream>

using namespace std;

bool checkPalindrome(int n)
{
    int temp=n, rem, rev=0;
    while(temp!=0)
    {
        rem = temp%10;
        temp = temp/10;
        rev = rev*10 + rem;
    }
    if(rev == n)
        return true;
    else
        return false;
}

int main()
{
    int n;
    cout<<"Enter no. = ";
    cin>>n;
    cout<<checkPalindrome(n);
    return 0;
}