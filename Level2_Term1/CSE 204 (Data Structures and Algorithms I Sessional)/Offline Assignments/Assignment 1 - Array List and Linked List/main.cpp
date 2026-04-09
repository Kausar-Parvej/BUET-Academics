#include "MyList by Array.cpp"
#include "MyList by LinkedList.cpp"

#include <bits/stdc++.h>
#include <fstream>

#define input_file "list_input.txt"
#define output_file "list_output.txt"

using namespace std;
int main()
{
    ifstream fin(input_file);
    ofstream fout(output_file);


    int k, x;
    fin >> k >> x;

    int a[k];
    for (int i = 0; i < k; i++)
        fin >> a[i];

    //MyArrayList<int> list(x, k, a);
    MyLinkedList<int> list(x, k, a);

    int q;
    fin >> q;
    int f[q], p[q];
    for (int i = 0; i < q; i++)
        fin >> f[i] >> p[i];

    cout << list.printList();
    fout << list.printList();
    for (int i = 0; i < q; i++)
    {
        if (f[i] == 1)
        {
            int n = list.size();
            cout << list.printList();
            cout << n << endl;
            fout << list.printList();
            fout << n << endl;

        }

        else if (f[i] == 2)
        {
            list.push(p[i]);
            cout<<list.printList();
            cout << -1 << endl;
            fout << list.printList();
            fout << -1 << endl;
        }

        else if (f[i] == 3)
        {
            list.pushBack(p[i]);
            cout<<list.printList();
            cout << -1 << endl;
            fout << list.printList();
            fout << -1 << endl;
        }

        else if (f[i] == 4)
        {
            int n = list.erase();
            cout << list.printList();
            cout << n << endl;
            fout << list.printList();
            fout << n << endl;
        }

        else if (f[i] == 5)
        {
            list.setToBegin();
            cout<<list.printList();
            cout << -1 << endl;
            fout << list.printList();
            fout << -1 << endl;
        }

        else if (f[i] == 6)
        {
            list.setToEnd();
            cout<<list.printList();
            cout << -1 << endl;
            fout << list.printList();
            fout << -1 << endl;
        }

        else if (f[i] == 7)
        {
            list.prev();
            cout<<list.printList();
            cout << -1 << endl;
            fout << list.printList();
            fout << -1 << endl;
        }

        else if (f[i] == 8)
        {
            list.next();
            cout<<list.printList();
            cout << -1 << endl;
            fout << list.printList();
            fout << -1 << endl;
        }

        else if (f[i] == 9)
        {
            int n = list.currPos();
            cout << list.printList();
            cout << n << endl;
            fout << list.printList();
            fout << n << endl;
        }

        else if (f[i] == 10)
        {
            list.setToPos(p[i]);
            cout<<list.printList();
            cout << -1 << endl;
            fout << list.printList();
            fout << -1 << endl;
        }

        else if (f[i] == 11)
        {
            int n = list.getValue();
            cout << list.printList();
            cout << n << endl;
            fout << list.printList();
            fout << n << endl;
        }

        else if (f[i] == 12)
        {
            int n = list.find(p[i]);
            cout << list.printList();
            cout << n << endl;
            fout << list.printList();
            fout << n << endl;
        }

        else if (f[i] == 13)
        {
            list.clear();
            cout<<list.printList();
            cout << -1 << endl;
            fout << list.printList();
            fout << -1 << endl;
        }
    }
    fin.close();
    fout.close();

    cout<<endl<<"\t---->Check list_output.txt<----"<<endl;

    return 0;
}
