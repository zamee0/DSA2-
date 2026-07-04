#include<bits/stdc++.h>
using namespace std;

class Node
{
public:
    int w;
    int parent;
    int u;

    bool operator>(const Node &other) const
    {
        return w > other.w;
    }
};

class Edge
{
public:
    int u,v,w;
};

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

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    vector<bool> visited(n+1,false);

    vector<Edge> mst;

    pq.push({0,-1,1});      // weight,parent,node

    int cost=0;
    int taken=0;

    while(!pq.empty())
    {
        Node cur=pq.top();
        pq.pop();

        if(visited[cur.u])
            continue;

        visited[cur.u]=true;

        cost+=cur.w;
        taken++;

    
        if(cur.parent!=-1)
        {
            mst.push_back({cur.parent,cur.u,cur.w});
        }

        for(auto child:adj[cur.u])
        {
            int next=child.first;
            int w=child.second;

            if(!visited[next])
            {
                pq.push({w,cur.u,next});
            }
        }
    }

    if(taken!=n)
    {
        cout<<"IMPOSSIBLE";
        return 0;
    }

    cout<<"Minimum Cost = "<<cost<<endl;

    cout<<"MST Edges"<<endl;

    for(auto e:mst)
    {
        cout<<e.u<<" "<<e.v<<" "<<e.w<<endl;
    }

    return 0;
}