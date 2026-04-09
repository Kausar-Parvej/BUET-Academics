#include <bits/stdc++.h>

using namespace std;

#define input_file "Input.txt"

int INF = 1000000;
typedef pair<int,int> pairs;

int team_num;
int source;
vector<string> team;
vector<int> win,loss,remain;
vector< vector<int> >game_num;

vector< vector<int> > flow;
vector<int> bfs_parent;

bool bfs(vector< vector<int> > r_adj, int n, int s, int t){
    bool visit[n] = {false};
    for(int i=0; i<n; i++) bfs_parent[i] = -1;

    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        visit[u] = true;

        for(auto v : r_adj[u]){
            if(visit[v] == false && flow[u][v] > 0){
                if(v == t){
                    bfs_parent[v] = u;
                    return true;
                }
                visit[v] = true;
                q.push(v);
                bfs_parent[v] = u;
            }
        }
    }
    return false;
}


bool max_flow(int team){
    vector< vector<pairs> > adj;

    int num = (team_num*team_num + team_num + 4)/2;
    adj.resize(num);
    bfs_parent.resize(num,-1);

    int s = num-2;
    source = s;
    int t = num-1;
    int counter = 0;
    for(int i=0; i<team_num; i++){
        if(i == team) continue;
        adj[i].push_back(make_pair(t,win[team]+remain[team]-win[i]));
        for(int j=i+1; j<team_num; j++){
            if(j == team) continue;
            adj[s].push_back(make_pair(team_num+counter,game_num[i][j]));
            adj[team_num+counter].push_back(make_pair(i,INF));
            adj[team_num+counter].push_back(make_pair(j,INF));
            counter++;
        }
    }

    vector< vector<int> > rGraph;
    rGraph.resize(num);
    // flow.resize(num);
    // for(int i=0; i<num; i++) flow[i].resize(num);


    for(int i=0; i<adj.size(); i++){
        if(adj[i].empty()) continue;
        for(auto temp : adj[i]){
            rGraph[i].push_back(temp.first);
            rGraph[temp.first].push_back(i);
            flow[i][temp.first] = temp.second;
        }
    }

    int minn = INF;
    while(bfs(rGraph,num,s,t)){
        for(int v = t; v != s; v = bfs_parent[v]){
            int u = bfs_parent[v];
            minn = flow[u][v] < minn ? flow[u][v] : minn;
        }
        for(int v = t; v != s; v = bfs_parent[v]){
            int u = bfs_parent[v];
            flow[u][v] -= minn;
            flow[v][u] += minn;
        }
    }

    for(auto temp : rGraph[s]){
        // cout<<flow[s][temp]<<" ";
        if(flow[s][temp] > 0) return true;
    }
    return false;

}

int main()
{
    ifstream fin(input_file);
    int n;
    fin>>n;
    team_num = n;

    game_num.resize(n);
    string str;
    int a,b,c,d;
    for(int i=0; i<n; i++){
        fin>>str;
        team.push_back(str);

        fin>>a>>b>>c;
        win.push_back(a);
        loss.push_back(b);
        remain.push_back(c);

        for(int j=0; j<n; j++){
            fin>>d;
            game_num[i].push_back(d);
        }
    }

    map<string, int> to_num;
    map<int, string> to_str;
    for(int i=0; i<n; i++){
        to_num[team[i]] = i;
        to_str[i] = team[i];
    }
    vector<int> track;
    int max_win=0;
    int maxx=0;
    for(int i=0; i<team_num; i++){
        if(maxx < win[i]){
            maxx = win[i];
            max_win = i;
        }
    }

    int num1 = (team_num*team_num + team_num + 4)/2;
    flow.resize(num1);
    for(int i=0; i<num1; i++) flow[i].resize(num1);

    for(int i=0; i<team_num; i++){

        if (win[i] + remain[i] < win[max_win]){
            cout << to_str[i] << " is eliminated.\n";
            cout << "They can win at most " << win[i] << " + " << remain[i] << " = " << win[i] + remain[i] << " games.\n";
            cout << to_str[max_win] << " has already won a total of " << win[max_win] << " games.\n";
            cout<<"\n\n";
            continue;
        }

        bool temp = max_flow(i);
        if(temp == true){
            cout<<to_str[i]<<" is eliminated.\n";
            cout<<"They can win at most "<<win[i]<<" + "<<remain[i]<<" = "<<win[i]+remain[i]<<" games.\n";
            track.clear();
            for(int i=0; i<team_num; i++){
                if(bfs_parent[i] != -1){
                    track.push_back(i);
                }
            }
            int nn = track.size();
            int t_win=0;
            int t_game=0;

            for (int p = 0; p < nn; p++){
                if(p != 0 && p != nn-1) cout<<", ";
                if (p == nn - 1) cout << " and " << to_str[track[p]];
                else cout << to_str[track[p]];

                t_win += win[track[p]];
                for (int j = p + 1; j < nn; j++){
                    t_game += game_num[track[p]][track[j]];
                }
            }
            cout << " have won a total of " << t_win << " game.\n";
            cout << "They play each other " << t_game << " times.\n";
            cout << "So on average, each of the teams wins " << t_win + t_game << "/" << nn << " = ";
            cout <<float(t_win + t_game) / nn<< " games.\n";
            cout<<"\n\n";
        }

    }
}
