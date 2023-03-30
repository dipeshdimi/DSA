#include<iostream>
#include<climits>
#include<queue>
#include<vector>

using namespace std;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

struct NameOfTheStructure
{
    int parameter1;
    int parameter2;

    NameOfTheStructure(int p1, int p2)
    {
        parameter1 = p1;
        parameter2 = p2;
    }
};

struct myComp_pair
{
    // For pairs
    bool operator() (pair<int,int> &p1, pair<int,int> &p2)
    {
        // Comparing the second elements of the pairs
        return p1.second < p2.second;
        // Arranges in decreasing order of second element
    }
};

struct myComp_struct
{
    // For user defined structures
    bool operator() (NameOfTheStructure &p1, NameOfTheStructure &p2)
    {
        // Comparing paramter1 and paramter2
        return p1.parameter2 < p2.parameter1;
        // NOT SURE OF THE ORDER, MAYBE WILL THINK ABOUT IT LATER
    }
};

struct heap
{
    int *arr;
    int size;
    int cap;

    heap(int capacity)
    {
        arr = new int[capacity];
        size = 0;
        cap = capacity;
    }

    int Left_Child(int i)
    {
        return 2*i+1;
    }

    int Right_Child(int i)
    {
        return 2*i+2;
    }

    int Parent(int i)
    {
        return (i-1)/2;
        // C++ performs the floor function automatically
    }

    void Print_Heap()
    {
        for(int i=0; i<size; i++)
            cout<<arr[i]<<"  ";
    }

    void insert_minHeap(int x)
    {
        if(size == cap)
        {
            cout<<"Heap Overflow\n";
            return;
        }

        size++;
        arr[size-1] = x;
        
        // This is also a heapifying algorithm when the element to be heapified is a leaf node (no children). Here, since we are attaching/inserting the new element at the end of the tree, the condition is automatically satisfied. The reason for this condition is, in this method the element passed (i) can only move upwards and thus, we won't know which element to pass as argument for a given element to be heapified.
        int i=size-1;
        while(i!=0 && arr[Parent(i)] > arr[i])
        {
            swap(&arr[Parent(i)], &arr[i]);
            i = Parent(i);
        }
    }

