/*
    => OPEN ADDRESSING
        1) In open addressing, all elements are stored in the hash table itself.
        2) Each table entry contains either a record or NIL.
        3) Size (no. of slots) of the Table (m) >= Total No. of Keys (n)
        4) Cache Friendly
        5)  (i) Linear Probing
            (ii) Quadratic Probing
            (iii) Double Hashing
*/
/*
    => LINEAR PROBING
        1) In linear probing, we linearly probe for the next slot.
        2) Let hash(key) be the slot index computed using a hash function and S be the table size, then :-
                hash(key,gap) = (hash(key,gap) + gap) % S)
        3) The typical gap between the two probes is taken as 1.
        4) Ex:  If slot hash(x) % S is full, then we try (hash(x) + 1) % S
                If (hash(x) + 1) % S is also full, then we try (hash(x) + 2) % S
                If (hash(x) + 2) % S is also full, then we try (hash(x) + 3) % S
                ...
        5) Clustering: The main problem with linear probing is clustering, many consecutive elements form groups and it starts taking time to find a free slot or to search an element.
*/
/*
    => QUADRATIC PROBING
        1) We look for (i²)ᵗʰ slot in iᵗʰ iteration.

        2) Let hash(key,i) be the slot index computed using a hash function and S be the table size, then :-
                hash(key,i) = (hash(key,i) + i*i) % S)
                
        3) Ex:  If slot hash(x) % S is full, then we try (hash(x) + 1*1) % S
                If (hash(x) + 1*1) % S is also full, then we try (hash(x) + 2*2) % S
                If (hash(x) + 2*2) % S is also full, then we try (hash(x) + 3*3) % S
                ...
                
        4) Clustering: No primary clusters like in linear probing, but  there are still secondary clusters. In linear probing, if the hash function gave us the result as one of the slots in a cluster, we would have to travel the entire cluster linearly, including passing through elements clustered by both originally desired (as per hash function) slot's element and most probably even others. In case of quadratic clustering, on the other hand, we have to pass through only the elements clustered by the originally desired (as per hash function) slot's element and not others.

        5) In case of quadratic probing, there is no guarantee a slot will be assigned to an element even when there're empty slots available since we do not go through the entire list of slots (like in linear probing). To guarantee this :-
            (i) α < 0.5         [i.e., over double table size]
            (ii) m is prime     [m is the size/no. of slots, n is the no. of keys & α = n/m]
*/
/*
    => DOUBLE HASHING
        1) hash(key, i) = [h1(key) + i*h2(key)] % m
                h1(key) = key % m
                h2(key) = PRIME – (key % PRIME) where PRIME is a prime smaller than the TABLE_SIZE
                (for the ith probe)
        
        2) A good second Hash function is :-
            -> It must never evaluate to zero (as h2(key)=0 => we keep probing the same slot for every value of i as hash() = [h1() + i*0] % m)
            -> Just make sure that all cells can be probed 

        3) Ex:  If slot (h1(x) + 0*h2(x)) % S is full, then we try (hash(x) + 1*hash2(x)) % S
                If (h1(x) + 1*h2(x)) % S is also full, then we try (hash(x) + 2*hash2(x)) % S
                If (h1(x) + 2*h2(x)) % S is also full, then we try (hash(x) + 3*hash2(x)) % S
                ...
        
        4) To ensure that hash(key,i) actually generates a probe sequence that’s a permutation of (0, ... , m−1), a necessary and sufficient condition is that h2(key) is coprime/relatively prime* to m (proof beyond the scope).

        5) No Clustering

        *Co-prime numbers or relatively prime numbers are those numbers that have their HCF (Highest Common Factor) as 1.
*/
/*
    => PERFORMANCE ANALYSIS OF OPEN ADDRESSING (Simple Uniform Hashing)
        -> Assumption : Every probe, we look at a random location i.e., each key is equally likely to be hashed to any slot of the table (simple uniform hashing).
        -> α = n/m <=1 (Open Addressing requires m>=n)
        -> Fraction of empty slots = 1-α
        -> Thus, No. of probes require to find an empty slot = 1/(1-α)

    => Linear probing has the best cache performance but it suffers from clustering. One more advantage of Linear probing that it is easy to compute.
    => Quadratic probing lies between the two in terms of cache performance and clustering.
    => Double hashing has poor cache performance but no clustering. Double hashing requires more computation time as two hash functions need to be computed.
*/
/*
    => SEPARATE CHAINING    V/S    OPEN ADDRESSING
        1.	Chaining is simpler to implement while open Addressing requires more computation.
        2.	In chaining, Hash table never fills up, we can always add more elements to chain while in open addressing, table may become full.
        3.	Chaining is Less sensitive to the hash function or load factors while open addressing requires extra care for to avoid clustering and load factor.
        4.	Chaining is mostly used when it is unknown how many and how frequently keys may be inserted or deleted while open addressing is used when the frequency and number of keys is known.
        5.	Cache performance of chaining is not good as keys are stored using linked list while open addressing provides better cache performance as everything is stored in the same table.
        6.	Chaining causes wastage of space (some parts of hash table in chaining are never used) while in open addressing, a slot can be used even if an input doesn't map to it.
        7.	Chaining uses extra space for links whlile there are no links in open addressing.
*/

