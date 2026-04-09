#include <bits/stdc++.h>
using namespace std;

#define input_file "in.txt"
#define output_file "prim.txt"

#define INF INT_MAX
typedef pair<int, int> pairs;

int main()
{
    ifstream fin(input_file);
    ofstream fout(output_file);

    int n, m;
    fin >> n >> m;
    int total_weight = 0;

    vector<pairs> adj[n];
    int root;
    int v1, v2, weights;
    for (int i = 0; i < m; i++)
    {
        fin >> v1 >> v2 >> weights;
        adj[v1].push_back(make_pair(v2, weights));
        adj[v2].push_back(make_pair(v1, weights));
        if (i == 0)
            root = v1;
    }

    int key[n];
    int parent[n];
    bool taken[n];
    for (int i = 0; i < n; i++)
    {
        key[i] = INF;
        parent[i] = -1;
        taken[i] = false;
    }
    root =4;
    key[root] = 0;
    priority_queue<pairs, vector<pairs>, greater<pairs>> pq;
    pq.push(make_pair(key[root], root));
    for (int i = 0; i < n; i++)
    {
        if (i != root)
        {
            pq.push(make_pair(key[i], i));
        }
    }

    int flag = 0;
    //int count = 0;

    while (!pq.empty() && flag < n)
    {
        //count++;
        pairs temp;
        temp = pq.top();
        pq.pop();

        int u = temp.second;

        if (taken[u])
            continue;
        taken[u] = true;
        total_weight += key[u];
        flag++;

        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (!taken[v] && weight < key[v])
            {
                parent[v] = u;
                key[v] = weight;
                pq.push(make_pair(key[v], v));
            }
        }
    }
    //cout << "count = "<< count<<"\n";
    cout << "Prim's Algorithm:\n\n";
    cout << "Total weight = " << total_weight << "\n";
    cout << "Root node = " << root << "\n";

    fout << "Prim's Algorithm:\n\n";
    fout << "Total weight = " << total_weight << "\n";
    fout << "Root node = " << root << "\n";

    for(int i=0; i<n; i++)
    {
        if(parent[i] != -1)
        {
            cout<<parent[i]<<" "<<i<<"\n";
            fout<<parent[i]<<" "<<i<<"\n";
        }
    }

    return 0;
}
