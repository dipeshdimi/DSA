// Array Representation / Sequential Representation of BT

#include<stdio.h>

// Global arrays will be initialized with their default values when no initializer is specified. For instance, the integer arrays are initialized by 0 . Double and float values will be initialized with 0.0 . For char arrays, the default value is '\0' .
char tree[30];

void root(char value)
{
    tree[0] = value;
}

void left_child(int parent_index, char value)
{
    if(tree[parent_index] == '\0')
    {
        printf("Parent Not Found at index %d\n", parent_index);
    }
    else
    {
        tree[2*parent_index + 1] = value;
    }
}

void right_child(int parent_index, char value)
{
    if(tree[parent_index] == '\0')
    {
        printf("Parent Not Found at index %d\n", parent_index);
    }
    else
    {
        tree[2*parent_index + 2] = value;
    }
}

void print_tree()
{
    for (int i = 0; i < 30; i++)
    {
        if(tree[i] != '\0')
            printf("%c", tree[i]);
        else
            printf("-");
    }
    printf("\n");
}

int main()
{
    root('A');
    left_child(0, 'B');
    right_child(0, 'C');
    left_child(1, 'D');
    right_child(1, 'E');
    right_child(2, 'F');
    left_child(2, 'G');
    
    print_tree();
    /*
        A(0)
       /    \
    B(1)    C(2)
    / \     |   \
  D(3) E(4) G(5) F(6)
    */


    root('H');
    print_tree();
    /*
        H(0)
       /    \
    B(1)    C(2)
    / \     |   \
  D(3) E(4) G(5) F(6)
    */

    right_child(5, 'I');
    right_child(3, 'J');
    right_child(6, 'K');
    left_child(12, 'L');
    left_child(7, 'M');     // No parent at index 7
    print_tree();
    /*
        H(0)
       /    \
    B(1)    C(2)
    / \     |   \
  D(3) E(4) G(5) F(6)
    \         \      \
     J(8)      I(12)  K(14)
              /
            L(25)
    */

    return 0;
}