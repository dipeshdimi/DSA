#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void addEdgeDirected(vector <int> adj_list[], int from, int to)
{
	adj_list[from].push_back(to);
}

void Topological_Sorting_DFS_Recur(vector <int> adj_list[], int src, int visited[], stack <int> &s)
{
    visited[src] = true;
    for(int x:adj_list[src])
    {
        if(!visited[x])
            Topological_Sorting_DFS_Recur(adj_list, x, visited, s);
    }
    s.push(src);
    // Since it is DFS, first node pushed would be one of the leaf nodes (i.e., no other node depends on them) and then the nodes which don't have any node depending on them except for the already pushed nodes would be pushed. Thus, the last nodes pushed would be the independent nodes since before them would be the nodes depended on them (already pushed)
    // Dependent Node => Child Node
}

void Topological_Sorting_DFS(vector <int> adj_list[], int V)
{
    int visited[V];
    for(int i=0; i<V; i++)
        visited[i] = false;
    
    stack <int> s;
    for(int i=0; i<V; i++)
    {
        if(!visited[i])
            Topological_Sorting_DFS_Recur(adj_list, i, visited, s);
            // PTA NHI YE s ka &s kaise ho gya, stack STL pdhkr ana
            // NONSENSE/WRONG EXPLANATION -> Entire stack cannot be passed as a function argument, thus, when we write the stack name, it means address/pointer to the beginning of the stack in memory (heap), just like in case of array(arr => arr[] or *arr or &arr).
    }

    // Printing stack elements in topological order starting with one of the independent nodes.
    while(!s.empty())
    {
        cout<<s.top()<<"  ";
        s.pop();
    }
}

int main()
{
    vector <int> adj_list_dir[5];               // DIRECTED ACYCLIC GRAPH (DAG)
    addEdgeDirected(adj_list_dir, 0, 1);
    addEdgeDirected(adj_list_dir, 1, 3);        //  0     2
    addEdgeDirected(adj_list_dir, 2, 3);        //  ↓    ↙ ↘
    addEdgeDirected(adj_list_dir, 2, 4);        //  1 → 3 → 4
    addEdgeDirected(adj_list_dir, 3, 4);

    Topological_Sorting_DFS(adj_list_dir, 5);

    return 0;
}