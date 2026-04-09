
#include<bits/stdc++.h>
using namespace std;

class resturants{
    public:
    int index;
    int distance;
    int profit;
    int parent;

    resturants(){
        index=0;
    }
};

int max1(int a, int b){
    return a>=b ? a:b;
}



int closest_index(int index, int k, int array[]){
    for(int i=index-1; i>=0; i--){
        if(array[index]-k >= array[i]){
            //cout<<i<<endl;
            return i;
        }
    }
    return 0;
}

int main(){
    int n,k;
    cin>>n>>k;

    int m[n+1];
    int p[n+1];

    int table[n+1];
    table[0]=0;
    m[0]=0;
    p[0]=0;

    set<int> path;

    //cout<<"distance:\n";
    for(int i=1; i<=n; i++){
        cin>>m[i];
    }
    //cout<<"profit:\n";
    for(int i=1; i<=n; i++){
        cin>>p[i];
    }

    for(int j=1; j<=n; j++){
        table[j]= max1(table[j-1], p[j]+table[closest_index(j,k,m)]);
    }

    cout<<"Total Profit: "<<table[n]<<"\n";

    /*for(int i=0; i<=n; i++){
        cout<<table[i]<<" ";
    }*/
    int i = n;
    while (table[i] != 0)
    {
        if ((p[i]+table[closest_index(i,k,m)]) > table[i - 1])
            {
                path.insert(i);
                i = closest_index(i,k,m);
            }
            i=i-1;
    }


    /*for (auto k : path)
    {
        cout<<k<<" ";
    }
    cout << "\n";*/

    return 0;
}
