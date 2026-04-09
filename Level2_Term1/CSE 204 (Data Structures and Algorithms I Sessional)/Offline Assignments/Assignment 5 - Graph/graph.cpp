#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

#define input_file "input.txt"
#define output_file "output.txt"

using namespace std;

class graph
{
private:
    int vertex_num;
    //vector<list<int>> adj_list;
    vector<vector<int>> adj_list;

public:
    graph(int n)
    {
        vertex_num = n+1;
        adj_list.resize(n);
    }

    void addEdge(int v, int w)
    {
        adj_list[v].push_back(w);
    }

    string BFS(int source)
    {
        vector<bool> visited_vertex;
        list<int> edge;
        visited_vertex.resize(vertex_num, false);

        list<int> queue;

        queue.push_back(source);

        string print("Breadth-First Search:\n\n");
        print.append("Vertices: ");

        while (!queue.empty())
        {
            source = queue.front();
            /*if(visited_vertex[source] == false)
            {
                cout << source << " -> ";
                for (auto adjecent : adj_list[source])
                {
                    if (!visited_vertex[adjecent])
                    {
                        visited_vertex[adjecent] = true;
                        cout<<adjecent<<",";
                    }
                }
                cout<<"\n";
            }*/

            visited_vertex[source] = true;

            print.append(to_string(source));
            print.append(" ");

            for(auto i : adj_list[source])
            {
                if(visited_vertex[i] == false)
                {
                    edge.push_back(source);
                    edge.push_back(i);
                }
            }
            queue.pop_front();

            for (auto adjecent : adj_list[source])
            {
                if (!visited_vertex[adjecent])
                {
                    visited_vertex[adjecent] = true;
                    queue.push_back(adjecent);

                }
            }
        }
        print.append("\nedges:\n");
        while(!edge.empty())
        {
            int v1=edge.front();
            edge.pop_front();
            int v2=edge.front();
            edge.pop_front();
            print.append("(");
            print.append(to_string(v1));
            print.append(", ");
            print.append(to_string(v2));
            print.append(")\n");
        }
        return print;
    }
    string DFS(int source)
    {
        string print("Depth-First Search:\n\n");
        print.append("Vertices: ");
        bool visited_vertex[vertex_num];
        list<int> edge;
        for(int i=0; i<vertex_num; i++)
        {
            visited_vertex[i]=false;
        }
        visit(source, visited_vertex,edge,print);

        print.append("\nedges:\n");
        while(!edge.empty())
        {
            int v1=edge.front();
            edge.pop_front();
            int v2=edge.front();
            edge.pop_front();
            print.append("(");
            print.append(to_string(v1));
            print.append(", ");
            print.append(to_string(v2));
            print.append(")\n");
        }
        return print;

    }

    void visit(int source,bool visit[],list<int> &edge, string &print)
    {
        stack<int>stk;
        stk.push(source);
        visit[source]=true;
        while(!stk.empty())
        {
            int temp=stk.top();
            print.append(to_string(temp));
            print.append(" ");
            for(auto i : adj_list[temp])
            {
                if(visit[i] == false)
                {
                    edge.push_back(temp);
                    edge.push_back(i);
                    break;
                }
            }
            stk.pop();

            for(int i=0; i<adj_list[temp].size(); i++)
            {
                if(!visit[adj_list[temp][i]])
                {
                    stk.push(adj_list[temp][i]);
                    visit[adj_list[temp][i]]=true;
                }
            }
        }

    }
};


int main()
{
    ifstream fin(input_file);
    //ofstream fout(output_file);

    int vertex_num,edge_num;
    fin>>vertex_num>>edge_num;
    graph my_graph(vertex_num+5);

    int v1,v2;
    for(int i=0; i<edge_num; i++)
    {
        fin>>v1>>v2;
        my_graph.addEdge(v1,v2);
    }

    int source;
    fin>>source;
    cout<<my_graph.BFS(source);
    cout<<"\n\n";
    cout<<my_graph.DFS(source);
    cout<<"\n\n";

    //cout << endl
         //<< "\t------>Check output.txt<------" << endl;

    return 0;
}
