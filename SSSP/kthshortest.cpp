#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
    }

    priority_queue<
        pair<ll, int>,
        vector<pair<ll, int>>,
        greater<pair<ll, int>>
    > pq;

    vector<vector<ll>> dist(n + 1);

    dist[1].push_back(0);
    pq.push({0, 1});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        // Outdated state হলে skip
        if (d > dist[u].back())
            continue;

        for (auto [v, w] : adj[u])
        {
            ll nd = d + w;

            if (dist[v].size() < k)
            {
                dist[v].push_back(nd);
                sort(dist[v].begin(), dist[v].end());

                pq.push({nd, v});
            }
            else if (nd < dist[v].back())
            {
                dist[v].back() = nd;
                sort(dist[v].begin(), dist[v].end());

                pq.push({nd, v});
            }
        }
    }

    for (ll x : dist[n])
        cout << x << " ";

    cout << endl;

    return 0;
}