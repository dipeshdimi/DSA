#include<iostream>
#include<vector>

using namespace std;

void addEdge_Undirected(vector <int> adj_list[], int u, int v)
{
	adj_list[u].push_back(v);
	adj_list[v].push_back(u);
}

void addEdge_Directed(vector <int> adj_list[], int from, int to)
{
	adj_list[from].push_back(to);
}

void printGraph(vector <int> adj_list[], int V)
{
	for(int i=0; i<V; i++)
	{
		cout<<i<<"\t";
		for(int x:adj_list[i])
		{
			cout<<x<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";
}

int main()
{
/*
    => USING ADJACENCY MATRIX
        -> A 2D array of size VxV where V is the number of vertices in a graph.
        -> A slot adj_mat[i][j]==1 implies an edge from vertex i to j.
        -> Adjacency matrix for an undirected graph is always symmetric.
        -> Adjacency matrix is also used to represent weighted graphs (i.e., adj_mat[i][j]=w represents an edge form vertex i to j carrying weight w).
        -> In case of directed graphs, in its adjacency matrix, we mark only the outgoing edges of a vertex.
        -> Ex:                                      __|_0_|_1_|_2_|_3_|_4_
                    0----1\                         0 | 0 | 1 | 1 | 0 | 0 
                    |  / | 4                        1 | 1 | 0 | 1 | 1 | 1 
                    | /  |/    --->  adj_mat[][] =  2 | 1 | 1 | 0 | 1 | 0 
                    2----3                          3 | 0 | 1 | 1 | 0 | 1 
                                                    4 | 0 | 1 | 0 | 1 | 0 


        -> HOW TO HANDLE VERTICES WITH ARBITRARY NAMES?
            # All the vertices are stored in an array of strings/characters/numbers and the index of each of the vertex in this array is used to represent the corresponding vertex in the adjacency matrix.
            # For an efficient implementation, a hash table h would be required for reverse mapping (i.e., to obtain the index from the vertex's actual name) as we can find the array element using its index in O(1) time while it will take O(n) time to find index using the array element.
            # Ex:   ABC---CED
                    |    /  | \
                    |   /   |  XYZ  --->    arr[] = {"ABC", "CED", "DGJ", "MOP", "XYZ"}
                    |  /    | /                                 |
                    DGJ---MOP                                  \|/
                                                    __|_0_|_1_|_2_|_3_|_4_
                                                    0 | 0 | 1 | 1 | 0 | 0 
                                                    1 | 1 | 0 | 1 | 1 | 1 
                                                    2 | 1 | 1 | 0 | 1 | 0 
                                                    3 | 0 | 1 | 1 | 0 | 1 
                                                    4 | 0 | 1 | 0 | 1 | 0 


        -> COMPLEXITY ANALYSIS
            # Auxiliary Space   :   θ(V²)	[Needs a VxV matrix]
            # Time Comlexity    :   θ(V²)	[Need to set if adj_mat[i][j]==0 or adj_mat[i][j]==1 at V² matrix indices]
                ~ To check if vertices u and v are adjacent :   θ(1)
                        [We just need to check if adj_mat[u][v]==1 (or we could check if adj_mat[v][u])==1]

                ~ To find all vertices adjacent to u :  θ(V)
                        [Will need to iterate through the entire row (column would also work) corresponding to u to check if adj_mat[u][i]==1 (or adj_mat[i][u]==1)]

                ~ To find degree (outdegree in case of directed graphs) of u :  θ(V)
                        [Will need to iterate through the entire row (or column) corresponding to u and the count the no. of times adj_mat[u][i]==1 (or adj_mat[i][u]==1)]

                ~ To add/remove an edge :   θ(1)
                        [Just need to update adj_mat[i][j]=1 to add & adj_mat[i][j]=0 to remove, where (i,j) is the edge we wish to add/remove]
                
                ~ To add/remove a vertex :  θ(V²)
                        [Will need to add an entirely new row as well as column, which will require creating a larger matrix and copying the previous one into this one and then initializing the extra row and column with 0 & 1]

        
        -> PROS & CONS
            # Pros: Representation is easier to implement and follow. Removing an edge takes O(1) time. Queries like whether there is an edge from vertex 'u' to vertex 'v' are efficient and can be done in O(1) time.
            # Cons: Consumes more space O(V²). Even if the graph is sparse(contains less number of edges), it consumes the same space. Adding a vertex is O(V²) time.
*/

/*
    => USING ADJACENCY LIST
        -> An array of lists (i.e., every index of the array will contain an entire list).
        -> Size of array = No. of vertices
        -> arr[i] will store the list of vertices connected/adjacent to the vertex numbered i (which is why a connection between vertices u and v will be mentioned both times in case of directed graphs and one or both times in case of directed graphs).
        -> Implemented using :  (i)  Vectors/Arrays
                                        [Adv: Ease of implementation & Cache Friendliness]
                                        [Disadv: Waste of memory due to pre-allocation & Even though on average, add element operation takes θ(1) time, in case the pre-allocated capacity is full, it takes θ(n+1) time]
                                (ii) Linked Lists
        -> This representation can also be used to represent a weighted graph. The weights of edges can be represented as lists of pairs.                ________________
        -> Ex:                                          |_0_|_1->2_______|
                    0----1\                             |_1_|_0->2->3->4_|
                    |  / | 4    -->   adj_list[]   =    |_2_|_0->1->3____|
                    | /  |/                             |_3_|_1->2->4____|
                    2----3                              |_4_|_1->3_______|

                    0--w₀₁--1\                           _______________________________________________
                    |      /| w₁₄                       |_0_||_|1|w₀₁|_->_|2|w₀₂|_______________________|
                    |     / |   \                       |_1_||_|0|w₀₁|_->_|2|w₁₂|_->_|3|w₁₃|_->_|4|w₁₄|_|
                   w₀₂  w₁₂ w₁₃  4   -->  adj_list[] =  |_2_||_|0|w₀₂|_->_|1|w₁₂|_->_|3|w₂₃|____________|
                    |  /    |   /                       |_3_||_|1|w₁₃|_->_|2|w₂₃|_->_|4|w₃₄|____________|
                    | /     | w₃₄                       |_4_||_|1|w₁₄|_->_|3|w₃₄|_______________________|
                    2--w₂₃--3/


        -> COMPLEXITY ANALYSIS                |-> θ(V+E)	[Directed Graphs]
            # Auxiliary Space   :   θ(V+E) ---|
            				      |-> θ(V+2E)	[Unirected Graphs]
			θ(V+E) :	V: Vector/linked list of size V to store V lists, one for each vertex.
			 			E: A list corresponding to a vertex would contain the elements connected to that vertex, i.e., the degree of that vertex. Thus, if we count the total no. of elements contained in all of the lists, it would be equal to the sum of degrees of all the vertices i.e., no. of edges.
			θ(V+2E):	V: Vector/linked list of size V to store V lists, one for each vertex.
						E: A connection between two edges u and v is counted as just one edge but in the adjacency list representation it is represented twice, both from u to v as well as v to u i.e., both in the list corresponding to vertex u as well as in the list corresponding to vertex v.
			NOTE: In worst case scenario, every vertex is connected to every other vertex (fully connected graph), thus there are V*(V-1) elements stored in total combining all the lists (in case of both directed as well as undirected graphs), which is also equal to the max no. of edges in directed graphs [V(V-1)] and twice the max no. of edges in undirected graphs [2 * V(V-1)/2]. Besides we still need a vector of size V to store V lists, one for each vertex. Thus, θ(V+E) & θ(V+2E) still hold true (would be same as θ(V²) in the worst case scenario).

            # Time Comlexity    :   O(V²)	[In the worst case scenario, there would be a total of V(V-1)/2 possible pairs of vertices to be added to the lists across the V vertices]
                ~ To check if vertices u and v are adjacent :   O(V)
                        [Will need to iterate through the entire list corresponding to u (or v) until v (or u) is found or the list ends, this list could contain a max of V elements]

                ~ To find all vertices adjacent to u :  θ(degree of u)
                        [Will need to iterate through the entire list corresponding to u]

                ~ To find degree (outdegree in case of directed graphs) of u :  θ(degree of u) OR θ(1)
                        [Will need to iterate through the entire list corresponding to u and count the no. of elements in it]
								OR
						[We could just use the list_u.size() function or calculate sizeof(list_u)/sizeof(list_u[0])]

                ~ To add an edge/vertex :   θ(1)
                        [Will just need to add one new element to an already existing list to add an edge to the graph & will just need to increase the size of the vector which is a θ(1) time operation]
                
                ~ To remove an edge :	θ(V)
                        [Will need to shift the list elements to fill the space left behind by the deleted edge (twice in case of undirected graphs)]
				
				~ To remove a vertex :   Better than adjacency matrix

        
        -> PROS & CONS
			# Pros: Saves space O(|V|+|E|). In the worst case, there can be C(V, 2) number of edges in a graph thus consuming O(V^2) space. Adding a vertex is easier.
			# Cons: Queries like whether there is an edge from vertex u to vertex v are not efficient and can be done O(V).
*/

// Adj list is usually preferred over adj matrix due to most graphs being sparsely connected. It works better for BFS, DFS, Dijkstra, Prims, etc.

	// ADJACENCY LIST IMPLEMENTATION
	int V = 5;	// No. of vertices in the graph
	vector <int> adj_list_Undirected[V];
		// Array of vectors (we could have also used vector of vectors/array of arrays/list of vectors/vector of arrays/vector of linked list/...)
		// vector <datatype> vector_name(V) -> Vector of size V each of whose element is datatype (int, char, etc)
		// vector <datatype> array_name[V] -> Array of size V each of whose element is a vector of tupe datatype
	
	addEdge_Undirected(adj_list_Undirected, 0, 1);
	addEdge_Undirected(adj_list_Undirected, 0, 2);
	addEdge_Undirected(adj_list_Undirected, 1, 2);
	addEdge_Undirected(adj_list_Undirected, 1, 3);
	addEdge_Undirected(adj_list_Undirected, 1, 4);
	addEdge_Undirected(adj_list_Undirected, 2, 3);
	addEdge_Undirected(adj_list_Undirected, 3, 4);

	printGraph(adj_list_Undirected, V);


	vector <int> adj_list_Directed[V];
	
	addEdge_Directed(adj_list_Directed, 0, 1);
	addEdge_Directed(adj_list_Directed, 0, 2);
	addEdge_Directed(adj_list_Directed, 1, 2);
	addEdge_Directed(adj_list_Directed, 1, 3);
	addEdge_Directed(adj_list_Directed, 1, 4);
	addEdge_Directed(adj_list_Directed, 2, 3);
	addEdge_Directed(adj_list_Directed, 3, 4);

	printGraph(adj_list_Directed, V);


    return 0;
}