    void insert_maxHeap(int x)
    {
        if(size == cap)
        {
            cout<<"Heap Overflow\n";
            return;
        }

        size++;
        arr[size-1] = x;
        
        // Same as METHOD 2 of max_heapify(size-1).
        int i=size-1;
        if(i!=0 && arr[Parent(i)] < arr[i])
        {
            swap(&arr[Parent(i)], &arr[i]);
            i=Parent(i);
        }
    }

// When arr[index] needs to be moved down for heapifying.
    void min_heapify_recursive_down(int index)
    {
    // The element passed, i.e., 'index' should be the element greater than its descendant(s) (element will go downwards in the tree, since we know exactly which element to pass, we pass only the element which needs to be moved downwards).
    // min_heapify_recursive_down(1); needs to be passed.
        int smallest = index;
        int left_Child = 2*index+1;
        int right_Child = 2*index+2;

        if(arr[left_Child] < arr[smallest] && left_Child < size)
            smallest = left_Child;

        if(arr[right_Child] < arr[smallest] && right_Child < size)
            smallest = right_Child;
        
        if(smallest != index)
        {
            swap(&arr[smallest], &arr[index]);
            min_heapify_recursive_down(smallest);
        }
    }

// When arr[index] needs to be moved up for heapifying.
    void min_heapify_recursive_up(int index)
    {
        int parent = (index-1)/2;
        if(parent >= 0 && arr[parent] > arr[index])
        {
            swap(&arr[parent], &arr[index]);
            min_heapify_recursive_up(parent);
        }
    }

// When arr[index] needs to be moved down for heapifying.
    void min_heapify_iterative_down(int index)
    {
    // The element passed, i.e., 'index' should be the element greater than its descendant(s) (element will go downwards in the tree, since we know exactly which element to pass, we pass only the element which needs to be moved downwards).
    // min_heapify_iterative_down_down(1); needs to be passed.
        while(true)
        {
            int smallest = index;
            int left_Child = 2*index+1;
            int right_Child = 2*index+2;

            if(arr[left_Child] < arr[smallest] && left_Child < size)
                smallest = left_Child;

            if(arr[right_Child] < arr[smallest] && right_Child < size)
                smallest = right_Child;
            
            if(smallest == index)
                return;
            
            swap(&arr[smallest], &arr[index]);
            index = smallest;
        }
    }

// When arr[index] needs to be moved up for heapifying.
    void min_heapify_iterative_up(int index)
    {
        int parent = (index-1)/2;
        while(parent >= 0 && arr[parent] > arr[index])
        {
            swap(&arr[parent], &arr[index]);
			index = parent;
            parent = (index-1)/2;
        }
    }

// When arr[index] needs to be moved down for heapifying.
    void max_heapify_recursive_down(int index)
    {
    // The element passed, i.e., 'index' should be the element smaller than its descendant(s) (element will go downwards in the tree, since we know exactly which element to pass, we pass only the element which needs to be moved downwards).
    // max_heapify_recursive_down(1); needs to be passed.
        int greatest = index;
        int left_child = 2*index+1;
        int right_child = 2*index+2;

        if(arr[left_child] > arr[greatest]  &&  left_child < size)
            greatest = left_child;

        if(arr[right_child] > arr[greatest]  &&  right_child < size)
            greatest = right_child;
        
        if(greatest != index)
        {
            swap(&arr[greatest], &arr[index]);
            max_heapify_recursive_down(greatest);
        }
    }

// When arr[index] needs to be moved up for heapifying.
    void max_heapify_recursive_up(int index)
    {
        int parent = (index-1)/2;
        if(parent >= 0 && arr[parent] < arr[index])
        {
            swap(&arr[parent], &arr[index]);
            max_heapify_recursive_up(parent);
        }
    }

// When arr[index] needs to be moved down for heapifying.
    void max_heapify_iterative_down(int index)
    {
    // The element passed, i.e., 'index' should be the element smaller than its descendant(s) (element will go downwards in the tree, since we know exactly which element to pass, we pass only the element which needs to be moved downwards).
    // max_heapify_iterative_down(1); needs to be passed.
        while(true)
        {
            int greatest = index;
            int left_child = 2*index+1;
            int right_child = 2*index+2;

            if(arr[left_child] > arr[greatest]  &&  left_child < size)
                greatest = left_child;

            if(arr[right_child] > arr[greatest]  &&  right_child < size)
                greatest = right_child;
            
            if(greatest == index)
                return;
            
            swap(&arr[greatest], &arr[index]);
            index = greatest;
        }
    }

// When arr[index] needs to be moved up for heapifying.
    void max_heapify_iterative_up(int index)
    {
        int parent = (index-1)/2;
        while(parent >= 0 && arr[parent] < arr[index])
        {
            swap(&arr[parent], &arr[index]);
			index = parent;
            parent = (index-1)/2;
        }
    }

    int getMin()    // from min-heap
    {
        return arr[0];
    }

    int getMax()    // from max-heap
    {
        return arr[0];
    }

    int extractMin()
    {
        if(size==0)
            return INT_MAX;

        if(size==1)
        {
            size--;
            return arr[0];
        }
        
        size--;
        swap(&arr[0], &arr[size]);
        min_heapify_iterative_down(0);
        return arr[size];
    }

    int extractMax()
    {
        if(size==0)
            return INT_MIN;
        if(size==1)
        {
            size--;
            return arr[size];
        }
        size--;
        swap(&arr[0], &arr[size]);
        max_heapify_iterative_down(0);
        return arr[size];
    }

	void decreaseKey_minHeap(int index, int new_value)
	{
		arr[index] = new_value;
		min_heapify_iterative_up(index);
	}

	void increaseKey_minHeap(int index, int new_value)
	{
		arr[index] = new_value;
		min_heapify_iterative_down(index);
	}

	void decreaseKey_maxHeap(int index, int new_value)
	{
		arr[index] = new_value;
		max_heapify_iterative_down(index);
	}

	void increaseKey_maxHeap(int index, int new_value)
	{
		arr[index] = new_value;
		max_heapify_iterative_up(index);
	}

    void delete_minHeap(int index)
    {
        decreaseKey_minHeap(index, INT_MIN);
        extractMin();
    }

