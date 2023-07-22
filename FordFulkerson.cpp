#include <bits/stdc++.h>
using namespace std;

int const n = 6;

int BFS(int g[n][n], int s, int t, int parent[n])
{
    
    int visited[n];
    for (int i = 0; i < n; ++i)
    {
        visited[i] = 0;
    }

    queue<int> q;
    q.push(s);
    visited[s] = 1;
    parent[s] = -1;
    int flow = INT_MAX; // bottle neck capacity
    while (q.empty() != 0)
    {
        int u = q.front();
        
        cout << "u = " << u << endl;
        for (int v = 0; v < n; ++v)
        {
            if (visited[v] == 0 && g[u][v] > 0)
            {
                cout << "v = " << v << endl;
                parent[v] = u;
                if (v == t)
                {
                    return flow;
                }
                q.push(v);
                visited[v] = 1;

                if (flow > g[u][v])
                {
                    flow = g[u][v];
                }
            }
        }
    }
    return 0;
}

int FordFulkerson(int G[n][n], int s, int t)
{
    int rGraph[n][n];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            rGraph[i][j] = G[i][j];
        }
    }

    int parent[n];
    int flow = BFS(rGraph, s, t, parent); // flow along a path ->bottle nack capacity
    int max_flow = 0;

    while (flow)
    {   
        flow = BFS(rGraph, s, t, parent);
        int v = t;
        int u;
        do
        {
            u = parent[v];
            rGraph[u][v] -= flow;
            rGraph[v][u] += flow;
            
            v = u;
        } while (u != s);

        max_flow += flow;
    }
    return max_flow;
}

int main()
{
    int G[n][n] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}

    };

    cout << "Max-Flow = " << FordFulkerson(G, 0, n - 1);

    return 0;
}