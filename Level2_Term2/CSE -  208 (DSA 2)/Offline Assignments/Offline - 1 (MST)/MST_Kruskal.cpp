#include <bits/stdc++.h>
using namespace std;


#define input_file "in.txt"
#define output_file "kruskal.txt"

typedef pair<int, int> pairs;

void init(int parent[], int rank[], int size)
{
    for (int i = 0; i < size; i++)
    {
        parent[i] = i;
        rank[i] = 1;
    }
}

int find(int parent[], int size, int v)
{
    if (parent[v] == v)
        return v;
    parent[v] = find(parent, size, parent[v]);
    return parent[v];
}

void unite(int parent[], int rank[], int size, int u, int v)
{
    int pu = find(parent, size, u);
    int pv = find(parent, size, v);

    if (pu == pv)
        return;

    if (rank[pu] > rank[pv])
        parent[pv] = pu;

    else if (rank[pu] < rank[pv])
        parent[pu] = pv;

    else
    {
        parent[pv] = pu;
        rank[pu]++;
    }
}

int main()
{

    ifstream fin(input_file);
    ofstream fout(output_file);

    int n, m;
    fin >> n >> m;
    int total_weight = 0;

    vector<pair<int, pairs>> edges;

    int v1, v2, weights;
    for (int i = 0; i < m; i++)
    {
        fin >> v1 >> v2 >> weights;
        pairs temp = make_pair(v1, v2);
        edges.push_back(make_pair(weights, temp));
    }

    sort(edges.begin(), edges.end());

    int parent[n];
    int rank[n];
    init(parent, rank, n);

    vector<pairs> path;

    for (auto edge : edges)
    {
        pairs temp = edge.second;
        if (find(parent, n, temp.first) != find(parent, n, temp.second))
        {
            total_weight += edge.first;
            path.push_back(make_pair(temp.first,temp.second));
            unite(parent, rank, n, temp.first, temp.second);
        }
    }

    cout << "Kruskal's Algorithm:\n\n";
    cout << "Total weight = " << total_weight << "\n";

    fout << "Kruskal's Algorithm:\n\n";
    fout << "Total weight = " << total_weight << "\n";

    for(auto edge : path){
        cout<<edge.first<<" "<<edge.second<<"\n";
        fout<<edge.first<<" "<<edge.second<<"\n";
    }


    return 0;
}