    void delete_maxHeap(int index)
    {
        increaseKey_maxHeap(index, INT_MAX);
        extractMax();
    }

    void build_minHeap()
    {
        // Starting from the last non-leaf node {i.e., parent of last leaf node = ((size-1)-1)/2} because the leaf nodes don't need to be heapified as they already follow the heap property (i.e., parent smaller than children, and leaf nodes have no children).
        for(int i=(size-2)/2; i>=0; i--)
            min_heapify_iterative_down(i);
            // Down since parent will need to be moved, not the child
        /* Heapifying all the nodes starting from a last non-leaf node works bcoz :-
            [c is the root node, b is the last non-leaf node]
            CASE I: [(a>b>c) & not considering other elements for simplicity]
                      /           /           /           /
                     a           a*          c*          c
                    / \         / \         / \         / \
                       b*  -->     c   -->     a   -->     b
                      / \         / \         / \         / \
                         c           b           b           a
                    [* -> Current i for min_heapify_iterative_down(i)]

            => With each heapify, we ensure that i is placed correctly relative to the position of elements below it, which may take several swaps like in case of a*, c*.
            => This doesn't mean lower elements won't be shifted, they will need to be shifted when the current element i encountered is small enough to go more than one level down.
            => Those elements which needed to be moved upward automatically do so when the elements described in the previous point mov downwards.
        */
    }

    void build_maxHeap()
    {
        for(int i=(size-2)/2; i>=0; i--)
            max_heapify_iterative_down(i);
    }
};


