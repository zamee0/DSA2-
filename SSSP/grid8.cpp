#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

class State
{
public:
    long long d;
    int r, c;

    bool operator>(const State &other) const
    {
        return d > other.d;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];

    vector<vector<long long>> dist(n, vector<long long>(m, INF));

    priority_queue<
        State,
        vector<State>,
        greater<State>
    > pq;

    int dr[8]={-1,-1,-1,0,0,1,1,1};
    int dc[8]={-1,0,1,-1,1,-1,0,1};



    // Source
    dist[0][0] = grid[0][0];
    pq.push({dist[0][0], 0, 0});

    while (!pq.empty())
    {
        State cur = pq.top();
        pq.pop();

        long long d = cur.d;
        int r = cur.r;
        int c = cur.c;

        if (d != dist[r][c])
            continue;

        for (int k = 0; k < 8; k++)
        {
            int nr = r + dr[k];
            int nc = c + dc[k];

            // Outside Grid
            if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                continue;

                
    // if(grid[nr][nc]=='#')   // Wall
    //     continue;
    
            long long nd = d + grid[nr][nc];

            if (nd < dist[nr][nc])
            {
                dist[nr][nc] = nd;
                pq.push({nd, nr, nc});
            }
        }
    }

    cout << dist[n - 1][m - 1] << endl;

    return 0;
}