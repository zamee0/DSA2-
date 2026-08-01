#include <bits/stdc++.h>
using namespace std;


int bfs(int s, int t,
        vector<vector<int>> &capacity,
        vector<vector<int>> &adj,
        vector<int> &parent)
{
    queue<pair<int, int>> q;

    fill(parent.begin(), parent.end(), -1);

    parent[s] = -2;

    q.push({s, INT_MAX});

    while (!q.empty())
    {
        int cur = q.front().first;
        int f = q.front().second;

        q.pop();

        for (int next : adj[cur])
        {
            if (parent[next] == -1 &&
                capacity[cur][next] > 0)
            {
                parent[next] = cur;

                int new_f = min(f, capacity[cur][next]);

                if (next == t)
                {
                    return new_f;
                }

                q.push({next, new_f});
            }
        }
    }

    return 0;
}


int maxflow(int s, int t,
            vector<vector<int>> &capacity,
            vector<vector<int>> &adj,
            vector<int> &parent)
{
    int total_flow = 0;

    while (true)
    {
        int new_f = bfs(
            s,
            t,
            capacity,
            adj,
            parent
        );

        if (new_f == 0)
        {
            break;
        }

        total_flow += new_f;

        int cur = t;

        while (cur != s)
        {
            int prev = parent[cur];

            capacity[prev][cur] -= new_f;

            capacity[cur][prev] += new_f;

            cur = prev;
        }
    }

    return total_flow;
}


int main()
{
    int n, m;

    cin >> n >> m;

    int s, t;

    cin >> s >> t;


    // ------------------------------------
    // Node Splitting
    // ------------------------------------

    int totalNodes = 2 * n;

    vector<vector<int>> capacity(
        totalNodes,
        vector<int>(totalNodes, 0)
    );

    vector<vector<int>> adj(totalNodes);

    vector<int> parent(totalNodes);


    // ------------------------------------
    // Functions for in-node and out-node
    // ------------------------------------

    auto in = [](int v)
    {
        return 2 * v;
    };

    auto out = [](int v)
    {
        return 2 * v + 1;
    };


    const int INF = 1e9;


    // ------------------------------------
    // Split every vertex
    // ------------------------------------

    for (int v = 0; v < n; v++)
    {
        int nodeCapacity = 1;

        // Source and destination can be
        // shared by multiple paths
        if (v == s || v == t)
        {
            nodeCapacity = INF;
        }

        capacity[in(v)][out(v)] = nodeCapacity;

        adj[in(v)].push_back(out(v));
        adj[out(v)].push_back(in(v));
    }


    // ------------------------------------
    // Original directed edges
    // ------------------------------------

    for (int i = 0; i < m; i++)
    {
        int u, v;

        cin >> u >> v;

        /*
            Original:

                u → v

            After splitting:

                u_out → v_in
        */

        capacity[out(u)][in(v)] += INF;

        adj[out(u)].push_back(in(v));
        adj[in(v)].push_back(out(u));
    }


    // ------------------------------------
    // Source and Target
    // ------------------------------------

    int source = out(s);

    int target = in(t);


    // ------------------------------------
    // Maximum Flow
    // ------------------------------------

    int result = maxflow(
        source,
        target,
        capacity,
        adj,
        parent
    );


    if (result == 0)
    {
        cout << -1;
    }
    else
    {
        cout << result;
    }


    return 0;
}