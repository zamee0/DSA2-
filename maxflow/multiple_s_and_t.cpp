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
        int new_f = bfs(s, t, capacity, adj, parent);

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

    // Number of sources and sinks
    int S, T;
    cin >> S >> T;


    // ----------------------------------
    // Extra nodes
    // ----------------------------------

    int superSource = n;
    int superSink = n + 1;

    int totalNodes = n + 2;


    vector<vector<int>> capacity(
        totalNodes,
        vector<int>(totalNodes, 0)
    );

    vector<vector<int>> adj(totalNodes);

    vector<int> parent(totalNodes);


    // ----------------------------------
    // Connect Super Source to Sources
    // ----------------------------------

    for (int i = 0; i < S; i++)
    {
        int source;
        cin >> source;

        capacity[superSource][source] = INT_MAX;

        adj[superSource].push_back(source);
        adj[source].push_back(superSource);
    }


    // ----------------------------------
    // Connect Sinks to Super Sink
    // ----------------------------------

    for (int i = 0; i < T; i++)
    {
        int sink;
        cin >> sink;

        capacity[sink][superSink] = INT_MAX;

        adj[sink].push_back(superSink);
        adj[superSink].push_back(sink);
    }


    // ----------------------------------
    // Original edges
    // ----------------------------------

    for (int i = 0; i < m; i++)
    {
        int u, v, c;

        cin >> u >> v >> c;

        capacity[u][v] += c;

        // Forward edge
        adj[u].push_back(v);

        // Reverse edge for residual graph
        adj[v].push_back(u);
    }


    // ----------------------------------
    // Maximum Flow
    // ----------------------------------

    int result = maxflow(
        superSource,
        superSink,
        capacity,
        adj,
        parent
    );


    cout << result << endl;

    return 0;
}