#include<iostream>
#include<algorithm>
#include<vector>
#include<functional>

using namespace std;

struct point{
    int x, y;
};

bool myComp(point p1, point p2)
{
    /* Pehle wala chhota h ko true return kiya  =>  Pehle wale ko age place krna h          =>  Asc
       Pehle wala bda h ko true return kiya     =>  Pehle wale ko fir bhi age place krna h =>  Desc */
    
    return (p1.x < p2.x);       // Sorting in ascending order of x-coordinate value
    // return (p1.x > p2.x);       // Sorting in descending order of x-coordinate value
    // return (p1.y < p2.y);       // Sorting in ascending order of y-coordinate value
    // return (p1.y > p2.y);       // Sorting in descending order of y-coordinate value

    // Between the first and (then) second point, just use the sign ('>' or '<') as per which you want the sorting to happen i.e., '<' for ascending (a < b < c <...)  and '>' for descending (a > b > c >...)
}

void printArray(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d->", arr[i]);
    }
    printf("\n");
}

int main()
{
    /*  # SYNTAX  ->    sort(pointer_to_first_element, pointer_to_the element_beyond_the_last_element)
                        sort(pointer_to_first_element, pointer_to_the element_beyond_the_last_element, comparison_function)
                
        # Worst Case -> O(nlogn)
          Average Case -> O(nlogn)

        # Uses Intro Sort
        [Hybrid of Quick Sort, Heap Sort (when quick sort is doing unfair partioning & takes more than nlogn time complexity) and Insertion Sort (when the array size is small)]
    */

        // ARRAY
            int arr[] = {2,4,0,-5,-2,2,8};
            int n = sizeof(arr)/sizeof(arr[0]);
            sort(arr, arr+n);   // Sorts in ascending order by default
            printArray(arr, n);

            sort(arr, arr+n, greater<int>());   // Sorts in descending order
            printArray(arr, n);

        
        // VECTOR
            vector<int> v = {2,4,0,-5,-2,2,8};

            sort(v.begin(), v.end());
            for(int x:v)
                cout<<x<<"->";
            cout<<endl;

            sort(v.begin(), v.end(), greater<int>());   // greater<datatype>, would be greater<pair<int, char>> in case of pair, for instance 
            for(int x:v)
                cout<<x<<"->";
            cout<<endl;


        // User defined comparison function
            point arr_2d[] = {{2,3}, {-6,7}, {5,-4}};
            int size = sizeof(arr_2d)/sizeof(arr_2d[0]);

            sort(arr_2d, arr_2d+size, myComp);

            for(auto i : arr_2d)
                cout<<"("<<i.x<<", "<<i.y<<")"<<endl;

    return 0;
}