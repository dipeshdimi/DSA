#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void addEdgeDirected(vector <int> adj_list[], int from, int to, int indegree[])
{
	adj_list[from].push_back(to);

    indegree[to]++;
}

bool Cycle_Detection_Kahns_BFS(vector <int> adj_list[], int V, int indegree[])
{
    queue <int> q;
    for(int i=0; i<V; i++)
    {
        if(indegree[i] == 0)
            q.push(i);
    }

    int count=0;

    while(!q.empty())
    {
        for(int x : adj_list[q.front()])
        {
            indegree[x]--;
            if(indegree[x] == 0)
                q.push(x);
        }
        q.pop();
        count++;
    }
    return (count!=V);
}

int main()
{
    // CYCLE => Every vertex in the cycle is dependent on another vertex, thus, we won't find any vertex in the cycle with indegree=0
    vector <int> adj_list_dir_cyclic[5];
    vector <int> adj_list_dir_acyclic[5];               

    int indegree_cyclic[5];
    for(int i=0; i<5; i++)
        indegree_cyclic[i] = 0;

    int indegree_acyclic[5];
    for(int i=0; i<5; i++)
        indegree_acyclic[i] = 0;

    addEdgeDirected(adj_list_dir_cyclic, 0, 1, indegree_cyclic);
    addEdgeDirected(adj_list_dir_cyclic, 1, 4, indegree_cyclic);      //  0 --→ 1↘
    addEdgeDirected(adj_list_dir_cyclic, 2, 0, indegree_cyclic);      //  ↑  ↗  ↑ 4
    addEdgeDirected(adj_list_dir_cyclic, 2, 1, indegree_cyclic);      //  2 --→ 3↙
    addEdgeDirected(adj_list_dir_cyclic, 2, 3, indegree_cyclic);
    addEdgeDirected(adj_list_dir_cyclic, 3, 1, indegree_cyclic);
    addEdgeDirected(adj_list_dir_cyclic, 4, 3, indegree_cyclic);

    addEdgeDirected(adj_list_dir_acyclic, 0, 1, indegree_acyclic);
    addEdgeDirected(adj_list_dir_acyclic, 1, 3, indegree_acyclic);      //  0 --→ 1↘
    addEdgeDirected(adj_list_dir_acyclic, 1, 4, indegree_acyclic);      //  ↑  ↗  ↓ 4
    addEdgeDirected(adj_list_dir_acyclic, 2, 0, indegree_acyclic);      //  2 --→ 3↙
    addEdgeDirected(adj_list_dir_acyclic, 2, 1, indegree_acyclic);
    addEdgeDirected(adj_list_dir_acyclic, 2, 3, indegree_acyclic);
    addEdgeDirected(adj_list_dir_acyclic, 4, 3, indegree_acyclic);

    cout<<Cycle_Detection_Kahns_BFS(adj_list_dir_cyclic, 5, indegree_cyclic)<<"\n";
    cout<<Cycle_Detection_Kahns_BFS(adj_list_dir_acyclic, 5, indegree_acyclic)<<"\n";
    
    return 0;
}