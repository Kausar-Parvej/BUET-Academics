#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

#define input_file "input.txt"
#define output_file "output.txt"

using namespace std;

int main(){

    ifstream fin(input_file);
    ofstream fout(output_file);

    vector<pair<int,int>> time_pair;
    vector<pair<int,int>> ans_pair;

    int n,t1,t2;
    fin>>n;
    for(int i=0; i<n; i++){
        fin>>t1>>t2;
        time_pair.push_back(make_pair(t2,t1));
    }

    sort(time_pair.begin(),time_pair.end());

    ans_pair.push_back(time_pair[0]);
    for(int i=1; i<time_pair.size(); i++){
        if(ans_pair[ans_pair.size()-1].first <= time_pair[i].second){
            ans_pair.push_back(time_pair[i]);
        }
    }

    fout<<ans_pair.size()<<"\n";
    for(auto i=ans_pair.begin(); i<ans_pair.end(); i++){
        fout<<(*i).second<<" "<<(*i).first<<"\n";
    }


    fin.close();
    fout.close();

    cout << endl
         << "\t------>Check output.txt<------" << endl;

    return 0;
}
