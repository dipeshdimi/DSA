#include<iostream>
#include<algorithm>

using namespace std;

bool myComp(pair<char, pair<int,int>> a, pair<char, pair<int,int>> b)
{
    return a.second.second > b.second.second;
}

void jobSeq(pair<char, pair<int,int>> jobs[], int n)
{
    sort(jobs, jobs+n, myComp);
    char result[n];
    bool slot[n];

    for(int i=0; i<n; i++)
        slot[i] = false;

    int profit=0;
    for(int i=0; i<n; i++)
    {
        for(int j = min(n, jobs[i].second.first) - 1; j>=0; j--)
        {
            if(!slot[j])
            {
                result[j] = jobs[i].first;
                slot[j] = true;
                profit += jobs[i].second.second;
                break;
            }
        }
    }

    cout<<"Optimal Job Sequence -> ";
    for(int i=0; i<n; i++)
    {
        if(slot[i])
            cout<<result[i]<<"  ";
    }
    cout<<"\nProfit Yielded = "<<profit;

}

int main()
{
    // Problem: Given an array of jobs where every job has a deadline and associated profit if the job is finished before the deadline. It is also given that every job takes a single unit of time, so the minimum possible deadline for any job is 1. How to maximize total profit if only one job can be scheduled at a time?

    pair<char, pair<int,int>> jobs[] = 
        {{'a',{4,50}}, {'b',{1,5}}, {'c',{1,20}}, {'d',{5,10}}, {'e',{5,80}}};
            // {jobID, {deadline, profit}}

    int n = sizeof(jobs)/sizeof(pair<char, pair<int,int>>);

    jobSeq(jobs, n);

    return 0;
}