#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

#include "MyList by LinkedList.cpp"
#include "Stack and Queue by LinkedList.cpp"

#define input_file "input.txt"
#define output_file "output.txt"

using namespace std;

class myGraph
{
private:
    int vertex_num;
    MyLinkedList<int> *adjacent_list;
    bool *isVisited;
    MyLinkedList<int> *store_bfs;
    MyLinkedList<int> *store_dfs;

public:
    myGraph(int num)
    {
        vertex_num = num + 1;
        adjacent_list = new MyLinkedList<int>[vertex_num];
        isVisited = new bool[vertex_num];
        store_bfs = new MyLinkedList<int>[vertex_num];
        store_dfs = new MyLinkedList<int>[vertex_num];
    }

    ~myGraph()
    {
        for (int i = 0; i < vertex_num; i++)
        {
            adjacent_list[i].clear();
            store_bfs[i].clear();
            store_dfs[i].clear();
        }
        delete[] adjacent_list;
        delete[] isVisited;
        delete[] store_bfs;
        delete[] store_dfs;
    }

    void addEdge(int vertex1, int vertex2)
    {
        if (vertex1 >= vertex_num)
            return;

        adjacent_list[vertex1].pushBack(vertex2);
    }

    string BFS(int source)
    {
        for (int i = 0; i < vertex_num; i++)
        {
            isVisited[i] = false;
        }

        isVisited[source] = true;
        LinkedList_Queue<int> bfs_queue(5);
        bfs_queue.enqueue(source);

        while (bfs_queue.length() != 0)
        {
            int vertex = bfs_queue.dequeue();
            for (int j = 0; j < adjacent_list[vertex].size(); j++)
            {
                adjacent_list[vertex].setToPos(j);
                if (isVisited[adjacent_list[vertex].getValue()] == false)
                {
                    isVisited[adjacent_list[vertex].getValue()] = true;
                    bfs_queue.enqueue(adjacent_list[vertex].getValue());
                    store_bfs[vertex].pushBack(adjacent_list[vertex].getValue());
                }
            }
        }

        string print("BFS Tree:\n");
        for (int k = 0; k < vertex_num; k++)
        {
            if (store_bfs[k].size() != 0)
            {
                print.append(to_string(k));
                print.append("-> ");
                for (int p = 0; p < store_bfs[k].size(); p++)
                {
                    store_bfs[k].setToPos(p);
                    print.append(to_string(store_bfs[k].getValue()));
                    if (p != store_bfs[k].size() - 1)
                        print.append(",");
                }
                print.append("\n");
            }
        }
        return print;
    }

    string DFS(int source)
    {
        for (int i = 0; i < vertex_num; i++)
        {
            isVisited[i] = false;
        }
        isVisited[source] = true;

        DFS_visit(source);

        for (int j = 0; j < vertex_num; j++)
        {
            if (isVisited[j] == false)
            {
                DFS_visit(j);
            }
        }

        string print("DFS Tree:\n");
        for (int k = 0; k < vertex_num; k++)
        {
            if (store_dfs[k].size() != 0)
            {
                print.append(to_string(k));
                print.append("-> ");
                for (int p = 0; p < store_dfs[k].size(); p++)
                {
                    store_dfs[k].setToPos(p);
                    print.append(to_string(store_dfs[k].getValue()));
                    if (p != store_dfs[k].size() - 1)
                        print.append(",");
                }
                print.append("\n");
            }
        }
        return print;
    }
    void DFS_visit(int vertex)
    {
        isVisited[vertex] = true;
        for (int i = 0; i < adjacent_list[vertex].size(); i++)
        {
            adjacent_list[vertex].setToPos(i);
            if (isVisited[adjacent_list[vertex].getValue()] == false)
            {
                isVisited[adjacent_list[vertex].getValue()] == true;
                store_dfs[vertex].pushBack(adjacent_list[vertex].getValue());
                DFS_visit(adjacent_list[vertex].getValue());
            }
        }
    }

    //-----------------------online----------------------//

