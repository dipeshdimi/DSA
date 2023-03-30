#include<iostream>

using namespace std;

struct deque_cir_arr
{
    int front, rear, cap;
    int *arr;

    deque_cir_arr(int inpCap)
    {
        cap = inpCap;
        front = -1;
        rear = -1;
        arr = new int[cap];
    }

    bool isFull()
    {
        if((rear+1)%cap == front)
            return true;
        else
            return false;
    }

    bool isEmpty()
    {
        if(front == -1)    // OR rear == -1
            return true;
        else
            return false;
        // NOTE: front == rear == -1 is not the same as front == -1 && rear == -1
                    To evalua
    }

    void enqueue_front(int val)
    {
        if(cap == rear-front+1)     // full()
            cout<<"Deque already full !!!";
        else if(front == -1)    // or rear == -1
        {
            front = (front+1)%cap;
            rear = (rear+1)%cap;
            arr[front] = val;
        }
        else
        {
            front = (front-1+cap)%cap;      // (+cap) to make sure it remains +ve in case of front == 0
            arr[front] = val;
        }
    }

    void enqueue_rear(int val)
    {
        if(cap == rear-front+1)     // full()
            cout<<"Deque already full !!!";
        else if(rear == -1)     // or front == -1
        {
            front = (front+1)%cap;
            rear = (rear+1)%cap;
            arr[rear] = val;
        }
        else
        {
            rear = (rear+1)%cap;      // (+cap) to make sure it remains +ve in case of front == 0
            arr[rear] = val;
        }
    }

    void dequeue_front()
    {
        if(front == rear && front != 0 && rear != 0)
            cout<<"Deque already empty";
        else
            front = (front+1)%cap;
    }

    void dequeue_rear()
    {
        if(front == rear && front != 0/* && rear != 0*/)    // rear!=0 needs not be mentioned as front==rear already
            cout<<"Deque already empty";
        else
            rear = (rear-1)%cap;
    }
};

int main()
{
    
    return 0;
}