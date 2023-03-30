#include<iostream>
#include<climits>

using namespace std;

template <typename T>       // OR template <class T>
// template <typename T, typename U>    // more than one type names also possible
T myMax (T x, T y)
{
    return (x>y)?x:y;
}

template <typename T, int limit>
T maxArr (T Arr[], int n)
{
    if(n > limit)
    {
        cout<<"Limit Exceeded";
        return 0;
    }
    else
    {
        T max = Arr[0];
        for (int i = 0; i < n; i++)
        {
            if(Arr[i] > max)
                max = Arr[i];
        }
        return max;
    }
}

template <typename T>
struct Pair     // or create a class
{
    T x, y;

    Pair(T i, T j)
    {
        x = i;
        y = j;
    }

    T getFirst()        // Defining function inside the structure/class
    {
        return x;
    }

    T getSecond();      // Defining function outside the structure/class
};

template <typename T>
T Pair<T>::getSecond()
{
    return y;
}


int main()
{
/*
=> TEMPLATES
    -> A template is a blueprint to create a generic class.function, that passes data type as a parameter so that we don’t need to write the same code for different data types.
    -> Need to be written once and then can be used for any data type.
    -> Like macros, templates are processed by the compiler, but they are better than the macros in a way that templates perform the type-checking.
    -> Ex: A software company may need sort() for different data types. Rather than writing and maintaining the multiple codes, we can write one sort() and pass data type as a parameter.

    -> TYPES:-
        1) Function Template: We write a generic function that can be used for different data types. Examples of function templates are sort(), max(), min(), printArray()
        2) Class Template: Like function templates, class templates are useful when a class defines something that is independent of the data type. It is used to reproduce the code for various data types. It can be useful for classes like LinkedList, BinaryTree, Stack, Queue, Array, etc.

    -> SYNTAX :-
        # Template Declaration:     template <typename datatype_alias>
                                                OR
                                    template <class datatype_alias>
        # Function/Class Template:  datatype_alias function_name/class_name (datatype_alias parameter)
                                    {
                                        // code
                                    }
        # Function/Class Call:      function_name/class_name <datatype> (parameter);
                                    NOTE: <datatype> is optional [A function call to a function template where every template parameter is deducible or has a default can use empty angle brackets or can omit them, both ways are valid. The difference is that if you omit the angle brackets, you're inviting overload resolution to also consider non-template functions that happen to be named the same and happen to be callable with the same parameter list.]
*/

// FUNCTION TEMPLATE
    cout << myMax <int> (3,4) << endl;
    cout << myMax <char> ('a', 'c') << endl;
    cout << myMax <float> (3.9, 9.4) << endl;
    cout << myMax <int> (60, 'b') << endl;
    cout << myMax <float> (8.7, 28) << endl;
    cout << myMax <char> ('a', 110) << endl;

/* 
    NOTE 1: The compiler has the ability to guess the data type of an element or array but is always a good practice to specify the data type of the element being passed.

    NOTE 2: The template can also take values as parameters alongside the data type, for example, limit in the program below.

    NOTE 3: Apparently, template scope lasts for only one function/class declaration
*/
    int arr[] = {2,4,9,1,11,4};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << maxArr <int, 100> (arr, n) << "\n";

// CLASS TEMPLATE
    Pair <int> p (10, 20);
    cout<<p.getFirst()<<"\n";
    cout<<p.getSecond()<<"\n";

    return 0;
}