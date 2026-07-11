#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

vector<vector<int>> parent;
vector<int> path;
int source;

// DFS to print all shortest paths
void printPath(int u)
{
    path.push_back(u);

    if (u == source)
    {
        // path এখন destination -> source
        for (int i = path.size() - 1; i >= 0; i--)
            cout << path[i] << " ";
        cout << endl;
    }
    else
    {
        for (int p : parent[u])
            printPath(p);
    }

    path.pop_back();
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
    }

    cin >> source;

    vector<long long> dist(n + 1, INF);

    parent.resize(n + 1);

    priority_queue<
        pair<long long,int>,
        vector<pair<long long,int>>,
        greater<pair<long long,int>>
    > pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u])
            continue;

        for (auto [v, w] : adj[u])
        {
            // Better shortest path
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;

                parent[v].clear();
                parent[v].push_back(u);

                pq.push({dist[v], v});
            }

            // Another shortest path
            else if (dist[u] + w == dist[v])
            {
                parent[v].push_back(u);
            }
        }
    }

    int destination;
    cin >> destination;

    if (dist[destination] == INF)
    {
        cout << "No Path\n";
        return 0;
    }

    cout << "Shortest Distance = " << dist[destination] << endl;
    cout << "All Shortest Paths:\n";

    printPath(destination);

    return 0;
}