#include<iostream>
#include<math.h>
#include<unordered_set>
#include<unordered_map>

using namespace std;

struct LinearProbing
{
    int cap, size;
    int *arr;

    LinearProbing(int c)
    {
        cap = c;
        size = 0;
        arr = new int[cap];
        for(int i=0; i<cap; i++)
        {
            arr[i] = -1;        // Assuming -1 is not an element and just represents an empty slot. In library implementation (maps), the value itself is not stored, instead the pointers to those values are stored and thus, empty slot can be checked using NULL pointer.
        }
    }
    
    bool Search(int val)
    {
        int h = val % cap;
        while(arr[h] != -1)
        {
            if(arr[h] == val)
                return true;    // Element found
            
            h = (h+1)%cap;

            if(h == val%cap)
                return false;   // We return to where we started -> Element not present
        }
        return false;           // arr[h]==-1 -> Empty slot found -> Element not present
    }

    bool Insert(int val)
    {
        if(size == cap)
            return false;   // Array full, can't insert. Due to this step, we don't need to worry about returning to the same element as we already know at least, there will be one empty slot (arr[h] == -1 or -2)

        int h = val % cap;

        // Empty/deleted/already present (assuming no duplicates are to be allowed)
        while(arr[h] != -1 && arr[h] != -2 && arr[h]!=val)
            h = (h+1) % cap;
        
        if(arr[h] == val)
            return false;   // Can't insert, element already present
        else
        {
            size++;
            arr[h] = val;
            return true;    // Insert successful
        }
    }

    bool erase(int val)
    {
        int h = val % cap;
        while(arr[h] != -1)
        {
            if(arr[h] == val)
            {
                // Same as search, just with the following two lines added. Here, we assume -2 is not an element that would be added to the array and that it just signifies a slot whose element was deleted. In the library implementation, we just store the pointer to a dummy variable whenever we delete an element.
                arr[h] = -2;
                size--;
                return true;    // Element found
            }
            
            h = (h+1)%cap;

            if(h == val%cap)
                return false;   // We return to where we started -> Element not present
        }
        return false;
    }

    void print()
    {
        for(int i=0; i<cap; i++)
            cout<<arr[i]<<" -> ";
        cout<<"\n";
    }
};

struct QuadProbing
{
    int cap, size;
    int *arr;

    QuadProbing(int c)
    {
        cap = c;
        size = 0;
        arr = new int[cap];
        for(int i=0; i<cap; i++)
            arr[i] = -1;        // Assuming -1 is not an element and just represents an empty slot. In library implementation (maps), the value itself is not stored, instead the pointers to those values are stored and thus, empty slot can be checked using NULL pointer.
    }
    
    bool Search(int val)
    {
        int i=0;
        int h = (val%cap + i*i) % cap;
        while(arr[h] != -1)
        {
            if(arr[h] == val)
                return true;    // Element found
            
            i++;
            h = (val%cap + i*i)%cap;

            if(h == val%cap)
                return false;   // We return to where we started -> Element not present
        }
        return false;           // arr[h]==-1 -> Empty slot found -> Element not present
    }

    bool Insert(int val)
    {
        if(size == cap)
            return false;
        
        int i=0;
        int h = (val%cap + i*i) % cap;

        while(arr[h] != -1 && arr[h] != -2 && arr[h]!=val)
        {
            if(i+1 > cap)
                return false;   // If your no. of probes is greater than the size of the table, you may be going into an infinte loop (not definitely so, but a high chance or otherwise indicates a poorly written hash function for sure)
            i++;
            h = (val%cap + i*i) % cap;
        }
        
        if(arr[h] == val)
            return false;
        else
        {
            size++;
            arr[h] = val;
            return true;
        }
    }

