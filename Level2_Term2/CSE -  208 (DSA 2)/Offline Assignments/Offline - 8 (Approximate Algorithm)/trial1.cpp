
#include <bits/stdc++.h>
using namespace std;

// Number of vertices in the graph
#define V 5
typedef pair<int, int> pairs;

// Dynamic array to store the final answer
vector<int> final_ans;

int minimum_key(int key[], bool mstSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

vector<vector<int>> MST(int parent[], int graph[V][V])
{
    vector<vector<int>> v;
    for (int i = 1; i < V; i++)
    {
        vector<int> p;
        p.push_back(parent[i]);
        p.push_back(i);
        v.push_back(p);
        p.clear();
    }
    return v;
}

// getting the Minimum Spanning Tree from the given graph
// using Prim's Algorithm
vector<vector<int>> primMST2(int graph[V][V])
{
    int parent[V];
    int key[V];

    // to keep track of vertices already in MST
    bool mstSet[V];

    // initializing key value to INFINITE & false for all mstSet
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // picking up the first vertex and assigning it to 0
    key[0] = 0;
    parent[0] = -1;

    // The Loop
    for (int count = 0; count < V - 1; count++)
    {
        // checking and updating values wrt minimum key
        int u = minimum_key(key, mstSet);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
    vector<vector<int>> v;
    v = MST(parent, graph);
    return v;
}

// getting the preorder walk of the MST using DFS
void DFS(vector<vector<int> > edges_list,int num_nodes,int starting_vertex,bool* visited_nodes)
{
    // adding the node to final answer
    final_ans.push_back(starting_vertex);

    // checking the visited status
    visited_nodes[starting_vertex] = true;

    // using a recursive call
    for(int i=0;i<num_nodes;i++)
    {
        if(i==starting_vertex)
        {
            continue;
        }
        if(edges_list[starting_vertex][i]==1)
        {
            if(visited_nodes[i])
            {
                continue;
            }
            DFS(edges_list,num_nodes,i,visited_nodes);
        }
    }
}

vector< vector<int> > primMST(vector<vector<int> > graph){
    int key[V];
    int parent[V];
    bool taken[V];
    for (int i = 0; i < V; i++){
        key[i] = 99999;
        parent[i] = -1;
        taken[i] = false;
    }
    int root = 0;
    key[root] = 0;
    priority_queue<pairs, vector<pairs>, greater<pairs>> pq;
    pq.push(make_pair(key[root], root));
    for (int i = 0; i < V; i++)
    {
        if (i != root)
        {
            pq.push(make_pair(key[i], i));
        }
    }

    int flag = 0;
    //int count = 0;

    while (!pq.empty() && flag < V)
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

        for (int v = 0; v < V; v++)
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

    for(int i=0; i<V; i++){
        if(parent[i] == -1) continue;
        vector<int> temp;
        temp.push_back(parent[i]);
        temp.push_back(i);
        path.push_back(temp);
        cout<<temp[0]<<" "<<temp[1]<<"\n";
        temp.clear();
    }

    return path;
}


int main()
{
    // initial graph
    vector< vector<int> > graph;
    graph.resize(V);
    for(int i=0; i<V; i++) graph[i].resize(V);
    int g[V][V] = {   { 0, 10, 18, 40, 20 },
                { 10, 0, 35, 15, 12 },
                { 18, 35, 0, 25, 25 },
                { 40, 15, 25, 0, 30 },
                { 20, 13, 25, 30, 0 } };
    for(int i=0; i<V; i++){
        for(int j=0; j<V; j++){
            graph[i][j]=(g[i][j]);
        }
    }

    vector<vector<int>> v;

    // getting the output as MST
    v = primMST(graph);

    // creating a dynamic matrix
    vector<vector<int> > edges_list;
    edges_list.resize(V);
    for(int i=0;i<V;i++)
    {
        edges_list[i].resize(V);
    }

    // setting up MST as adjacency matrix
    for(int i=0;i<v.size();i++)
    {
        int first_node = v[i][0];
        int second_node = v[i][1];
        edges_list[first_node][second_node] = 1;
        edges_list[second_node][first_node] = 1;
    }

    // a checker function for the DFS
    bool* visited_nodes = new bool[V];
    for(int i=0;i<V;i++)
    {
        bool visited_node;
        visited_nodes[i] = false;
    }

    //performing DFS
    DFS(edges_list,V,0,visited_nodes);

    // adding the source node to the path
    final_ans.push_back(final_ans[0]);

    // printing the path
    for(int i=0;i<final_ans.size();i++)
    {
        cout << final_ans[i] << "-";
    }
    return 0;
}
