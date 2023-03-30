#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void addEdgeDirected(vector <int> adj_list[], int from, int to, int indegree[])
{
	adj_list[from].push_back(to);

    indegree[to]++;
}

void Kahns_Topo_BFS(vector <int> adj_list[], int V, int indegree[])
{
    // // If indegree not recorded in the addEdgeDirected() function
    // int indegree[V];
    // for(int i=0; i<V;i ++)
    // {
    //     indegree[i] = 0;
    // }
    // for(int i=0; i<V; i++)
    // {
    //     for(auto x:adj_list[i])
    //         indegree[x]++;
    // }

    queue <int> q;
    for(int i=0; i<V; i++)
    {
        if(indegree[i] == 0)
        {
            q.push(i);
        }
    }

    while(!q.empty())
    {
        for(auto x:adj_list[q.front()])
        {
            indegree[x]--;
            if(indegree[x] == 0)
                q.push(x);
        }
        cout<<q.front()<<"  ";
        q.pop();
    }
}

int main()
{
    // Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge uv, vertex u comes before v in the ordering.
    // Topological Sorting for a graph is not possible if the graph is not a DAG (CYCLE => Every vertex in the cycle is dependent on another vertex, thus, we won't find any vertex in the cycle with indegree=0).
    /* 
        1)    5   4             => 4 1 5 2 3 0      => 4 5 1 2 3 0      => 4 5 2 1 3 0
             ↙ ↘↙ ↘            => 4 5 2 3 0 1      => 4 5 2 3 1 0      => 5 2 3 4 0 1
            2   0   1           => 5 2 3 4 1 0      => 5 2 4 1 3 0      => 5 2 4 3 0 1
             ↘ ↗                => 5 2 4 3 1 0      => 5 4 1 2 3 0      => 5 4 2 1 3 0
              3                 => 5 4 2 3 0 1      => 5 4 2 3 1 0
        
        2)      0
              ↙  ↘
             1     2            =>  0 1 2 3 4 5 
               ↘ ↙              =>  0 1 2 3 5 4
                3               =>  0 2 1 3 4 5
              ↙  ↘              =>  0 2 1 3 5 4
             4    5

            { |__| implies these vertices in any order }
    */
    /* BFS SOLUTION :   1) Store indegree of each vertex.
                        2) Create a queue q.
                        3) Add all 0 indegree vertices into q.
                        4) while (q is not empty)
                            {
                                for(every adj v of u)
                                {
                                    indegree(v)--
                                    if(indegree(v) == 0)
                                        q.push(v)
                                }
                                cout<<q.front()
                                q.pop()
                            }
    */

    vector <int> adj_list_dir[6];

    int indegree[6];
    for(int i=0; i<6; i++)
        indegree[i] = 0;

    addEdgeDirected(adj_list_dir, 5, 2, indegree);
    addEdgeDirected(adj_list_dir, 5, 0, indegree);        //    5   4
    addEdgeDirected(adj_list_dir, 4, 0, indegree);        //   ↙ ↘↙ ↘
    addEdgeDirected(adj_list_dir, 4, 1, indegree);        //  2   0   1
    addEdgeDirected(adj_list_dir, 2, 3, indegree);        //   ↘ ↗
    addEdgeDirected(adj_list_dir, 3, 0, indegree);        //    3

    Kahns_Topo_BFS(adj_list_dir, 6, indegree);     // JUST ONE OF THE POSSIBLE WAYS TO GET ONE OF THE TOPOLOGICAL SORTS

    return 0;
}