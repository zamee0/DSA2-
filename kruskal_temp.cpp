#include<bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int u,v,w;
};

vector<int> parent;

int find(int u)
{
    if(parent[u]==u)
        return u;

    return parent[u]=find(parent[u]);
}

void unite(int u,int v)
{
    u=find(u);
    v=find(v);

    if(u!=v)
        parent[v]=u;
}

int main()
{
    int n,m;
    cin>>n>>m;

    vector<Edge> edges;

    for(int i=0;i<m;i++)
    {
        Edge e;
        cin>>e.u>>e.v>>e.w;
        edges.push_back(e);
    }

    parent.resize(n+1);

    for(int i=1;i<=n;i++)
        parent[i]=i;

    sort(edges.begin(),edges.end(),[](Edge a,Edge b)
    {
        return a.w<b.w;
    });

    int cost=0;
    int taken=0;

    vector<Edge> mst;

    for(auto e:edges)
    {
        if(find(e.u)!=find(e.v))
        {
            cost+=e.w;
            taken++;

            mst.push_back(e);

            unite(e.u,e.v);

            if(taken==n-1)
                break;
        }
    }
}