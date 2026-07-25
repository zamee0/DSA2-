#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1e18;

struct Edge {
    int to;
    int time;
    int cost;
};

int main() {

    ll K;
    cin >> K;

    int N;
    cin >> N;

    int X;
    cin >> X;

    vector<vector<Edge>> adj(N + 1);

    for (int i = 0; i < X; i++) {
        int u, v, t, c;
        cin >> u >> v >> t >> c;

        adj[u].push_back({v, t, c});
        adj[v].push_back({u, t, c}); // Bidirectional
    }

    int S, D;
    cin >> S >> D;

    vector<ll> dist(N + 1, INF);
    vector<ll> totalTime(N + 1, INF);
    vector<int> parent(N + 1, -1);

    priority_queue<
        pair<ll, int>,
        vector<pair<ll, int>>,
        greater<pair<ll, int>>
    > pq;

    dist[S] = 0;
    totalTime[S] = 0;

    pq.push({0, S});

    while (!pq.empty()) {

        ll curCost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (curCost != dist[u])
            continue;

        for (auto e : adj[u]) {

            int v = e.to;

            ll waitTime = (u == S) ? 0 : 1;

            ll newTime = totalTime[u] + e.time + waitTime;

            ll newCost = dist[u]
                       + e.cost
                       + (ll)e.time * K
                       + waitTime * K;

            if (newCost < dist[v]) {

                dist[v] = newCost;
                totalTime[v] = newTime;
                parent[v] = u;

                pq.push({dist[v], v});
            }
        }
    }

    if (dist[D] == INF) {
        cout << "Error\n";
        return 0;
    }

    vector<int> path;

    int cur = D;

    while (cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }

    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i + 1 != path.size())
            cout << "->";
    }

    cout << " " << totalTime[D] << " " << dist[D] << "\n";

    return 0;
}