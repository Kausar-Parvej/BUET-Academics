#include "Stack and Queue by Array.cpp"
#include "Stack and Queue by LinkedList.cpp"

#include <iostream>
#include <fstream>

#define input_file "task2_input.txt"
#define output_file "task2_output.txt"

using namespace std;

int main()
{
    ifstream fin(input_file);
    ofstream fout(output_file);

    // Array_Queue<int> line1(10);
    // Array_Stack<int> line2(10);

    LinkedList_Queue<int> line1(10);
    LinkedList_Stack<int> line2(10);

    int n, c;
    fin >> n >> c;

    int index[n + 1];
    int arrival[n + 1];
    int duration[n + 1];
    int start_play[n + 1];

    for (int i = 1; i <= n; i++)
    {
        index[i] = i;
        start_play[i] = -1;
        fin >> arrival[i];
        fin >> duration[i];
    }

    int num = 1;
    int next_play1 = 0;
    int next_play2 = 0;

    for (int i = arrival[1]; i <= c; i++)
    {

        if (i == next_play1)
        {
            if (line1.length() != 0)
            {
                // cout<<next_play1<<endl;
                int p = line1.dequeue();
                start_play[p] = next_play1;
                // cout << p << endl;
                next_play1 = next_play1 + duration[p];
            }
        }
        if (i == next_play2)
        {
            if (line2.length() != 0)
            {
                // cout<<next_play2<<endl;
                int p1 = line2.pop();
                start_play[p1] = next_play2;
                // cout << p1 << endl;
                next_play2 += duration[p1];
            }
        }

        if (i == arrival[num])
        {
            if (line1.length() >= 3)
            {
                if (line2.length() == 0)
                {
                    if (next_play2 > arrival[num])
                    {
                        line2.push(index[num]);
                    }
                    else
                    {
                        start_play[num] = arrival[num];
                        next_play2 = arrival[num] + duration[num];
                        // cout<<num<<endl;
                    }
                }

                else
                {
                    line2.push(index[num]);
                }
            }

            if (line1.length() == 0)
            {
                if (next_play1 > arrival[num])
                {
                    line1.enqueue(index[num]);
                }
                else
                {
                    start_play[num] = arrival[num];
                    next_play1 = arrival[num] + duration[num];
                }
            }
            else if (line1.length() < 3 && line1.length() != 0)
            {
                line1.enqueue(index[num]);
                // cout<<num<<endl;
            }

            ++num;
        }
    }
    for (int k = 1; k <= n; k++)
    {
        cout << k << " > ";
        fout << k << " > ";
        if (start_play[k] == -1)
        {
            cout << c << endl;
            fout << c << endl;
        }
        else if ((start_play[k] + duration[k]) >= c)
        {
            cout << c << endl;
            fout << c << endl;
        }
        else
        {
            cout << start_play[k] + duration[k] << endl;
            fout << start_play[k] + duration[k] << endl;
        }
    }

    // timestamp1 = a[1] + b[1];
    // cout<<1<<endl;

    /*for (int i = 2; i <= n; i++)
    {
        if (a[i] >= timestamp1)
        {
            int k=line1.dequeue();
            cout << k << endl;
            timestamp1 += b[k];
        }

        if (a[i] >= timestamp2  && line2.length() != 0)
        {
            int d=line2.pop();
            cout << d << endl;
            timestamp2 += b[d];
        }

        if (line1.length() < 3 )
        {
            line1.enqueue(i);

        }
        if(line1.length() == 3){
            if(line2.length()==0)
            {
                line2.push(i);
                cout<<i<<endl;
                timestamp2 = (a[i]+b[i]);
            }
            line2.push(i);
        }
    }*/

    cout << endl << "\t---->Check task2_output.txt<----" << endl;

    return 0;
}
