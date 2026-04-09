#include "MinHeap_byArray.cpp"

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

    minHeap<int> my_minHeap(40);
    string str;
    int a,b;

    while (!fin.eof())
    {
        fin >> str;

        if (str == "INS")
        {
            fin >> a;
            my_minHeap.Insert(a);
            fout<<"INSERTED "<<a<<endl;
        }

        else if (str == "PRI")
        {
            fout<<my_minHeap.Print();
        }

        else if (str == "DEC")
        {
            fin >>a>>b;
            my_minHeap.DecreaseKey(a,b);
            fout<<a<<" decreased to "<<b<<endl;
        }

        else if (str == "FIN")
        {
            int ret=my_minHeap.FindMin();
            fout<<"FindMin returned "<<ret<<endl;
        }
        else if (str == "EXT")
        {
            int ret=my_minHeap.ExtractMin();
            fout<<"ExtractMin returned "<<ret<<endl;
        }
    }
    fin.close();

    cout << endl
         << "\t------>Check output.txt<------" << endl;

    return 0;
}
