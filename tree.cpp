#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
    }

    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);

    priority_queue<
        pair<long long,int>,
        vector<pair<long long,int>>,
        greater<pair<long long,int>>
    > pq;

    dist[1] = 0;
    pq.push({0, 1});
    vector<int>edgeweight(n+1,INF) ;

    while (!pq.empty()) {

        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d != dist[u])
            continue;

        for (auto edge : adj[u]) {

            int v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v]) {

                dist[v] = dist[u] + w;
                parent[v] = u;
                edgeweight[v] = w ;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[n] == INF) {
        cout << -1 << endl;
        return 0;
    }

    vector<int> path;

    int cur = n;

    while (cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }

    reverse(path.begin(), path.end());

    long long sum = 0;

for (int i = 2; i <= n; i++) {
    if (parent[i] != -1)
        sum += edgeweight[i];
}

cout << sum << endl;
   
}