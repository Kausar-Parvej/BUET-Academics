#include <bits/stdc++.h>
using namespace std;

template <class data_type>
class node
{
public:
    data_type element;
    node *next;

    node(data_type item, node *next_node = NULL)
    {
        element = item;
        next = next_node;
    }
    node(node *next_node = NULL)
    {
        next = next_node;
    }
};

//--------------------------------Implementing Stack--------------------------------------------//

template <class data_type>
class LinkedList_Stack
{
    node<data_type> *top;
    int stack_length;

public:
    LinkedList_Stack(int unused = 0)
    {
        top = NULL;
        stack_length = 0;
    }
    ~LinkedList_Stack()
    {
        while (top != NULL)
        {
            node<data_type> *temp = top;
            top = top->next;
            delete temp;
        }
    }

    void clear()
    {
        while (top != NULL)
        {
            node<data_type> *temp = top;
            top = top->next;
            delete temp;
        }
        top = NULL;
        stack_length = 0;
    }

    void push(data_type item)
    {
        node<data_type> *temp;
        temp = new node<data_type>(item);
        temp->next = top;
        top = temp;
        stack_length++;
    }

    data_type pop()
    {
        if (top == NULL)
            return -1;

        data_type item = top->element;
        node<data_type> *temp = top->next;
        delete top;
        top = temp;
        stack_length--;
        return item;
    }

    int length()
    {
        return stack_length;
    }

    data_type topValue()
    {
        if (top == NULL)
            return -1;

        return top->element;
    }

    string printStack()
    {
        node<data_type> *temp;
        temp = top;

        data_type a[stack_length];
        for (int i = 0; i < stack_length; i++)
        {
            a[i] = temp->element;
            temp = temp->next;
        }

        string print("<");
        for (int i = stack_length - 1; i >= 0; i--)
        {
            if (i == 0)
                print.append("| ");

            print.append(to_string(a[i]));
            if (i != 0)
                print.append(" ");
        }

        print.append("> \n");
        return print;
    }
};

//------------------------------Implementing Queue---------------------------------------------//

template <class data_type>
class LinkedList_Queue
{
    node<data_type> *front;
    node<data_type> *rear;
    int queue_length;

public:
    LinkedList_Queue(int unused = 0)
    {
        front = new node<data_type>();
        rear = front;
        queue_length = 0;
    }
    ~LinkedList_Queue()
    {
        while (front->next != NULL)
        {
            rear = front;
            front = front->next;
            delete rear;
        }
        delete front;
    }

    void clear()
    {
        while (front != NULL)
        {
            rear = front;
            front = front->next;
            delete rear;
        }
        front = new node<data_type>();
        rear = front;
        queue_length = 0;
    }

    void enqueue(data_type item)
    {
        node<data_type> *temp;
        temp = new node<data_type>(item, NULL);
        rear->next = temp;
        rear = temp;
        queue_length++;
    }

    data_type dequeue()
    {
        if (queue_length <= 0)
            return -1;

        data_type item = front->next->element;
        node<data_type> *temp = front->next;
        front->next = temp->next;

        if (temp == rear)
            rear = front;
        delete temp;
        queue_length--;
        return item;
    }

    int length()
    {
        return queue_length;
    }

    data_type frontValue()
    {
        if (queue_length == 0)
            return -1;

        return front->next->element;
    }

    data_type rearValue()
    {
        if (queue_length == 0)
            return -1;

        return rear->element;
    }

    data_type leaveQueue()
    {
        if (queue_length <= 0)
            return -1;

        data_type item = rear->element;
        node<data_type> *temp;
        temp=front;

        queue_length-=1;
        for(int i=0; i<queue_length; i++)
        {
            temp = temp->next;
        }
        rear=temp;
        delete rear->next;
        rear->next = NULL;
        return item;
    }
    string printQueue()
    {
        node<data_type> *temp = front->next;
        string print("<");
        for (int i = 0; i < queue_length; i++)
        {
            if (i == 0)
                print.append("| ");

            print.append(to_string(temp->element));
            temp = temp->next;
            if (i != length() - 1)
                print.append(" ");
        }

        print.append("> \n");
        return print;
    }
};
