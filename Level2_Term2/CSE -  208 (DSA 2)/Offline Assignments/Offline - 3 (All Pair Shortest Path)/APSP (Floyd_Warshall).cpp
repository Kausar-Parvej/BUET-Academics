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
    fin >> n >> m;

    int distance[n + 1][n + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == j) distance[i][j] = 0;
            else distance[i][j] = INF;
        }
    }

    int u, v, w;
    for (int i = 0; i < m; i++) {
        fin >> u >> v >> w;
        distance[u][v] = w;
    }


    for(int k=1; k<=n; k++){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                if(distance[i][j] > distance[i][k]+distance[k][j])
                    distance[i][j] = distance[i][k]+distance[k][j];
            }
        }
    }


    cout << "Shortest distance matrix\n";
    fout << "Shortest distance matrix\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (distance[i][j] >= INF){
                cout << "INF ";
                fout << "INF ";
            }
            else{
               cout << distance[i][j] << " ";
               fout << distance[i][j] << " ";
            }
        }
        cout << "\n";
        fout << "\n";
    }

    return 0;
}
