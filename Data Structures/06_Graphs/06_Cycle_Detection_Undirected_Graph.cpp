#include<iostream>
#include<vector>
#include<queue>

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


bool check_Cycle_Undir_DFS_Recur(vector<int> adj_list[], int source, int parent, bool visited[])
{
    visited[source] = true;

    for(int x:adj_list[source])
    {
        if(!visited[x])
        {
            // We just need to detect a single cycle, thus, once check_Cycle_Undir_DFS_Recur() returns true, we just terminate all the functions in the recursion stack to return the final answer as true. If, however, check_Cycle_Undir_DFS_Recur() returns false, we move on to check if any of the neighbour of the next vertex in the loop is already visited and isn't its parent. Once we have looped through all the vertices in the graph and still haven't found a cycle, then we finally return false.
            // Child -> x (i.e., neighbours of source)
            // Parent -> source (as we will be calling this function for source's neighbours next)
            if(check_Cycle_Undir_DFS_Recur(adj_list, x, source, visited))
                return true;
        }
        else if(x != parent)
            return true;
            // A visited* vertex which is not the parent of the current source vertex => CYCLE
            // *We know a vertex going through the else if condition is already visited since we have already checked for unvisited vertex in the previous if condition and if visited[x]!=false, it must be true.
    }
    // Once we have loop through all the vertices in the graph, then we finally return false.
    return false;
}

bool check_Cycle_Undir_DFS(vector<int> adj_list[], int vertices)
{
    bool visited[vertices];
    for(int i=0; i<vertices; i++)
        visited[i] = false;
    
    for(int i=0; i<vertices; i++)
    {
        if(!visited[i])
        {
            // We just need to detect a single cycle, thus, once check_Cycle_Undir_DFS_Recur() returns true, we just terminate all the functions in the recursion stack to return the final answer as true. If, however, check_Cycle_Undir_DFS_Recur() returns false, we move on to check if any of the neighbour of the next vertex in the loop is already visited and isn't its parent. Once we have looped through all the vertices in the graph and still haven't found a cycle, then we finally return false.
            // i -> First element of a connected graph or a segment of a disconnected graph
            // Parent -> -1 (since i is the first element for which check_Cycle_Undir_DFS_Recur() is being called, it has no parent)
            if(check_Cycle_Undir_DFS_Recur(adj_list, i, -1, visited))
                return true;
        }
    }
    // Once we have looped through all the vertices in the graph and still haven't found a cycle, then we finally return false.
    return false;
}


bool check_Cycle_Undir_BFS(vector<int> adj_list[], int vertices)
{
    bool visited[vertices];
    for(int i=0; i<vertices; i++)
        visited[i] = false;
    
    // Parent array/vector to keep track of which vertex is supposed to be the parent of which vertex. Unlike in DFS in which we simply used a parent variable, here, we need to use a parent array/vector as there we had recursion which kept the respective parent nodes preserved when we backtracked to the previous nodes. Here, once we update a parent variable, the value is gone forever.
    vector <int> parent(vertices, -1);
    
    for(int i=0; i<vertices; i++)
    {
        if(!visited[i])
        {
            queue <int> q;
            q.push(i);
            visited[i] = true;
            
            while(!q.empty())
            {
                for(int x:adj_list[q.front()])
                {
                    if(!visited[x])
                    {
                        q.push(x);
                        visited[x] = true;
                        // Since we are looping through the neighbours of q.front() in the for loop, q.front() would be the parent of the neighbours(x).
                        parent[x] = q.front();
                    }
                    // A visited* vertex (x) which is not the parent of q.front() i.e., the vertex whose neighbours we looping through right now => CYCLE
                    // *We know a vertex going through the else if condition is already visited since we have already checked for unvisited vertex in the previous if condition and if visited[x]!=false, it must be true.
                    else if(x != parent[q.front()])
                        return true;
                }
                q.pop();
            }
        }
    }
    // Once we have looped through all the vertices in the graph and still haven't found a cycle, then we finally return false.
    return false;
}


int main()
{
    vector <int> adj_list_undir_cyclic[5];
    addEdgeUndirected(adj_list_undir_cyclic, 0, 1);
    addEdgeUndirected(adj_list_undir_cyclic, 0, 2);    /*  0----1\  */
    addEdgeUndirected(adj_list_undir_cyclic, 1, 3);    //  |    | 4
    addEdgeUndirected(adj_list_undir_cyclic, 1, 4);    //  2    3/
    addEdgeUndirected(adj_list_undir_cyclic, 3, 4);

    vector <int> adj_list_undir_acyclic[5];
    addEdgeUndirected(adj_list_undir_acyclic, 0, 1);
    addEdgeUndirected(adj_list_undir_acyclic, 0, 2);    /*  0----1\     */
    addEdgeUndirected(adj_list_undir_acyclic, 1, 3);    //  |    | 4
    addEdgeUndirected(adj_list_undir_acyclic, 1, 4);    //  2    3
    
// A VISITED VERTEX WHICH ISN'T THE PARENT OF THE CURRENT SOURCE VERTEX => CYCLE
    cout<<check_Cycle_Undir_DFS(adj_list_undir_cyclic, 5)<<"\n";
    cout<<check_Cycle_Undir_DFS(adj_list_undir_acyclic, 5)<<"\n";

    cout<<check_Cycle_Undir_BFS(adj_list_undir_cyclic, 5)<<"\n";
    cout<<check_Cycle_Undir_BFS(adj_list_undir_acyclic, 5)<<"\n";


// TIME COMPLEXITY -> O(V+E)    [for both, BFS as well as DFS based solution]


    return 0;
}