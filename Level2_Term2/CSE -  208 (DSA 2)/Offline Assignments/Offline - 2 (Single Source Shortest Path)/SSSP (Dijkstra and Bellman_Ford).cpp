#include <bits/stdc++.h>
using namespace std;

#define input_file "Input.txt"
#define output_file "Output.txt"
ifstream fin(input_file);
ofstream fout(output_file);


#define INF INT_MAX/2
typedef pair<int, int> pairs;

int N, M;
vector<pair<pairs, int>> edges;

vector<int> distance_dijkstra;
vector<int> parent_dijkstra;

vector<int> distance_bellman;
vector<int> parent_bellman;

void print_path(int node, vector<int> path) {
    if (path[node] == -1) {
        cout << node;
        fout<<node;
        return;
    }
    print_path(path[node], path);
    cout << "->" << node;
    fout << "->" << node;
}

bool bellman_ford(int source) {
    bool flag = true;

    distance_bellman.resize(2*N);
    parent_bellman.resize(2*N);
    for (int i = 0; i < N; i++) {
        distance_bellman[i] = INF;
        parent_bellman[i] = -1;
    }

    distance_bellman[source] = 0;

    for (int i = 0; i < N; i++) {
        for (auto temp : edges) {
            int u = temp.first.first;
            int v = temp.first.second;
            int weight = temp.second;

            if (distance_bellman[v] > distance_bellman[u] + weight) {
                distance_bellman[v] = distance_bellman[u] + weight;
                parent_bellman[v] = u;
            }
        }
    }

    for (auto temp : edges) {
        int u = temp.first.first;
        int v = temp.first.second;
        int weight = temp.second;

        if (distance_bellman[v] > distance_bellman[u] + weight) {
            flag = false;
            return flag;
        }
    }
    return flag;
}

void dijkstra(int source) {

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
            }
        }
    }
}

int main() {

    int n, m;
    fin >> n >> m;

    N = n;
    M = m;

    int u, v, weight;
    for (int i = 0; i < m; i++) {
        fin >> u >> v >> weight;
        pair<int, int> temp = make_pair(u, v);
        edges.push_back(make_pair(temp, weight));
    }

    int s, d;
    fin >> s >> d;

    cout << "Bellman Ford Algorithm:\n";
    fout << "Bellman Ford Algorithm:\n";

    bool flag = bellman_ford(s);
    if (flag == true) {

        if(distance_bellman[d]==INF) {
            cout << "no path" << "\n";
            fout << "no path" << "\n";
        } else {
            cout << distance_bellman[d] << "\n";
            fout << distance_bellman[d] << "\n";

            print_path(d, parent_bellman);
        }

        cout << "\n";
        fout << "\n";
    } else {
        cout << "Negative weight cycle present\n";
        fout << "Negative weight cycle present\n";
    }


    cout << "\nDijkstra Algorithm:\n";
    fout << "\nDijkstra Algorithm:\n";

    dijkstra(s);
    if(distance_dijkstra[d]==INF) {
        cout << "no path" << "\n";
        fout << "no path" << "\n";
    } else {
        cout << distance_dijkstra[d] << "\n";
        fout << distance_dijkstra[d] << "\n";

        print_path(d, parent_dijkstra);
    }


    cout << "\n";
    fout << "\n";

    return 0;
}
