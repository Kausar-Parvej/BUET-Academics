#include <bits/stdc++.h>
using namespace std;

#define INF 100000.1
typedef pair<int, int> pairs;
typedef pair<double, int> prob;

int N, M;
vector<pair<pairs, double>> edges;

vector<double> distance_dijkstra;
vector<int> parent_dijkstra;


void print_path(int node, vector<int> path) {
    if (path[node] == -1) {
        cout << node;
        return;
    }
    print_path(path[node], path);
    cout << " -> " << node;
}

void dijkstra(int source) {

    vector<pair<int,double>> adj[N];
    for (auto edge : edges) {
        pairs temp = edge.first;
        double weight = edge.second;
        adj[temp.first].push_back(make_pair(temp.second, weight ));
    }

    distance_dijkstra.resize(N);
    parent_dijkstra.resize(N);
    for (int i = 0; i < N; i++) {
        distance_dijkstra[i] = 0.0;
        parent_dijkstra[i] = -1;
    }

    distance_dijkstra[source] = 1;
    priority_queue<prob> Q;
    for (int i = 0; i < N; i++) {
        Q.push(make_pair(distance_dijkstra[i], i));
    }

    while (!Q.empty()) {
        pairs temp = Q.top();
        Q.pop();

        int u = temp.second;

        for (auto edge : adj[u]) {
            int v = edge.first;
            double w = edge.second;

            if (distance_dijkstra[v] < distance_dijkstra[u] * w) {
                distance_dijkstra[v] = distance_dijkstra[u] * w;
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

    int u, v;
    double weight;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> weight;
        pair<int, int> temp = make_pair(u, v);
        edges.push_back(make_pair(temp, weight));
    }

    int s, d;
    cin >> s >> d;

    dijkstra(s);
    if (distance_dijkstra[d] <= 0.0) {
        cout << "no path"
            << "\n";
    }
    else {
        cout <<"Most reliable path score: " <<distance_dijkstra[d] << "\n";
        print_path(d, parent_dijkstra);
    }
    cout << "\n";

    return 0;
}
