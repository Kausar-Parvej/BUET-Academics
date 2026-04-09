//weighted interval shceduling

#include<bits/stdc++.h>
using namespace std;

class jobs{
    public:
    int start;
    int end;
    int weight;

    jobs(){
        start=0;
        end=0;
        weight=0;
    }
};

int max1(int a, int b){
    return a>=b ? a:b;
}

bool compare(jobs ob1, jobs ob2){
    return ob1.end < ob2.end;
}

int closest_compatible(int index, jobs array[]){
    for(int i=index-1; i>=0; i--){
        if(array[i].end <= array[index].start){
            return i;
        }
    }
    return 0;
}

int main(){
    int n;
    cin>>n;

    jobs interval[n+1];
    int table[n+1];
    table[0]=0;

    for(int i=1; i<=n; i++){
        cin>>interval[i].start>>interval[i].end>>interval[i].weight;
    }

    sort(interval+1, interval+(n+1), compare);

    for(int j=1; j<=n; j++){
        table[j]= max1(table[j-1],interval[j].weight+table[closest_compatible(j,interval)]);
    }

    cout<<table[n]<<"\n";
    
    /*for(int i=0; i<=n; i++){
        cout<<table[i]<<" ";
    }*/

    return 0;
}