#include<bits/stdc++.h>
using namespace std;

int V;
int INF = 100000;
vector<bool> visit;

bool bfs(vector<vector<int> > rGraph, int s, int t, int parent[])
{
    for(int i=0; i<V; i++) visit[i]=false;

	queue <int> q;
	q.push(s);
	visit[s] = true;
	parent[s] = -1;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int v=0; v<V; v++)
		{
			if (visit[v]==false && rGraph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				visit[v] = true;
			}
		}
	}

	return (visit[t]==true);
}


int max_flow(vector<vector<int> > graph, int s, int t)
{
	int u, v;
    int maxflow = 0;

	vector<vector<int> > rGraph;
    rGraph.resize(V);
    for(int i=0; i<V; i++) rGraph[i].resize(V,0);
	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			rGraph[u][v] = graph[u][v];

	int parent[V]; 

	while (bfs(rGraph, s, t, parent))
	{
		int path_flow = INF;
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
        maxflow += path_flow;
	}

	for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++)
		    if (visit[i] && !visit[j] && graph[i][j]>0)
			    cout << i << " - " << j << endl;
    }
	

	return maxflow;
}

int main()
{
	int n,m;
    cin>>n>>m;
    V=n;
    for(int i=0; i<n; i++){
        visit.push_back(false);
    }
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

    int s,t;
    cin>>s>>t;

	int maxflow = max_flow(graph, s, t);
    cout<<"Max flow = "<<maxflow<<"\n";

	return 0;
}
