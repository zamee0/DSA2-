#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {

    int n, m;
    cin >> n >> m;
      vector<int> mn(n+1,INT_MAX);
    vector<int> mx(n+1,0);


    vector<vector<pair<int,int>>> adj(n + 1);
    vector<int>ways(n+1 , 0) ;

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
    ways[1] = 1 ; 
    mn[1] = 0;
    mx[1] = 0;

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
                ways[v] = ways[u] ;

                
                mn[v]=mn[u]+1;
                mx[v]=mx[u]+1;

                pq.push({dist[v], v});
            }
            
            else if(dist[u]+ w == dist[v])
            {
                parent[v] = u ; 
                ways[v]+= ways[u] ;
                pq.push({dist[v] , v}); 
                
                mn[v]=min(mn[v],mn[u]+1);

                mx[v]=max(mx[v],mx[u]+1);
                
            }
        }
    }
    cout<<dist[n]<<" ";
    cout<<ways[n]<<" ";
    cout<<mn[n]<<" ";
    cout<<mx[n]<<endl;

}