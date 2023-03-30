#include<iostream>

using namespace std;

// Classes can also be used here, though it will make the program lengthy.
// Unlike in classes, all the members are public in structures.
struct node
{
    int data;
    node *next;
    // struct node *next;
    // In C++, the struct keyword is optional before the declaration of a variable. In C, it is mandatory.

    // CONSTRUCTOR => An automatically invoked (whenever a class object / structure instance is created) special member function with the same name as the class, with no return type, which is used to initialize the instances of its structure (objects of its class) with desired structure member values.
    node(int x)     // whenever a structure instance is declared (like testing), this argument will need to be passed
    {
        data = x;
        next = NULL;
    }
};


void recursive_traversal(node *traversal)
{
    if(traversal == NULL)
    {
        cout<<"\n";
        return;
    }

    cout<<traversal->data<<"->";
    recursive_traversal(traversal->next);
}


int search_iterative(node*head, int key)
{
    for (int position = 1; head != NULL; position++)
    {
        if(head->data == key)
            return position;
        
        head = head->next;
    }
    return -1;
}


int search_recursive(node*head, int key)
{
    if(head == NULL)
        return -1;      // when head reaches the end of the linked list
    
    if(head->data == key)
        return 1;
    
    int res = search_recursive(head->next, key);
    if(res == -1)
        return -1;      // res == -1 only when head reaches the end of the linked list and yet, no matching element is found, thus we keep returning -1 until all the function calls are terminated from the stack and the required output(-1) is returned to the original function call.
    else
        return res+1;
            // Position of required element == No. of function calls it took to reach the key element (including the original function call)
            // The function call which termiates with head->data == key, returns 1 as output and then, with each successive termination of previous function calls, we keep increasing the output by 1.
            // Canalso be thought of as position of key element in current linked list (i.e., we consider the linked list to start from wherever head is at that moment).
}


// This method reverses the linked list when function call is terminated
node *reverse_recursive_1(node *head)
{
    if(head->next == NULL || head == NULL)
        return head;
        // Base case returns head when we reach the linked list's last element (i.e., it return the last elmement of the original linked list)
    
    node *rev_head = reverse_recursive_1(head->next);
    // rev_head is the new head of the reversed linked list i.e., the last element of the original linked list (same element is returned every time this is executed).
    // The first time, this function returns the last element of the original linked list from the base case (return head;).
    // Rest of the times, it returns the last element of the original linked list from the return statement at the bottom (return rev_head;).
    
    node *rev_tail = head->next;
    // rev_tail is the tail of the reversed linked list (with each function call, we call we are reversing the part of the original linked list beyond head and thus, it's the element next to the current head).

    rev_tail->next = head;
    // Since rev_tail is the element next to head, we reverse it to make head as the element next to rev_tail.

    head->next = NULL;
    // With this, the linked list has been reversed upto the element at address head (head is the last element of the reversed linked list)

    return rev_head;
    // This is the last element of the original linked list every time this return statement is executed.
}


// This is the recursive version of the iterative solution
// This method reverses the linked list with function call instead for waiting for its termination
node *reverse_recursive_2(node *curr, node *prev)
{
    if(curr == NULL)
        return prev;
    
    node *next = curr->next;
    curr->next =  prev;

    return reverse_recursive_2(next, curr);
}


int main()
{
    node *testing_pointer;          // No argument needs to be passed as this is not a structure instance which will have members data and *next. This is just a pointer that would point to a structure instance (not assigned here, just a wild pointer) 

    node testing_structure(6);      // 6 needs to be passed because the constructor demands an (integer) argument
    cout<<"Data for testing_structure = "<<testing_structure.data<<"\n\n";


// This will create 7 unlinked struct node instances, each with the input 'data' value and '*next' pointer pointing to NULL (thanks to the constructor)
    node *head = new node(-20);     // *head => Pointer pointing to instance with data = -20 and *next=NULL
    node *second = new node(-10);
    node *third = new node(30);
    node *fourth = new node(10);
    node *fifth = new node(0);
    node *sixth = new node(-10);
    node *seventh = new node(20);
    // If there was no constructor, simply use, node *whatever = new node;, data and *next will hold garbage values.

    /*  DMA in CPP:-
        [1] <pointer_data_type> <pointer_variable> = new <data_type> (<data>);
                        {(<data>) is optional, a garbage value will be assigned if we do not specify}
        [2] <pointer_data_type> <pointer_variable> = new <data_type> [<size>];
                        {ALLOACTION OF A BLOCK OF MEMORY, <size> elements of type <data_type>, all initialised with garbage values}
            Ex: 1) int *p = new int(1109);
                2) int *p = new int;
                3) int *p = new structure_name;
                4) int *p = new structure_name(<constructor_argument(s)>);
                5) int *p = new int[10];
                6) int *p = new structure_name[10];  */
        int *p1 = new int(293);
        int *p2 = new int;
        int *p3 = new int[10];
        cout<<"Value stored at address "<<p1<<"(p1) = "<<*p1<<"\t[Input Value]\n";
        cout<<"Value stored at address "<<p2<<"(p2) = "<<*p2<<"\t[Garbage Value]\n\n";
        for (int i = 0; i < 10; i++)
            cout<<"Value stored at address "<<int(&p3[i])<<" OR "<<&p3[i]<<" OR "<<int(p3)+i*sizeof(int)<<" (p3["<<i<<"]) = "<<p3[i]<<"\t[Garbage Value]\n";
        cout<<"\n";
        


// Linking the above 7 instance via these pointers
    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = fifth;
    fifth->next = sixth;
    sixth->next = seventh;

    recursive_traversal(head);
    cout<<"\n\n";

    cout<<"Position of element -10 = "<<search_iterative(head, -10)<<"\n";
    cout<<"Position of element 0 = "<<search_iterative(head, 0)<<"\n";
    cout<<"Position of element 99 = "<<search_iterative(head, 99)<<"\n";
    cout<<"Position of element 20 = "<<search_recursive(head, 20)<<"\n";
    cout<<"Position of element 0 = "<<search_recursive(head, 0)<<"\n";
    cout<<"Position of element -29 = "<<search_recursive(head, -29)<<"\n\n";
    /*
        Iterative Search in Linked List -> O(n) [Time Complexity]   |   O(1) [Auxiliary Space]
        Iterative Search in Linked List -> O(n) [Time Complexity]   |   O(n) [Auxiliary Space (n+1 function call stacks in worst case)]

        NOTE: Binary search doesn't work in O(log₂n) time in linked list as it doesn't allow random access (finding the middle/last element won't take Θ(1) time unlike in an array).
    */

    head = reverse_recursive_1(head);
    recursive_traversal(head);

    head = reverse_recursive_2(head, NULL);
    recursive_traversal(head);


    return 0;
}