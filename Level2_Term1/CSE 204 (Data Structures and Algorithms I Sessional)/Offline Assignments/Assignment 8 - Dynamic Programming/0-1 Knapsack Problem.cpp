#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

#define input_file "input.txt"
#define output_file "output.txt"


using namespace std;

int main()
{
    ifstream fin(input_file);
    ofstream fout(output_file);

    int n;
    fin >> n;
    int weight[n + 1];
    int values[n + 1];
    int total_weight;

    set<int> path_index;

    weight[0] = 0;
    values[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        fin >> weight[i] >> values[i];
    }
    fin >> total_weight;
    int table[n + 1][total_weight + 1];

    for (int i = 0; i <= n; i++)
        table[i][0] = 0;
    for (int j = 0; j <= total_weight; j++)
        table[0][j] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= total_weight; j++)
        {
            if (weight[i] > j)
            {
                table[i][j] = table[i - 1][j];
            }
            else
            {
                table[i][j] = (table[i - 1][j - weight[i]] + values[i]) > table[i - 1][j] ? (table[i - 1][j - weight[i]] + values[i]) : table[i - 1][j];
            }
        }
    }

    fout << table[n][total_weight] << "\n";

    int i = n;
    int j = total_weight;

    while (table[i][j] != 0)
    {
        if (weight[i] > j)
        {
            i = i - 1;
        }
        else
        {
            if ((table[i - 1][j - weight[i]] + values[i]) > table[i - 1][j])
            {
                path_index.insert(i);
                j=j-weight[i];
            }
            i=i-1;
        }
    }

    /*for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= total_weight; j++)
        {
            cout << table[i][j] << " ";
        }
        cout << "\n";
    }*/

    for (auto k : path_index)
    {
        fout << weight[k] << " ";
        //cout<<k<<" ";
    }
    fout << "\n";


    fin.close();
    fout.close();

    cout << endl
         << "\t------>Check output.txt<------" << endl;

    return 0;
}
