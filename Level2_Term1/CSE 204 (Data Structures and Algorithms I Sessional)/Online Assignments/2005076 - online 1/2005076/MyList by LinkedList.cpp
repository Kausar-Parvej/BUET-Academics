#include <bits/stdc++.h>

using namespace std;

template <class data>
class LinkedNode
{
public:
    data element;
    LinkedNode *next;
    LinkedNode(data item, LinkedNode *nextItem = NULL)
    {
        element = item;
        next = nextItem;
    }
    LinkedNode(LinkedNode *nextItem = NULL)
    {
        element = -1;
        next = nextItem;
    }
};

template <class data>
class MyLinkedList
{
    LinkedNode<data> *head;
    LinkedNode<data> *current;
    LinkedNode<data> *tail;
    int length;

public:
    MyLinkedList()
    {
        head = current = tail = new LinkedNode<data>;
        length = 0;
    }
    MyLinkedList(int X)
    {
        head = current = tail = new LinkedNode<data>;
        length = 0;
    }
    MyLinkedList(int X, int K, data var[])
    {

        head = current = tail = new LinkedNode<data>;
        length = 0;

        for (int i = 0; i < K; i++)
        {
            this->pushBack(var[i]);

            if (i < K / 2)
            {
                current = current->next;
            }
        }
    }
    ~MyLinkedList()
    {
        while (head != NULL)
        {
            current = head;
            head = head->next;
            delete current;
        }
    }

    int size()
    {
        return length;
    }

    void push(data item)
    {
        LinkedNode<data> *temp;
        temp = new LinkedNode<data>(item, current->next);
        current->next = temp;

        if (tail == current)
        {
            tail = current->next;
        }
        length++;
    }

    void pushBack(data item)
    {
        LinkedNode<data> *temp;
        temp = new LinkedNode<data>(item);
        tail->next = temp;
        tail = temp;
        length++;
    }

    data erase()
    {
        if (current->next == NULL)
            return -1;
        data item = current->next->element;
        LinkedNode<data> *temp = current->next;

        if (current->next == tail)
        {
            tail = current;
        }
        current->next = current->next->next;
        delete temp;
        length--;

        if (current == tail)
        {
            this->prev();
        }
        return item;
    }

    void setToBegin()
    {
        current = head;
    }
    void setToEnd()
    {
        LinkedNode<data> *temp = head;
        while (temp->next != tail)
            temp = temp->next;
        current = temp;
    }

    void prev()
    {
        if (current == head)
            return;

        LinkedNode<data> *temp = head;
        while (temp->next != current)
            temp = temp->next;
        current = temp;
    }

    void next()
    {
        if (current->next != tail)
            current = current->next;
    }

    int currPos()
    {
        LinkedNode<data> *temp = head;
        int i;
        for (i = 0; current != temp; i++)
            temp = temp->next;
        return i;
    }

    void setToPos(int pos)
    {
        if (pos >= 0 && pos < length)
        {
            current = head;
            for (int i = 0; i < pos; i++)
                current = current->next;
        }
    }

    data getValue()
    {
        if (current->next == NULL)
            return -1;
        return current->next->element;
    }

    int find(data item)
    {
        if(head->next == NULL)
            return -1;
        LinkedNode<data> *temp = head->next;
        for (int i = 0; i < length; i++)
        {
            if (temp->element == item)
                return i;

            temp = temp->next;
        }
        return -1;
    }

    void clear()
    {
        while (head != NULL)
        {
            current = head;
            head = head->next;
            delete current;
        }
        head = current = tail = new LinkedNode<data>;
        length = 0;
    }

    string printList()
    {
        LinkedNode<data> *temp;
        temp = head->next;
        string print("<");
        if (head == current && current != tail)
            print.append("| ");
        for (int i = 0; i < length; i++)
        {
            print.append(to_string(temp->element));
            if (temp == current)
                print.append(" |");
            temp = temp->next;
            if (i != length - 1)
                print.append(" ");
        }

        print.append("> \n");
        return print;
    }

    MyLinkedList merge(MyLinkedList<int> &list2)
    {

        int a=this->size();
        int b=list2.size();
        MyLinkedList<int> tempList1(a);
        MyLinkedList<int> tempList2(b);

        this->setToBegin();
        list2.setToBegin();

        for(int i =0; i<a; i++)
        {
            if(tempList1.find(this->getValue()) == -1)
                tempList1.pushBack(this->getValue());

            this->next();
        }
        for(int i =0; i<b; i++)
        {
            if(tempList2.find(list2.getValue()) == -1)
                tempList2.pushBack(list2.getValue());

            list2.next();

        }

        a=tempList1.size();
        b=tempList2.size();
        int n=a+b;
        int temp1=0,temp2=0;
        MyLinkedList<int> temp(n);

        tempList1.setToBegin();
        tempList2.setToBegin();

        int t= a>b? a:b;

        for(int i=0; i<t; i++)
        {
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

    MyLinkedList<int> list1(10,3,a);
    MyLinkedList<int> list2(12,6,b);

    MyLinkedList<int> list3(20);

    list3=list1.merge(list2);
    cout<<list3.printList();

    return 0;
}

