#include<iostream>
#include<algorithm>

using namespace std;

bool myComp(pair <int,int> a, pair<int,int> b)
{
    return ((double)a.first/a.second > (double)b.first/b.second);
}

double Fractional_Knapsack(pair<int,int> items[], int n, int W)
{
    sort(items, items+n, myComp);
    double res = 0;

    for(int i=0; i<n; i++)
    {
        if(items[i].second <= W)
        {
            res += items[i].first;
            W -= items[i].second;
        }
        else
        {
            res += items[i].first * (double)W/items[i].second;
            break;
        }
    }
    return res;
}

int main()
{
    // PROBLEM : Given a list of elements with specific values and weights associated with them, the task is to fill a Knapsack of weight W using these elements such that the value of knapsack is maximum possible. You are allowed to take a fraction of an element also in order to maximize the value.
    
    pair<int,int> items[] = {{100,20}, {120,29}, {60,10}};      // {value, weight}
    int n = sizeof(items)/sizeof(pair<int,int>);
    int W = 50;     // Knapsack's capacity (weight it can hold)

    cout<<Fractional_Knapsack(items, n, W);

    return 0;
}