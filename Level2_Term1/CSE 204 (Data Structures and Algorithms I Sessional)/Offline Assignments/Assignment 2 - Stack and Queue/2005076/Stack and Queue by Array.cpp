#include <bits/stdc++.h>
using namespace std;

template <class data_type>
class Array_Stack
{
    int capacity;
    int top;
    data_type *array;

public:
    Array_Stack(int size = 5)
    {
        capacity = size;
        top = 0;
        array = new data_type[capacity];
    }
    ~Array_Stack()
    {
        delete[] array;
    }

    void clear()
    {
        delete[] array;
        capacity = 5;
        top = 0;
        array = new int[capacity];
    }

    void push(data_type item)
    {
        if (top >= capacity)
        {
            data_type temp[top];
            for (int i = 0; i < top; i++)
            {
                temp[i] = array[i];
            }
            delete[] array;
            capacity = 2 * capacity;
            array = new data_type[2 * capacity];
            for (int i = 0; i < top; i++)
            {
                array[i] = temp[i];
            }
            array[top] = item;
            top++;
        }
        else
        {
            array[top] = item;
            top++;
        }
    }

    data_type pop()
    {
        data_type temp1;
        if (top <= 0)
        {
            return -1;
        }
        else
            temp1 = array[top - 1];

        if (2 * (top - 1) < capacity && capacity > 8)
        {
            data_type temp[top];
            for (int i = 0; i < top - 1; i++)
            {

                temp[i] = array[i];
            }
            delete[] array;
            capacity = capacity / 2;
            array = new data_type[capacity];
            for (int i = 0; i < top - 1; i++)
            {
                array[i] = temp[i];
            }
            top--;
        }

        else
        {
            if (top <= 1)
            {
                capacity = 5;
                delete[] array;
                array = new data_type[5];
            }
            top--;
        }
        return temp1;
    }

    int length()
    {
        return top;
    }

    data_type topValue()
    {
        if (top <= 0)
            return -1;

        return array[top - 1];
    }

    string printStack()
    {

        string print("<");
        for (int i = 0; i < top; i++)
        {
            if (i == top - 1)
                print.append("| ");

            print.append(to_string(array[i]));
            if (i != top - 1)
                print.append(" ");
        }

        print.append("> \n");
        return print;
    }
};

//------------------------------Implementing Queue---------------------------------------------//

template <class data_type>
class Array_Queue
{
    int capacity;
    int front;
    int rear;
    data_type *array;

public:
    Array_Queue(int size = 5)
    {
        capacity = size + 1;
        front = 1;
        rear = 0;
        array = new data_type[capacity];
    }

    ~Array_Queue()
    {
        delete[] array;
    }

    void clear()
    {
        delete[] array;
        capacity = 5;
        front = 1;
        rear = 0;
        array = new int[capacity];
    }

    void enqueue(data_type item)
    {
        if ((rear + 2) % capacity == front)
        {
            data_type temp[capacity];
            for (int i = 0; i < capacity; i++)
                temp[i] = array[i];

            delete[] array;
            int n = capacity;
            capacity = 2 * capacity;
            array = new data_type[capacity];
            for (int i = 0; i < n - 1; i++)
            {
                array[i] = temp[(front + i) % n];
            }

            front = 0;
            rear = n - 1;
            array[rear] = item;
        }
        else
        {
            rear = (rear + 1) % capacity;
            array[rear] = item;
        }
    }

    data_type dequeue()
    {
        if (length() == 0){
            return -1;
        }

        data_type item = array[front];
        front = (front + 1) % capacity;
        return item;
    }

    int length()
    {
        int n = (rear + capacity - front + 1) % capacity;
        return n;
    }

    data_type frontValue()
    {
        if (length() == 0)
            return -1;

        return array[front];
    }

    data_type rearValue()
    {
        if (length() == 0)
            return -1;

        return array[rear];
    }

    data_type leaveQueue()
    {
        if (length() == 0)
            return -1;

        data_type item = array[rear];
        rear = (rear - 1) % capacity;
        return item;
    }

    string printQueue()
    {
        int a=front;
        string print("<");
        for (int i = 0; i < length(); i++)
        {
            if (i == 0)
                print.append("| ");

            print.append(to_string(array[a]));
            a=(a+1)%capacity;
            if (i != length() - 1)
                print.append(" ");
        }

        print.append("> \n");
        return print;
    }
};
