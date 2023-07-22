#include <bits/stdc++.h>
using namespace std;
#define n 4

bool bfs(int rg[n][n], int s, int t, int parent[])
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

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; ++v)
        {
            if (visited[v] == 0 && rg[u][v] > 0)
            {
                if (v == t)
                {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                visited[v] = 1;
                parent[v] = u;
            }
        }
    }
    return false;
}

int Ford_Fulkerson(int G[n][n], int s, int t)
{
    int rg[n][n];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            rg[i][j] = G[i][j];
        }
    }
    int max_flow = 0;
    int parent[n];

    while (bfs(rg, s, t, parent))
    {
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            path_flow = min(path_flow, rg[u][v]);
        }

        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            rg[u][v] -= path_flow;
            rg[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main()
{
    /* n = 6;

    int G[n][n] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };
    */
    int G[n][n] = {
        {0, 3, 2, 0},
        {0, 0, 5, 2},
        {0, 0, 0, 3},
        {0, 0, 0, 0}

    };

    cout << "max-flow = " << Ford_Fulkerson(G, 0, n - 1) << endl;

    return 0;
}
