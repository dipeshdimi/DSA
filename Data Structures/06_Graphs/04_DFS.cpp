#include<iostream>
#include<vector>

using namespace std;

void addEdgeUndirected(vector <int> adj_list[], int u, int v)
{
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
}

void addEdgeDirected(vector <int> adj_list[], int from, int to)
{
    adj_list[from].push_back(to);
}

void DFS_Recur(vector <int> adj_list[], int source, bool visited[])
{
    visited[source] = true;
    cout<<source<<"  ";

    for(auto x : adj_list[source])
    {
        if(visited[x] == false)
            DFS_Recur(adj_list, x, visited);
    }
}

void DFS(vector <int> adj_list[], int source, int vertices)
{
    bool visited[vertices];
    for (int i = 0; i < vertices; i++)
        visited[i] = false;

// FOR CONNECTED GRAPH :-
    DFS_Recur(adj_list, source, visited);

// FOR DISCONNECTED GRAPH :-
    for (int i = 0; i < vertices; i++)
    {
        if(visited[i] == false)
            DFS_Recur(adj_list, i, visited);
    }
}

int main()
{
    vector <int> adj_list_undir[5];
    addEdgeUndirected(adj_list_undir, 0, 1);
    addEdgeUndirected(adj_list_undir, 0, 2);    /*  0----1\     */
    addEdgeUndirected(adj_list_undir, 1, 2);    /*  |   /| \    */
    addEdgeUndirected(adj_list_undir, 1, 3);    //  |  / |  4
    addEdgeUndirected(adj_list_undir, 1, 4);    //  | /  | /
    addEdgeUndirected(adj_list_undir, 2, 3);    //  2----3/
    addEdgeUndirected(adj_list_undir, 3, 4);
    
    vector <int> adj_list_dir[5];               
    addEdgeDirected(adj_list_dir, 0, 1);
    addEdgeDirected(adj_list_dir, 1, 3);      //  0 --→ 1↘
    addEdgeDirected(adj_list_dir, 1, 4);      //  ↑  ↗  ↓ 4
    addEdgeDirected(adj_list_dir, 2, 0);      //  2 --→ 3↙
    addEdgeDirected(adj_list_dir, 2, 1);
    addEdgeDirected(adj_list_dir, 2, 3);
    addEdgeDirected(adj_list_dir, 4, 3);

    cout<<"DFS for Undirected Graph (starting from 0)\t->\t";
    DFS(adj_list_undir, 0, 5);
    cout<<"\nDFS for Undirected Graph (starting from 1)\t->\t";
    DFS(adj_list_undir, 1, 5);
    cout<<"\nDFS for Undirected Graph (starting from 2)\t->\t";
    DFS(adj_list_undir, 2, 5);
    cout<<"\nDFS for Undirected Graph (starting from 3)\t->\t";
    DFS(adj_list_undir, 3, 5);
    cout<<"\nDFS for Undirected Graph (starting from 4)\t->\t";
    DFS(adj_list_undir, 4, 5);

    cout<<"\n\nDFS for Directed Graph (starting from 0)\t->\t";
    DFS(adj_list_dir, 0, 5);
    cout<<"\nDFS for Directed Graph (starting from 1)\t->\t";
    DFS(adj_list_dir, 1, 5);
    cout<<"\nDFS for Directed Graph (starting from 2)\t->\t";
    DFS(adj_list_dir, 2, 5);
    cout<<"\nDFS for Directed Graph (starting from 3)\t->\t";
    DFS(adj_list_dir, 3, 5);
    cout<<"\nDFS for Directed Graph (starting from 4)\t->\t";
    DFS(adj_list_dir, 4, 5);

// NOTE: Just like BFS, DFS can also be used to solve the no. of islands/no. of connected components problem.

// TIME COMPLEXITY  :    O(V+E)     [Just like in BFS]
// SPACE COMPLEXITY :    O(V)       [Just like in BFS]

/*
=> BFS vs DFS
    # BFS -> In BFS, we first walk through all nodes on the same level before moving on to the next level (thus called breadth first).

    # DFS -> In DFS, we start at the root node and explore as far as possible along each branch before backtracking (thus called depth first).

    # BFS is slower than DFS.
*/

/*
=> APPLICATIONS OF DFS :-
    1) Detecting cycle in a graph
    2) Path Finding
    3) Topological Sorting
    4) To test if a graph is bipartite
    5) Finding Strongly Connected Components of a graph
    6) Solving puzzles with only one solution, such as mazes
*/

    return 0;
}