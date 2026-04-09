#include <bits/stdc++.h>
using namespace std;

#define input_file "Input.txt"
#define output_file "Output.txt"
ifstream fin(input_file);
ofstream fout(output_file);

#define INF 1000001
typedef pair<int, int> pairs;

int N, M;
vector<pair<pairs, int>> edges;

vector<int> distance_dijkstra;
vector<int> parent_dijkstra;

void print_path(int node, vector<int> path)
{
    if (path[node] == -1)
    {
        cout << node;
        fout << node;
        return;
    }
    print_path(path[node], path);
    cout << " -> " << node;
    fout << " -> " << node;
}

void dijkstra(int source)
{

    vector<pairs> adj[N];
    for (auto edge : edges)
    {
        pairs temp = edge.first;
        int weight = abs(edge.second);
        adj[temp.first].push_back(make_pair(temp.second, weight));
    }

    distance_dijkstra.resize(N);
    parent_dijkstra.resize(N);
    for (int i = 0; i < N; i++)
    {
        distance_dijkstra[i] = INF;
        parent_dijkstra[i] = -1;
    }

    distance_dijkstra[source] = 0;
    priority_queue<pairs, vector<pairs>, greater<pairs>> Q;
    for (int i = 0; i < N; i++)
    {
        Q.push(make_pair(distance_dijkstra[i], i));
    }

    while (!Q.empty())
    {
        pairs temp = Q.top();
        Q.pop();

        int u = temp.second;

        for (auto edge : adj[u])
        {
            int v = edge.first;
            int w = edge.second;

            if (distance_dijkstra[v] > distance_dijkstra[u] + w)
            {
                distance_dijkstra[v] = distance_dijkstra[u] + w;
                parent_dijkstra[v] = u;
                Q.push(make_pair(distance_dijkstra[v], v));
            }
        }
    }
}

int main()
{

    int n, m;
    fin >> n >> m;

    N = n;
    M = m;

    int u, v, weight;
    for (int i = 0; i < m; i++)
    {
        fin >> u >> v >> weight;
        pair<int, int> temp = make_pair(u, v);
        edges.push_back(make_pair(temp, weight));
    }

    int s;
    fin >> s;

    dijkstra(s);
    vector<int> fromS;
    vector<int> go_path;

    for(auto temp : distance_dijkstra){
        fromS.push_back(temp);
    }
    for(auto temp : parent_dijkstra){
        go_path.push_back(temp);
    }

    int min_time = INF;
    int d = s;
    for (int i = 0; i < n; i++)
    {
        if (i == s)
            continue;
        dijkstra(i);
        int temp = fromS[i] + distance_dijkstra[s];
        if(temp < min_time){
            min_time = temp;
            d = i;
        }
    }

    dijkstra(s);
    int go_time = distance_dijkstra[d];
    dijkstra(d);
    int return_time = distance_dijkstra[s];

    cout<<"Minimum total time: "<<go_time+return_time<<"\n";
    fout<<"Minimum total time: "<<go_time+return_time<<"\n";

    cout<<"\nPaths:\n";
    fout<<"\nPaths:\n";
    print_path(d,go_path);
    cout<<" (time: "<<go_time<<")\n";
    fout<<" (time: "<<go_time<<")\n";


    print_path(s,parent_dijkstra);
    cout<<" (time: "<<return_time<<")\n";
    fout<<" (time: "<<return_time<<")\n";

    return 0;
}
