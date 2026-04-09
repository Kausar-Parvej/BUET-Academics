#include <bits/stdc++.h>
using namespace std;

#define N 1000001
vector<int> adj[N];
bool visitt[N];

vector<int> ans;
bool flag;
bool inPath[N];

void dfs_visit(int v)
{
    visitt[v] = true;
    for (int i = 0; i < adj[v].size(); i++)
    {
        if (visitt[adj[v][i]] == false)
        {
            visitt[adj[v][i]] == true;
            dfs_visit(adj[v][i]);
        }
        if (inPath[adj[v][i]] == false)
        {
           inPath[adj[v][i]] == true;
        }
        else{
            flag = true;
        }
    }
    inPath[v] = false;
    ans.push_back(v);
}

int main()
{
    int n, m;
    cin >> n >> m;
    flag = false;

    int a, b, root;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj[a].push_back(b);
        if (i == 0)
            root = a;
    }

    for (int i = 0; i <= n; i++)
    {
        visitt[i] = false;
        inPath[i] = false;
    }

    for (int i = 1; i <= n; i++)
    {
        if (visitt[i] == false)
        {
            inPath[i] = true;
            dfs_visit(i);
        }
    }
    if (flag == true)
        cout << "IMPOSSIBLE" << "\n";
    else
    {
        for (int i = ans.size() - 1; i >= 0; i--)
        {
            cout << ans[i] << " ";
        }
    }
    return 0;
}