#include <bits/stdc++.h>
using namespace std;

#define INF 100001
typedef pair<int, int> pairs;

int N, M;
vector<pair<pairs, int>> edges;

vector<int> distance_dijkstra;
vector<int> parent_dijkstra;

vector<int> path_length;

void print_path(int node, vector<int> path) {
    if (path[node] == -1) {
        cout << node;
        return;
    }
    print_path(path[node], path);
    cout << "->" << node;
}



void dijkstra(int source) {

    path_length.resize(N,10);
    path_length[source]=0;

    vector<pairs> adj[N];
    for (auto edge : edges) {
        pairs temp = edge.first;
        int weight = abs(edge.second);
        adj[temp.first].push_back(make_pair(temp.second, weight));
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
                path_length[v] = path_length[u] + 1;
            }
            else if(distance_dijkstra[v] >= distance_dijkstra[u] + w  && path_length[u] + 1 < path_length[v]){
                distance_dijkstra[v] = distance_dijkstra[u] + w;
                parent_dijkstra[v] = u;
                Q.push(make_pair(distance_dijkstra[v], v));
                path_length[v] = path_length[u] + 1;
            }
        }
    }
}

int main() {

    int n, m;
    cin >> n >> m;

    N = n;
    M = m;

    int u, v, weight;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> weight;
        pair<int, int> temp = make_pair(u, v);
        edges.push_back(make_pair(temp, weight));
    }

    int s, d;
    cin >> s >> d;

    dijkstra(s);
    if(distance_dijkstra[d]==INF) {
        cout << "no path" << "\n";
    } else {
        cout << distance_dijkstra[d] << "\n";

        print_path(d, parent_dijkstra);
    }

    cout << "\n";

    return 0;
}
