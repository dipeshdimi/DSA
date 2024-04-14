#include<iostream>
#include<climits>

using namespace std;

#define V 5

void printMST(int adj_mat[V][V], int parent[])      // int *parent is equivalent to int parent[]
{
    int MST_Weight=0;
    cout<<"\nMST :   Edge  |  Weight\n      --------|------------\n";
    for(int i=1; i<V; i++)
    {
        cout<<"        "<<parent[i]<<"-"<<i<<"   |   "<<adj_mat[parent[i]][i]<<"\n";
        MST_Weight += adj_mat[parent[i]][i];
    }
    cout<<"\nWeight of the constructed MST = "<<MST_Weight<<"\n\n";
}

int Min_Key_Index(bool MST_Set[], int key[])
{
    int min = INT_MAX;  // Here we can't initialize min with key[0] or just any random value from the array (key[]) for which we wish to find the min element as our goal is to find the min out of the 'not yet in MST' vertices and key[0] is part of 'already in MST' subgraph instead.
    int min_index;

    for(int i=0; i<V; i++)
    {
        if(MST_Set[i] == false && key[i] < min)
        {
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}

 void Prims_Algo(int adj_mat[][V])
{   
    // The idea of using key values is to pick the minimum weight edge from the cut. The key value for a 'already in MST' vertex would indicate the weight of the edge that connected it to the 'already in MST' subgraph AND the key value for a 'not yet in MST' vertex indicates the minimum weight edge connecting it to the 'already in MST' subgraph (this value is according to only the graph explored up until that point in the algorithm, it would change if we find a lower weight edge connecting the 'already in the MST' subgraph with that vertex).
    int key[V];
    bool MST_Set[V];        // false for 'not yet in MST' vertices and true for 'already in MST' vertices
    for(int i=0; i<V; i++)
    {
        key[i] = INT_MAX;       // Initialize all key values to infinity as there is no vertex in the 'already in the MST' subgraph as of now, so, no edge connecting any of the vertices to the 'already in the MST' subgraph.
        MST_Set[i] = false;
    }
    
    key[0] = 0;     // First vertex in the 'already in the MST' subgraph (it would be the first vertex to be added to the MST as 0 would be min value when compared with all other vertices which hold INT_MAX value), thus min weight edge from the cut i.e., 'already in the MST' subgraph to vertex 0 would be 0.

    int parent[V];  // For a node i, parent[i] would mean the node with which i was connected when it was added to the MST i.e., node parent[i] is already in the MST (in 'already in MST' subgraph), and then we add node i (currently in the 'not yet in MST' subgraph) into the MST by connecting it to the parent[i] node.
    parent[0] = -1; // First node of the MST (root node) has no parent.

    for(int count=0; count<V-1; count++)    // We have already included vertex 0 in the MST, thus we only need to run this loop for V-1 times, each time adding a new edge to the MST as per Prim's Algo (constructing a tree with V vertices).
    {
        // This function returns the min weight vertex which is picked to be added to the MST. We look for the min weight edge from the 'already in MST' subgraph to the 'not yet in MST' subgraph i.e., vertex in the 'not yet in MST' subgraph (MST_Set[] = false for 'not yet in MST' vertices) which can be connected to the 'already in MST' subgraph with min weight edge i.e., index of key[] array element with min value while comparing only 'not yet in MST' elements to obtain the min value.
        int minWeightVertex = Min_Key_Index(MST_Set, key);

        MST_Set[minWeightVertex] = true;    // Including the min weight vertex (picked vertex) in the MST

        // Update key[] & parent[] for the adjacent vertices of the picked vertex (min weight vertex). Consider only those vertices which are not yet included in MST.
        for(int v=0; v<V; v++)
        {
            // adj_mat[minWeightVertex][v] is non zero only for adjacent vertices of minWeighVertex
            // MST_Set[v] is false for vertices not yet included in MST 
            // Update the key only if adj_mat[minWeightVertex][v] is smaller than key[v] 
            // Basically, since we just added minWeightEdge to the MST, we opened another vertex to connect the 'not yet in MST' subgraph to the 'already in MST' subgraph, and since key[x] array represents, the minimum weight edge that connects node 'x' from the 'not yet in MST' subgraph to the 'already in MST' subgraph (OR the edge that connected node 'x' that is already in the MST to it, however, we do not need to bother with that case since we have already calculated the min edge for it, and it won't change as we further explore the graph, that's why we have included MST_Set[v]==false here), we would need to update it in case the newly added minWeightVertex offers an even lower weighted edge to connect to x.
            if(adj_mat[minWeightVertex][v] != 0 && MST_Set[v]==false && key[v] > adj_mat[minWeightVertex][v])
            {
                key[v] = adj_mat[minWeightVertex][v];
                parent[v] = minWeightVertex;  // The min weight edge to connect v to the MST is be the edge between v and minWeightEdge as per the graph explored so far, thus currently, minWeightEdge is the potential parent of v.
            }
        }
    }
    printMST(adj_mat, parent);
}


int main()
{
/*
    => SPANNING TREE
        -> Given a connected and undirected graph, a spanning tree of that graph is a subgraph that is a tree (a tree is a connected graph without any cycles, with a single root node) and connects all the vertices together (directly or through intermediate edges) with the min no. of edges (min V-1 edges're required to connect V vertices).
        -> Spanning Tree = No Cycle + (V-1) Edges       [Connected, Undirected graph]
        -> A single graph can have many different spanning trees.
    
    => MINIMUM SPANNING TREE (MST)
        -> A minimum spanning tree (MST) or minimum weight spanning tree for a weighted, connected and undirected graph is a spanning tree with weight less than or equal to the weight of every other spanning tree.
        -> The weight of a spanning tree is the sum of weights given to each edge of the spanning tree.
        -> MST = No Cycle + (V-1) Edges + Min Weight    [Weighted, Connected, Undirected graph]
    
    => PRIM'S ALGORITHM
        -> Greedy Algorithm.
        -> It starts with an empty spanning tree. The idea is to maintain two sets of vertices. The first set contains the vertices already included in the MST, the other set contains the vertices not yet included. At every step, it considers all the edges that connect the two sets, and picks the minimum weight edge from these edges. After picking the edge, it moves the other endpoint of the edge to the set containing MST.
        -> A group of edges that connects two set of vertices in a graph is called cut in graph theory. So, at every step of Prim’s algorithm, we find a cut (of two sets, one contains the vertices already included in MST and other contains rest of the vertices), pick the minimum weight edge from the cut and include this vertex to MST Set (the set that contains already included vertices).
        -> The idea behind Prim's algorithm is simple, a spanning tree means all vertices must be connected. So the two disjoint subsets (discussed above) of vertices must be connected to make a Spanning Tree. And they must be connected with the minimum weight edge to make it a Minimum Spanning Tree.
        -> The formation of a cycle is not possible in the above described process as for a cycle to form, we'll either need to connect two vertices in the MST constructed thus far through the algorithm or we'll need to connect the 'not yet in MST' vertex with two 'already in MST' vertices. In Prim's Algorithm, we are only connecting one 'not yet in MST' vertex with one 'already in MST' vertex. Thus, no cycle will ever be formed.

*/
    int adj_mat[V][V] = {   { 0, 2, 0, 6, 0 }, 
                            { 2, 0, 3, 8, 5 }, 
                            { 0, 3, 0, 0, 7 }, 
                            { 6, 8, 0, 0, 9 }, 
                            { 0, 5, 7, 9, 0 }   };
/*
        (0)--2--(1)--3--(2)
         |      /\       |
         6    8    5     7
         |  /        \   |
        (3)------9-----(4)
               
*/

    Prims_Algo(adj_mat);

/*
    => TIME COMPLEXITY
        -> θ(V²)
        -> OPTIMISATION : Adjacency List & Min Heap => O(V*log₂V) + O((V+E)*log₂V)
                                                    => O(V*log₂V) + O(E*log₂V)      {E>V}
                                                    => O(E*log₂V)                   {E*log₂V > V*log₂V}
*/
    
    return 0;
}