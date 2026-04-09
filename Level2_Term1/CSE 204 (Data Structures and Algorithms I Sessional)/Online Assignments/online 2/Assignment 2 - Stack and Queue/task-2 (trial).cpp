#include "Stack and Queue by Array.cpp"
#include "Stack and Queue by LinkedList.cpp"

#include <iostream>
#include <fstream>

// #define input_file "task2_input.txt"
// #define output_file "task2_output.txt"

using namespace std;

class player
{
public:
    int index;
    int arrival;
    int duration;
    int start_play;

    player()
    {
        index = 0;
        arrival = 0;
        duration = 0;
        start_play = -1;
    }
};

int main()
{
    // ifstream fin(input_file);
    // ofstream fout(output_file);

    Array_Queue<player> line1(10);
    Array_Stack<player> line2(10);

    int n, c;
    cin >> n >> c;

    int a[n + 1];
    int b[n + 1];
    player player_array[n + 2];
    a[0] = 0;
    b[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        player_array[i].index = i;
        player_array[i].start_play = -1;
        cin >> player_array[i].arrival;
        cin >> player_array[i].duration;
    }

    int p = 1;
    int next_play1 = 0;
    int next_play2 = 0;

    for (int i = player_array[1].arrival; i <= c; i++)
    {

        if (i == next_play1)
        {
            if (line1.length() != 0)
            {
                // cout<<next_play1<<endl;
                player p = line1.dequeue();
                player_array[p.index].start_play = next_play1;
                // cout << p.index << endl;
                next_play1 = next_play1 + p.duration;
            }
        }
        if (i == next_play2)
        {
            if (line2.length() != 0)
            {
                // cout<<next_play2<<endl;
                player p1 = line2.pop();
                player_array[p1.index].start_play = next_play2;
                //cout << p1.index << endl;
                next_play2 += p1.duration;
            }
        }

        if (i == player_array[p].arrival)
        {
            if (line1.length() >= 3)
            {
                if (line2.length() == 0)
                {
                    if (next_play2 > player_array[p].arrival)
                    {
                        line2.push(player_array[p]);
                    }
                    else
                    {
                        player_array[p].start_play = player_array[p].arrival;
                        next_play2 = player_array[p].arrival + player_array[p].duration;
                        // cout<<p<<endl;
                    }
                }

                else
                {
                    line2.push(player_array[p]);
                }
            }

            if (line1.length() == 0)
            {
                if (next_play1 > player_array[p].arrival)
                {
                    line1.enqueue(player_array[p]);
                }
                else
                {
                    player_array[p].start_play = player_array[p].arrival;
                    next_play1 = player_array[p].arrival + player_array[p].duration;
                }
            }
            else if (line1.length() < 3 && line1.length() != 0)
            {
                line1.enqueue(player_array[p]);
                // cout<<p<<endl;
            }

            ++p;
        }
    }
    for (int k = 1; k <= n; k++)
    {
        cout << k << " > ";
        if (player_array[k].start_play == -1)
        {
            cout << c << endl;
        }
        else if((player_array[k].start_play + player_array[k].duration) >= c)
            cout<<c<<endl;
        else
            cout << player_array[k].start_play + player_array[k].duration << endl;
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

    // cout << endl << "\t---->Check lru_output.txt<----" << endl;

    return 0;
}
