#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

class State
{
public:
    long long d;
    int node;
    int used; // 0 = discount not used, 1 = discount used

    bool operator>(const State &other) const
    {
        return d > other.d;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
    }

    vector<vector<long long>> dist(n + 1, vector<long long>(2, INF));

    priority_queue<State, vector<State>, greater<State>> pq;

    dist[1][0] = 0;
    pq.push({0, 1, 0});

    while (!pq.empty())
    {
        State cur = pq.top();
        pq.pop();

        long long d = cur.d;
        int u = cur.node;
        int used = cur.used;

        if (d != dist[u][used])
            continue;

        for (auto edge : adj[u])
        {
            int v = edge.first;
            int w = edge.second;

            // Go without using discount
            if (d + w < dist[v][used])
            {
                dist[v][used] = d + w;
                pq.push({dist[v][used], v, used});
            }

            // Use discount on this edge
            if (used == 0)
            {
                if (d + w / 2 < dist[v][1])
                {
                    dist[v][1] = d + w / 2;
                    pq.push({dist[v][1], v, 1});
                }
            }
        }
    }

    if (dist[n][1] == INF)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << dist[n][1] << endl;
    }

    return 0;
}