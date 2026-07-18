#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    // Reachability Matrix
    vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));

    // Every node can reach itself
    for (int i = 1; i <= n; i++)
        reach[i][i] = true;

    // Input edges
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        // Directed Graph
        reach[u][v] = true;

        // For Undirected Graph
        // reach[v][u] = true;
    }

    // Warshall Algorithm
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (!reach[i][k])
                continue;

            for (int j = 1; j <= n; j++)
            {
                if(!reach[k][j])
                {
                    continue;
                }

                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
            }
        }
    }

    // Print Reachability Matrix
    cout << "Reachability Matrix:\n";

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << reach[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}