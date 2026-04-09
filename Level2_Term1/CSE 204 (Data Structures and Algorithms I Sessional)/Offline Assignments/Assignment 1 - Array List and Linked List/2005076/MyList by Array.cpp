#include <bits/stdc++.h>

using namespace std;

template <class data>
class MyArrayList
{
    int capacity;
    int length;
    int positon;
    data *arr;

public:
    MyArrayList()
    {
        capacity = 1;
        length = 0;
        positon = 0;
        arr = NULL;
    }
    MyArrayList(int X)
    {
        capacity = X;
        length = 0;
        positon = 0;
        arr = new data[X];
    }
    MyArrayList(int X, int K, data var[])
    {
        capacity = X;
        length = K;
        positon = K / 2;
        arr = new data[X];
        for (int i = 0; i < K; i++)
        {
            arr[i] = var[i];
        }
    }
    ~MyArrayList()
    {
        delete[] arr;
    }

    int size()
    {
        return length;
    }

    void push(data item)
    {
        if (length >= capacity)
        {
            data temp[length];
            for (int i = 0; i < length; i++)
            {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = new data[2 * length];
            for (int i = 0; i <= length; i++)
            {
                if (i < positon)
                    arr[i] = temp[i];

                else if (i = positon)
                    arr[positon] = item;

                else if (i > positon)
                    arr[i] = temp[i - 1];
            }
            length++;
            capacity = 2 * capacity;
        }

        else
        {
            for (int i = length; i > positon; i--)
            {
                arr[i] = arr[i - 1];
            }
            arr[positon] = item;
            length++;
        }
    }

    void pushBack(data item)
    {
        if (length >= capacity)
        {
            data temp[length];
            for (int i = 0; i < length; i++)
            {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = new data[2 * length];
            for (int i = 0; i < length; i++)
            {
                arr[i] = temp[i];
            }
            arr[length] = item;
            length++;
            capacity = 2 * capacity;
        }
        else
        {
            arr[length] = item;
            length++;
        }
    }

    data erase()
    {
        data temp1;
        if(length <= 0)
            return -1;
        else
            temp1 = arr[positon];
        if (2 * (length - 1) < capacity && capacity > 5)
        {
            data temp[length];
            for (int i = 0; i < length - 1; i++)
            {
                if (i >= positon)
                {
                    temp[i] = arr[i + 1];
                }
                else
                {
                    temp[i] = arr[i];
                }
            }
            delete[] arr;
            capacity = capacity / 2;
            arr = new data[capacity];
            for (int i = 0; i < length - 1; i++)
            {
                arr[i] = temp[i];
            }
            length--;
        }
        else
        {
            for (int i = positon; i < length - 1; i++)
            {
                arr[i] = arr[i + 1];
            }

            if (length <= 1)
            {
                length = 1;
                capacity = 3;
                positon = 0;
                delete[] arr;
                arr = new data[3];
            }
            length--;
        }
        if (length <= positon)
            this->prev();
        return temp1;
    }

    void setToBegin()
    {
        this->positon = 0;
    }
    void setToEnd()
    {
        this->positon = length - 1;
    }
    void prev()
    {
        if (positon != 0)
            positon -= 1;
    }
    void next()
    {
        if (positon != length - 1)
            positon += 1;
    }

    int currPos()
    {
        return positon;
    }

    void setToPos(int pos)
    {
        if (pos < length && pos >= 0)
            positon = pos;
    }

    data getValue()
    {
        return arr[positon];
    }

    int find(data item)
    {
        for (int i = 0; i < length; i++)
        {
            if (item == arr[i])
                return i;
        }
        return -1;
    }

    void clear()
    {
        length = 0;
        capacity = 3;
        positon = 0;
        delete[] arr;
        arr = new data[capacity];
    }

    string printList()
    {
        string print("<");
        for (int i = 0; i < length; i++)
        {
            if (i == positon)
                print.append("| ");
            print.append(to_string(arr[i]));
            if (i != length - 1)
                print.append(" ");
        }
        print.append(">\n");
        return print;
    }
};
