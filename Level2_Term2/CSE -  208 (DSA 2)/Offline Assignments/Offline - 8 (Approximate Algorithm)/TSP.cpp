#include<bits/stdc++.h>
#include <climits>
using namespace std;

#include <experimental/random>
using namespace experimental;

typedef pair<int, int> pairs;
const int vertex_number = 20;
int INF = 999999;

vector<int> approximate_tspPath;
vector<int> exact_tspPath;

vector<vector<int> > create_random_graph(int V, vector<vector<int> > graph){
    for(int i=0; i<V; i++){
        for(int j=i; j<V; j++){
            if(i==j) graph[i][j] = 0;
            else{
                int r = randint(50, 200);
                for(int k=i+1; k<j; k++){
                    if(graph[i][k]==0 || graph[k][j]==0) continue;
                    if(graph[i][k] + graph[k][j] < r){
                        r = graph[i][k] + graph[k][j];
                        break;
                    }
                }
                graph[i][j] = r;
                graph[j][i] = r;
            }
        }
    }
    return graph;
}

class Graph{
public:
    int vertex_num;
    vector<vector<int> > matrix;

    Graph(int v_num){
        vertex_num = v_num;
        matrix.resize(v_num +1);
        for(int i=0; i<=v_num; i++){
            matrix[i].resize(v_num+1);
        }

        matrix = create_random_graph(vertex_num, matrix);
    }
};

int dp_table[vertex_number + 1][1 << (vertex_number+1)];
int exact_TSP(Graph &graph, int cur_vertex, int bit_mask){
    if(bit_mask == (1 << vertex_number) - 1){
        exact_tspPath.push_back(0);
        return graph.matrix[cur_vertex][0];
    }

    if(dp_table[cur_vertex][bit_mask] != -1){
        return dp_table[cur_vertex][bit_mask];
    }

    int min_cost = INF;
    int next_index = -1;
    for(int next_vertex = 0; next_vertex < vertex_number; next_vertex++){
        if(!(bit_mask & (1<<next_vertex))){
            int new_mask = bit_mask | (1<<next_vertex);
            int tour_cost = exact_TSP(graph, next_vertex, new_mask) + graph.matrix[cur_vertex][next_vertex];
            if(tour_cost < min_cost){
                min_cost = tour_cost;
                next_index = next_vertex;
            }
        }
    }

    dp_table[cur_vertex][bit_mask] = min_cost;
    if (next_index != -1) {
        exact_tspPath.push_back(next_index);
    }
    return min_cost;
}

vector< vector<int> > primMST(vector<vector<int> > graph){
    int key[vertex_number];
    int parent[vertex_number];
    bool taken[vertex_number];
    for (int i = 0; i < vertex_number; i++){
        key[i] = INF;
        parent[i] = -1;
        taken[i] = false;
    }
    int root = 0;
    key[root] = 0;
    priority_queue<pairs, vector<pairs>, greater<pairs>> pq;
    pq.push(make_pair(key[root], root));
    for (int i = 0; i < vertex_number; i++)
    {
        if (i != root)
        {
            pq.push(make_pair(key[i], i));
        }
    }

    int flag = 0;
    //int count = 0;

    while (!pq.empty() && flag < vertex_number)
    {
        //count++;
        pairs temp;
        temp = pq.top();
        pq.pop();

        int u = temp.second;

        if (taken[u])
            continue;
        taken[u] = true;
        flag++;

        for (int v = 0; v < vertex_number; v++)
        {
            //if(v == u  || graph[u][v] == 0) continue;
            if (!taken[v] && graph[u][v] < key[v] && graph[u][v] != 0)
            {
                parent[v] = u;
                //cout<<u<<" "<<v<<"\n";
                key[v] = graph[u][v];
                pq.push(make_pair(key[v], v));
            }
        }
    }

    vector<vector<int> > path;

    for(int i=0; i<vertex_number; i++){
        if(parent[i] == -1) continue;
        vector<int> temp;
        temp.push_back(parent[i]);
        temp.push_back(i);
        path.push_back(temp);
        //cout<<temp[0]<<" "<<temp[1]<<"\n";
        temp.clear();
    }

    return path;
}

void dfs(vector<vector<int> > adj_edge, int root, bool visit[] ){
    approximate_tspPath.push_back(root);
    visit[root] = true;

    for(int i=0; i<vertex_number; i++){
        if(i==root) continue;
        if(adj_edge[root][i] == 1){
            if(visit[i] == false)
                dfs(adj_edge, i, visit);
        }
    }
}

void metric_approximation_tsp(Graph &graph){
    approximate_tspPath.clear();
    vector<vector<int> > temp;
    temp = primMST(graph.matrix);

    vector<vector<int> > dfs_edge;
    dfs_edge.resize(vertex_number);
    for(int i=0; i<vertex_number; i++) dfs_edge[i].resize(vertex_number);

    for(int i=0; i<temp.size(); i++){
        int a = temp[i][0];
        int b = temp[i][1];
        dfs_edge[a][b] = 1;
        dfs_edge[b][a] = 1;
    }

    bool visit[vertex_number] = {false};
    dfs(dfs_edge, 0, visit);

    approximate_tspPath.push_back(approximate_tspPath[0]);
}

int calculate_tour_length(vector<int> tour, vector<vector<int> > graph){
    int tour_legth = 0;
    for(int i=0; i<tour.size()-1; i++){
        tour_legth += graph[tour[i]][tour[i+1]];
    }
    return tour_legth;
}




int main()
{
    int x;
    cout<<"Enter number of TestCases : ";
    cin>>x;
    cout<<"\n";

    for(int p=0; p<x; p++){
        Graph graph(20);

        for(int i=0; i<=vertex_number; i++){
            for(int j=0; j<=(1 << vertex_number); j++){
                dp_table[i][j] = -1;
            }
        }
        exact_tspPath.clear();

        int exact_cost = exact_TSP(graph, 0, 1);
        // cout<<"exact cost "<<p+1<<": "<< exact_cost<<"\n";

        metric_approximation_tsp(graph);
        int approximate_cost = calculate_tour_length(approximate_tspPath, graph.matrix);
        //cout<<"approximate cost "<<p+1<<": "<<approximate_cost<<"\n";
        float ratioo = (float) approximate_cost/exact_cost;
        cout<<"TestCase "<<p+1<<" -> Ratio : "<<ratioo<<"\n";

    }





//   for(int i=0; i<20; i++){
//     for(int j=0; j<20; j++){
//         cout<<graph.matrix[i][j]<<" ";
//     }
//     cout<<"\n";
//   }

  return 0;
}

