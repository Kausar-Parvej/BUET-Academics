#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX / 2
typedef pair<int, int> pairs;

int N, M;
vector<pair<pairs, int>> edges;

vector<int> distance_dijkstra;
vector<int> parent_dijkstra;

map<string, int> toNum;
map<int, string> toStr;
map<int, int> layover;

void print_path(int node, vector<int> path) {
    if (path[node] == -1) {
        cout << toStr[node];
        return;
    }
    print_path(path[node], path);
    cout << " -> " << toStr[node];
}

void dijkstra(int source) {

    vector<pairs> adj[N];
    for (auto edge : edges) {
        pairs temp = edge.first;
        int weight = abs(edge.second);
        adj[temp.first].push_back(make_pair(temp.second, weight + layover[temp.second]));
        adj[temp.second].push_back(make_pair(temp.first, weight + layover[temp.first]));
    }

    distance_dijkstra.resize(N);
    parent_dijkstra.resize(N);
    for (int i = 0; i < N; i++) {
        distance_dijkstra[i] = INF;
        parent_dijkstra[i] = -1;
    }

    distance_dijkstra[source] = 0;
    priority_queue<pairs, vector<pairs>, greater<pairs>> Q;
    for (int i = 0; i < N; i++) {
        Q.push(make_pair(distance_dijkstra[i], i));
    }

    while (!Q.empty()) {
        pairs temp = Q.top();
        Q.pop();

        int u = temp.second;

        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (distance_dijkstra[v] > distance_dijkstra[u] + w) {
                distance_dijkstra[v] = distance_dijkstra[u] + w;
                parent_dijkstra[v] = u;
                Q.push(make_pair(distance_dijkstra[v], v));
            }
        }
    }
}

int main() {

    int n, m;
    cin >> n >> m;

    N = n;
    M = m;

    string u, v;
    int weight;
    for (int i = 0; i < n; i++) {
        cin >> u >> weight;
        toNum[u] = i;
        toStr[i] = u;
        layover[i] = weight;
    }

    for (int i = 0; i < m; i++) {
        cin >> u >> v >> weight;
        int a = toNum[u];
        int b = toNum[v];
        pair<int, int> temp = make_pair(a, b);
        edges.push_back(make_pair(temp, weight));
    }

    string a, b;
    cin >> a >> b;
    int s = toNum[a];
    int d = toNum[b];

    dijkstra(s);
    if (distance_dijkstra[d] == INF) {
        cout << "no path"
            << "\n";
    }
    else {
        cout << distance_dijkstra[d] << "\n";

        print_path(d, parent_dijkstra);
    }
    cout << "\n";

    return 0;
}
