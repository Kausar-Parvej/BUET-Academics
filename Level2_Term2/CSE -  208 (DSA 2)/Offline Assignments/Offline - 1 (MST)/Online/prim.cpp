#include <bits/stdc++.h>
using namespace std;


#define INF INT_MAX
typedef pair<int, int> pairs;

int main()
{
    int n;
    cin>>n;
    int total_weight = 0;
    int N = 1001;

    vector<pairs> adj;
    int root;
    int v1, v2;
    for (int i = 0; i < n; i++)
    {
        cin >> v1 >> v2;
        adj.push_back(make_pair(v1,v2));
    }

    int key[n];
    int parent[n];
    bool taken[n];
    int weights[n];
    root=0;
    for (int i = 0; i < n; i++)
    {
        key[i] = 1000;
        parent[i] = -1;
        taken[i] = false;
    }

    key[root] = 0;
    weights[root]=adj[root].first+adj[root].second;
    priority_queue<pairs, vector<pairs>, greater<pairs>> pq;
    pq.push(make_pair(key[root], root));
    for (int i = 0; i < n; i++)
    {
        if (i != root)
        {
            pq.push(make_pair(key[i], i));
        }
    }

    int flag = 0;
    //int count = 0;

    while (!pq.empty() )
    {
        //count++;
        pairs temp;
        temp = pq.top();
        pq.pop();

        int u = temp.second;

        if (taken[u])
            continue;
        taken[u] = true;
        total_weight += key[u];
        flag++;

        for (int i = 0; i < n; i++)
        {
            if(i==u) continue;

            int temp = abs(adj[i].first-adj[u].first) + abs(adj[i].second-adj[u].second);

            if (!taken[i] && temp < key[i])
            {
                parent[i] = u;
                key[i] = temp;
                pq.push(make_pair(key[i], i));
            }
        }
    }
    //cout << "count = "<< count<<"\n";
    cout << "Total weight = " << total_weight << "\n";
    

    return 0;
}
