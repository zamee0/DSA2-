#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int u, v;
    long long w;
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<Edge> edges;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;

        edges.push_back({u, v, w});
    }

    // dist = 0 because we want to detect
    // any negative cycle in the graph
    vector<long long> dist(n + 1, 0);
    vector<int> parent(n + 1, -1);

    int x = -1;

    // Run Bellman-Ford n times
    for (int i = 1; i <= n; i++)
    {
        x = -1;

        for (auto e : edges)
        {
            if (dist[e.u] + e.w < dist[e.v])
            {
                dist[e.v] = dist[e.u] + e.w;
                parent[e.v] = e.u;
                x = e.v;
            }
        }
    }

    if (x == -1)
    {
        cout << "NO\n";
        return 0;
    }

    // Move x inside the cycle
    for (int i = 0; i < n; i++)
        x = parent[x];

    vector<int> cycle;

    int cur = x;

    do
    {
        cycle.push_back(cur);
        cur = parent[cur];
    }
    while (cur != x);

    cycle.push_back(x);

    reverse(cycle.begin(), cycle.end());

    cout << "YES\n";

    for (int v : cycle)
        cout << v << " ";

    cout << endl;

    return 0;
}