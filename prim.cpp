#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,m;
    cin>>n>>m;

    vector<vector<pair<int,int>>> adj(n+1);

    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;

        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    priority_queue<
    pair<int,int>,
    vector<pair<int,int>>,
    greater<pair<int,int>>> pq;

    vector<bool> visited(n+1,false);

    pq.push({0,1});

    int cost=0;
    int taken=0;

    while(!pq.empty())
    {
        auto cur=pq.top();
        pq.pop();

        int weight=cur.first;
        int node=cur.second;

        if(visited[node])
            continue;

        visited[node]=true;

        cost+=weight;

        taken++;

        for(auto child:adj[node])
        {
            int next=child.first;
            int w=child.second;

            if(!visited[next])
            {
                pq.push({w,next});
            }
        }
    }

    if(taken!=n)
    {
        cout<<"IMPOSSIBLE";
        return 0;
    }

    cout<<cost;
}