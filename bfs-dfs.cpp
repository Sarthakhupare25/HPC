#include <bits/stdc++.h>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void BFS(int start)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        cout << start << " ";

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < adj[u].size(); i++)
            {
                int v = adj[u][i];
                if (!visited[v])
                {
                    cout << v << " ";
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }
    void ParallelBFS(int start)
    {
        queue<int> q;
        vector<bool> visited(V, false);
        cout << start << " ";
        q.push(start);
        visited[start] = true;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
#pragma omp parallel for
            for (int i = 0; i < adj[u].size(); i++)
            {
                int v = adj[u][i];

                if (!visited[v])
                {
                    cout << v << " ";
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }
    void dfs(int u, vector<bool> &visited)
    {
        cout << u << " ";
        visited[u] = true;
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
            if (!visited[v])
            {
                dfs(v, visited);
            }
        }
    }
    void DFS(int start)
    {
        vector<bool> visited(V, false);
        dfs(start, visited);
    }

    void pdfs(int u, vector<bool> &visited)
    {
        cout << u << " ";
        visited[u] = true;
#pragma omp parallel for
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
            if (!visited[v])
            {
                pdfs(v, visited);
            }
        }
    }
    void ParallelDFS(int start)
    {
        vector<bool> visited(V, false);
        pdfs(start, visited);
    }
};

int main()
{
    cout << "Enter the the number of nodes ";
    int n;
    cin >> n;
    Graph g(n);

    cout << "Enter the number of Edges : ";
    int e;
    cin >> e;
    for (int i = 0; i < e; i++)
    {
        cout << "Enter the Edge " << i + 1 << " : ";
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    cout << "Enter the start Node : ";
    int s;
    cin >> s;

    auto start = high_resolution_clock::now();
    g.BFS(s);
    auto end = high_resolution_clock::now();
    auto result1 = end - start;
    cout << " : BFS took time " << result1.count() << endl;

    start = high_resolution_clock::now();
    g.ParallelBFS(s);
    end = high_resolution_clock::now();
    auto result2 = end - start;
    cout << ": Parallel BFS took time " << result2.count() << endl;

    start = high_resolution_clock::now();
    g.DFS(s);
    end = high_resolution_clock::now();
    auto result3 = end - start;
    cout << " : DFS took time " << result3.count() << endl;

    start = high_resolution_clock::now();
    g.ParallelDFS(s);
    end = high_resolution_clock::now();
    auto result4 = end - start;
    cout << ": Parallel DFS took time " << result4.count() << endl;
}
