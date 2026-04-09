#include "myBST.cpp"

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

#define input_file "input.txt"

using namespace std;
int main()
{
    ifstream fin(input_file);

    MyBst<int> mybst;
    char ch;
    int a;
    string str;

    while (!fin.eof())
    {
        fin >> ch;

        if (ch == 'I')
        {
            fin >> a;
            mybst.insert(a);
            mybst.current_state();
        }

        else if (ch == 'F')
        {
            fin >> a;
            mybst.find(a);
        }

        else if (ch == 'D')
        {
            fin >> a;
            mybst.Delete(a);
        }

        else if (ch == 'T')
        {
            fin >> str;
            mybst.traversal(str);
        }
    }
    fin.close();

    cout << endl
         << "\t------>Check output.txt<------" << endl;

    return 0;
}
