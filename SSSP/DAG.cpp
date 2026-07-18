#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n + 1);
    vector<int> indegree(n + 1);

    for (int i = 0; i < m; i++) {

        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        indegree[v]++;
    }

    queue<int> q;

    for (int i = 1; i <= n; i++)
        if (indegree[i] == 0)
            q.push(i);

    vector<int> topo;

    while (!q.empty()) {

        int u = q.front();
        q.pop();

        topo.push_back(u);

        for (auto [v, w] : adj[u]) {

            indegree[v]--;

            if (indegree[v] == 0)
                q.push(v);
        }
    }

    int source;
    cin >> source;

    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);

    dist[source] = 0;

    for (int u : topo) {

        if (dist[u] == INF)
            continue;

        for (auto [v, w] : adj[u]) {

            if (dist[u] + w < dist[v]) {

                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i <= n; i++)
        cout << dist[i] << " ";
}