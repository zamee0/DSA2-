#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {

    int n, m , k;
    cin >> n >> m >> k ;

    vector<vector<pair<int,int>>> adj(n + 1);
    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);

    for(int i = 0 ; i<k ;i++)
    {
        int u ;
        cin>>u ;
        adj[u].push_back({0,0}) ;
        adj[0].push_back({u,0}) ;

    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[v].push_back({u, w});
    }



    priority_queue<
        pair<long long,int>,
        vector<pair<long long,int>>,
        greater<pair<long long,int>>
    > pq;

    dist[0] = 0;
    pq.push({0, 0});

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

                pq.push({dist[v], v});
            }
        }
    }

    for(int i =1 ;i<= n; i++){

        if (dist[i] == INF) {
            dist[i] = -1; 
    }
    }

    for(int i =1 ;i<=n ;i++)
    {
        cout<< dist[i] << endl ;
    }
  

}