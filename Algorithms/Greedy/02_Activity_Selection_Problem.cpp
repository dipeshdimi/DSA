#include<iostream>
#include<algorithm>

using namespace std;

bool myComp(pair<int,int> a, pair<int,int> b)
{
    return a.second < b.second;     // Sorts in ascending order of finish time
}

int ActivitySelection(pair<int,int> act[], int n)
{
    sort(act, act+n, myComp);
    int res = 1;
    int prev = 0;

    for(int curr=1; curr<n; curr++)
    {
        if(act[prev].second <= act[curr].first)
        {
            res++;
            prev = curr;
        }
    }
    return res;
}

int main()
{
/*
    => Problem: You are given N activities with their start and finish times. Select the maximum number of activities that can be performed by a single person, assuming that a person can only work on a single activity at a time.

    => Greedy Approach : Always pick the next activity whose finish time is least among the remaining activities and the start time is more than or equal to the finish time of previously selected activity. We can sort the activities according to their finishing time so that we always consider the next activity as minimum finishing time activity.
    
    => Min finishing time -> Would be finished quickly -> More activities can be performed.

    => -----|...    [Min start time]    -|_ min finish time
        ---|...     [Min finish time]   -|  more preferrable
    
    => PROOF THAT STARTING WITH MIN FINISH TIME WOULD GIVE AT LEAST ONE OF THE OPTIMAL SOLUTIONS
        -> Let the given set of activities be S = {1, 2, 3, …n}, and activities are sorted by finish time. The greedy choice is to always pick activity 1. How come activity 1 always provides one of the optimal solutions?
        -> We can prove it by showing that if there is another solution B with the first activity other than 1, then there is also a solution A of the same size as activity 1 as the first activity. Let the first activity selected by B be k, then there always exist A = {B – {k}} U {1}.
        -> Note: The activities in B are independent and k has the smallest finishing time among all. Since k is not 1, finish(k) >= finish(1))
*/
    
    pair<int,int> activities[] = {{1,2}, {3,4}, {2,3}, {5,6}};
    int n = sizeof(activities)/sizeof(pair<int,int>);

    cout<<ActivitySelection(activities, n);

    return 0;
}