    bool erase(int val)
    {
        int i=0;
        int h = (val%cap + i*i) % cap;
        while(arr[h] != -1)
        {
            if(arr[h] == val)
            {
                arr[h] = -2;
                size--;
                return true;
            }
            
            i++;
            h = (val%cap + i*i)%cap;

            if(h == val%cap)
                return false;
        }
        return false;
    }

    void print()
    {
        for(int i=0; i<cap; i++)
            cout<<arr[i]<<" -> ";
        cout<<"\n";
    }
};

struct DoubleHashing
{
    int cap, size;
    int *arr;
    DoubleHashing(int c)
    {
        cap = c;
        size = 0;
        arr = new int[cap];
        for(int i=0; i<cap; i++)
            arr[i] = -1;
    }

    bool isPrime(int n)
    {
        // Check if n=1 or n=0
        if (n <= 1)
            return false;
        // Check if n=2 or n=3
        if (n == 2 || n == 3)
            return true;
        // Check whether n is divisible by 2 or 3
        if (n % 2 == 0 || n % 3 == 0)
            return false;
        // Check from 5 to square root of n
        // Iterate i by (i+6)
        for (int i = 5; i <= sqrt(n); i = i + 6)
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
    
        return true;
    }

    bool Search(int val)
    {
        int probe = val%cap;        // Hash Function I
        int prime = cap-1;
        while(!isPrime(prime))      // Prime number smaller and nearest to cap (table size)
            prime--;
        int offset = prime - (val % prime);     // Hash Function II
        
        int count = 1;
        while(arr[probe] != -1)     // Starting with h1 + 0·h2 = h1 i.e., probe
        {
            if(count > cap)
                return false;
            count++;
            
            if(arr[probe] == val)
                return true;
            
            // Addding an offset to probe with every loop, equivalent to h1+i·h2
            probe = (probe + offset) % cap;
        }
        return false;
    }

    bool Insert(int val)
    {
        if(size == cap)
            return false;

        int probe = val % cap;
        int prime = cap-1;
        while(!isPrime(prime))
            prime--;
        int offset = prime - (val % prime);
        
        int count = 1;
        while(arr[probe] != -1 && arr[probe] != -2 && arr[probe] != val)
        {
            if(count == cap)
                return false;
            count++;
            
            probe = (probe + offset) % cap;
        }
        if(arr[probe] == val)
            return false;
        else
        {
            arr[probe] = val;
            size++;
            return true;
        }
    }

    bool erase(int val)
    {
        int probe = val % cap;
        int prime = cap-1;
        while(!isPrime(prime))
            prime--;
        int offset = prime - (val % prime);
        
        int count = 1;
        while(arr[probe] != -1)
        {
            if(count==cap)
                return false;
            count++;

            if(arr[probe] == val)
            {
                arr[probe] = -2;
                size--;
                return true;
            }
            probe = (probe + offset) % cap;
        }
        return false;
    }

    void print()
    {
        for(int i=0; i<cap; i++)
            cout<<arr[i]<<" -> ";
        cout<<"\n";
    }
};

