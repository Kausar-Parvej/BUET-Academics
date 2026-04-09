#include <bits/stdc++.h>
using namespace std;

#define INF 100001
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
        return;
    }
    print_path(path[node], path);
    cout << "->" << node;
}



void dijkstra(int source) {

    vector<pairs> adj[N];
    vector<int> ad[N];
    int extra[N]={0};
    bool visit[N]={false};

    for (auto edge : edges) {
        pairs temp = edge.first;
        ad[temp.first].push_back(temp.second);
        ad[temp.second].push_back(temp.first);
    }
    queue<int> q;
    q.push(source);
    while(!q.empty()){
        int temp = q.front();
        q.pop();
        visit[temp]=true;
        for(auto i : ad[temp]){
            if(visit[i]==false){
                visit[i]=true;
                q.push(i);
                extra[i]=extra[temp]+1;
            }
        }
    }

    for (auto edge : edges) {
        pairs temp = edge.first;
        int weight = abs(edge.second);
        adj[temp.first].push_back(make_pair(temp.second, weight+extra[temp.second]));
        adj[temp.second].push_back(make_pair(temp.first, weight+extra[temp.first]));
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

    int u, v, weight;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> weight;
        pair<int, int> temp = make_pair(u, v);
        edges.push_back(make_pair(temp, weight));
    }

    int s, d;
    cin >> s >> d;


    dijkstra(s);
    if(distance_dijkstra[d]>=INF) {
        cout << "no path" << "\n";
    }
     else {
        cout << distance_dijkstra[d] << "\n";

        print_path(d, parent_dijkstra);
    }

    cout << "\n";

    return 0;
}
