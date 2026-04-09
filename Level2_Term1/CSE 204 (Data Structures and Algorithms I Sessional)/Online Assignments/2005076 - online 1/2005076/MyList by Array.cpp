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
        if(length==0)
            return -1;
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

    MyArrayList merge(MyArrayList<int> &list2)
    {

        int a=this->size();
        int b=list2.size();
        MyArrayList<int> tempList1(a);
        MyArrayList<int> tempList2(b);

        this->setToBegin();
        list2.setToBegin();

        for(int i =0; i<a; i++)
        {
            if(tempList1.find(this->getValue()) == -1)
                tempList1.pushBack(this->getValue());
            this->next();

        }
        cout<<"checking 1..."<<tempList1.printList();
        for(int i =0; i<b; i++)
        {
            if(tempList2.find(list2.getValue()) == -1)
                tempList2.pushBack(list2.getValue());

            list2.next();

        }
        cout<<"checking 2..."<<tempList2.printList();

        a=tempList1.size();
        b=tempList2.size();
        int n=a+b;
        int temp1=0,temp2=0;
        MyArrayList<int> temp(n+1);

        tempList1.setToBegin();
        tempList2.setToBegin();

        int t= a>b? a:b;

        for(int i=0; i<t; i++){
            if(temp1<a)
            {
                temp.pushBack(tempList1.getValue());
                tempList1.next();
                temp1++;
            }
            if(temp2<b)
            {
                temp.pushBack(tempList2.getValue());
                tempList2.next();
                temp2++;
            }
        }
        return temp;

    }
};

int main()
{
    int a[]={1, 2, 2};
    int b[]={3, 3, 4, 4, 5, 6};

    MyArrayList<int> list1(10,3,a);
    MyArrayList<int> list2(12,6,b);

    MyArrayList<int> list3(20);

    list3=list1.merge(list2);
    cout<<list3.printList();

    return 0;
}
