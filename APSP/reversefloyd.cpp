#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    // Distance Matrix
    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> dist[i][j];
        }
    }

    // Deletion Order
    vector<int> del(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> del[i];

    // Active Nodes
    vector<bool> active(n + 1, false);

    // Answers
    vector<long long> ans;

    // Reverse Floyd
    for (int idx = n; idx >= 1; idx--)
    {
        int k = del[idx];

        active[k] = true;

        // Floyd Update
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dist[i][j] = min(dist[i][j],
                                 dist[i][k] + dist[k][j]);
            }
        }

        long long sum = 0;

        // Sum only active nodes
        for (int i = 1; i <= n; i++)
        {
            if (!active[i])
                continue;

            for (int j = 1; j <= n; j++)
            {
                if (!active[j])
                    continue;

                sum += dist[i][j];
            }
        }

        ans.push_back(sum);
    }

    reverse(ans.begin(), ans.end());

    for (long long x : ans)
        cout << x << " ";

    cout << "\n";

    return 0;
}