#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main()
{
    int n, m;
    cin >> n >> m;

    // Distance Matrix
    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));

    // Distance to itself = 0
    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;

    // Input edges
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;

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

                    dist[i][j] = min(dist[i][j] , dist[i][k]+ dist[k][j]);
            }
        }
    }

    vector<long long >e(n+1 , -INF) ;
    
    for(int i =1 ; i<= n; i++ )
    {
        for(int j = 1 ; j<= n ;j++)
        {
            if(dist[i][j] > e[i])
                e[i] = dist[i][j] ;
        }
    }

    int radius , rnode; 

    radius = INF ;

    for(int i = 1 ; i<=n ; i++)
    {
        if(radius > e[i])
        {
            radius = e[i] ; 
        }
    }

    cout<< radius ;
}