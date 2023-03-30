#include<iostream>
#include<vector>

using namespace std;

void addEdgeUndirected(vector <int> adj_list[], int u, int v, int w)
{
    
}

void addEdgeDirected(vector <int> adj_list[], int from, int to, int w)
{
    
}

void Dijkstra(vector <int> adj_list[], int src)
{

}


int main()
{
    vector <int> adj_list_undir[5];
    
    vector <int> adj_list_dir[5];

    Dijkstra(adj_list_dir, 0);
    Dijkstra(adj_list_dir, 1);
    Dijkstra(adj_list_dir, 2);
    Dijkstra(adj_list_dir, 3);
    Dijkstra(adj_list_dir, 4);

    Dijkstra(adj_list_undir, 0);
    Dijkstra(adj_list_undir, 1);
    Dijkstra(adj_list_undir, 2);
    Dijkstra(adj_list_undir, 3);
    Dijkstra(adj_list_undir, 4);

    // Let's say hm vertex'v'pohunch pa rhe h through 'u'. Then, agr 'u' se jane pr hme ek shorter path milega to'v'tk pohunche wale path ko updat kr denge, vrna nhi krenge. Jb tk'v'ka 'src' se distance finalize nhi ho jata, tb tk hm'v'tk pohunche k sbhi alternative paths ko bhi consider krte rehte h jiski vajah se akhir me shortest path milne ki guarantee hoti h. Yahan'v'ka distance/path finalization sirf tb hota h unfinalized vertices me se'v'ki 'src' se distance min ho jae. Is case me kyonki sbhi finalized vertices se hm 'v' tk pahunchne wale paths already consider kr chuke honge aur unfinalized vertices ki 'src' se distance already 'v' ki 'src' se distance se zyada h to unke through 'v' tk koi shorter path milna impossible hoga (except in case of negative weight cycles, jiski vajah se Dijkstra's algorithm negative weights k liye generally kam nhi krti, kuchh specific conditions hone pr kr bhi jati h), isliye 'v' ki 'src' se shortest distance finalize kri ja skti h.

    // Add => Diff Shortest Path
    // Multiply => Same Shortest Path

    return 0;
}