#include<iostream>
#include<vector>
#include<climits>
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

void printDist(int dist[], int vertices)
{
    for(int i=0; i<vertices; i++)
    {
        if(dist[i] == INT_MAX)
            cout<<"INF"<<"["<<i<<"]  ";
        else
            cout<<dist[i]<<"["<<i<<"]  ";
    }
    cout<<"\n";
}

void shortest_Path_Unweighted(vector<int> adj_list[], int source, int vertices)
{
    bool visited[vertices];
    for(int i=0; i<vertices; i++)
        visited[i] = false;
    
    int dist[vertices];
    for(int i=0; i<vertices; i++)
        dist[i] = INT_MAX;
        // Initialised with infinity (INT_MAX here).
        // If for a vertex, dist[i], remains infinity (INT_MAX here), it implies that the said vertex in unreachable from the source vertex.
    
    queue <int> q;
    q.push(source);
    visited[source] = true;
    dist[source] = 0;       // Distance from source to source = 0

    while(!q.empty())
    {
        for(auto x : adj_list[q.front()])
        {
            if(!visited[x])
            {
                visited[x] = true;
                q.push(x);
                dist[x] = dist[q.front()] + 1;
                // In BFS, we first traverse through the vertices that are 1 edge away from the source vertex, then vertices that are 2 edges away from the source vertex (or 1 vertex away from the current vertex i.e., q.front()) and so on. As soon as we find a vertex, we set visited[i]=true and thus, even if there are other longer paths, they are not considered. It's like first marking the vertices that 1 edge away, then 2 edges away, then 3 edges away and so on and thus, edges are marked in order of their vicinity to the source vertex. Thus, shortest path to a vertex is found and longer ones are not considered (already marked).
            }
        }
        q.pop();
    }
    printDist(dist, vertices);
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

    cout<<"For an undirected, unweighted graph, shortest path distances from 0 would be:  ";
    shortest_Path_Unweighted(adj_list_undir, 0, 5);
    cout<<"For an undirected, unweighted graph, shortest path distances from 1 would be:  ";
    shortest_Path_Unweighted(adj_list_undir, 1, 5);
    cout<<"For an undirected, unweighted graph, shortest path distances from 2 would be:  ";
    shortest_Path_Unweighted(adj_list_undir, 2, 5);
    cout<<"For an undirected, unweighted graph, shortest path distances from 3 would be:  ";
    shortest_Path_Unweighted(adj_list_undir, 3, 5);
    cout<<"For an undirected, unweighted graph, shortest path distances from 4 would be:  ";
    shortest_Path_Unweighted(adj_list_undir, 4, 5);

    cout<<"\nFor a directed, unweighted graph, shortest path distances from 0 would be:  ";
    shortest_Path_Unweighted(adj_list_dir, 0, 5);
    cout<<"\nFor a directed, unweighted graph, shortest path distances from 1 would be:  ";
    shortest_Path_Unweighted(adj_list_dir, 1, 5);
    cout<<"For a directed, unweighted graph, shortest path distances from 2 would be:  ";
    shortest_Path_Unweighted(adj_list_dir, 2, 5);
    cout<<"\nFor a directed, unweighted graph, shortest path distances from 3 would be:  ";
    shortest_Path_Unweighted(adj_list_dir, 3, 5);
    cout<<"\nFor a directed, unweighted graph, shortest path distances from 4 would be:  ";
    shortest_Path_Unweighted(adj_list_dir, 4, 5);

/*                              ___
    TIME COMPLEXITY : O(V+E)       |_ Same as BFS
    SPACE COMPLEXITY: O(V)      ___|
*/
/*
    => ARRAY DECAY: The loss of type and dimensions of an array is known as decay of an array.This generally occurs when we pass the array into function by value or pointer. What it does is, it sends first address to the array which is a pointer, hence the size of array is not the original one, but the one occupied by the pointer in the memory [When we pass an array as an argument, it is passed on as a pointer].
*/

    return 0;
}