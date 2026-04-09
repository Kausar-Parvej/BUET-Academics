#include<bits/stdc++.h>
using namespace std;

#define input_file "Input.txt"
#define output_file "Output.txt"

#define INF 100001

int main()
{
    ifstream fin(input_file);
    ofstream fout(output_file);

    int n, m;
    cin >> n >> m;

    int distance[n + 1][n + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == j) distance[i][j] = 0;
            else distance[i][j] = INF;
        }
    }

    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        distance[u][v] = w;
    }


    for(int k=0; k<=n; k++){
        for(int i=0; i<=n; i++){
            for(int j=0; j<=n; j++){
                if(distance[i][j] > distance[i][k]+distance[k][j])
                    distance[i][j] = distance[i][k]+distance[k][j];
            }
        }
    }

    
    bool Cflag = false;
    for (int i = 1; i <= n; i++) {
        if(distance[i][i] < 0){
            Cflag = true;
            break;
        }
    }
    if(Cflag) cout<<"Yes\n";
    else cout<<"No\n";

    return 0;
}
