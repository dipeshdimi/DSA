#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void addEdgeDirected(vector <int> adj_list[], int from, int to)
{
	adj_list[from].push_back(to);
}

void Shortest_Path_DAG(vector <int> adj_list[], int V)
{

}

int main()
{
    // find longest paths: just negate the lengths of all the edges.
    // ?????Topological sort isliye chahiye kyonki usse ye guarantee mil jaegi ki jis bhi node ki next node pr jump krne wale ho us tak ka min distance (from source) maloom h. Agr yhi na pta ho to next step ka distance kaise calculate kroge coz dist(src to next node) = dist(src to curr node) + weight?????
    vector <int> adj_list_dir_acyclic[5];               
    addEdgeDirected(adj_list_dir_acyclic, 0, 1);
    addEdgeDirected(adj_list_dir_acyclic, 1, 3);      //  0 --→ 1↘
    addEdgeDirected(adj_list_dir_acyclic, 1, 4);      //  ↑  ↗  ↓ 4
    addEdgeDirected(adj_list_dir_acyclic, 2, 0);      //  2 --→ 3↙
    addEdgeDirected(adj_list_dir_acyclic, 2, 1);
    addEdgeDirected(adj_list_dir_acyclic, 2, 3);
    addEdgeDirected(adj_list_dir_acyclic, 4, 3);

    Shortest_Path_DAG(adj_list_dir_acyclic, 5);

    return 0;
}