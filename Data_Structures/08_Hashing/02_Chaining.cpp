/*
    => CHAINING
        -> The idea is to make each cell of the hash table point to a linked list of records that have the same hash function value.
            _____
            |___|->...
            |___|->...
                .
                .
                .
            |___|->...

        -> Chaining is simple, but it requires additional memory outside the table.

        -> Performance
            # m = No. of slots in the hash table
            # n = No. of keys to be inserted
            # Load Factor (α) = n/m = Expected Chain Length    [Min α for better performance]
            # Expected Time to Search/Insert/Delete = O(1+α)   [1 for hashing function computation and α for traversal]
        
        -> Data Structures for Storing Chains
            1) Linked List
                # O(l) for search/insert/delete in a chain of length l.
                # Not cache-friendly since elements're stored in non-contiguous manner.
                # Need to store an extra 'next' pointer.

            2) Dynamic Sized Arrays (Vectors in CPP)
                # O(l) for search/insert/delete in a chain of length l.
                # Cache-friendly since elements're stored in contiguous manner.
                # No need to store an extra 'next' pointer.

            3) Self-Balancing Tree (AVL & Red-Black Trees)
                # O(log₂l) for search/insert/delete in a chain of length l.
                # Not cache-friendly since elements're stored in non-contiguous manner.
                # No need to store an extra 'next' pointer.
*/

#include<iostream>
#include<list>

using namespace std;

struct Chaining
{
    // We use an array of lists (a list is equivalent to doubly linked list in CPP STL).
    int bucket_size;    // Table Size / Array Size, is specified by the user
    list <int> *table; 
    Chaining(int b)
    {
        bucket_size = b;
        table = new list<int>[bucket_size];
        // Array Size - Fixed
        // List Size - Variable
    }

    void insert(int key)
    {
        table[key%bucket_size].push_back(key);
    }

    void remove(int key)
    {
        // remove(key) would mean deleting all occurences of the number 'key' from the list
        table[key%bucket_size].remove(key);
    }

    bool search (int key)
    {
        for(auto x:table[key%bucket_size])
            if(x==key)
                return true;

        return false;
    }

    void print()
    {
        cout<<"----------\n";
        for(int i=0; i<bucket_size; i++)
        {
            for(auto x:table[i])
                cout<<x<<"->";

            cout<<endl;
        }
        cout<<"---------\n";
    }
};

int main()
{
    Chaining c(7);

    c.insert(69);
    c.insert(32);
    c.insert(93);
    c.insert(7);
    c.insert(29);
    c.insert(44);
    c.insert(12);

    c.print();
    
    cout<<c.search(29)<<"\n";
    cout<<c.search(2)<<"\n";

    c.remove(12);
    c.print();

    return 0;
}