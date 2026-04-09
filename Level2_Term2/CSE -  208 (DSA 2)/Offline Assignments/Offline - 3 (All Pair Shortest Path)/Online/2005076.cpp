#include<bits/stdc++.h>
using namespace std;

#define input_file "Input.txt"
#define output_file "Output.txt"

#define INF 100001

void print_path(int node1,int node2, vector<int> path[]) {
    if (node1 == node2) {
        cout << node2;
        return;
    }
    print_path(path[node1][node2],node2, path);
    cout << "->" << node1;
}

int main()
{
    ifstream fin(input_file);
    ofstream fout(output_file);

    int n, m;
    cin >> n >> m;

    int distance[n + 1][n + 1];
    vector<int> parent[n+1];
    for(int i=0; i<=n ; i++){
        parent[i].resize(n+1);
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            parent[i][j] = -1;
            if (i == j) distance[i][j] = 0;
            else distance[i][j] = INF;
        }
    }

    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        distance[u][v] = w;
        distance[v][u] = w;
        parent[u][v] = v;
        parent[v][u] = u;
    }

    int w1,w2;
    cin>>w1>>w2;

    int wall_street = distance[w1][w2];


    for(int k=0; k<=n; k++){
        for(int i=0; i<=n; i++){
            for(int j=0; j<=n; j++){
                if(distance[i][j] > distance[i][k]+distance[k][j]){
                    distance[i][j] = distance[i][k]+distance[k][j];
                    parent[i][j] = parent[i][k];
                }
            }
        }
    }

    int temp1,temp2,ans;
    bool flag2 = false;


    int k1=0,k2=0;
    while(true){
        cin>>k1>>k2;
        if(k1 == -1 || k2 == -1) break;

        temp1 = distance[k1][w1] + distance[w2][k2] ;
        temp2 = distance[k1][w2] + distance[w1][k2] ;

        if(temp1 < temp2){
            ans = temp1 + wall_street;
        }
        else{
            ans = temp2 + wall_street;
            int temp3=w1;
            w1=w2;
            w2=temp3;
        }

        if(ans >= INF) cout<<"No path from "<<k1<<" to "<<k2<<" through the Wall Street\n";
        else{
            cout<<"Shortest Path Weight: "<<ans<<"\n";
            cout<<"Path: ";
            print_path(k2,w1,parent);
            cout<<"->"<<w1<<"->"<<w2<<"->";
            print_path(w2,k1,parent);
            cout<<"\n";
        }
    }

    return 0;
}
