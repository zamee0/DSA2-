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
    int N, M, E;

    cin >> N >> M >> E;


    /*
        Node numbering:

        Students:
        0 ... N-1

        Projects:
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
    // Source -> Students
    // --------------------------------

    for (int i = 0; i < N; i++)
    {
        capacity[source][i] = 1;

        adj[source].push_back(i);
        adj[i].push_back(source);
    }


    // --------------------------------
    // Student -> Project
    // --------------------------------

    for (int i = 0; i < E; i++)
    {
        int student, project;

        cin >> student >> project;

        // Convert 1-based input to 0-based
        student--;

        // Project nodes start from N
        int projectNode = N + (project - 1);

        capacity[student][projectNode] = 1;

        adj[student].push_back(projectNode);
        adj[projectNode].push_back(student);
    }


    // --------------------------------
    // Project -> Sink
    // --------------------------------

    for (int i = 0; i < M; i++)
    {
        int projectNode = N + i;

        capacity[projectNode][sink] = 1;

        adj[projectNode].push_back(sink);
        adj[sink].push_back(projectNode);
    }


    // --------------------------------
    // Maximum Matching
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