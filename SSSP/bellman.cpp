#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

struct Edge {

    int u, v;
    long long w;
};

int main() {

    int n, m;
    cin >> n >> m;

    vector<Edge> edges;

    for (int i = 0; i < m; i++) {

        int u, v;
        long long w;

        cin >> u >> v >> w;

        edges.push_back({u, v, w});
    }

    int source;
    cin >> source;

    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);

    dist[source] = 0;

    for (int i = 1; i <= n - 1; i++) {

        bool updated = false;

        for (auto e : edges) {

            if (dist[e.u] == INF)
                continue;

            if (dist[e.u] + e.w < dist[e.v]) {

                dist[e.v] = dist[e.u] + e.w;
                parent[e.v] = e.u;

                updated = true;
            }
        }

        if (!updated)
            break;
    }

    bool negativeCycle = false;

    for (auto e : edges) {

        if (dist[e.u] == INF)
            continue;

        if (dist[e.u] + e.w < dist[e.v]) {

            negativeCycle = true;
            break;
        }
    }

    if (negativeCycle)
        cout << "Negative Cycle Exists\n";
    else
        for (int i = 1; i <= n; i++)
            cout << dist[i] << " ";
}