#include<iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;

    Node(int inputData)
    {
        data = inputData;
        next = NULL;
    }
};

struct stack_LL
{
    Node *head;
    int sz;

    stack_LL()
    {
        head = NULL;
        sz = 0;
    }

    void push(int val)
    {
        Node *ptr = new Node(val);
        if(ptr == NULL)
        {
            cout<<"\nHeap/Stack Overflow !!!\n";
            return;
        }
        ptr->next = head;
        head = ptr;
        sz++;
    }

    void pop()
    {
        if(head == NULL)
        {
            cout<<"\nStack Underflow !!!\n";
            return;
        }
        Node *temp = head;
        head = head->next;
        cout<<"\nPopped Value = "<<temp->data<<"\n";
        delete(temp);
        sz--;
    }

    void peekTop()
    {
        if(head == NULL)
        {
            cout<<"\nStack Underflow !!!\n";
            return;
        }
        cout<<"\nPeek Top = "<<head->data<<"\n";
    }

    int size()
    {
        return sz;
    }

    void display()
    {
        Node *curr = head;
        cout<<"\n";
        while(curr != NULL)
        {
            cout<<curr->data<<"->";
            curr = curr->next;
        }
        cout<<"\n";
    }
};

int main()
{
    stack_LL s;
    // stack_LL s() does not work despite the presence of a constructor (with no argument)

    s.pop();

    s.push(-27);
    s.push(40);
    s.push(30);
    s.push(-69);
    s.push(7);

    s.display();

    s.pop();
    s.pop();

    s.peekTop();

    cout<<"\nSize = "<<s.size()<<"\n";

    s.display();

    return 0;
}