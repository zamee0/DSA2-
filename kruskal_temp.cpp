#include<bits/stdc++.h>
using namespace std;

vector<int> parent;

class Edge
{
public:
    int u,v,w;
};

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

    vector<Edge> e(m);

    for(int i=0;i<m;i++)
    {
        cin>>e[i].u>>e[i].v>>e[i].w;
    }

    parent.resize(n+1);

    for(int i=1;i<=n;i++)
        parent[i]=i;

    sort(e.begin(),e.end(),[](Edge a,Edge b)
    {
        return a.w<b.w;
    });

    int cost=0;

    vector<Edge> mst;

    for(auto ed:e)
    {
        if(find(ed.u)!=find(ed.v))
        {
            mst.push_back(ed);
            unite(ed.u,ed.v);
        }
    }

}