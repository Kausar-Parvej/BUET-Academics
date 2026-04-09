#include "MyList by Array.cpp"
#include "MyList by LinkedList.cpp"
#include <iostream>
#include<fstream>

#define input_file "lru_input.txt"
#define output_file "lru_output.txt"

using namespace std;

template <class type1, class type2>
class LRUCache
{
public:
    int capacity;

    //MyArrayList<type1> *key;
    //MyArrayList<type2> *value;

    MyLinkedList<type1> *key;
    MyLinkedList<type2> *value;

    LRUCache(int n)
    {
        capacity = n;

        //key = new MyArrayList<type1>(n);
        //value = new MyArrayList<type2>(n);

        key = new MyLinkedList<type1>(n);
        value = new MyLinkedList<type2>(n);
    }

    type2 get(type1 k)
    {
        int i = key->find(k);
        if (i == -1)
            return -1;
        value->setToPos(i);
        type2 val = value->getValue();

        value->erase();
        value->pushBack(val);
        key->setToPos(i);
        key->erase();
        key->pushBack(k);

        return val;
    }

    void put(type1 k, type2 v)
    {
        int i = key->find(k);
        if (i != -1)
        {
            key->setToPos(i);
            key->erase();
            key->pushBack(k);

            value->setToPos(i);
            value->erase();
            value->pushBack(v);
        }
        else
        {
            if (capacity > key->size())
            {
                key->pushBack(k);
                value->pushBack(v);
            }
            else
            {
                key->setToBegin();
                key->erase();
                value->setToBegin();
                value->erase();

                key->pushBack(k);
                value->pushBack(v);
            }
        }
    }
};

int main()
{
    ifstream fin(input_file);
    ofstream fout(output_file);

    int c, q;
    fin >> c >> q;

    LRUCache<int, int> cache(c);
    for (int i = 0; i < q; i++)
    {
        int a;
        fin>>a;

        if(a==1){
            int x;
            fin>>x;
            cout<<cache.get(x)<<endl;
            fout<<cache.get(x)<<endl;
        }
        if(a==2){
            int x,y;
            fin>>x>>y;
            cache.put(x,y);
        }
    }

    cout<<endl<<"\t---->Check lru_output.txt<----"<<endl;

    return 0;
}
