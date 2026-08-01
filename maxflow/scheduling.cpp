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
    int N, M;

    cin >> N >> M;


    // --------------------------------
    // Job capacities
    // --------------------------------

    vector<int> jobCapacity(M);

    for (int i = 0; i < M; i++)
    {
        cin >> jobCapacity[i];
    }


    int E;
    cin >> E;


    /*
        Node numbering:

        Workers:
        0 ... N-1

        Jobs:
        N ... N+M-1

        Source:
        N + M

        Sink:
        N + M + 1
    */

    int source = N + M;

    int sink = N + M + 1;

    int totalNodes = N + M + 2;


    vector<vector<int>> capacity(
        totalNodes,
        vector<int>(totalNodes, 0)
    );

    vector<vector<int>> adj(totalNodes);

    vector<int> parent(totalNodes);


    // --------------------------------
    // Source → Workers
    // --------------------------------

    for (int worker = 0; worker < N; worker++)
    {
        capacity[source][worker] = 1;

        adj[source].push_back(worker);
        adj[worker].push_back(source);
    }


    // --------------------------------
    // Worker → Job
    // --------------------------------

    for (int i = 0; i < E; i++)
    {
        int worker, job;

        cin >> worker >> job;

        // Convert worker to 0-based
        worker--;

        // Job node starts from N
        int jobNode = N + (job - 1);

        capacity[worker][jobNode] = 1;

        adj[worker].push_back(jobNode);
        adj[jobNode].push_back(worker);
    }


    // --------------------------------
    // Job → Sink
    // --------------------------------

    for (int job = 0; job < M; job++)
    {
        int jobNode = N + job;

        capacity[jobNode][sink] = jobCapacity[job];

        adj[jobNode].push_back(sink);
        adj[sink].push_back(jobNode);
    }


    // --------------------------------
    // Maximum Flow
    // --------------------------------

    int result = maxflow(
        source,
        sink,
        capacity,
        adj,
        parent
    );


    cout << result << endl;

    return 0;
}