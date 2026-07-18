#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main()
{
    int n, m;
    cin >> n >> m;

    // Distance Matrix
    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));
    vector<vector<int>> next(n + 1, vector<int>(n + 1, -1));

    // Distance to itself = 0
    for (int i = 1; i <= n; i++){
        dist[i][i] = 0;
        next[i][i] = i;
    }
        

    // Input edges
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        next[u][v] = v ;
        // Directed Graph
        dist[u][v] = min(dist[u][v], w);

        // dist[v][u] = min(dist[v][u], w);
    }


    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            // Optimization
            if (dist[i][k] == INF)
                continue;

            for (int j = 1; j <= n; j++)
            {
                if (dist[k][j] == INF)
                    continue;

                    if((dist[i][k]+dist[k][j]) < dist[i][j])
                    {
                        dist[i][j] = dist[i][k]+ dist[k][j] ; 
                        next[i][j] = next[i][k] ;
                    }
            }
        }
    }

    int u, v;
cin >> u >> v;

if(next[u][v] == -1)
{
    cout << "No Path\n";
    return 0;
}

vector<int> path;

int cur = u;

while(cur != v)
{
    path.push_back(cur);
    cur = next[cur][v];
}

path.push_back(v);

for(int node : path)
    cout << node << " ";
    
}