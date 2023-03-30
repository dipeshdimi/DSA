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

void BFS_Connected(vector <int> adj_list[], int start, int vertices_count)
{
    bool visited[vertices_count];       // Vertices_count+1 if vertex number starts from 1
    for (int i = 0; i < vertices_count; i++)
        visited[i] = false;

    queue <int> q;
    q.push(start);      // OR push any other vertex in case the starting vertex is not given e.g., q.push(adj_list[0][0]);
    visited[start] = true;

    /* 1) Push start into a queue.
       2) Push every unvisited neighbour of start into the queue and pop start from the queue once done.
       3) Repeat the same process for every element in the queue until the queue is empty.
       4) Keep printing the queue elmemnts in the order they were added.
    */
    while(!q.empty())
    {
        cout<<q.front()<<"  ";
        for(auto x : adj_list[q.front()])
        {
            if(!visited[x])
            {
                visited[x] = true;
                q.push(x);          // push an element into the queue if it hasn't already been visited
            }
        }
        q.pop();
    }
}

void BFS_Disconnected(vector <int> adj_list[], /*int start,*/ int vertices_count)
{
    bool visited[vertices_count];

    for(int i=0; i<vertices_count; i++)
    {
        if(!visited[i])
        {
            queue <int> q;
            q.push(i);      // Start Vertex
            visited[i] = true;

            while(!q.empty())
            {
                cout<<q.front()<<"  ";
                for(auto x : adj_list[q.front()])
                {
                    if(!visited[x])
                    {
                        visited[x] = true;
                        q.push(x);
                    }
                }
                q.pop();
            }
        }
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

// NOTE: adj_list_dir is a disconnected graph as we can't traverse the entire graph if we start the traversal from certain nodes i.e., (0,1,3,4)

    cout<<"BFS for Undirected Graph (starting from 0)\t->\t";
    BFS_Connected(adj_list_undir, 0, 5);
    cout<<"\nBFS for Undirected Graph (starting from 1)\t->\t";
    BFS_Connected(adj_list_undir, 1, 5);
    cout<<"\nBFS for Undirected Graph (starting from 2)\t->\t";
    BFS_Connected(adj_list_undir, 2, 5);
    cout<<"\nBFS for Undirected Graph (starting from 3)\t->\t";
    BFS_Connected(adj_list_undir, 3, 5);
    cout<<"\nBFS for Undirected Graph (starting from 4)\t->\t";
    BFS_Connected(adj_list_undir, 4, 5);

    cout<<"\n\nBFS for Directed Graph (starting from 0)\t->\t";
    BFS_Connected(adj_list_dir, 0, 5);
    cout<<"\nBFS for Directed Graph (starting from 1)\t->\t";
    BFS_Connected(adj_list_dir, 1, 5);
    cout<<"\nBFS for Directed Graph (starting from 2)\t->\t";
    BFS_Connected(adj_list_dir, 2, 5);
    cout<<"\nBFS for Directed Graph (starting from 3)\t->\t";
    BFS_Connected(adj_list_dir, 3, 5);
    cout<<"\nBFS for Directed Graph (starting from 4)\t->\t";
    BFS_Connected(adj_list_dir, 4, 5);

    cout<<"\n\nBFS for Disconnected Graph\t->\t";
    BFS_Disconnected(adj_list_dir, 5);

// NOTE: No. of islands problem is based upon the traversal of a disconnected graph.

/*                                          _
    => TIME COMPLEXITY: Directed: O(V+E)     |  -> We use O(V+E) instead of O(E) to include
                        Directed: O(V+2E)    |  the corner case of a disconnected graph:-
                                             |-   0  1  [Here, the V=4, E=0 but we still have 
                                             |    2  3  to traverse through all the 4 vertices]
                                             |  -> In case of a connected graph, V<=E+1, so,
                                            _|  O(V+E) = O(E), thus, it still works.

    => AUXILIARY SPACE: O(V)    [For visited[] and queue]
*/

/*
# APPLICATIONS OF BFS :-

    1) SHORTEST PATH AND MINIMUM SPANNING TREE FOR UNWEIGHTED GRAPH: In an unweighted graph, the shortest path is the path with least number of edges. With Breadth First, we always reach a vertex from given source using the minimum number of edges. Also, in case of unweighted graphs, any spanning tree is Minimum Spanning Tree and we can use either Depth or Breadth first traversal for finding a spanning tree.

    2) IN GARBAGE COLLECTION: Breadth First Search is used in copying garbage collection using Cheney’s algorithm (checks for reachable memory allocations using all the variables and then deletes the inaccessible ones). Breadth First Search is preferred over Depth First Search because of better locality of reference.

    3) CYCLE DETECTION IN UNDIRECTED GRAPH: Both BFS as well as DFS can be used to detect cycle in both undirected as well as directed graphs.
    
    4) FORD–FULKERSON ALGORITHM: In Ford-Fulkerson algorithm, we can either use Breadth First or Depth First Traversal to find the maximum flow. Breadth First Traversal is preferred as it reduces worst case time complexity to O(VE2).

    5) TO TEST IF A GRAPH IS BIPARTITE: We can either use Breadth First or Depth First Traversal.

    6) PATH FINDING: We can either use Breadth First or Depth First Traversal to find if there is a path between two vertices.
    
    7) FINDING ALL NODES WITHIN A CONNECTED COMPONENT: We can either use Breadth First or Depth First Traversal to find all nodes reachable from a given node.
*/


    return 0;
}