int main()
{
    LinearProbing l(7);

    cout<<l.Insert(49)<<"\n";
    cout<<l.Insert(10)<<"\n";
    cout<<l.Insert(54)<<"\n";
    cout<<l.Insert(63)<<"\n";
    cout<<l.Insert(12)<<"\n";
    cout<<l.Insert(12)<<"\n";
    cout<<l.Insert(0)<<"\n";

    l.print();

    cout<<l.Search(62)<<"\n";
    cout<<l.Search(63)<<"\n";

    cout<<l.erase(62)<<"\n";
    cout<<l.erase(63)<<"\n";

    cout<<l.size<<"\n";
    
    l.print();


    cout<<"\n\n------------------------------------------------------\n\n";


    QuadProbing q(7);

    cout<<q.Insert(49)<<"\n";
    cout<<q.Insert(10)<<"\n";
    cout<<q.Insert(54)<<"\n";
    cout<<q.Insert(63)<<"\n";
    cout<<q.Insert(12)<<"\n";
    cout<<q.Insert(12)<<"\n";
    cout<<q.Insert(0)<<"\n";

    q.print();

    cout<<q.Search(62)<<"\n";
    cout<<q.Search(63)<<"\n";

    cout<<q.erase(62)<<"\n";
    cout<<q.erase(63)<<"\n";

    cout<<q.size<<"\n";

    q.print();


    cout<<"\n\n------------------------------------------------------\n\n";


    DoubleHashing d(7);

    cout<<d.Insert(49)<<"\n";
    cout<<d.Insert(10)<<"\n";
    cout<<d.Insert(54)<<"\n";
    cout<<d.Insert(63)<<"\n";
    cout<<d.Insert(12)<<"\n";
    cout<<d.Insert(12)<<"\n";
    cout<<d.Insert(0)<<"\n";

    d.print();

    cout<<d.Search(62)<<"\n";
    cout<<d.Search(63)<<"\n";

    cout<<d.erase(62)<<"\n";
    cout<<d.erase(63)<<"\n";

    cout<<d.size<<"\n";

    d.print();


    cout<<"\n\n------------------------------------------------------\n\n";


    // UNORDERED SET
        // Stores keys.
        // Not stored in any order.
        // No duplicates.
        // begin(), end(), cbegin(), cend(), empty(), size() are O(1) operations in worst case while insert(), erase(value), erase(iterator), find(), count() are all O(1) operations on average.
    
    unordered_set <int> s;

    s.insert(24);
    s.insert(30);
    s.insert(99);
    s.insert(17);
    s.insert(25);
    s.insert(10);
    s.insert(71);
    s.insert(59);

    for(auto x:s)
        cout<<x<<"  ";      // printed in random order
    cout<<"\n";
    
    for(auto it=s.begin(); it!=s.end(); it++)
        cout<<*it<<"  ";
    cout<<"\n";
    
    // find() returns the iterator of the element if it is found and it returns the iterator s.end() if the element is not found.
    if(s.find(71) == s.end())
        cout<<"Not Found\n";
    else
        cout<<"Found : "<<*s.find(71)<<"\n";
    
    // count() just returns 0 or 1 indicating if the element is found or not (returns 1 for present as the map only contains a unique key).
    if(s.count(70))
        cout<<"Found\n";
    else
        cout<<"Not Found\n";

    cout<<s.size()<<"\n";
    s.erase(30);                    // Erase by value
    s.erase(s.find(99));            // Erase by iterator
    cout<<s.size()<<"\n";
    s.erase(s.begin(), s.end());    // Erase in range
    cout<<s.size()<<"\n";

    // UNORDERED MAP
        // Stores key-value pairs.
        // Not stored in any order.
        // Zero-initialization for non-existing keys.
        // Duplicate keys not allowed, duplicate values allowed.
        // unordered_map <key_datatype, value_datatype> m;
        // begin(), end(), empty(), size() are O(1) operations in worst case while insert(), erase(value), erase(iterator), find(), count(), [], at() are all O(1) operations on average.
        unordered_map <string, int> m;
        m["Aman"] = 6;
        m["Ishita"] = 9;
        m["Faizal"] = 5;
        m["Pawan"] = 7;
        m["Archit"] = 10;
        m.insert({"Ayan", 8});
        for(auto x:m)
            cout<<x.first<<" -> "<<x.second<<"\n";      // printed in random order
    cout<<"\n";

        cout<<"Zero-initialization for non-existing keys -> "<<m["Dipesh"]<<"\n\n";
    
    for(auto it=m.begin(); it!=m.end(); it++)
        cout<<it->first<<" -> "<<it->second<<"\n";
    cout<<"\n";
    
    // find() returns the iterator of the element if it is found and it returns the iterator s.end() if the element is not found.
    if(m.find("Pawan") == m.end())
        cout<<"Not Found\n";
    else
        cout<<"Found : "<<m.find("Pawan")->second<<"\n";
    
    // count() just returns 0 or 1 indicating if the element is found or not (returns 1 for present as the map only contains a unique key).
    if(m.count("Ayan"))
        cout<<"Found\n";
    else
        cout<<"Not Found\n";

    cout<<m.size()<<"\n";
    m.erase("Aman");                    // Erase by value
    m.erase(m.find("Archit"));          // Erase by iterator
    cout<<m.size()<<"\n";
    m.erase(m.begin(), m.end());    // Erase in range
    cout<<m.size()<<"\n";

    // NOTE: count()'s returntype is size_t (https://www.geeksforgeeks.org/size_t-data-type-c-language/)


    return 0;
}