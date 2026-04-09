#include "Stack and Queue by Array.cpp"
#include "Stack and Queue by LinkedList.cpp"

#include <bits/stdc++.h>
#include <fstream>

#define input_file "input.txt"
#define output_file "output.txt"

using namespace std;
int main()
{

    ifstream fin(input_file);
    ofstream fout(output_file);

    int k, x;
    fin >> k >> x;
    //cin >> k >> x;

    //Array_Queue<int> queue(x);
    LinkedList_Queue<int> queue(x);

    int a;
    for (int i = 0; i < k; i++)
    {
        //cin >> a;
        fin>>a;
        queue.enqueue(a);
    }

    int m, y;
    fin >> m >> y;

    //Array_Stack<int> stack(y);
    LinkedList_Stack<int> stack(y);

    int b;
    for (int i = 0; i < m; i++)
    {
        fin >> b;
        stack.push(b);
    }

    int q;
    fin >> q;

    int f[q], p[q];
    for (int i = 0; i < q; i++)
        fin >> f[i] >> p[i];

    cout << queue.printQueue();
    cout << stack.printStack();
    fout << queue.printQueue();
    fout<<stack.printStack();
    for (int i = 0; i < q; i++)
    {
        if (f[i] == 1)
        {
            queue.clear();
            cout << queue.printQueue();
            cout << -1 << endl;
            fout << queue.printQueue();
            fout << -1 << endl;
        }

        else if (f[i] == 2)
        {
            queue.enqueue(p[i]);
            cout << queue.printQueue();
            cout << -1 << endl;
            fout << queue.printQueue();
            fout << -1 << endl;
        }

        else if (f[i] == 3)
        {
            int n = queue.dequeue();
            cout << queue.printQueue();
            cout << n << endl;
            fout << queue.printQueue();
            fout << n << endl;
        }

        else if (f[i] == 4)
        {
            int n = queue.length();
            cout << queue.printQueue();
            cout << n << endl;
            fout << queue.printQueue();
            fout << n << endl;
        }

        else if (f[i] == 5)
        {
            int n = queue.frontValue();
            cout << queue.printQueue();
            cout << n << endl;
            fout << queue.printQueue();
            fout << n << endl;
        }

        else if (f[i] == 6)
        {
            int n = queue.rearValue();
            cout << queue.printQueue();
            cout << n << endl;
            fout << queue.printQueue();
            fout << n << endl;
        }

        else if (f[i] == 7)
        {
            int n = queue.leaveQueue();
            cout << queue.printQueue();
            cout << n << endl;
            fout << queue.printQueue();
            fout << n << endl;
        }

        else if (f[i] == 8)
        {
            stack.clear();
            cout << stack.printStack();
            cout << -1 << endl;
            fout << stack.printStack();
            fout << -1 << endl;
        }

        else if (f[i] == 9)
        {
            stack.push(p[i]);
            cout << stack.printStack();
            cout << -1 << endl;
            fout << stack.printStack();
            fout << -1 << endl;
        }

        else if (f[i] == 10)
        {
            int n = stack.pop();
            cout << stack.printStack();
            cout << n << endl;
            fout << stack.printStack();
            fout << n << endl;
        }

        else if (f[i] == 11)
        {
            int n = stack.length();
            cout << stack.printStack();
            cout << n << endl;
            fout << stack.printStack();
            fout << n << endl;
        }

        else if (f[i] == 12)
        {
            int n = stack.topValue();
            cout << stack.printStack();
            cout << n << endl;
            fout << stack.printStack();
            fout << n << endl;
        }
    }
    fin.close();
    fout.close();

    cout << endl << "\t------>Check output.txt<------" << endl;

    return 0;
}