    bool isBipartite(int source)
    {
        for (int i = 0; i < vertex_num; i++)
        {
            isVisited[i] = false;
        }

        isVisited[source] = true;
        LinkedList_Queue<int> bfs_queue(5);
        bfs_queue.enqueue(source);

        while (bfs_queue.length() != 0)
        {
            int vertex = bfs_queue.dequeue();

            if (adjacent_list[vertex].find(vertex) != -1)
                return false;

            for (int j = 0; j < adjacent_list[vertex].size(); j++)
            {
                adjacent_list[vertex].setToPos(j);
                if (isVisited[adjacent_list[vertex].getValue()] == false)
                {
                    isVisited[adjacent_list[vertex].getValue()] = true;
                    bfs_queue.enqueue(adjacent_list[vertex].getValue());
                    store_bfs[vertex].pushBack(adjacent_list[vertex].getValue());
                }
            }

            for (int j = 0; j < adjacent_list[vertex].size(); j++)
            {
                adjacent_list[vertex].setToPos(j);
                if (isVisited[j] == false)
                {
                    isVisited[j] = true;
                    bfs_queue.enqueue(adjacent_list[vertex].getValue());
                }

                else if (isVisited[j] == isVisited[vertex])
                    return false;
            }
        }
        return true;
    }
};

int main()
{
    ifstream fin(input_file);
    ofstream fout(output_file);

    int vertex_num, edge_num;
    cin >> vertex_num >> edge_num;
    myGraph my_graph(vertex_num);

    int v1, v2;
    int a;
    for (int i = 0; i < edge_num; i++)
    {
        cin >> v1 >> v2;
        if (i == 0)
            a = v1;
        my_graph.addEdge(v1, v2);
    }

    int source;
    cin >> source;
    cout << "\n";

    bool ans = my_graph.isBipartite(a);

    if(ans)
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;

    // fout<<my_graph.BFS(source);
    // fout<<"\n\n";

    // fout<<my_graph.DFS(source);
    // fout<<"\n\n";

    // cout << endl
    //<< "\t------>Check output.txt<------" << endl;

    return 0;
}

// C++ program to find out whether a
// given graph is Bipartite or not
#include <iostream>
#include <queue>
#define V 4

using namespace std;

// This function returns true if graph
// G[V][V] is Bipartite, else false
bool isBipartite(int G[][V], int src)
{
    // Create a color array to store colors
    // assigned to all vertices. Vertex
    // number is used as index in this array.
    // The value '-1' of colorArr[i]
    // is used to indicate that no color
    // is assigned to vertex 'i'. The value 1
    // is used to indicate first color
    // is assigned and value 0 indicates
    // second color is assigned.
    int colorArr[V];
    for (int i = 0; i < V; ++i)
        colorArr[i] = -1;

    // Assign first color to source
    colorArr[src] = 1;

    // Create a queue (FIFO) of vertex
    // numbers and enqueue source vertex
    // for BFS traversal
    queue<int> q;
    q.push(src);

    // Run while there are vertices
    // in queue (Similar to BFS)
    while (!q.empty())
    {
        // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 )
        int u = q.front();
        q.pop();

        // Return false if there is a self-loop
        if (G[u][u] == 1)
            return false;

        // Find all non-colored adjacent vertices
        for (int v = 0; v < V; ++v)
        {
            // An edge from u to v exists and
            // destination v is not colored
            if (G[u][v] && colorArr[v] == -1)
            {
                // Assign alternate color to this adjacent v of u
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }

            // An edge from u to v exists and destination
            // v is colored with same color as u
            else if (G[u][v] && colorArr[v] == colorArr[u])
                return false;
        }
    }

    // If we reach here, then all adjacent
    // vertices can be colored with alternate color
    return true;
}

// Driver program to test above function
int main()
{
    int G[][V] = {{0, 1, 0, 1},
                  {1, 0, 1, 0},
                  {0, 1, 0, 1},
                  {1, 0, 1, 0}};

    isBipartite(G, 0) ? cout << "Yes" : cout << "No";
    return 0;
}