int main()
{
/*
    => HEAP
        A Heap is a Tree-based data structure, which satisfies the below properties :-
            -> A Heap is a Complete Tree (All levels are completely filled except possibly the last level and the last level has all keys as left as possible).
            -> A Heap is either Min Heap or Max Heap :-
                # Min Heap : [Different ways of saying the same thing :-]
                                1) The key at root must be minimum among all keys present in the Binary Heap. The same property must be recursively true for all nodes in the Tree.
                                2) Highest priority item assigned lowest value.
                                3) Every node smaller than its descendant(s).
                # Min Heap : [Different ways of saying the same thing :-]
                                1) The key at root must be maximum among all keys present in the Binary Heap. The same property must be recursively true for all nodes in the Tree.
                                2) Highest priority item assigned highest value.
                                3) Every node greater than its descendant(s).
    
    => BINARY HEAP
        A Binary Heap is a heap where each node can have at most two children. In other words, a Binary Heap is a complete Binary Tree satisfying the above-mentioned properties.
    
    => APPLICATIONS OF BINARY HEAP
        -> Heapsort
        -> Priority Queue
    
    => BINARY HEAP REPRESENTATION
        Since a Binary Heap is a complete Binary Tree, it can be easily represented using Arrays :-
            -> The root element will be at Arr[0].
            -> For the ith node, i.e., Arr[i],
                # Parent Node = Arr[(i-1)/2]    { ⌊(i-1)/2⌋ OR ⌈(i-2)/2⌉ }*
                # Left Child = Arr[(2*i)+1]
                # Right Child = Arr[(2*i)+2]
                    * ⌈x⌉ -> Ceiling Function / SIF (upper part bent)
                      ⌊x⌋ -> Floor Function / GIF   (lower part bent)

    => ADVANTAGES OF BINARY HEAP
        -> Random Access
        -> Cache Friendly [Since all items at contiguous location, they have locality of reference]
        -> Min Height [Bcoz of this being a complete binary tree, its height would be minimum, and the operations in binary heap data structure depend upon its height (e.g., heapify, insert, etc.)]
        -> No Space Wasted [Array is completely filled in case of complete binary trees, no blank spaces in between]
    
    => EXAMPLES
        ->           2
                   /   \
                  4     8           -> MIN BINARY HEAP
                 / \   / \          -> Array Representation : | 2 | 4 | 8 | 6 | 5 | 9 | 10 | 10 | 20 |
                6   5 9  10
               / \
              10 20
        
        ->          20
                   /  \
                  10   10           -> MAX BINARY HEAP
                 / \   / \          -> Array Representation : | 20 | 10 | 10 | 9 | 6 | 5 | 4 | 8 | 2 |
                9   6 5   4
               / \
              8   2
        
        -> NOTE: Given a set of numbers, they can be arranged in multiple ways to form a min/max heap, and all would be valid.
    
    => GETTING MAX/MIN ELEMENT FROM A MAX/MIN HEAP
        -> Getting Maximum Element: In a Max-Heap, the maximum element is always present at the root node which is the first element in the array used to represent the Heap. So, the maximum element from a max heap can be simply obtained by returning the root node as Arr[0] in O(1) time complexity.
        -> Getting Minimum Element: In a Min-Heap, the minimum element is always present at the root node which is the first element in the array used to represent the Heap. So, the minimum element from a minheap can be simply obtained by returning the root node as Arr[0] in O(1) time complexity.
*/

    heap minHeap1(100);
    heap minHeap2(100);
    /*          2
              /   \
             4     8           -> MIN BINARY HEAP
            / \   / \          -> Array Representation : | 2 | 4 | 8 | 6 | 5 | 9 | 10 | 10 | 20 |
           6   5 9  10
          / \
        10  20
    */

    minHeap1.insert_minHeap(2);
    minHeap1.insert_minHeap(4);
    minHeap1.insert_minHeap(8);
    minHeap1.insert_minHeap(6);
    minHeap1.insert_minHeap(5);
    minHeap1.insert_minHeap(9);
    minHeap1.insert_minHeap(10);
    minHeap1.insert_minHeap(10);
    minHeap1.insert_minHeap(20);

    minHeap2.insert_minHeap(10);
    minHeap2.insert_minHeap(8);
    minHeap2.insert_minHeap(2);
    minHeap2.insert_minHeap(5);
    minHeap2.insert_minHeap(20);
    minHeap2.insert_minHeap(10);
    minHeap2.insert_minHeap(6);
    minHeap2.insert_minHeap(4);
    minHeap2.insert_minHeap(9);

    cout<<"Min Heap 1 : ";
    minHeap1.Print_Heap();
    cout<<"\nMin Heap 2 : ";
    minHeap2.Print_Heap();
    cout<<"\n\n";
    
    // minHeap1 and minHeap2 are both made up of the same numbers but these numbers arrange in different ways to form two separate min heaps. 


    heap maxHeap1(100);
    heap maxHeap2(100);
    /*  ->          20
                   /  \
                  10   10           -> MAX BINARY HEAP
                 / \   / \          -> Array Representation : | 20 | 10 | 10 | 9 | 6 | 5 | 4 | 8 | 2 |
                9   6 5   4
               / \
              8   2
    */

    maxHeap1.insert_maxHeap(20);
    maxHeap1.insert_maxHeap(10);
    maxHeap1.insert_maxHeap(10);
    maxHeap1.insert_maxHeap(9);
    maxHeap1.insert_maxHeap(6);
    maxHeap1.insert_maxHeap(5);
    maxHeap1.insert_maxHeap(4);
    maxHeap1.insert_maxHeap(8);
    maxHeap1.insert_maxHeap(2);

    maxHeap2.insert_maxHeap(6);
    maxHeap2.insert_maxHeap(20);
    maxHeap2.insert_maxHeap(8);
    maxHeap2.insert_maxHeap(5);
    maxHeap2.insert_maxHeap(10);
    maxHeap2.insert_maxHeap(4);
    maxHeap2.insert_maxHeap(10);
    maxHeap2.insert_maxHeap(2);
    maxHeap2.insert_maxHeap(9);

    cout<<"Max Heap 1 : ";
    maxHeap1.Print_Heap();
    cout<<"\nMax Heap 2 : ";
    maxHeap2.Print_Heap();
    cout<<"\n\n";
    
    // maxHeap1 and maxHeap2 are both made up of the same numbers but these numbers arrange in different ways to form two separate max heaps.



/*
    => HEAPIFY: The process of placing a heap element at the correct location so that it satisfies the Heap property is known as Heapify.
    => Time Complexity: O(h) = O(log₂n)
    => Auxiliary Space: O(h) = O(log₂n)     [Recursive, since upto h call stacks are possible]
       Auxiliary Space: O(1)                [Iterative, no call stack]
            [Iterations are by design faster and more efficient than recursions due to absence call stacks]
*/
// MIN HEAPIFY :-
    minHeap1.arr[1] = 7;
    minHeap1.min_heapify_recursive_down(1);
    /*          2                   2                   2
              /   \               /   \               /   \
             4     8             7     8             5     8
            / \   / \   ->      / \   / \   ->      / \   / \
           6   5 9  10         6   5 9  10         6   7 9  10
          / \                 / \                 / \
         10 20               10 20               10 20
    */
    minHeap1.Print_Heap();
    cout<<"\n\n";

    minHeap2.arr[1] = 7;
    minHeap2.min_heapify_iterative_down(1);
    /*          2                   2                   2
              /   \               /   \               /   \
             4     6             7     6             5     6
            / \   / \   ->      / \   / \   ->      / \   / \
           5  20 10  8         5  20 10  8         7  20 10  8
          / \                 / \                 / \
         10  9               10  9               10  9
    */
    minHeap2.Print_Heap();
    cout<<"\n\n";


// MAX HEAPIFY :-
    maxHeap1.arr[1] = 7;
    maxHeap1.max_heapify_recursive_down(1);
    /*         20                 20                   20                    20
              /  \               /  \                 /  \                  /  \
            10    10            7    10              9    10               9    10
            /\    /\   ->      / \   / \    ->      / \   / \   ->        / \   / \
           9  6  5  4         9   6 5   4          7   6 5   4           8   6 5   4
          / \                / \                  / \                   / \
         8   2              8   2                8   2                 7   2
    */
    maxHeap1.Print_Heap();
    cout<<"\n\n";

    maxHeap2.arr[1] = 7;
    maxHeap2.max_heapify_iterative_down(1);
    /*         20                 20                   20
              /  \               /  \                 /  \
            10    10            7    10              9    10
            /\    /\   ->      / \   / \    ->      / \   / \
           9  6  4  8         9   6 4   8          7   6 4   8
          / \                / \                  / \
         2   5              2   5                2   5
    */
    maxHeap2.Print_Heap();
    cout<<"\n\n";

    // min_heapify_recursive_up(), min_heapify_iterative_up(), max_heapify_recursive_up() & max_heapify_iterative_up() are also there.



// getMin(), getMax()
    cout<<"Min element from min-heap = "<<minHeap1.getMin()<<"\n";
    cout<<"Max element from max-heap = "<<maxHeap1.getMax()<<"\n\n";



// EXTRACT MIN & EXTRACT MAX
    /*
        => Removing the min element from min heap & max element from max heap.
        => Time Complexity: O(h) = O(log₂n)
        => Auxiliary Space: O(h) = O(log₂n)     [Recursive, since upto h call stacks are possible]
           Auxiliary Space: O(1)                [Iterative, no call stack]
            [Iterations are by design faster and more efficient than recursions due to absence call stacks]
    */
    cout<<"Extracted Element from the min heap = "<<minHeap2.extractMin()<<"\t\t[";
    minHeap2.Print_Heap();
    cout<<"\b\b]";
    /*          2                   9                   9                   5                   5
              /   \               /   \               /   \               /   \               /   \
             5     6             5     6             5     6             9     6             7     6
            / \   / \   ->      / \   / \   ->      / \   / \   ->      / \   / \   ->      / \   / \
           7  20 10  8         7  20 10  8         7  20 10  8         7  20 10  8         9  20 10  8
          / \                 / \                 /                   /                   /
         10  9               10  2               10                  10                  10
    */

    cout<<"\nExtracted Element from the max heap = "<<maxHeap1.extractMax()<<"\t[";
    maxHeap1.Print_Heap();
    cout<<"\b\b]\n\n";
    /*        20                  2                    2                    10                  10
             /  \               /   \                /   \                 /  \                /  \
            9    10            9    10              9     10              9    2              9    5
           /\    /\   ->      / \   / \    ->      / \   /  \    ->      /\   / \    ->      /\   / \
          8  6  5  4         8   6 5   4          8   6 5    4          8  6 5   4          8  6 2   4
         / \                / \                  /                     /                   /
        7   2              7   20               7                     7                   7
    */



// DECREASE KEY & INCREASE KEY
    /*
        => MIN HEAP + DECREASE KEY -> UP
           MIN HEAP + INCREASE KEY -> DOWN
           MAX HEAP + DECREASE KEY -> DOWN
           MAX HEAP + INCREASE KEY -> UP
        => Time Complexity: O(h) = O(log₂n)
        => Auxiliary Space: O(h) = O(log₂n)     [Recursive, since upto h call stacks are possible]
           Auxiliary Space: O(1)                [Iterative, no call stack]
            [Iterations are by design faster and more efficient than recursions due to absence call stacks]
    */
   	minHeap1.decreaseKey_minHeap(7, 1);
	minHeap1.Print_Heap();
	cout<<"\n";
	/*          2                   2                   2                   2                   1
              /   \               /   \               /   \               /   \               /   \
             5     8             7     8             5     8             1     8             2     8
            / \   / \   ->      / \   / \   ->      / \   / \   ->      / \   / \   ->      / \   / \
           6   7 9  10         6   5 9  10         1   7 9  10         5   7 9  10         5   7 9  10
          / \                 / \                 / \                 / \                 / \
         10 20               1  20               6  20               6  20               6  20
    */

   	minHeap1.increaseKey_minHeap(1, 11);
	minHeap1.Print_Heap();
	cout<<"\n";
	/*          1                    1                    1                   1
              /   \                /   \                /   \               /   \
             2     8             11     8              5     8             5     8
            / \   / \   ->      /  \   / \   ->       / \   / \   ->      / \   / \
           5   7 9  10         5    7 9  10          11  7 9  10         6   7 9  10
          / \                 / \                   / \                 / \
         6  20               6  20                 6  20               11  20
    */

   	maxHeap1.decreaseKey_maxHeap(1, 3);
	maxHeap1.Print_Heap();
	cout<<"\n";
	/*        10                 10                  10                  10
             /  \               /  \                /  \                /  \
            9    5             3    5              8    5              8    5
           /\   / \   ->      /\   / \    ->      /\   / \    ->      /\   / \
          8  6 2   4         8  6 2   4          3  6 2   4          7  6 2   4
         /                  /                   /                   /
        7                  7                   7                   3
    */

   	maxHeap1.increaseKey_maxHeap(5, 9);
	maxHeap1.Print_Heap();
	cout<<"\n\n";
	/*        10                 10                  10
             /  \               /  \                /  \
            8    5             8    5              8    9
           /\   / \   ->      /\   / \    ->      /\   / \
          7  6 2   4         7  6 9   4          7  6 5   4
         /                  /                   /
        3                  3                   3
    */



// DELETE OPERATION
    /*
        => We can't use the exact same procedure as used in the extract function since there, we were deleting a root node every time and thus we knew where the swapped node at the root and the deletion of the original root would move towards i.e., down and thus could use the appropriate algorithm for heapifying the new root.
        => Time Complexity: O(h) = O(log₂n)
        => Auxiliary Space: O(h) = O(log₂n)     [Recursive, since upto h call stacks are possible]
           Auxiliary Space: O(1)                [Iterative, no call stack]
            [Iterations are by design faster and more efficient than recursions due to absence call stacks] 
    */
    minHeap1.delete_minHeap(4);
    minHeap1.Print_Heap();
    cout<<"\n";
	/*          1                   1                    1                 -INF                 20
              /   \               /   \                /   \               /   \               /  \
             5     8             5      8           -INF    8             1     8             1    8
            / \   / \   ->      / \    / \   ->      / \   / \   ->      / \   / \   ->      /\   / \
           6   7 9  10         6 -INF 9  10         6   5 9  10         6   5 9  10         6  5 9  10
          / \                 / \                  / \                 / \                 / \
         11  20              11  20               11  20              11  20              11 -INF

	               20                  1                   1
                  /  \               /   \               /   \
                 1    8             20    8             5     8
        ->      /\   / \   ->      / \   / \   ->      / \   / \
               6  5 9  10         6   5 9  10         6  20 9  10
              /                  /                   /
             11                 11                  11
    */
    
    maxHeap1.delete_maxHeap(3);
    maxHeap1.Print_Heap();
    cout<<"\n\n";
    /*        10
             /  \
            8    9
           /\   / \
          3  6 5   4
    */



// BUILD HEAP
    /* 
        => Building a Binary Heap from the given array.
        => Time Complexity: O(n)
            [C:\Programming\DAA\Data Structures\05_Heap\TimeComplexity_BuildHeap.png]
    */
    int arr[] = {5,1,9,0,-4,7,11,2};

    heap minHeap3(100);
    for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
        minHeap3.arr[i] = arr[i];
    minHeap3.size = sizeof(arr)/sizeof(arr[0]);
    minHeap3.build_minHeap();
    minHeap3.Print_Heap();
    cout<<"\n";

    heap maxHeap3(100);
    for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
        maxHeap3.arr[i] = arr[i];
    maxHeap3.size = sizeof(arr)/sizeof(arr[0]);
    maxHeap3.build_maxHeap();
    maxHeap3.Print_Heap();
    cout<<"\n";



// PRIORITY QUEUE (C++ STL for binary heap data structure defined inside #include<queue> header file)
    priority_queue <int> p1;        // Max heap, by default
    priority_queue <int, vector<int>, greater<int>> p2;     // For min heap
    // Priority queue is implemented using vectors

    p1.push(8);
    p1.push(-3);
    p1.push(11);
    p1.push(1);

    p2.push(8);
    p2.push(-3);
    p2.push(11);
    p2.push(1);

    cout<<"\np1 top = "<<p1.top()<<"\n";
    cout<<"p2 top = "<<p2.top()<<"\n";

    cout<<"p1 size = "<<p1.size()<<"\n";
    cout<<"p2 size = "<<p2.size()<<"\np1:  ";

    while(!p1.empty())
    {
        cout<<p1.top()<<"  ";
        p1.pop();
    }
    cout<<endl<<"p2:  ";

    while(!p2.empty())
    {
        cout<<p2.top()<<"  ";
        p2.pop();
    }
    cout<<endl<<"pq_a:  ";

    // No such thing as random access in priority queue due to which the following code won't work, you can only access the top (min/max) element.
    // for(int i=0; i<p2.size(); i++)
    //     cout<<"\n"<<p2[i]<<"  ";
    
    int a[] = {3,0,-2,-1,9};
    priority_queue <int, vector<int>, greater<int>> pq_a(a, a+5);
    // We passed arr+5 (pointer to position after the last element) instead of arr+4 (pointer to last element) bcoz priority queue is implemented using vectors and vectors require the iterator next to the last element (v.end()) or else the entire array won't be passed.
    // This is faster than pushing elements one by one since this implements the build heap function whose time complexity would be O(n) while if we push elements one by one, time complexity would be O(n*log₂n).

    vector <int> v {3,0,-2,-1,9};
    priority_queue <int> pq_v(v.begin(), v.end());

    while(!pq_a.empty())
    {
        cout<<pq_a.top()<<"  ";
        pq_a.pop();
    }
    cout<<endl<<"pq_v:  ";

    while(!pq_v.empty())
    {
        cout<<pq_v.top()<<"  ";
        pq_v.pop();
    }
    cout<<endl;

    // When we pass pairs to a priority queue, they're arranged based on their first elment.
    // If we want to specify the rule on the basis of which pairs would be considered greater/smaller, we would need to define a structure.
    NameOfTheStructure arr_struct[] = {{21,6}, {8,-19}, {10,10}, {-2,0}};
    priority_queue <NameOfTheStructure, vector<NameOfTheStructure>, myComp_struct> pq_struct(arr_struct, arr_struct+4);
    while(!pq_struct.empty())
    {
        cout<<"{("<<pq_struct.top().parameter1<<", "<<pq_struct.top().parameter2<<"), ";
        pq_struct.pop();
    }
    cout<<"\b\b}\n";

    pair<int,int> arr_pair[] = {{21,6}, {8,-19}, {10,10}, {-2,0}};
    priority_queue <pair<int,int>, vector<pair<int,int>>, myComp_pair> pq_pair(arr_pair, arr_pair+4);
    while(!pq_pair.empty())
    {
        cout<<"{("<<pq_pair.top().first<<", "<<pq_pair.top().second<<"), ";
        pq_pair.pop();
    }
    cout<<"\b\b}\n";


    return 0;
}