#include <bits/stdc++.h>
using namespace std;

int bfs(int s, int t, vector<vector<int>> &capacity, vector<vector<int>> &adj, vector<int> &parent )
{

    queue<pair<int, int>> q;

    fill(parent.begin(), parent.end(), -1);

    parent[s] = -2;

    q.push({s, INT_MAX});


    while(!q.empty())
    {
        int cur = q.front().first;

        int f = q.front().second;

        q.pop();

        for(int next:adj[cur])
        {
            if(parent[next]==-1 && capacity[cur][next] > 0)
            {

                parent[next] = cur;

                int new_f = min(f,capacity[cur][next]);

                if(next == t)
                {
                    return new_f;

                }
                    
                q.push({next, new_f}) ;
            }
        }
    }

    return 0;
}

int maxflow( int s, int t, vector<vector<int>> &capacity, vector<vector<int>> &adj, vector<int> &parent)
{
    int total_flow = 0;
    int count = 0 ;

    while(1 )
    {
        
        int new_f = bfs(s,t,capacity,adj,parent);
        

        if(new_f== 0)
        {
                break;
        }
        else
        {
            count++ ;
        }
           

        total_flow += new_f;

        int cur = t;

        while(cur != s)
        {
            int prev = parent[cur];

            capacity[prev][cur] -= new_f;

            capacity[cur][prev] += new_f;

            cur = prev;
        }

    }

    return count ; 
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> capacity(n, vector<int>(n, 0));

    vector<vector<int>> adj(n);

    vector<int> parent(n);

    for(int i = 0; i < m; i++)
    {

        int u, v;
        int c ;
        cin >> u >> v;
       

        capacity[u][v]+=1;

        adj[u].push_back(v);

       adj[v].push_back(u);
    }

    int source = 0;

    int target = n - 1;

    cout << maxflow(source,target,capacity,adj,parent);

}