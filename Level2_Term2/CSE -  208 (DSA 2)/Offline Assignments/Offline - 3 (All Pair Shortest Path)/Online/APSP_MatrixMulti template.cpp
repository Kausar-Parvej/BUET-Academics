#include<bits/stdc++.h>
using namespace std;

#define input_file "Input.txt"
#define output_file "Output.txt"

#define INF 100001

int** matrix_multipy(int **a, int **b,int n){
    int **c = new int*[n+1];
    for(int i=0; i<=n; i++){
        c[i] = new int[n+1];
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            int minn = INF;
            for(int k=1; k<=n; k++){
                minn = min(minn,a[i][k]+b[k][j]);
            }
            c[i][j] = minn;
        }
    }
    return c;

}

int main()
{
    ifstream fin(input_file);
    ofstream fout(output_file);

    int n, m;
    cin >> n >> m;

    int **distance= new int*[n+1];
    for(int i=0; i<=n; i++){
        distance[i] = new int[n+1];
    }

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


    int d=1;
    while(d < n){
        distance = matrix_multipy(distance,distance,n);
        d = d+1;
    }


    cout << "Shortest distance matrix\n";

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (distance[i][j] >= INF){
                cout << "INF ";
            }
            else{
               cout << distance[i][j] << " ";
               fout << distance[i][j] << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}
