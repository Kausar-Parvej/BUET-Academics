#include<bits/stdc++.h>
using namespace std;

int V;

int bfs(vector<vector<int> > rGraph, int s, int t, int parent[])
{
	bool visited[V];
	memset(visited, 0, sizeof(visited));

	queue <int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int v=0; v<V; v++)
		{
			if (visited[v]==false && rGraph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return (visited[t] == true);
}


void dfs(vector<vector<int> > rGraph, int s, bool visited[])
{
	visited[s] = true;
	for (int i = 0; i < V; i++)
	if (rGraph[s][i] && !visited[i])
		dfs(rGraph, i, visited);
}

void minCut(vector<vector<int> > graph, int s, int t)
{
	int u, v;

	vector<vector<int> > rGraph;
    rGraph.resize(V);
    for(int i=0; i<V; i++) rGraph[i].resize(V);
	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			rGraph[u][v] = graph[u][v];

	int parent[V]; 

	while (bfs(rGraph, s, t, parent))
	{
		int path_flow = INT_MAX/2;
		for (v=t; v!=s; v=parent[v])
		{
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		for (v=t; v != s; v=parent[v])
		{
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}
	}

	bool visited[V];
	memset(visited, false, sizeof(visited));
	dfs(rGraph, s, visited);

	for (int i = 0; i < V; i++)
	for (int j = 0; j < V; j++)
		if (visited[i] && !visited[j] && graph[i][j])
			cout << i << " - " << j << endl;

	return;
}

int main()
{
	int n,m;
    cin>>n>>m;
    V=n;
    vector< vector<int> >graph;
    graph.resize(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            graph[i].push_back(0);
        }
    }

    int a,b,w;
    for(int i=0; i<m; i++){
        cin>>a>>b>>w;
        graph[a][b] = w;
    }

	minCut(graph, 0, 5);

	return 0;
}
