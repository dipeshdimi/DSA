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

bool cycleDirected_DFS_Recur(vector <int> adj_list[], int src, bool visited[], bool recur_stack[])
{
    visited[src] = true;
    recur_stack[src] = true;    // Recursion called for src

    for(int x : adj_list[src])
    {
        // There is a cycle in a graph only if there is a BACK EDGE present in the graph. Depth First Traversal can be used to detect a cycle in a Graph, DFS for a connected graph produces a tree. 
        // If the graph is disconnected then get the DFS forest and check for a cycle in individual trees by checking back edges. To detect a back edge, keep track of vertices currently in the recursion stack of function for DFS traversal. If a vertex is reached that is already in the recursion stack then there is a cycle in the tree.
        // Note: A Back edge is an edge that is from a node to itself (self-loop) or one of its ancestors in the tree produced by DFS. Thus the edge that connects the current vertex to the vertex in the recursion stack is a back edge. Here, the back edge is from src to x.
        // C:\Programming\DAA\Data Structures\05_Graphs\07_Detect_Cycle_in_Directed_Graph.png
        if(visited[x] && recur_stack[x])
            return true;
        // Going through yet unvisited elements
        else if (cycleDirected_DFS_Recur(adj_list, x, visited, recur_stack))
            return true;
    }

    // cycleDirected_DFSrecur(src) is about to terminate, thus, src would no longer be in the recursion stack
    recur_stack[src] = false;

    // We didn't manage to find a cycle when we traversed to the elements connected directly or indirectly to the vertex src
    return false;
}

bool cycleDirected_DFS(vector <int> adj_list[], int vertices)
{
    bool visited[vertices];
    bool recur_stack[vertices];
    // recur_stack keeps track of the elements currently in recursion stack of cycleDirected_DFS_Recur() function

    for(int i=0; i<vertices; i++)
    {
        visited[i] = false;
        recur_stack[i] = false;     // No recursion stack in the beginning
    }

    for(int i=0; i<vertices; i++)
    {
        if(!visited[i])
        {
            if(cycleDirected_DFS_Recur(adj_list, i, visited, recur_stack))
                return true;
        }
    }
    return false;
}

int main()
{
    vector <int> adj_list_dir_cyclic[5];               
    addEdgeDirected(adj_list_dir_cyclic, 0, 1);
    addEdgeDirected(adj_list_dir_cyclic, 1, 4);      //  0 --→ 1↘
    addEdgeDirected(adj_list_dir_cyclic, 2, 0);      //  ↑  ↗  ↑ 4
    addEdgeDirected(adj_list_dir_cyclic, 2, 1);      //  2 --→ 3↙
    addEdgeDirected(adj_list_dir_cyclic, 2, 3);
    addEdgeDirected(adj_list_dir_cyclic, 3, 1);
    addEdgeDirected(adj_list_dir_cyclic, 4, 3);
    
    vector <int> adj_list_dir_acyclic[5];               
    addEdgeDirected(adj_list_dir_acyclic, 0, 1);
    addEdgeDirected(adj_list_dir_acyclic, 1, 3);      //  0 --→ 1↘
    addEdgeDirected(adj_list_dir_acyclic, 1, 4);      //  ↑  ↗  ↓ 4
    addEdgeDirected(adj_list_dir_acyclic, 2, 0);      //  2 --→ 3↙
    addEdgeDirected(adj_list_dir_acyclic, 2, 1);
    addEdgeDirected(adj_list_dir_acyclic, 2, 3);
    addEdgeDirected(adj_list_dir_acyclic, 4, 3);

    cout<<cycleDirected_DFS(adj_list_dir_cyclic, 5)<<"\n";
    cout<<cycleDirected_DFS(adj_list_dir_acyclic, 5)<<"\n";

    return 0;
}